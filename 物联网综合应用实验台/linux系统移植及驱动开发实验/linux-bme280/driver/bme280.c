/*********************************************************************************************
#####         �Ϻ�Ƕ��ʽ��԰-�������̳�         #####
#####                    www.embedclub.com                        #####
#####             http://embedclub.taobao.com               #####

* File��		poll_drv_drv.c
* Author:		Hanson
* Desc��	one drv scan (with polling method) device driver 
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
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/spinlock.h>

/* #define  IOMUXC_SW_MUX_CTL_PAD_GPIO05  (unsigned int*)ioremap(0x20e0230,4)
#define  GPIO1_DR                      (unsigned int*)ioremap(0x209c000,4)
#define  GPIO1_GDIR                    (unsigned int*)ioremap(0x209c004,4) */

unsigned int *IOMUXC_SW_MUX_CTL_PAD_GPIO05;
unsigned int *GPIO1_DR;
unsigned int *GPIO1_GDIR;

#define SDA_GPIO_NBR 23
/* #define SDA_PAD            (unsigned int*)ioremap(0x20e0530,4)
#define SDA_MUX            (unsigned int*)ioremap(0x20e0160,4)
#define SDA_GPIO_GDIR      (unsigned int*)ioremap(0x20a4004,4)
#define SDA_GPIO_DR        (unsigned int*)ioremap(0x20a4000,4) */

unsigned int *SDA_PAD;
unsigned int *SDA_MUX;
unsigned int *SDA_GPIO_GDIR;
unsigned int *SDA_GPIO_DR;

#define SCL_GPIO_NBR 31

/* #define SCL_PAD 		   (unsigned int*)ioremap(0x20e0550,4)
#define SCL_MUX   		   (unsigned int*)ioremap(0x20e0180,4)
#define SCL_GPIO_GDIR      (unsigned int*)ioremap(0x20a4004,4)
#define SCL_GPIO_DR        (unsigned int*)ioremap(0x20a4000,4) */

unsigned int *SCL_PAD;
unsigned int *SCL_MUX;
unsigned int *SCL_GPIO_GDIR;
unsigned int *SCL_GPIO_DR;

#define ATMOS_DEVICE_ADDR (0x76<<1)

static volatile int drv_value;//����ֵ
static int drv_major = 0;     //
static int drv_minor = 0; 

