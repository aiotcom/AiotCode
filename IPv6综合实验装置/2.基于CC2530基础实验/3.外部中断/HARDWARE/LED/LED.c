#include "delay.h"
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
   LED_OFF();          //��ʼ���ر�LED��
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


//==========================================================
//	�������ƣ�	Water_Lamp
//
//	�������ܣ�	LED��ˮ��
//
//	��ڲ�����	time:������ˮ��ʱ����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Water_Lamp(uint16_t time)
{
  static uint8_t Time_Flag = 1;		//ִ�б�־λ
  static uint16_t Time_Count = 0;	//����ֵ
  
  switch(Time_Flag)
  {
    case 1://����LED1
      LED1_ON();
      delay_ms(1);
      Time_Count++;

      if(Time_Count>=time)
      {
        LED1_OFF();
        Time_Flag = 2;
        Time_Count = 0;
      }
      break;
    case 2://����LED2
      LED2_ON();
      delay_ms(1);
      Time_Count++;

      if(Time_Count>=time)
      {
        LED2_OFF();
        Time_Flag = 3;
        Time_Count = 0;
      }
      break;
    case 3://����LED4 
      LED4_ON();
      delay_ms(1);
      Time_Count++;

      if(Time_Count>=time)
      {
        LED4_OFF();
        Time_Flag = 4;
        Time_Count = 0;
      }
      break;
    case 4://����LED3
      LED3_ON();
      delay_ms(1);
      Time_Count++;

      if(Time_Count>=time)
      {
        LED3_OFF();
        Time_Flag = 1;
        Time_Count = 0;
      }
      break;
    default: break;
  }
}