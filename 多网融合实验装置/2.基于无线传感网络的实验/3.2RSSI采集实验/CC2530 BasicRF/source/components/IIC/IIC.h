#ifndef __IIC_H 
#define __IIC_H 			   

#include <ioCC2530.h>
#include "delay.h"

#define Bit_SET  	  1
#define Bit_RESET    	  0

#define ACK_OK  	  0x00
#define ACK_ERROR    	  0x01

#define SCL_PIN           P0_6
#define SDA_PIN           P0_7

#define SCL_HIGH()        P0_6 = 1;//P0_6 = 1;
#define SCL_LOW()         P0_6 = 0;//P0_6 = 0;

#define SDA_HIGH()        P0_7 = 1;//P0_7 = 1;
#define SDA_LOW()         P0_7 = 0;//P0_7 = 1;

#define SCL_STATE()       P0_6
#define SDA_STATE()       P0_7

//IIC���в�������
void IIC_Delay(u32 n);		//IIC��ʱ����
void IIC_Init(void);           	//��ʼ��IIC��IO��		
void IIC_Start(void);		//����IIC��ʼ�ź�
void IIC_Stop(void);	  	//����IICֹͣ�ź�
void IIC_Ack(void);		//IIC����ACK�ź�
void IIC_NAck(void);		//IIC������ACK�ź�
u8 IIC_Wait_Ack(void);		//�ȴ�Ӧ���źŵ���
void IIC_SCL_OUTPUT(void);	//IICʱ�������ģʽ
void IIC_SCL_INPUT(void);	//IICʱ��������ģʽ
void IIC_SDA_OUTPUT(void);	//IIC���������ģʽ 
void IIC_SDA_INPUT(void);	//IIC����������ģʽ
u8 IIC_Read_Byte(u8 ack);	//IIC��ȡ����
void IIC_Send_Byte(u8 txd);	//IICд����
u8 SHT2x_I2cReadByte(void);	//SHT20��ȡ����
u8 Write_IIC_Byte(u8 byte);	//IICд����

#endif

