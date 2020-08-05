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
#define CHB_MAGIC 'k'
#define IOCTRL_CMD_P3A _IOW(CHB_MAGIC, 1, int)
#define IOCTRL_CMD_P4A _IOW(CHB_MAGIC, 2, int)
#define IOCTRL_CMD_P5A _IOW(CHB_MAGIC, 3, int)
#define IOCTRL_CMD_P6  _IOW(CHB_MAGIC, 4, int)
#define IOCTRL_CMD_DISP_P3A _IOW(CHB_MAGIC, 5, int)
#define IOCTRL_CMD_DISP_P4A _IOW(CHB_MAGIC, 6, int)
#define IOCTRL_CMD_DISP_P5A _IOW(CHB_MAGIC, 7, int)
#define IOCTRL_CMD_DISP_P6  _IOW(CHB_MAGIC, 8, int)
static struct _gpio_table{
	unsigned int *t_gpioadd;
	unsigned int t_gpionbr;	
	unsigned int *r_gpioadd;	
	unsigned int r_gpionbr;
}gpio_table[4];

#define PA2_SCL_GPIO_NBR                  26
unsigned int *PA2_SCL_MUX;
unsigned int *PA2_SCL_GPIO_GDIR;
unsigned int *PA2_SCL_GPIO_DR;

#define PA3_DIN_GPIO_NBR                  27
unsigned int *PA3_DIN_MUX;
unsigned int *PA3_DIN_GPIO_GDIR;
unsigned int *PA3_DIN_GPIO_DR;

#define PA1_R4_GPIO_NBR                  6
unsigned int *PA1_R4_MUX;
unsigned int *PA1_R4_GPIO_GDIR;
unsigned int *PA1_R4_GPIO_DR;

#define PA0_T4_GPIO_NBR                  12
unsigned int *PA0_T4_MUX;
unsigned int *PA0_T4_GPIO_GDIR;
unsigned int *PA0_T4_GPIO_DR;

#define PA7_T1_GPIO_NBR                  23
unsigned int *PA7_T1_MUX;
unsigned int *PA7_T1_GPIO_GDIR;
unsigned int *PA7_T1_GPIO_DR;

#define PA6_R1_GPIO_NBR                  24
unsigned int *PA6_R1_MUX;
unsigned int *PA6_R1_GPIO_GDIR;
unsigned int *PA6_R1_GPIO_DR;

#define PA5_T2_GPIO_NBR                  27
unsigned int *PA5_T2_MUX;
unsigned int *PA5_T2_GPIO_GDIR;
unsigned int *PA5_T2_GPIO_DR;

#define PA4_R2_GPIO_NBR                  25
unsigned int *PA4_R2_MUX;
unsigned int *PA4_R2_GPIO_GDIR;
unsigned int *PA4_R2_GPIO_DR;

#define PB7_T3_GPIO_NBR   23

unsigned int *PB7_T3_GPIO_MUX;
unsigned int *PB7_T3_GPIO_GDIR; 
unsigned int *PB7_T3_GPIO_DR;
	
#define PB6_R3_GPIO_NBR   31
unsigned int *PB6_R3_GPIO_MUX;
unsigned int *PB6_R3_GPIO_GDIR; 
unsigned int *PB6_R3_GPIO_DR;
		
