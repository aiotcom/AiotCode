#include <ioCC2530.h>
#include "TIM.h"
#include "UART.h"
#include "stdio.h"
#include "string.h"
#include "type.h"
#include "LORA.h"
//****�궨��*******************  
#define RF_Frequency 500  //��Χ 410-525 (��λ��M)
//****�궨��*******************

//****��������*****************
void System_clockInit(void);
uint8_t KeyPoll(void);
//****��������*****************

//****��������*******************
uint8 version,IRQ_RegValue,LedState=1;
uint8_t LoraSendBuffer[32]={"toggle led\r\n"};
uint8_t LoraRecvBuffer[32]={"toggle led\r\n"};
//****��������*******************

void main(void)
{
  	System_clockInit();
    TIM1_Init();
	LORA_Init(RF_Frequency);
    version = SX1276ReadBuffer(REG_LR_VERSION);
    if(version == 0x12)
    {//���ģ�鰲�����ף���500ms
        LED_SET=0;
        HAL_Delay(500);
        LED_SET=1;
    }	
	while(1)
	{
		if(KeyPoll())
		{
			Sx1278SendLong(LoraSendBuffer,strlen((const char*)LoraSendBuffer));  
		}

		IRQ_RegValue = SX1276ReadBuffer( REG_LR_IRQFLAGS );
		if((IRQ_RegValue)&&(IRQ_RegValue != 0XFF))//�� LORA�жϼĴ��� REG_LR_IRQFLAGS���ж��Ƿ����жϷ���
		{
			if(INT_FLG_RX_DONE == SX1278_InteruptHandler(LoraRecvBuffer))
			{//�ǽ����жϣ������յ����ݱ��浽LoraRecvBuffer��
				if(strstr((const char*)LoraRecvBuffer,(const char*)"toggle led"))
				{
					LedState?(LED_SET=0):(LED_SET=1);
					LedState =  1-LedState;//�л��Ƶ�״̬
				}
			}
		} 
	}
}	
//==========================================================
//	�������ƣ�	void System_clockInit(void)
//
//	�������ܣ�	��ʼ��ϵͳʱ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		��ʱ��ʱ��16MHz���ж�����1000HZ
//==========================================================
void System_clockInit(void)
{
  CLKCONCMD &= ~(1<<6);        /*ѡ��32MHz����*/  
  while(!(CLKCONSTA & (1<<6))); /*�ȴ������ȶ�*/  
  CLKCONCMD &= ~0x47;          /* ����Ƶ,ϵͳʱ��32MHZ����ʱ��ʱ��16MHZ*/             
}
//==========================================================
//	�������ƣ�	uint8_t KeyPoll(void)
//
//	�������ܣ�	ģ������İ���ɨ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
uint8_t KeyPoll(void)
{
	static uint8_t kstate = 0;
		   uint8_t kv;
		   
	kv = !KEY_INPUT;
	
	if(kv&&(!kstate))
	{
		kstate = 1;
		return 1;
	}
	else if((!kv)&&(kstate))
	{
		kstate = 0;
	}
	
	return 0;
}