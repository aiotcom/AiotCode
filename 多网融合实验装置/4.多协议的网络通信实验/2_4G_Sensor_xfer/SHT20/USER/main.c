#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "TM1640.h"	
#include "SHT20.h"	
#include "delay.h"
#include "timer.h"
#include "Usart.h"
#include "RS485.h"
#include "ADC.h"
#include "USART.h"
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
*	˵���� 		��ʪ��ģ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
void RS485_HandlerCb(void); //485����ͨ�����������ɶ�ʱ��3�жϵ��ã��ڸú��������ݴ���ʱ�䲻�ܹ���
uint8_t SensorData[5];      //485�������ݷ��ͻ���
int main(void)
{
    HAL_Init();             					//��ʼ��HAL��  
	ADC_Init();									//��ʼ��ADC
    USART3_Init(115200);
	SHT2x_Init();								//��ʼ��SHT20
	TM1640_Init();								//��ʼ��TM1640
    Rs485_Init();
	TIM3_Init(10000-1,64-1,RS485_HandlerCb);	//��ʼ����ʱ���ж�����64M/64/10000/ = 100HZ
    
    printf("sht20:usart3 print\r\n");           //������Ϣ��ͨ��PB10 �ܽ����   
	while(1)
	{
		Display_Data();						    //��ȡ��ʪ�Ȳ���ʾ���������

        /*����������ֵת�������飬����ͨ��485���߷���*/
        SensorData[0] = g_sht2x_param.TEMP_POLL;        
        SensorData[1] = g_sht2x_param.HUMI_HM;
        SensorData[2] = (uint8_t)LDR_Data;
        SensorData[3] = (uint8_t)(LDR_Data>>8);          
	}
}
//==========================================================
//	�������ƣ�	void RS485_HandlerCb(void)
//
//	�������ܣ�	ͨ��485���߻�ȡ���ݴ�����
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		����ͨ��485���߷��͹�������������
//==========================================================
void RS485_HandlerCb(void)
{  
    if((!DataHandling_485(Addr_SHT20))&&(SHT20_Get_All == Rx_Stack.Command))
    {
        Rs485_Send(Addr_SHT20,Addr_2_4G,SHT20_All,4,SensorData);
    }        
}




