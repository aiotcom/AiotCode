#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "ADC.h"

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
*	˵���� 		���洫����
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
uint16_t Data_Flam0 = 0,Data_Flam1 = 0;

int main(void)
{
  HAL_Init();             		//��ʼ��HAL��  
	ADC_Init();									//��ʼ��ADC
	Rs485_Init();								//��ʼ��485
	UART1_Init(115200);					//��ʼ������1

	while(1)
	{
		Data_Flam0 = Get_Adc_Average(ADC_CHANNEL_2,20);	//��ȡPA0 ���洫��������
		delay_ms(50);
		Data_Flam1 = Get_Adc_Average(ADC_CHANNEL_3,20);	//��ȡPA1 ���洫��������
		delay_ms(50);

		if((Data_Flam0<4050 && Data_Flam0>3800) || (Data_Flam1<4050 && Data_Flam1>3800))
		{
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);
		}
		else if(Data_Flam0<3800 || Data_Flam1<3800)
		{
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_RESET);
			 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
		}
		else
		{
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_SET);
			 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_RESET);
		}
	}
}