/*
����PINΪGPIOģʽ
*/
void imx6_gpio_mode(unsigned int* padd)
{
	writel(0x05,padd);		
}
/*
����PINΪGPIO ���ģʽ
*/
void imx6_gpio_out(unsigned int *padd,unsigned int pos)
{
	int tempreg;
	tempreg  = readl(padd);
	tempreg |= 1<<pos;
	writel(tempreg,padd);
}
void imx6_gpio_op(unsigned int *padd)
{
	int tempreg;
	tempreg  = readl(padd);
	tempreg |= 1<<11; 
	writel(tempreg,padd);	
}
/*
����PINΪGPIO ����ģʽ
*/
void imx6_gpio_in(unsigned int *padd,unsigned int pos)
{
	int tempreg;
	tempreg  = readl(padd);
	tempreg &= ~(1<<pos);
	writel(tempreg,padd);
}
/*
����PINΪGPIO ��������ģʽ
*/
void imx6_gpio_pupd(unsigned int *padd,unsigned char mode)
{
	int tempreg;
	tempreg  = readl(padd);
/* */	tempreg &= ~(0x3<<14);
	tempreg |= mode<<14;
	printk("tempreg=%d\r\n",tempreg);
	writel(tempreg,padd);
	tempreg  = readl(padd); 
	printk("=%x",tempreg);
}
/*
дGPIO PIN 
*/
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
/*
��GPIO PIN������
*/
int imx6_gpio_read(unsigned int *padd,unsigned int pos)
{
	int tempreg;
	tempreg  = readl(padd);
	return (tempreg &(1<<pos))?1:0;
}
void SDA_OUT(void)
{
	imx6_gpio_op(SDA_PAD);//���óɿ�©		
	imx6_gpio_out(SDA_GPIO_GDIR,SDA_GPIO_NBR);
}
void SDA_IN(void)
{
	imx6_gpio_in(SDA_GPIO_GDIR,SDA_GPIO_NBR);	
}
void SCL_OUT(void)
{
	imx6_gpio_op(SCL_PAD);//���óɿ�©
	imx6_gpio_out(SCL_GPIO_GDIR,SCL_GPIO_NBR);
}
void SCL_IN(void)
{
	imx6_gpio_in(SCL_GPIO_GDIR,SCL_GPIO_NBR);	
}
void IIC_SDA(int val)
{
	imx6_gpio_write(SDA_GPIO_DR,SDA_GPIO_NBR,val?1:0);
}
void IIC_SCL(int val)
{
	imx6_gpio_write(SCL_GPIO_DR,SCL_GPIO_NBR,val?1:0);
}
/*
��ʼ��Io��
*/
void iic_init(void)
{

	IOMUXC_SW_MUX_CTL_PAD_GPIO05 = (unsigned int*)ioremap(0x20e0230,4);
	GPIO1_DR                     = (unsigned int*)ioremap(0x209c000,4);
	GPIO1_GDIR                   = (unsigned int*)ioremap(0x209c004,4);	

	SDA_PAD           = (unsigned int*)ioremap(0x20e0530,4);
	SDA_MUX           = (unsigned int*)ioremap(0x20e0160,4);
	SDA_GPIO_GDIR     = (unsigned int*)ioremap(0x20a4004,4);
	SDA_GPIO_DR       = (unsigned int*)ioremap(0x20a4000,4);

	SCL_PAD 		  =  (unsigned int*)ioremap(0x20e0550,4);
	SCL_MUX   	      =	 (unsigned int*)ioremap(0x20e0180,4);
	SCL_GPIO_GDIR     =  (unsigned int*)ioremap(0x20a4004,4);
	SCL_GPIO_DR       =  (unsigned int*)ioremap(0x20a4000,4);	
	
	imx6_gpio_mode(SDA_MUX);
	imx6_gpio_mode(SCL_MUX);

    imx6_gpio_out(SDA_GPIO_GDIR,SDA_GPIO_NBR);
    imx6_gpio_out(SCL_GPIO_GDIR,SCL_GPIO_NBR);
	imx6_gpio_op(SDA_PAD);//���óɿ�©
	imx6_gpio_op(SCL_PAD);//���óɿ�©

	imx6_gpio_write(SDA_GPIO_DR,SDA_GPIO_NBR,1);///���1	
	imx6_gpio_write(SCL_GPIO_DR,SCL_GPIO_NBR,1);//���1		
}
/*
iic start
*/
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA(1);	
	udelay(30);	
	IIC_SCL(1);
	udelay(50);
 	IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	udelay(50);
	IIC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}

void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL(0);
	udelay(30);	
	IIC_SDA(0);
 	udelay(50);	 
	IIC_SCL(1);//STOP:when CLK is high DATA change form low to high
 	udelay(50);	
	IIC_SDA(1);//����I2C���߽����ź� 						   	
}

unsigned char IIC_Wait_Ack(void)
{
	unsigned char ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA(1);udelay(50);	   
	IIC_SCL(1);udelay(50);	 
	while(imx6_gpio_read(SDA_GPIO_DR,SDA_GPIO_NBR))
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			udelay(5);
			return 1;
		}
	}
	IIC_SCL(0);//ʱ�����0 	   
	return 0;  
} 

void IIC_Ack(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(0);
	udelay(50);
	IIC_SCL(1);
	udelay(50);
	IIC_SCL(0);
}

void IIC_NAck(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(1);
	udelay(50);
	IIC_SCL(1);
	udelay(50);
	IIC_SCL(0);
}

