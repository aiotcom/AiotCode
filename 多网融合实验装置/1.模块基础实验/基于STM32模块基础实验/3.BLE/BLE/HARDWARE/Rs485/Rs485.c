#include "Rs485.h"	
#include "USART.H"
void Rs485_Config(uint8_t fag);
//==========================================================
//	�������ƣ�	Rs485_Init
//
//	�������ܣ�	��ʼ��485
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rs485_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��

    GPIO_Initure.Pin = GPIO_PIN_8;		//PA8
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;//�������
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; //����
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    Rs485_Config(0);   					//����485Ϊ����ģʽ
    
	UART1_Init(115200);								//��ʼ������1    
}

//==========================================================
//	�������ƣ�	Rs485_Config
//
//	�������ܣ�	����485�շ�ģʽ
//
//	��ڲ�����	1(485����)   0(485����)
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rs485_Config(uint8_t fag)
{
	if(fag){
		RS485_TX_EN; //����485����
	}
	else
		RS485_RX_EN; //����485����
}

void Rs485_Send(uint8_t *pDat,uint8_t len)
{
    Rs485_Config(1);
    HAL_Delay(20);    
    HAL_UART_Transmit(&UART1_Handler,pDat,len,1000);
    HAL_Delay(20);
    Rs485_Config(0);    
}


