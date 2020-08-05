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
#include <asm/ioctl.h>
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

#define LED_MAGIC 'k'
#define IOCTL_LED_ON _IOW(LED_MAGIC, 1, int)

#define  IOMUXC_SW_MUX_CTL_PAD_GPIO04  ioremap(0x020e022c,4)
#define  GPIO1_DR                      ioremap(0x0209c000,4)
#define  GPIO1_GDIR                    ioremap(0x0209c004,4)

unsigned int tempreg;
#define  LED_ON()         {tempreg = readl(GPIO1_DR);tempreg &= ~(1<<4);writel(tempreg,GPIO1_DR);}	
#define  LED_OFF()          {tempreg = readl(GPIO1_DR);tempreg |= (1<<4);writel(tempreg,GPIO1_DR);}	
static int led_major = 0;
static int led_minor = 0;
static struct cdev led_cdev;
//add your code
#define MAX_KEYS    1

/* �ȴ�����: 
 * ��û�а���������ʱ������н��̵���key_read������
 * ��������
 */
static DECLARE_WAIT_QUEUE_HEAD(key_waitq);

#define KEY_TIMER_DELAY    HZ/50   /*20ms*/

/* �¼���־, �м�����ʱ������1��key_read������0 */
static volatile int ev_press = 0;

/* Ӧ�ó�����豸�ļ�/dev/keyִ��open(...)ʱ��
 * �ͻ����led_open����
 */
static int led_open(struct inode *inode, struct file *file)
{	
	printk("led_open\r\n");
	return 0;
}
/* Ӧ�ó�����豸�ļ�/dev/keyִ��close(...)ʱ��
 * �ͻ����led_close����
 */
static int led_close(struct inode *inode, struct file *file)
{
    return 0;
}
/* Ӧ�ó�����豸�ļ�/dev/ledsִ��ioctl(...)ʱ��
 * �ͻ����s3c24xx_leds_ioctl����
 */
static long led_ioctl( struct file *file, 
					unsigned int cmd, 
					unsigned long arg)
{
	unsigned int data;

    if (__get_user(data, (unsigned int __user *)arg))
        return -EFAULT;
		
	switch(cmd){
		case IOCTL_LED_ON:
			if(data){		
				LED_ON();					
			}
			else{	
				LED_OFF();					
			}
		break;
	}
	
	return 0;
}
/* ����ṹ���ַ��豸��������ĺ���
 * ��Ӧ�ó�������豸�ļ�ʱ�����õ�open��read��write�Ⱥ�����
 * ���ջ��������ṹ�еĶ�Ӧ����
 */
static struct file_operations led_fops = {
    .owner   =   THIS_MODULE,    /* ����һ���ָ꣬�����ģ��ʱ�Զ�������__this_module���� */
    .open    =   led_open,
    .release =   led_close, 
	.unlocked_ioctl   =   led_ioctl,
};

/*
 * ����һ��cdev�ṹ��
 */
static void led_setup_cdev(struct cdev *dev, int minor,
                struct file_operations *fops)
{
        int err, devno = MKDEV(led_major, minor);

        cdev_init(dev, fops);
        dev->owner = THIS_MODULE;
        dev->ops = fops;
        err = cdev_add (dev, devno, 1);
        /* Fail gracefully if need be */
        if (err)
                printk (KERN_NOTICE "Error %d adding key%d", err, minor);
}
/*
 * ִ�С�insmod key_drv.ko������ʱ�ͻ�����������
 */
static int __init led_init(void)
{
	int result;
	dev_t devno ;
	 
	/* Figure out our device number. */
	result = alloc_chrdev_region(&devno, 0, 1, "one_led");
	led_major = MAJOR(devno);
	led_minor = MINOR(devno);
	//devno = MKDEV(led_major, led_minor);
	printk("led device installed, with major %d minor %d\r\n", led_major,led_minor);	
	if (result < 0) {
		printk(KERN_WARNING "led: unable to get major %d\n", led_major);
		return result;
	}
	if (led_major == 0){
		led_major = result;
	}																								 
	/* Now set up cdev. */
	//led_setup_cdev(&led_cdev, 0, &led_fops);
	cdev_init(&led_cdev, &led_fops);
	led_cdev.owner = THIS_MODULE;
	led_cdev.ops   = &led_fops;
	
	/* Fail gracefully if need be */
	if (cdev_add (&led_cdev, devno, 1))
		printk (KERN_NOTICE "Error add\r\n");
	
	writel(0x05,IOMUXC_SW_MUX_CTL_PAD_GPIO04);//����ΪGPIOģʽ

	 //����
	result = readl(GPIO1_GDIR);	
	result |= (1<<4);//���ó����
	writel(result,GPIO1_GDIR);//�ٴ�д�룬���ø�IOΪ���ģʽ

	LED_OFF();	//�ر�LED��
    return 0;
}

/*
 * ִ�Сrrmmod one_led������ʱ�ͻ����������� 
 */
static void __exit led_cleanup(void)
{
	cdev_del(&led_cdev);
	unregister_chrdev_region(MKDEV(led_major, 0), 1);
	printk("one led device uninstalled\n");
}

/* ������ָ����������ĳ�ʼ��������ж�غ��� */
module_init(led_init);
module_exit(led_cleanup);

/* �������������һЩ��Ϣ�����Ǳ���� */
MODULE_AUTHOR("bacheng");             // �������������
MODULE_DESCRIPTION("one led Driver");   // һЩ������Ϣ
MODULE_LICENSE("GPL");                              // ��ѭ��Э��

