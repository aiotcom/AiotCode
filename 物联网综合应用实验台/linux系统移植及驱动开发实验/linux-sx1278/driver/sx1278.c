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

#define PA2_GPIO_NBR                  26
unsigned int *PA2_MUX;
unsigned int *PA2_GPIO_GDIR;
unsigned int *PA2_GPIO_DR;
unsigned int *PA2_PAD;
#define PA3_GPIO_NBR                  27
unsigned int *PA3_MUX;
unsigned int *PA3_GPIO_GDIR;
unsigned int *PA3_GPIO_DR;

#define MOSI_GPIO_NBR                  23
unsigned int *MOSI_MUX;
unsigned int *MOSI_GPIO_GDIR;
unsigned int *MOSI_GPIO_DR;

#define MISO_GPIO_NBR                  24
unsigned int *MISO_MUX;
unsigned int *MISO_GPIO_GDIR;
unsigned int *MISO_GPIO_DR;
unsigned int *MISO_PAD_CTRL;

#define SCK_GPIO_NBR                  27
/* 
#define SCK_MUX                       (unsigned int*)ioremap(0x20e01D4,4)
#define SCK_GPIO_GDIR                 (unsigned int*)ioremap(0x20a0004,4)
#define SCK_GPIO_DR                   (unsigned int*)ioremap(0x20a0000,4) 
*/
unsigned int *SCK_MUX;
unsigned int *SCK_GPIO_GDIR;
unsigned int *SCK_GPIO_DR; 

#define CS_GPIO_NBR                  6
/*
#define CS_MUX                       (unsigned int*)ioremap(0x20e0234,4)
#define CS_GPIO_GDIR                 (unsigned int*)ioremap(0x209C004,4)
#define CS_GPIO_DR                   (unsigned int*)ioremap(0x209C000,4)
*/
unsigned int *CS_MUX;
unsigned int *CS_GPIO_GDIR;
unsigned int *CS_GPIO_DR;

#define RST_GPIO_NBR                  12
/*
#define RST_MUX                       (unsigned int*)ioremap(0x20e0250,4)
#define RST_GPIO_GDIR                 (unsigned int*)ioremap(0x20a8004,4)
#define RST_GPIO_DR                   (unsigned int*)ioremap(0x20a8000,4)
*/
unsigned int *RST_MUX;
unsigned int *RST_GPIO_GDIR;
unsigned int *RST_GPIO_DR;