#define SET_DATA_ORDER	0X40 //������������ ��ͨģʽ
#define SET_DISPLAY 0X8c	//��ʾ������ƣ������� 
#define RELAY_MAGIC 'k'
#define IOCTRL_CMD_RELAY_1 _IOW(RELAY_MAGIC, 1, int)
#define IOCTRL_CMD_RELAY_2 _IOW(RELAY_MAGIC, 2, int)

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
void imx6_gpio_pupd(unsigned int *padd,uint8_t mode)
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
static void bsp_init(void)
{
	PA2_SCL_MUX          =   (unsigned int*)ioremap(0x20e016c,4);
	PA2_SCL_GPIO_GDIR    =   (unsigned int*)ioremap(0x20A4004,4);
	PA2_SCL_GPIO_DR      =   (unsigned int*)ioremap(0x20A4000,4);

	PA3_DIN_MUX         = 	(unsigned int*)ioremap(0x20e0170,4);
	PA3_DIN_GPIO_GDIR   = 	(unsigned int*)ioremap(0x20A4004,4);
	PA3_DIN_GPIO_DR     = 	(unsigned int*)ioremap(0x20A4000,4);

	PA1_R4_MUX          =   (unsigned int*)ioremap(0x20e0234,4);
	PA1_R4_GPIO_GDIR    =   (unsigned int*)ioremap(0x209C004,4);
	PA1_R4_GPIO_DR      =   (unsigned int*)ioremap(0x209C000,4);

	PA0_T4_MUX         = 	(unsigned int*)ioremap(0x20e0250,4);
	PA0_T4_GPIO_GDIR   = 	(unsigned int*)ioremap(0x20a8004,4);
	PA0_T4_GPIO_DR     = 	(unsigned int*)ioremap(0x20a8000,4);
	
	PA7_T1_MUX         =   (unsigned int*)ioremap(0x20e013c,4);
	PA7_T1_GPIO_GDIR   =   (unsigned int*)ioremap(0x20a0004,4);
	PA7_T1_GPIO_DR     =   (unsigned int*)ioremap(0x20a0000,4);

	PA6_R1_MUX         =   (unsigned int*)ioremap(0x20e0140,4);
	PA6_R1_GPIO_GDIR   =   (unsigned int*)ioremap(0x20a0004,4);
	PA6_R1_GPIO_DR     =   (unsigned int*)ioremap(0x20a0000,4);	

	PA5_T2_MUX         =   (unsigned int*)ioremap(0x20e01D4,4);
	PA5_T2_GPIO_GDIR   =   (unsigned int*)ioremap(0x20a0004,4);
	PA5_T2_GPIO_DR     =   (unsigned int*)ioremap(0x20a0000,4);

	PA4_R2_MUX          =  (unsigned int*)ioremap(0x20e01D8,4);
	PA4_R2_GPIO_GDIR    =  (unsigned int*)ioremap(0x20A0004,4);
	PA4_R2_GPIO_DR      =  (unsigned int*)ioremap(0x20A0000,4);

	PB7_T3_GPIO_MUX          =  (unsigned int*)ioremap(0x20e0160,4);
	PB7_T3_GPIO_GDIR         =  (unsigned int*)ioremap(0x20a4004,4); 
	PB7_T3_GPIO_DR           =  (unsigned int*)ioremap(0x20a4000,4);

	PB6_R3_GPIO_MUX          =  (unsigned int*)ioremap(0x20e0180,4);
	PB6_R3_GPIO_GDIR         =  (unsigned int*)ioremap(0x20a4004,4); 
	PB6_R3_GPIO_DR           =  (unsigned int*)ioremap(0x20a4000,4);

		
	imx6_gpio_mode(PA2_SCL_MUX);
	imx6_gpio_mode(PA3_DIN_MUX);
	imx6_gpio_mode(PA1_R4_MUX);
	imx6_gpio_mode(PA0_T4_MUX);
	imx6_gpio_mode(PA5_T2_MUX);
	imx6_gpio_mode(PA4_R2_MUX);
	
	imx6_gpio_mode(PA7_T1_MUX);
	imx6_gpio_mode(PA6_R1_MUX);	
		
	imx6_gpio_out(PA2_SCL_GPIO_GDIR,PA2_SCL_GPIO_NBR);	
	imx6_gpio_out(PA3_DIN_GPIO_GDIR,PA3_DIN_GPIO_NBR);
	
	imx6_gpio_out(PA0_T4_GPIO_GDIR,PA0_T4_GPIO_NBR);	
	imx6_gpio_out(PA7_T1_GPIO_GDIR,PA7_T1_GPIO_NBR);
	imx6_gpio_out(PA5_T2_GPIO_GDIR,PA5_T2_GPIO_NBR);
	imx6_gpio_out(PB7_T3_GPIO_GDIR,PB7_T3_GPIO_NBR);
	
	imx6_gpio_in(PA1_R4_GPIO_GDIR,PA1_R4_GPIO_NBR);

	imx6_gpio_in(PA6_R1_GPIO_GDIR,PA6_R1_GPIO_NBR);
	imx6_gpio_in(PA4_R2_GPIO_GDIR,PA4_R2_GPIO_NBR);	
	imx6_gpio_in(PB6_R3_GPIO_GDIR,PB6_R3_GPIO_NBR);	
	
	imx6_gpio_write(PA3_DIN_GPIO_DR,PA3_DIN_GPIO_NBR,1);
	imx6_gpio_write(PA2_SCL_GPIO_DR,PA2_SCL_GPIO_NBR,1);
	imx6_gpio_write(PA0_T4_GPIO_DR,PA0_T4_GPIO_NBR,1);
	imx6_gpio_write(PA7_T1_GPIO_GDIR,PA7_T1_GPIO_NBR,1);
	imx6_gpio_write(PA5_T2_GPIO_GDIR,PA5_T2_GPIO_NBR,1);
	
	gpio_table[0].t_gpioadd = PA7_T1_GPIO_DR;
	gpio_table[0].t_gpionbr = PA7_T1_GPIO_NBR;
	gpio_table[0].r_gpioadd = PA6_R1_GPIO_DR;
	gpio_table[0].r_gpionbr = PA6_R1_GPIO_NBR;

	gpio_table[1].t_gpioadd = PA5_T2_GPIO_DR;
	gpio_table[1].t_gpionbr = PA5_T2_GPIO_NBR;
	gpio_table[1].r_gpioadd = PA4_R2_GPIO_DR;
	gpio_table[1].r_gpionbr = PA4_R2_GPIO_NBR;

	gpio_table[2].t_gpioadd = PB7_T3_GPIO_DR;
	gpio_table[2].t_gpionbr = PB7_T3_GPIO_NBR;
	gpio_table[2].r_gpioadd = PB6_R3_GPIO_DR;
	gpio_table[2].r_gpionbr = PB6_R3_GPIO_NBR;
	
	gpio_table[3].t_gpioadd = PA0_T4_GPIO_DR;
	gpio_table[3].t_gpionbr = PA0_T4_GPIO_NBR;
	gpio_table[3].r_gpioadd = PA1_R4_GPIO_DR;
	gpio_table[3].r_gpionbr = PA1_R4_GPIO_NBR;	
}
unsigned int get_channel(int ch)
{
	struct _gpio_table *table = &gpio_table[ch];
	int distance_raw;
	int count = 0,time = 0;	
	imx6_gpio_write(table->t_gpioadd,table->t_gpionbr,0);
	udelay(100);
	imx6_gpio_write(table->t_gpioadd,table->t_gpionbr,1);
	udelay(100);
	imx6_gpio_write(table->t_gpioadd,table->t_gpionbr,0);


	while(imx6_gpio_read(table->r_gpioadd,table->r_gpionbr)==0){
		udelay(1);
		if((++count)>1000){
			break;
		}
	}
	if(count>1000){//û�н��շ��صĸߵ�ƽ
		//printk("lost feedback\r\n");
		distance_raw= 0xffffffff;
	}
	else{//���յ����صĸߵ�ƽ
		count = 0;
		while(imx6_gpio_read(table->r_gpioadd,table->r_gpionbr)==1){
			udelay(10);
			if((++count)>10000){//����10ms
				break;
			}
		}
		if(count<10000){
			time = count*10;
			distance_raw = time;
		    //printk("time=%d mm\r\n",(time/2));
		}	
		else{
			//printk("alway hight level\r\n");
			distance_raw= 0xffffffff;
		}
	}
	return 	distance_raw;
}
#define sda_H imx6_gpio_write(PA3_DIN_GPIO_DR,PA3_DIN_GPIO_NBR,1); 
#define  scl_H imx6_gpio_write(PA2_SCL_GPIO_DR,PA2_SCL_GPIO_NBR,1);
#define sda_L imx6_gpio_write(PA3_DIN_GPIO_DR,PA3_DIN_GPIO_NBR,0); 
#define  scl_L imx6_gpio_write(PA2_SCL_GPIO_DR,PA2_SCL_GPIO_NBR,0);
/******	TM1640******/

