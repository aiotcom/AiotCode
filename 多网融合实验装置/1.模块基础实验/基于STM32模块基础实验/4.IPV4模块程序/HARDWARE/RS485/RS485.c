#include "RS485.h"	
#include "USART.h"
#include "delay.h"
//==========================================================
//	�������ƣ�	RS485_Init
//
//	�������ܣ�	��ʼ��485
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void RS485_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;    

    __HAL_RCC_GPIOA_CLK_ENABLE();           				    //����GPIOAʱ��

    GPIO_Initure.Pin = GPIO_PIN_8;							    //PA8
    GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;				    //�������
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; 					//����
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    RS485_RX_EN;	                                            //����RS485���ڽ���ģʽ
    
    UART1_Init(115200);                                         //��ʼ������1�����õ���UART1תRS485ģʽ
}
//==========================================================
//	�������ƣ�	RS485_Send()
//
//	�������ܣ�	ͨ��RS485���߷�������
//
//	��ڲ�����	uint8_t *pdata,ָ��ȴ��������ݵ�ָ�룬uint8_t len�ȴ����͵����ݳ���
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void RS485_Send(uint8_t *pdata,uint8_t len)
{
    RS485_TX_EN;                  //����RS485����ģʽ
    delay_us(10);                  //�ȴ�����ģʽ�������
    USART1_SendStream(pdata,len);
    delay_us(300); 
    RS485_RX_EN;                  //���ݷ�����ɺ󣬽������ģʽ   
}
//==========================================================
//	�������ƣ�	RS485_Send()
//
//	�������ܣ�	ͨ��RS485���߷�������
//
//	��ڲ�����	uint8_t *pdata,ָ��ȴ��������ݵ�ָ�룬uint8_t len�ȴ����͵����ݳ���
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void RS485_Printf(uint8_t *pdata,uint32_t Data)
{
    RS485_TX_EN;                  //����RS485����ģʽ
    delay_us(10);                  //�ȴ�����ģʽ�������
    printf((const char*)pdata,Data);
    delay_us(300); 
    RS485_RX_EN;                  //���ݷ�����ɺ󣬽������ģʽ   
}

