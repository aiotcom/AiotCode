#include "LED.h"

//==========================================================
//	�������ƣ�	LED_Init()
//
//	�������ܣ�	��ʼ��LED
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void LED_Init(void)
{
   P0DIR |= 0x0C;      //P0.2��P0.3����Ϊ���
   P1DIR |= 0xC0;      //P1.6��P1.7����Ϊ���
   LED1=1;LED2=1;LED3=1;LED4=1;
}

//==========================================================
//	�������ƣ�	LED_Set()
//
//	�������ܣ�	LED����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void LED_Set(void)
{ 
  LED1=0;delay_ms(500);LED1=1;
  LED2=0;delay_ms(500);LED2=1;
  LED4=0;delay_ms(500);LED4=1;
  LED3=0;delay_ms(500);LED3=1;
  
  LED1=0;delay_ms(400);LED1=1;
  LED2=0;delay_ms(400);LED2=1;
  LED4=0;delay_ms(400);LED4=1;
  LED3=0;delay_ms(400);LED3=1;
  
  LED1=0;delay_ms(300);LED1=1;
  LED2=0;delay_ms(300);LED2=1;
  LED4=0;delay_ms(300);LED4=1;
  LED3=0;delay_ms(300);LED3=1;
  
  LED1=0;delay_ms(200);LED1=1;
  LED2=0;delay_ms(200);LED2=1;
  LED4=0;delay_ms(200);LED4=1;
  LED3=0;delay_ms(200);LED3=1;
  
  LED1=0;delay_ms(100);LED1=1;
  LED2=0;delay_ms(100);LED2=1;
  LED4=0;delay_ms(100);LED4=1;
  LED3=0;delay_ms(100);LED3=1;
  
  LED1=0;LED2=0;LED3=0;LED4=0;delay_ms(500);
  LED1=1;LED2=1;LED3=1;LED4=1;delay_ms(500);
  LED1=0;LED2=0;LED3=0;LED4=0;delay_ms(300);
  LED1=1;LED2=1;LED3=1;LED4=1;delay_ms(300);
}