void IIC_Send_Byte(unsigned char txd)
{                        
    unsigned char t;   
	SDA_OUT(); 	    
    IIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ���
	udelay(50);
    for(t=0;t<8;t++){              
        IIC_SDA((txd&0x80)>>7);
        txd<<=1; 	  
		udelay(100);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL(1);
		udelay(100); 
		IIC_SCL(0);	
		udelay(100);
    }	 
} 

unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ ){
        IIC_SCL(0); 
        udelay(50);
		IIC_SCL(1);
		udelay(10);
        receive<<=1;
        if(imx6_gpio_read(SDA_GPIO_DR,SDA_GPIO_NBR)){
            receive++;
        }            
		udelay(50); 
    }					 
    if (!ack){
        IIC_NAck();//����nACK
    }
    else{
        IIC_Ack(); //����ACK   
    }
    return receive;
}

void AT24CXX_WriteSingleBytes(unsigned char DevAddr,unsigned char MemAddr,unsigned char *pDst)
{				    	    																 
    IIC_Start(); 
    IIC_Send_Byte(DevAddr|0);   //����������ַ0XA0,д���� 	   
    if(!IIC_Wait_Ack()){
        IIC_Send_Byte(MemAddr);	   
        if(!IIC_Wait_Ack()){
            IIC_Send_Byte(*pDst);
            IIC_Wait_Ack();
        }             
    }          
    IIC_Stop();//����һ��ֹͣ����	       
}

void AT24CXX_ReadNumBytes(unsigned char DevAddr,unsigned char MemAddr,unsigned char *pDst,unsigned char len)
{				  		  	    																 
    IIC_Start(); 
    IIC_Send_Byte(DevAddr|0);   //����������ַ0XA0,д���� 	   
    if(!IIC_Wait_Ack()){
        IIC_Send_Byte(MemAddr);
        IIC_Wait_Ack();        
        IIC_Start(); 
        IIC_Send_Byte(DevAddr|1);           //�������ģʽ			   
        if(!IIC_Wait_Ack()){            
            while(len){
                *pDst = IIC_Read_Byte((len>1)?1:0);
                pDst++;
                len--;
            }
        }            
    }       
    IIC_Stop();//����һ��ֹͣ����	       
}

void iic_write(unsigned char wrdata)
{
	
}
void iic_read(unsigned char rddate)
{
	
}
/*************************************************/

/* Ӧ�ó�����豸�ļ�/dev/drvִ��open(...)ʱ��
 * �ͻ����drv_open����
 */
static int drv_open(struct inode *inode, struct file *file)
{	
	return 0;
}

/* Ӧ�ó�����豸�ļ�/dev/drvִ��close(...)ʱ��
 * �ͻ����drv_close����
 */
static int drv_close(struct inode *inode, struct file *file)
{
    return 0;
}
#define DRV_MAGIC 'k'
#define IOCTRL_CMD_READ_ADD _IOW(DRV_MAGIC, 1, int)
#define IOCTRL_CMD_READ_LEN _IOW(DRV_MAGIC, 3, int)
int sel_cmd;
unsigned char read_add,read_len;
static long cmd_ioctl( struct file *file, 
					unsigned int cmd, 
					unsigned long arg)
{
	unsigned int data;

    if (__get_user(data, (unsigned int __user *)arg))
        return -EFAULT;
		
		
	switch(cmd){
		case IOCTRL_CMD_READ_ADD:
			read_add = data;
			//printk("add=%02x\r\n",data);
			break;
		case IOCTRL_CMD_READ_LEN:
			read_len = data;
			//printk("len=%02x\r\n",data);
			break;
	}
	//printk("cmd=%d\r\n",sel_cmd);
	return 0;
}
static int drv_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp)
{
    unsigned long err;
	unsigned char write_add,write_arg,buffer[2]={0,0};
	err = copy_from_user(buffer,buff,count);
	write_add = buffer[0];
	write_arg = buffer[1];
	//printk("add=%d,arg=%d\r\n",write_add,write_arg);
	AT24CXX_WriteSingleBytes(ATMOS_DEVICE_ADDR,write_add,&write_arg);
    return err ? -EFAULT : 1;//err = 0;��ʾ�ɹ�	
}