unsigned char TM164_DATA[14] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0X39,0X76,0X80};//0~9,�հף�C,H,��;
unsigned char TM164_SIG[4] = {0x01,0x02,0x04,0x08};
void HAL_Delay(int n)
{
	udelay(200*n);
}
//==========================================================
//	�������ƣ�	start
//
//	�������ܣ�	TM1640��ʼ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void start(void)
{
		sda_H;
		scl_H;
		HAL_Delay(2);
		sda_L;
		HAL_Delay(2);
		scl_L;
		HAL_Delay(2);
}

//==========================================================
//	�������ƣ�	stop
//
//	�������ܣ�	TM1640ֹͣ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void stop(void)
{
	sda_L;
	scl_H;
	HAL_Delay(2);
	sda_H;
	HAL_Delay(2);
	scl_L;
	HAL_Delay(2);
}


//==========================================================
//	�������ƣ�	write
//
//	�������ܣ�	��������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void tim1640_write(unsigned char date)
{
	unsigned char i,aa;
	aa=date;
	sda_L;
	scl_L;
	for(i=0;i<8;i++){
		scl_L;
		if(aa&0x01){
			sda_H;
			HAL_Delay(2);
		}
		else{
			sda_L
			HAL_Delay(2);
		}
		scl_H;
		HAL_Delay(2);
		aa=aa>>1;
	}
	scl_L;
	sda_L;
}


//==========================================================
//	�������ƣ�	init_tm1640_NEW
//
//	�������ܣ�	����TM1640
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void init_tm1640_NEW(void)
{
	unsigned char i;
	sda_H;
	scl_H;

	start();
	tim1640_write(SET_DATA_ORDER);	//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
	stop();

	start();
	tim1640_write(0x00);					//���õ�ַ
	for(i=0;i<4;i++)
		{
			tim1640_write(TM164_DATA[i]);
		}
	stop();

	start();
	tim1640_write(SET_DISPLAY);	//������ʾ������ʾ0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f�ֱ��Ӧ������
											//------------------1/16, 2/16, 4/16, 10/16, 11/16, 12/16, 13/16, 14/16
	//0x80����ʾ
	stop();

}

