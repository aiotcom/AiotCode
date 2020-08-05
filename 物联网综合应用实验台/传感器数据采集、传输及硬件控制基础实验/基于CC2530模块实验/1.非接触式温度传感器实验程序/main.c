/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-12-11
*
*	�汾�� 		V2.0
*
*	˵���� 		�ǽӴ��¶�ģ��ʵ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

#include "Noncontact_Temp.h"	
#include <ioCC2530.h>
#include "OLEDIIC.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "OLED.h"
#include "Lamp.h"

//==========================================================
//	�������ƣ�	main()
//
//	�������ܣ�	������ں���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================   
void main(void)
{
    unsigned char buf[10];
    unsigned char SlaveAddress; //Contains device address
    unsigned char command;//Contains the access command
    unsigned int  data;	  //Contains data value	
    float temp;
    SlaveAddress=SA<<1;	  //Set device address
    command=RAM_Access|RAM_To; 	
  
    Hal_Init_32M(); //��ʼ��32Mʱ��
    LampInit();     //��ʼ��������
    USRT1_Init();   //��ʼ������1
    Rs485_Init();   //��ʼ��485
    MLX90615_init();//��ʼ��MLX90615
    OLED_IIC_Init();//��ʼ��OLED_IIC
    OLED_Init();    //OLED����ʼ��
    OLED_Init_UI(); //OLED����ʼ������

    while(1)
    {
        data=MemRead(SlaveAddress,command); //Read memory
        temp=CalcTemp(data);
        sprintf((char *)buf," tmp:%0.2f  ",temp);
        OLED_P8x16Str(30,6,buf);
    }
}
