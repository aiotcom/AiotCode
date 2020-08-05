#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "ADC.h"
#include "pwm.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-12-18
*
*	�汾�� 		V2.0
*
*	˵���� 		PM2.5
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

uint16_t Data = 0;

uint8_t PM_Data[10];

int main(void)
{
  HAL_Init();             			//��ʼ��HAL��
	ADC_Init();										//��ʼ��ADC
	Rs485_Init();									//��ʼ��485
	UART1_Init(115200);						//��ʼ������1
	UART2_Init(115200);						//��ʼ������2
  TIM2_PWM_Init(64-1,1000-1);		//��ʼ����ʱ��(1ms)

	while(1)
	{
		Data = Get_Adc_Average(ADC_CHANNEL_3,100);
		printf("PM2.5-Data:%d\r\n",Data);
		PM_Data[0] = Data>>8;PM_Data[1] = Data;
		
		if(!DataHandling_485(Addr_PM2_5))		//����485����
		{
			Rs485_Send(Addr_PM2_5,Rx_Stack.Src_Adr,PM2_5_Conc,2,PM_Data);	//�������ݵ�WiFiģ��
			memset(PM_Data,0,10);
		}
		delay_ms(100);
	}
}



