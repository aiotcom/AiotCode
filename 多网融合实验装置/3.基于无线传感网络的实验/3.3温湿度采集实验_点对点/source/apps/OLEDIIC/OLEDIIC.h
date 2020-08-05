#ifndef __OLED_IIC_H 
#define __OLED_IIC_H 			   

#include <ioCC2530.h>
#include "delay.h"

#define OLED_Bit_SET  	  1
#define OLED_Bit_RESET    0

#define OLED_ACK_OK  	  0x00
#define OLED_ACK_ERROR    0x01

#define OLED_SCL_PIN      P0_6
#define OLED_SDA_PIN      P0_7

#define OLED_SCL_HIGH()   P0_6 = 1;P0_6 = 1;
#define OLED_SCL_LOW()    P0_6 = 0;P0_6 = 0;

#define OLED_SDA_HIGH()   P0_7 = 1;P0_7 = 1;
#define OLED_SDA_LOW()    P0_7 = 0;P0_7 = 0;

#define OLED_SCL_STATE()  P0_6
#define OLED_SDA_STATE()  P0_7

//IIC���в�������
void OLED_IIC_Delay(u32 n);	//OLED_IIC��ʱ����
void OLED_IIC_Init(void);       //��ʼ��OLED_IIC��IO��		
void OLED_IIC_Start(void);	//����OLED_IIC��ʼ�ź�
void OLED_IIC_Stop(void);	//����OLED_IICֹͣ�ź�
void OLED_IIC_Ack(void);	//OLED_IIC����ACK�ź�
void OLED_IIC_NAck(void);	//OLED_IIC������ACK�ź�
u8 OLED_IIC_Wait_Ack(void);	//�ȴ�Ӧ���źŵ���
void OLED_IIC_SCL_OUTPUT(void);	//OLED_IICʱ�������ģʽ
void OLED_IIC_SCL_INPUT(void);	//OLED_IICʱ��������ģʽ
void OLED_IIC_SDA_OUTPUT(void);	//OLED_IIC���������ģʽ 
void OLED_IIC_SDA_INPUT(void);	//OLED_IIC����������ģʽ
u8 OLED_IIC_Read_Byte(u8 ack);	//OLED_IIC��ȡ����
void OLED_IIC_Send_Byte(u8 txd);	//OLED_IICд����
u8 Write_OLED_IIC_Byte(u8 byte);//OLED_IICд����

#endif