#define SX1278_MAGIC 'k'
#define IOCTRL_CMD_CS _IOW(SX1278_MAGIC, 1, int)
#define IOCTRL_CMD_RST _IOW(SX1278_MAGIC, 2, int)
#define IOCTRL_CMD_READ_KEY _IOW(SX1278_MAGIC, 3, int)
#define IOCTRL_CMD_WRITE_LED _IOW(SX1278_MAGIC, 4, int)
void imx6_gpio_mode(unsigned int* padd)
{
	writel(0x05,padd);		
}
void imx6_gpio_out(unsigned int *padd,unsigned int pos)
{
	int tempreg;
	tempreg  = readl(padd);
	tempreg |= 1<<pos;
	writel(tempreg,padd);
}
void imx6_gpio_in(unsigned int *padd,unsigned int pos)
{
	int tempreg;
	tempreg  = readl(padd);
	tempreg &= ~(1<<pos);
	writel(tempreg,padd);
}
#define PU_47K_OHM 0x01
#define PU_100K_OHM 0x2
#define PU_22K_OHM 0x3
void imx6_gpio_pupd(unsigned int *padd,uint8_t mode)
{
	int tempreg;
	tempreg  = readl(padd);
	tempreg &= ~(0x3<<14);
	tempreg |= mode<<14;
	writel(tempreg,padd);
	tempreg  = readl(padd); 
}
void imx6_gpio_write(unsigned int *padd,unsigned int pos,unsigned int val)
{
	int tempreg;
	tempreg  = readl(padd);
	tempreg &= ~(1<<pos);
	if(val){
		tempreg |= 1<<pos;
	}
	writel(tempreg,padd);	
}
int imx6_gpio_read(unsigned int *padd,unsigned int pos)
{
	int tempreg;
	tempreg  = readl(padd);
	return (tempreg &(1<<pos))?1:0;
}
static void spi_init(void)
{
	MOSI_MUX        =   (unsigned int*)ioremap(0x20e013c,4);
	MOSI_GPIO_GDIR  =   (unsigned int*)ioremap(0x20a0004,4);
	MOSI_GPIO_DR    =   (unsigned int*)ioremap(0x20a0000,4);
	
	MISO_MUX        =   (unsigned int*)ioremap(0x20e0140,4);
	MISO_GPIO_GDIR  =   (unsigned int*)ioremap(0x20a0004,4);
	MISO_GPIO_DR    =   (unsigned int*)ioremap(0x20a0000,4);
	MISO_PAD_CTRL   =   (unsigned int*)ioremap(0x20e0510,4);

	SCK_MUX         =   (unsigned int*)ioremap(0x20e01D4,4);
	SCK_GPIO_GDIR   =   (unsigned int*)ioremap(0x20a0004,4);
	SCK_GPIO_DR     =   (unsigned int*)ioremap(0x20a0000,4); 

	CS_MUX          =   (unsigned int*)ioremap(0x20e0234,4);
	CS_GPIO_GDIR    =   (unsigned int*)ioremap(0x209C004,4);
	CS_GPIO_DR      =   (unsigned int*)ioremap(0x209C000,4);

	RST_MUX         = 	(unsigned int*)ioremap(0x20e0250,4);
	RST_GPIO_GDIR   = 	(unsigned int*)ioremap(0x20a8004,4);
	RST_GPIO_DR     = 	(unsigned int*)ioremap(0x20a8000,4);
	imx6_gpio_mode(MISO_MUX);
	imx6_gpio_mode(MOSI_MUX);
	imx6_gpio_mode(SCK_MUX);
	imx6_gpio_mode(CS_MUX);
	imx6_gpio_mode(RST_MUX);	
	
	imx6_gpio_in(MISO_GPIO_GDIR,MISO_GPIO_NBR);//MISO
	//imx6_gpio_out(MISO_GPIO_GDIR,MISO_GPIO_NBR);//MISO
	//imx6_gpio_pupd(MISO_PAD_CTRL,0xB0B1);
	writel(0xB0B1,MISO_PAD_CTRL);
	imx6_gpio_out(MOSI_GPIO_GDIR,MOSI_GPIO_NBR);//MOSI
	imx6_gpio_out(SCK_GPIO_GDIR,SCK_GPIO_NBR);//SCK
	imx6_gpio_out(RST_GPIO_GDIR,RST_GPIO_NBR);//RST
	imx6_gpio_out(CS_GPIO_GDIR,CS_GPIO_NBR);//CS	

	imx6_gpio_write(MOSI_GPIO_DR,MOSI_GPIO_NBR,1);
	imx6_gpio_write(CS_GPIO_DR,CS_GPIO_NBR,1);
	imx6_gpio_write(SCK_GPIO_DR,SCK_GPIO_NBR,0);
	imx6_gpio_write(RST_GPIO_DR,RST_GPIO_NBR,1);	

//������LED�Ƶĳ�ʼ��	
	PA2_MUX          =  (unsigned int*)ioremap(0x20e016c,4);
	PA2_GPIO_GDIR    =  (unsigned int*)ioremap(0x20A4004,4);
	PA2_GPIO_DR      =  (unsigned int*)ioremap(0x20A4000,4);
	PA2_PAD          =  (unsigned int*)ioremap(0x20E053C,4);
	
	PA3_MUX          = 	(unsigned int*)ioremap(0x20e0170,4);
	PA3_GPIO_GDIR    = 	(unsigned int*)ioremap(0x20A4004,4);
	PA3_GPIO_DR      = 	(unsigned int*)ioremap(0x20A4000,4);

	imx6_gpio_mode(PA2_MUX);
	imx6_gpio_mode(PA3_MUX);	
	
	imx6_gpio_in(PA2_GPIO_GDIR,PA2_GPIO_NBR);
	imx6_gpio_pupd(PA2_PAD,PU_22K_OHM);
	imx6_gpio_out(PA3_GPIO_GDIR,PA3_GPIO_NBR);
	
	imx6_gpio_write(PA2_GPIO_DR,PA2_GPIO_NBR,1);
	imx6_gpio_write(PA3_GPIO_DR,PA3_GPIO_NBR,1);	
}
/*************************************************/
static volatile int key_value;//����ֵ
static int key_major = 0;     //
static int key_minor = 0; 
/* �ȴ�����: 
 * ��û�а���������ʱ������н��̵���key_read������
 * ��������
 */
static DECLARE_WAIT_QUEUE_HEAD(key_waitq);



#define KEY_TIMER_DELAY    HZ/50   /*20ms*/

