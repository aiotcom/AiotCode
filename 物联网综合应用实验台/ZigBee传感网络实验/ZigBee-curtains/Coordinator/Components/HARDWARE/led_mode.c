#include "led_mode.h"
#include "stdio.h"
/*
��ʼ��LEDģ���ϵ�S4->P1.6������LED2->P1.2������IO���ڿ�
*/
void LedMode_Init(void)
{
    //LED��IO�ڳ�ʼ��
    P1SEL &= ~BV(2);     //����P1.2Ϊ��ͨIO��  
    P1DIR |= BV(2);      //P1.2����Ϊ���

    //����IO�ڳ�ʼ��    
    P1SEL &= ~(BV(5)|BV(4));     //����P1.5Ϊ��ͨIO��  
    P1DIR &= ~(BV(5)|BV(4));      //P1.5����Ϊ���� 
    P1INP &= ~(BV(5)|BV(4));     //��P1.5��������

    P0SEL &= ~(BV(0)|BV(1));     //����P1.5Ϊ��ͨIO��  
    P0DIR &= ~(BV(0)|BV(1));      //P1.5����Ϊ���� 
    P0INP &= ~(BV(0)|BV(1));     //��P1.5��������	
	
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
/*
��ȡ���еİ���
*/
uint8 key_all_read(void)
{
	uint8 kv = 0xf0;
	kv |= S1;
	kv |= S2<<1;
	kv |= S3<<2;
	kv |= S4<<3;
	
	return ~kv;
}
/*
��������
*/
uint8 key_handler(void)
{
    static unsigned char state = KEY_RELASE,prekv = 0,kv = 0;
	
	kv = key_all_read();	
	
	if(KEY_RELASE == state)
	
	{
		
		if((kv)&&(prekv == kv))
		
		{
	
			printf("key pressed\r\n");
		
			state = KEY_PRESS;
			return kv;
						
		
		}		
		
	}
	
	else if((KEY_PRESS == state)&&(kv == 0))
	
	{
		
		printf("key relase\r\n");
	
		state = KEY_RELASE;
	
	}
	prekv = kv;
	
	return 0;
	

}