/* Ӧ�ó�����豸�ļ�/dev/drvִ��read(...)ʱ�����������
 * �ͻ����drv_read����
 */
unsigned char atmos_data_buffer[32];
static int drv_read(struct file *filp, char __user *buff, 
                    size_t count, loff_t *offp)
{
    unsigned long err;

	AT24CXX_ReadNumBytes(ATMOS_DEVICE_ADDR,read_add,&atmos_data_buffer[0],read_len);
	//printk("read=%d,%d\r\n",atmos_data_buffer[0],atmos_data_buffer[1]);
    err = copy_to_user(buff, (const void *)&atmos_data_buffer[0], read_len);	
    return err ? -EFAULT : 1;
}
/**************************************************
* ���û��������select����ʱ��������������
* ����а������ݣ���select���������̷���
* ���û�а������ݣ�������ʹ��poll_wait�ȴ�
**************************************************/
static unsigned int drv_poll(struct file *file,
        			 struct poll_table_struct *wait)
{
	unsigned int mask = 0;
    	return mask;
}


/* ����ṹ���ַ��豸��������ĺ���
 * ��Ӧ�ó�������豸�ļ�ʱ�����õ�open��read��write�Ⱥ�����
 * ���ջ��������ṹ�еĶ�Ӧ����
 */
static struct file_operations drv_fops = {
    .owner   =   THIS_MODULE,    /* ����һ���ָ꣬�����ģ��ʱ�Զ�������__this_module���� */
    .open    =   drv_open,
    .release =   drv_close, 
    .read    =   drv_read,
	.write   =   drv_write,
    .poll    =   drv_poll,
	.unlocked_ioctl   =   cmd_ioctl,
};
/*
 * We export one drv device.  There's no need for us to maintain any
 * special housekeeping info, so we just deal with raw cdev.
 */
static struct cdev drv_cdev;

/*
 * ִ�С�insmod drv_drv.ko������ʱ�ͻ�����������
 */
#define SPI_BASE_REG_ADDR    0x020A4000

static int __init drv_init(void)
{
	int result;
	dev_t devno;
	 
	/* Figure out our device number. */
	result    = alloc_chrdev_region(&devno, 0, 1, "atmos");
	drv_major = MAJOR(devno);
	drv_minor = MINOR(devno);
	printk("atmos device installed, with major %d minor %d\r\n", drv_major,drv_minor);	
	if (devno < 0) {
		printk(KERN_WARNING "atmos: unable to get major %d\n", drv_major);
		return result;
	}
																									 
	/* Now set up cdev. */

	cdev_init(&drv_cdev, &drv_fops);
	drv_cdev.owner = THIS_MODULE;
	drv_cdev.ops   = &drv_fops;
	
	/* Fail gracefully if need be */
	if (cdev_add (&drv_cdev, devno, 1)){
		printk (KERN_NOTICE "Error add\r\n");
	}
	iic_init();
    return 0;
}
/*
 * ִ�Сrrmmod drv_drv.ko������ʱ�ͻ����������� 
 */
static void __exit drv_cleanup(void)
{
	cdev_del(&drv_cdev);
	unregister_chrdev_region(MKDEV(drv_major, 0), 1);
	//del_timer_sync(&drv_timer);
	printk("SHT20 device uninstalled\n");
}

/* ������ָ����������ĳ�ʼ��������ж�غ��� */
module_init(drv_init);
module_exit(drv_cleanup);

/* �������������һЩ��Ϣ�����Ǳ���� */
MODULE_AUTHOR("Hanson he");             // �������������
MODULE_DESCRIPTION("SHT20 Device Driver");   // һЩ������Ϣ
MODULE_LICENSE("GPL");                              // ��ѭ��Э��

