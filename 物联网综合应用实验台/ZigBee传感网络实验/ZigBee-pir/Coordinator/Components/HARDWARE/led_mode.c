#include "led_mode.h"
/*
��ʼ��LEDģ���ϵ�S4->P1.6������LED2->P1.2������IO���ڿ�
*/
void LedMode_Init(void)
{
    //LED��IO�ڳ�ʼ��
    P1SEL &= ~BV(2);     //����P1.2Ϊ��ͨIO��  
    P1DIR |= BV(2);      //P1.2����Ϊ���

    //����IO�ڳ�ʼ��    
    P1SEL &= ~BV(6);     //����P1.6Ϊ��ͨIO��  
    P1DIR &= ~BV(6);      //P1.6����Ϊ���� 
    P1INP &= ~BV(6);     //��P1.6��������
}
/*
LEDģ����LED2����
*/
void Led2_On(void)   
{
  P1_2 = 0;
}
/*
LEDģ����LED2Ϩ��
*/
void Led2_Off(void)  
{
  P1_2 = 1;
}
/*
��LEDģ���ϵİ���S4
*/
uint8 Key_ReadS4(void)
{
  return P1_6?KEY_RELASE:KEY_PRESS;
}