/* �¼���־, �м�����ʱ������1��key_read������0 */
static volatile int ev_press = 0;

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
int read_key = 0,write_led = 0;
static long cmd_ioctl( struct file *file, 
					unsigned int cmd, 
					unsigned long arg)
{
	unsigned int data;

    if (__get_user(data, (unsigned int __user *)arg)){
        return -EFAULT;
	}
				
	switch(cmd)
	{
		case IOCTRL_CMD_CS:
			imx6_gpio_write(CS_GPIO_DR,CS_GPIO_NBR,data?1:0);
			//printk("cs=%d\r\n",data);
			break;
		case IOCTRL_CMD_RST:
			imx6_gpio_write(RST_GPIO_DR,RST_GPIO_NBR,data?1:0);
			//printk("rst=%d\r\n",data);
			break;
		case IOCTRL_CMD_READ_KEY:
			read_key = 1;
			break;	
		case IOCTRL_CMD_WRITE_LED:
			write_led = 1;
			break;				
	}
	return 0;
}
unsigned char SPI_RW(unsigned char byte)
{
	unsigned char SPI_TxData,k;
	unsigned char RetData=0;
	SPI_TxData = byte;
	for(k=0;k<8;k++){
		if(SPI_TxData&0x80){
			imx6_gpio_write(MOSI_GPIO_DR,MOSI_GPIO_NBR,1);//NRF_MOSI_SET();
		}	   
		else{
			imx6_gpio_write(MOSI_GPIO_DR,MOSI_GPIO_NBR,0);//NRF_MOSI_CLR();
		}
		udelay(100); 				 
		imx6_gpio_write(SCK_GPIO_DR,SCK_GPIO_NBR,1);//NRF_SCK_SET();	   //clk=1
		udelay(100);
		RetData = RetData <<1;	
		if(imx6_gpio_read(MISO_GPIO_DR,MISO_GPIO_NBR)){
			RetData=RetData+0x01;
		}
		imx6_gpio_write(SCK_GPIO_DR,SCK_GPIO_NBR,0);//NRF_SCK_CLR(); 	   //clk=0
		SPI_TxData = SPI_TxData <<1;
	}
	return(RetData);           		  // return read byte
}
/* Ӧ�ó�����豸�ļ�/dev/keyִ��read(...)ʱ�����������
 * �ͻ����key_read����
 */
static int key_read(struct file *filp, char __user *buff,size_t count, loff_t *offp)
{
    unsigned long err;
	unsigned char byte;
	if(read_key == 0){
		byte = SPI_RW(0xff);
	}
	else{
		byte = imx6_gpio_read(PA2_GPIO_DR,PA2_GPIO_NBR);
	}
	read_key = 0;
	err = copy_to_user(buff, (const void *)&byte, 1);
    return err ? -EFAULT : 1;
}
static int key_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp)
{
    unsigned long err;
	unsigned char byte;
	//printk("write\r\n");
	err = copy_from_user(&byte,buff,1);
	//printk("write:byte=%d\r\n",byte);
	if(write_led == 0){
		SPI_RW(byte);
	}
	else{
		imx6_gpio_write(PA3_GPIO_DR,PA3_GPIO_NBR,byte);	
	}
	write_led = 0;
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
	.write   =   key_write,
    .poll    =   key_poll,
	.unlocked_ioctl   =   cmd_ioctl,
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
	result    = alloc_chrdev_region(&devno, 0, 1, "sx1278");
	key_major = MAJOR(devno);
	key_minor = MINOR(devno);
	printk("device installed, with major %d minor %d\r\n", key_major,key_minor);	
	if (devno < 0) {
		printk(KERN_WARNING "unable to get major %d\n", key_major);
		return result;
	}
																									 
	/* Now set up cdev. */

	cdev_init(&key_cdev, &key_fops);
	key_cdev.owner = THIS_MODULE;
	key_cdev.ops   = &key_fops;
	
	/* Fail gracefully if need be */
	if (cdev_add (&key_cdev, devno, 1)){
		printk (KERN_NOTICE "Error add\r\n");
	}
	/*init kernel timer
	init_timer(&key_timer);
	key_timer.function = &key_timer_handle;
	key_timer.data     = (unsigned long)key_value;//�������
	key_timer.expires  = jiffies + KEY_TIMER_DELAY;
	*/
	spi_init();
    return 0;
}
/*
 * ִ�Сrrmmod key_drv.ko������ʱ�ͻ����������� 
 */
static void __exit button_cleanup(void)
{
	cdev_del(&key_cdev);
	unregister_chrdev_region(MKDEV(key_major, 0), 1);
	//del_timer_sync(&key_timer);
	printk("SHT20 device uninstalled\n");
}

/* ������ָ����������ĳ�ʼ��������ж�غ��� */
module_init(button_init);
module_exit(button_cleanup);

/* �������������һЩ��Ϣ�����Ǳ���� */
MODULE_AUTHOR("Hanson he");             // �������������
MODULE_DESCRIPTION("SHT20 Device Driver");   // һЩ������Ϣ
MODULE_LICENSE("GPL");                              // ��ѭ��Э��

