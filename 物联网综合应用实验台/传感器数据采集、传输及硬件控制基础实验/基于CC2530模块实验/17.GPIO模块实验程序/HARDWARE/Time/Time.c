#include "Time.h"
#include "LED.h"

uint8_t LED_Count_Flag = 0,LED_Count_Flag2 =0;
uint32_t LED_Count = 0,LED_Count2 =0;
unsigned int count = 0;  //��ʱ������ֵ

//==========================================================
//	�������ƣ�	Init_Timer1()
//
//	�������ܣ�	��ʱ��1��ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����
//==========================================================
void Init_Timer1(void)
{
  T1CC0L = 0x7D;        //����������ֵ�ĵ�8λ
  T1CC0H = 0x00;        //����������ֵ�ĸ�8λ
  T1CCTL0 |= 0x04;      //����ͨ��0������Ƚ�ģʽ
  T1IE = 1;             //ʹ�ܶ�ʱ��1�ж�
  T1OVFIM = 1;          //ʹ�ܶ�ʱ��1����ж�
  EA = 1;               //ʹ�����ж�
  T1CTL = 0x0e;         //��Ƶϵ����128,ģģʽ
}

//==========================================================
//	�������ƣ�	Time_LED_Set()
//
//	�������ܣ�	LED����
//
//	��ڲ�����	Delay����ʱ(��λ��ms)
//
//	���ز�����	��
//
//	˵����		 
//==========================================================
void Time_LED_Set(uint16_t Delay)
{
  static uint8_t Flag1 = 1,Flag2 = 1;
  
  switch(Flag1)
  {
    case 1:
        switch(Flag2)
        {
          case 1:
            LED1 = 0;
            if(count>=Delay)
            {
              LED1=1;
              Flag2 = 2;
              count = 0;
            }
            break;
          case 2:
            LED2 = 0;
            if(count>=Delay)
            {
              LED2=1;
              Flag2 = 3;
              count = 0;
            }
            break; 
          case 3:
            LED4 = 0;
            if(count>=Delay)
            {
              LED4=1;
              Flag2 = 4;
              count = 0;
            }
            break; 
          case 4:
            LED3 = 0;
            if(count>=Delay)
            {
              LED3=1;
              Flag2 = 1;
              Flag1 = 2;
              count = 0;
            }
            break; 
          default:break;  
        }
      break;
    case 2:
        switch(Flag2)
        {
          case 1:
            LED1 = 0;
            if(count>=(Delay*4/5))
            {
              LED1=1;
              Flag2 = 2;
              count = 0;
            }
            break;
          case 2:
            LED2 = 0;
            if(count>=(Delay*4/5))
            {
              LED2=1;
              Flag2 = 3;
              count = 0;
            }
            break; 
          case 3:
            LED4 = 0;
            if(count>=(Delay*4/5))
            {
              LED4=1;
              Flag2 = 4;
              count = 0;
            }
            break; 
          case 4:
            LED3 = 0;
            if(count>=(Delay*4/5))
            {
              LED3=1;
              Flag2 = 1;
              Flag1 = 3;
              count = 0;
            }
            break; 
          default:break;  
        }
      break; 
    case 3:
        switch(Flag2)
        {
          case 1:
            LED1 = 0;
            if(count>=(Delay*3/5))
            {
              LED1=1;
              Flag2 = 2;
              count = 0;
            }
            break;
          case 2:
            LED2 = 0;
            if(count>=(Delay*3/5))
            {
              LED2=1;
              Flag2 = 3;
              count = 0;
            }
            break; 
          case 3:
            LED4 = 0;
            if(count>=(Delay*3/5))
            {
              LED4=1;
              Flag2 = 4;
              count = 0;
            }
            break; 
          case 4:
            LED3 = 0;
            if(count>=(Delay*3/5))
            {
              LED3=1;
              Flag2 = 1;
              Flag1 = 4;
              count = 0;
            }
            break; 
          default:break;  
        }
      break; 
    case 4:
        switch(Flag2)
        {
          case 1:
            LED1 = 0;
            if(count>=(Delay*2/5))
            {
              LED1=1;
              Flag2 = 2;
              count = 0;
            }
            break;
          case 2:
            LED2 = 0;
            if(count>=(Delay*2/5))
            {
              LED2=1;
              Flag2 = 3;
              count = 0;
            }
            break; 
          case 3:
            LED4 = 0;
            if(count>=(Delay*2/5))
            {
              LED4=1;
              Flag2 = 4;
              count = 0;
            }
            break; 
          case 4:
            LED3 = 0;
            if(count>=(Delay*2/5))
            {
              LED3=1;
              Flag2 = 1;
              Flag1 = 5;
              count = 0;
            }
            break; 
          default:break;  
        }
      break; 
    case 5:
        switch(Flag2)
        {
          case 1:
            LED1 = 0;
            if(count>=(Delay/5))
            {
              LED1=1;
              Flag2 = 2;
              count = 0;
            }
            break;
          case 2:
            LED2 = 0;
            if(count>=(Delay/5))
            {
              LED2=1;
              Flag2 = 3;
              count = 0;
            }
            break; 
          case 3:
            LED4 = 0;
            if(count>=(Delay/5))
            {
              LED4=1;
              Flag2 = 4;
              count = 0;
            }
            break; 
          case 4:
            LED3 = 0;
            if(count>=(Delay/5))
            {
              LED3=1;
              Flag2 = 1;
              Flag1 = 6;
              count = 0;
              Delay = 5;
            }
            break; 
          default:break;  
        }
      break; 
    case 6:
        switch(Flag2)
        {
          case 1:
            LED1=0;LED2=0;LED3=0;LED4=0;
            if(count>=Delay)
            {
              Flag2 = 2;
              count = 0;
            }
            break; 
          case 2:
            if(count>=Delay)
            {
              LED1=1;LED2=1;LED3=1;LED4=1;
              Flag2 = 3;
              count = 0;
            }
            break; 
          case 3:
            if(count>=Delay*3/5)
            {
              LED1=0;LED2=0;LED3=0;LED4=0;
              Flag2 = 4;
              count = 0;
            }
            break; 
          case 4:
            if(count>=(Delay*3/5))
            {
              LED1=1;LED2=1;LED3=1;LED4=1;
            }
            if(count>=(Delay*6/5))
            {
              Flag1 = 1;
              Flag2 = 1;
              count = 0;
            }
            break; 
          default:break;  
        }
      break; 
    default:break;  
  }
}

//==========================================================
//	�������ƣ�	Timer1_Sevice()
//
//	�������ܣ�	��ʱ��1������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice()
{
  T1STAT &= ~0x01;      //�����ʱ��1ͨ��0�жϱ�־
  
  if(LED_Count_Flag)	LED_Count++;	//����
  
  if(LED_Count_Flag2)	LED_Count2++;	//����2
}
