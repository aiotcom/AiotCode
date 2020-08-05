/*********************************************************************************************
#####         �Ϻ�Ƕ��ʽ��԰-�������̳�         #####
#####                    www.embedclub.com                        #####
#####             http://embedclub.taobao.com               #####

* File��		poll_key_drv.c
* Author:		Hanson
* Desc��	one key scan (with polling method) device driver 
* History:	May 16th 2011
*********************************************************************************************/

#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <asm/irq.h>
#include <asm-generic/io.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <asm-generic/poll.h>
#include <linux/poll.h>
#include <../arch/arm/mach-imx/iomux-v3.h>
#include <../arch/arm/mach-imx/hardware.h>
#include <../arch/arm/mach-imx/mx6.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/gpio_keys.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/spinlock.h>

static unsigned int *GPIO1_DR_ADDR;

#define  IOMUXC_SW_MUX_CTL_PAD_GPIO05  (unsigned int*)ioremap(0x020e0230,4)
#define  GPIO1_DR                      (unsigned int*)ioremap(0x0209c000,4)
#define  GPIO1_GDIR                    (unsigned int*)ioremap(0x0209c004,4)


#define READ_KEY_INPUT()   ((readl(GPIO1_DR_ADDR)&(1<<5))?1:0) 
//add your code
#define MAX_KEYS    1

static volatile int key_value;//����ֵ
static int key_major = 0;     //
static int key_minor = 0; 
/* �ȴ�����: 
 * ��û�а���������ʱ������н��̵���key_read������
 * ��������
 */
static DECLARE_WAIT_QUEUE_HEAD(key_waitq);

/*�ں˶�ʱ��*/
static struct timer_list key_timer;

#define KEY_TIMER_DELAY    HZ/50   /*20ms*/

/* �¼���־, �м�����ʱ������1��key_read������0 */
static volatile int ev_press = 0;


static void key_timer_handle(unsigned long data)
{
	static unsigned char pressed_state = 0,pre_io_value = 0,io_value = 0;
	
	io_value = READ_KEY_INPUT();
	if((io_value==pre_io_value) && (io_value) && (pressed_state == 0))
	{
		pressed_state = 1;
		ev_press = 1; 
		key_value = 1;
		wake_up_interruptible(&key_waitq); 
	}
	else if((!io_value) && (pressed_state == 1))
	{
		pressed_state = 0;		
	}	
	pre_io_value = io_value;
	key_timer.expires = jiffies + KEY_TIMER_DELAY;
	add_timer(&key_timer);

}


/* Ӧ�ó�����豸�ļ�/dev/keyִ��open(...)ʱ��
 * �ͻ����key_open����
 */
static int key_open(struct inode *inode, struct file *file)
{	
	return 0;
}

/* Ӧ�ó�����豸�ļ�/dev/keyִ��close(...)ʱ��
 * �ͻ����key_close����
 */
static int key_close(struct inode *inode, struct file *file)
{
    return 0;
}

/* Ӧ�ó�����豸�ļ�/dev/keyִ��read(...)ʱ�����������
 * �ͻ����key_read����
 */
static int key_read(struct file *filp, char __user *buff, 
                        size_t count, loff_t *offp)
{
    unsigned long err;
	
	if (!ev_press) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		else
			/* ���ev_press����0������ */
			wait_event_interruptible(key_waitq, ev_press);
	}
    /* ִ�е�����ʱ��ev_press����1��������0 */
    ev_press = 0;
    /* ������״̬���Ƹ��û�������0 */
    err = copy_to_user(buff, (const void *)&key_value, 4);
    memset((void *)&key_value, 0, sizeof(key_value));
    return err ? -EFAULT : 1;
}

/**************************************************
* ���û��������select����ʱ��������������
* ����а������ݣ���select���������̷���
* ���û�а������ݣ�������ʹ��poll_wait�ȴ�
**************************************************/
static unsigned int key_poll(struct file *file,
        			 struct poll_table_struct *wait)
{
	unsigned int mask = 0;
    	poll_wait(file, &key_waitq, wait);
    	if (ev_press)
        	mask |= POLLIN | POLLRDNORM;
    	return mask;
}


/* ����ṹ���ַ��豸��������ĺ���
 * ��Ӧ�ó�������豸�ļ�ʱ�����õ�open��read��write�Ⱥ�����
 * ���ջ��������ṹ�еĶ�Ӧ����
 */
static struct file_operations key_fops = {
    .owner   =   THIS_MODULE,    /* ����һ���ָ꣬�����ģ��ʱ�Զ�������__this_module���� */
    .open    =   key_open,
    .release =   key_close, 
    .read    =   key_read,
    .poll    =   key_poll,
};
/*
 * We export one key device.  There's no need for us to maintain any
 * special housekeeping info, so we just deal with raw cdev.
 */
static struct cdev key_cdev;


/*
 * ִ�С�insmod key_drv.ko������ʱ�ͻ�����������
 */
#define SPI_BASE_REG_ADDR    0x020A4000

static int __init button_init(void)
{
	int result;
	dev_t devno;
	 
	/* Figure out our device number. */
	result    = alloc_chrdev_region(&devno, 0, 1, "one_key");
	key_major = MAJOR(devno);
	key_minor = MINOR(devno);
	printk("key device installed, with major %d minor %d\r\n", key_major,key_minor);	
	if (devno < 0) {
			printk(KERN_WARNING "key: unable to get major %d\n", key_major);
			return result;
	}
																									 
	/* Now set up cdev. */

	cdev_init(&key_cdev, &key_fops);
	key_cdev.owner = THIS_MODULE;
	key_cdev.ops   = &key_fops;
	
	/* Fail gracefully if need be */
	if (cdev_add (&key_cdev, devno, 1))
			printk (KERN_NOTICE "Error add\r\n");

	/*init kernel timer*/
	init_timer(&key_timer);
	key_timer.function = &key_timer_handle;
	key_timer.data     = (unsigned long)key_value;//�������
	key_timer.expires  = jiffies + KEY_TIMER_DELAY;
	
	writel(0x05,IOMUXC_SW_MUX_CTL_PAD_GPIO05);//����IO�� ΪGPIO1_IO05	
	 //����
	result = readl(GPIO1_GDIR);
	//printk("result=0x%x\r\n",result);
	
	//�޸ĺ�д��	
	result &= ~(1<<5);
	//printk("write=0x%x\r\n",result);	
	writel(result,GPIO1_GDIR); //IO�� ΪGPIO1_IO05 Ϊ����ģʽ
	
	GPIO1_DR_ADDR = GPIO1_DR;
	add_timer(&key_timer);
    return 0;
}

/*
 * ִ�Сrrmmod key_drv.ko������ʱ�ͻ����������� 
 */
static void __exit button_cleanup(void)
{
	cdev_del(&key_cdev);
	unregister_chrdev_region(MKDEV(key_major, 0), 1);
	del_timer_sync(&key_timer);
	printk("key device uninstalled\n");
}

/* ������ָ����������ĳ�ʼ��������ж�غ��� */
module_init(button_init);
module_exit(button_cleanup);

/* �������������һЩ��Ϣ�����Ǳ���� */
MODULE_AUTHOR("Hanson he");             // �������������
MODULE_DESCRIPTION("S3C2440 KEY Driver");   // һЩ������Ϣ
MODULE_LICENSE("GPL");                              // ��ѭ��Э��

