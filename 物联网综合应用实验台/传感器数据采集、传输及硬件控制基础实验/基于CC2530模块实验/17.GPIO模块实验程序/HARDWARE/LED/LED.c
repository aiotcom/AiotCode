#include "delay.h"
#include "Time.h"
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

//==========================================================
//	�������ƣ�	Water_Lamp_Time
//
//	�������ܣ�	LED��ˮ��
//
//	��ڲ�����	time:������ˮ��ʱ����
//
//	���ز�����	��
//
//	˵����			
//==========================================================
uint8_t Water_Lamp_Time_Flag = 0,Water_Lamp_Time2_Flag = 0;
void Water_Lamp_Time(uint16_t time)
{
  switch(Water_Lamp_Time_Flag)
  {
    case 0:
      Water_Lamp_Time2_Flag = 0;
      LED_OFF();		//�ر�����LED��
      LED_Count_Flag = 1;	//��ʼ����
      LED1_ON();		//����LED1
      if(LED_Count>=time)
      {
        LED1_OFF();		//�ر�LED1
        LED_Count_Flag = 0;	//ֹͣ����
        LED_Count = 0;
        Water_Lamp_Time_Flag = 1;
      }
      break;
    case 1:
      LED_Count_Flag = 1;	//��ʼ����
      LED2_ON();		//����LED2
      if(LED_Count>=time)
      {
        LED2_OFF();		//�ر�LED2
        LED_Count_Flag = 0;	//ֹͣ����
        LED_Count = 0;
        Water_Lamp_Time_Flag = 2;
      }
      break;
    case 2:
      LED_Count_Flag = 1;	//��ʼ����
      LED4_ON();		//����LED4
      if(LED_Count>=time)
      {
        LED4_OFF();		//�ر�LED4
        LED_Count_Flag = 0;	//ֹͣ����
        LED_Count = 0;
        Water_Lamp_Time_Flag = 3;
      }
      break;
    case 3:
      LED_Count_Flag = 1;	//��ʼ����
      LED3_ON();		//����LED3
      if(LED_Count>=time)
      {
        LED3_OFF();		//�ر�LED3
        LED_Count_Flag = 0;	//ֹͣ����
        LED_Count = 0;
        Water_Lamp_Time_Flag = 0;
      }
      break;
    default:break;
  }
}

//==========================================================
//	�������ƣ�	Water_Lamp_Time2
//
//	�������ܣ�	LED��ˮ��
//
//	��ڲ�����	time:������ˮ��ʱ����
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void Water_Lamp_Time2(uint16_t time)
{
  switch(Water_Lamp_Time2_Flag)
  {
    case 0:
      Water_Lamp_Time_Flag = 0;
      LED_OFF();		//�ر�����LED��
      LED_Count_Flag2 = 1;	//��ʼ����2
      LED1_ON();		//����LED1
      if(LED_Count2>=time)	
      {
        LED_Count_Flag2 = 0;    //ֹͣ����2
        LED_Count2 = 0;
        Water_Lamp_Time2_Flag = 1;
      }
      break;
    case 1:
      LED2_ON();		//����LED2
      LED_Count_Flag2 = 1;	//��ʼ����2
      if(LED_Count2>=time)	
      {
        LED_Count_Flag2 = 0;    //ֹͣ����2
        LED_Count2 = 0;
        Water_Lamp_Time2_Flag = 2;
      }
      break;
    case 2:
      LED4_ON();		//����LED4
      LED_Count_Flag2 = 1;	//��ʼ����2
      if(LED_Count2>=time)	
      {
        LED_Count_Flag2 = 0;    //ֹͣ����2
        LED_Count2 = 0;
        Water_Lamp_Time2_Flag = 3;
      }
      break;
    case 3:
      LED3_ON();		//����LED3
      LED_Count_Flag2 = 1;	//��ʼ����2
      if(LED_Count2>=time)	
      {
        LED_Count_Flag2 = 0;    //ֹͣ����2
        LED_Count2 = 0;
        Water_Lamp_Time2_Flag = 4;
      }
      break;
    case 4:
      LED1_OFF();		//�ر�LED1
      LED_Count_Flag2 = 1;	//��ʼ����2
      if(LED_Count2>=time)	
      {
        LED_Count_Flag2 = 0;    //ֹͣ����2
        LED_Count2 = 0;
        Water_Lamp_Time2_Flag = 5;
      }
      break;
    case 5:
      LED2_OFF();		//�ر�LED2
      LED_Count_Flag2 = 1;	//��ʼ����2
      if(LED_Count2>=time)	
      {
        LED_Count_Flag2 = 0;    //ֹͣ����2
        LED_Count2 = 0;
        Water_Lamp_Time2_Flag = 6;
      }
      break;
    case 6:
      LED4_OFF();		//�ر�LED4
      LED_Count_Flag2 = 1;	//��ʼ����2
      if(LED_Count2>=time)	
      {
        LED_Count_Flag2 = 0;    //ֹͣ����2
        LED_Count2 = 0;
        Water_Lamp_Time2_Flag = 7;
      }
      break;
    case 7:
      LED3_OFF();		//�ر�LED3
      LED_Count_Flag2 = 1;	//��ʼ����2
      if(LED_Count2>=time)	
      {
        LED_Count_Flag2 = 0;    //ֹͣ����2
        LED_Count2 = 0;
        Water_Lamp_Time2_Flag = 8;
      }
      break;
    case 8:
      LED_OFF();		//�ر�����LED��
      LED_Count_Flag2 = 1;	//��ʼ����2
      if(LED_Count2>=time*9)	Water_Lamp_Time2_Flag = 0;
      {
        LED_Count_Flag2 = 0;    //ֹͣ����2
        Water_Lamp_Time2_Flag = 0;
        LED_Count2 = 0;
      }
      break;
    default:break;
  }
}

//==========================================================
//	�������ƣ�	LED_Type
//
//	�������ܣ�	LED�ƺ�������������
//
//	��ڲ�����	type:ѡ��ģʽ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void LED_Type(uint8_t type)
{
  switch(type)
  {
    case 1:
      Water_Lamp_Time(200);	//��ˮ��
      break;
    case 2:
      Water_Lamp_Time(600);	//��ˮ��
      break;
    case 3:
      Water_Lamp_Time2(100);    //��ˮ����ʽ2
      break;
    case 4:
      LED_OFF();		//ȫ��LED����
      LED_Count_Flag = 0;	//ֹͣ����2
      LED_Count_Flag2 = 0;	//ֹͣ����2
      LED_Count = 0;
      LED_Count2 = 0;
      break;
    default:break;
  }
}