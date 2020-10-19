#ifndef __IIC_H 
#define __IIC_H 			   


#include <hal_types.h>

#define Bit_SET  	  1
#define Bit_RESET    	  0

#define ACK_OK  	  0x00
#define ACK_ERROR    	  0x01

#define SCL_PIN           P0_6
#define SDA_PIN           P0_7

#define SCL_HIGH()        P0_6 = 1;P0_6 = 1;
#define SCL_LOW()         P0_6 = 0;P0_6 = 0;

#define SDA_HIGH()        P0_7 = 1;P0_7 = 1;;
#define SDA_LOW()         P0_7 = 0;P0_7 = 0;;

#define SCL_STATE()       P0_6
#define SDA_STATE()       P0_7

//IIC���в�������
void IIC_Delay(uint32 n);		//IIC��ʱ����
void IIC_Init(void);           	//��ʼ��IIC��IO��		
void IIC_Start(void);		//����IIC��ʼ�ź�
void IIC_Stop(void);	  	//����IICֹͣ�ź�
void IIC_Ack(void);		//IIC����ACK�ź�
void IIC_NAck(void);		//IIC������ACK�ź�
uint8 IIC_Wait_Ack(void);		//�ȴ�Ӧ���źŵ���
void IIC_SCL_OUTPUT(void);	//IICʱ�������ģʽ
void IIC_SCL_INPUT(void);	//IICʱ��������ģʽ
void IIC_SDA_OUTPUT(void);	//IIC���������ģʽ 
void IIC_SDA_INPUT(void);	//IIC����������ģʽ
uint8 IIC_Read_Byte(uint8 ack);	//IIC��ȡ����
void IIC_Send_Byte(uint8 txd);	//IICд����
uint8 SHT2x_I2cReadByte(void);	//SHT20��ȡ����
uint8 Write_IIC_Byte(uint8 byte);	//IICд����

#endif