//==========================================================
//	�������ƣ�	send_LED_Display
//
//	�������ܣ�	��ʾ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void send_LED_Display(unsigned char address,uint16_t data,unsigned char type)  
{
		unsigned char SEG_1 = 0,SEG_2 = 0,SEG_3 = 0,SEG_4 = 0;
		if(type == 1)//��ʾ������������
		{
			SEG_1 =  data/1000;
			SEG_2 = (data/100)%10;
			SEG_3 = (data/10)%10;
			SEG_4 = data%10;
		}
		
		sda_H;
		scl_H;
	
		start();
		tim1640_write(SET_DATA_ORDER);	//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
		stop();
		
		start();
		tim1640_write(address);	//������ʼ��ַ
		tim1640_write(TM164_DATA[SEG_1]);
		tim1640_write(TM164_DATA[SEG_2]);
		tim1640_write(TM164_DATA[SEG_3]);
		tim1640_write(TM164_DATA[SEG_4]);
		
		stop();
		
		start();
		tim1640_write(SET_DISPLAY);	//������ʾ������ʾ0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f�ֱ��Ӧ������
		//------------------1/16, 2/16, 4/16, 10/16, 11/16, 12/16, 13/16, 14/16
		//0x80����ʾ
		stop();
}

/******�Զ���һģʽ*****/

void send_z(unsigned char address,unsigned char date)
{
		unsigned char i;
		start();
		tim1640_write(address);	//������ʼ��ַ
		for(i=0;i<4;i++)
		{
			tim1640_write(TM164_DATA[i]);
		}
		stop();
}

/******�̶���ַģʽ*****/

void send(unsigned char address, unsigned char date)
{
	start();
	tim1640_write(address);	//����ʾ���ݶ�Ӧ��ַ
	tim1640_write(date);	//��BYTE��ʾ����
	stop();
}
//==========================================================
//	�������ƣ�	init_tm1640
//
//	�������ܣ�	��ʼ��TM1640
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void init_tm1640(void)
{
	sda_H;
	scl_H;
	start();
	tim1640_write(SET_DATA_ORDER);		//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
	stop();
	start();
	tim1640_write(SET_DISPLAY);				//������ʾ������ʾ0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f�ֱ��Ӧ������														//------------------1/16, 2/16, 4/16, 10/16, 11/16, 12/16, 13/16, 14/16
	//0x80����ʾ
	stop();	
}
/*********************TIM1640*************************/
static volatile int key_value;//����ֵ
static int key_major = 0;     //
static int key_minor = 0; 
/* �ȴ�����: 
 * ��û�а���������ʱ������н��̵���key_read������
 * ��������
 */
static DECLARE_WAIT_QUEUE_HEAD(key_waitq);

/*�ں˶�ʱ��*/
//static struct timer_list key_timer;

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
int chb_channel = 0;
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
		case IOCTRL_CMD_P3A:
			chb_channel = 0;
			break;
		case IOCTRL_CMD_P4A:
			chb_channel = 1;
			break;
		case IOCTRL_CMD_P5A:
			chb_channel = 2;
			break;
		case IOCTRL_CMD_P6:
			chb_channel = 3;
			break;	
		case IOCTRL_CMD_DISP_P3A:
		case IOCTRL_CMD_DISP_P4A:
		case IOCTRL_CMD_DISP_P5A:
		case IOCTRL_CMD_DISP_P6:
			send_LED_Display(0xC0,data,1);
			break;			
	}
	return 0;
}
/* Ӧ�ó�����豸�ļ�/dev/keyִ��read(...)ʱ�����������
 * �ͻ����key_read����
 */
 unsigned int distance;
static int key_read(struct file *filp, char __user *buff,size_t count, loff_t *offp)
{
    unsigned long err;
		
	distance = get_channel(chb_channel);
//	printk("distance=%d\r\n",distance);
	err = copy_to_user(buff, (const void *)&distance, 4);
    return err ? -EFAULT : 1;
}
static int key_write(struct file *filp, const char __user *buff, size_t count, loff_t *offp)
{
    unsigned long err = 0;
//	unsigned char byte = 0;
	//printk("write\r\n");
	//err = copy_from_user(&byte,buff,1);
	//printk("write:byte=%d\r\n",byte);
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
	result    = alloc_chrdev_region(&devno, 0, 1, "relay");
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
	bsp_init();

		
	//send_LED_Display(0xC0,55,2);
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

