#include "timer.h"
#include "Rs485.h"	
#include "delay.h"
#include "Usart.h"
#include "M5310.h"
#include "nbiot.h"
#include "stm32f1xx.h"

uint8_t RFID_Data[30],Realy_State[10]={0x30};
uint16_t Command_Relay,Command_KEY,Command;	//���Ƽ̵��������롢���հ���ֵ�����롢����RFID����������
uint32_t Task_Count = 0,Task_Count2 = 0;		//��ʱ�������ֵ
TIM_HandleTypeDef TIM2_Handler; 		//��ʱ����� 

//==========================================================
//	�������ƣ�	TIM2_Init
//
//	�������ܣ�	ͨ�ö�ʱ��3�жϳ�ʼ��
//
//	��ڲ�����	arr���Զ���װֵ��
//              psc��ʱ��Ԥ��Ƶ��
//
//	���ز�����	��
//
//	˵����		��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.   Ft=��ʱ������Ƶ��,��λ:Mhz
//==========================================================
void TIM2_Init(unsigned int arr,unsigned int psc)
{  
    TIM2_Handler.Instance=TIM2;                          //ͨ�ö�ʱ��2
    TIM2_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM2_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM2_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM2_Handler); //ʹ�ܶ�ʱ��2�Ͷ�ʱ��2�����жϣ�TIM_IT_UPDATE   
}

//==========================================================
//	�������ƣ�	HAL_TIM_Base_MspInit
//
//	�������ܣ�	ʹ�ܶ�ʱ��
//
//	��ڲ�����	htim����ʱ��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //ʹ��TIM2ʱ��
		HAL_NVIC_SetPriority(TIM2_IRQn,1,1);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //����ITM2�ж�   
	}
}

//==========================================================
//	�������ƣ�	TIM2_IRQHandler
//
//	�������ܣ�	��ʱ��2�жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			 
//==========================================================
void TIM2_IRQHandler(void)
{
	Task_Count++;
	Task_Count2++;
	switch(Task_Count)
	{
		case 10:	//100ms 	��ȡ������̰���ֵ
			Rs485_Send(Addr_NB,Addr_Matrixkey,NB_QueryMatrixkey,0,"");
			break;
		case 20:	//200ms 	��ȡRFIDֵ
			Rs485_Send(Addr_NB,Addr_RFID,NB_RFID,0,"");
			break;
		case 30:	//300ms 	�������ݵ�TFT����ʾ
			if(Command_KEY)
			{
				Rs485_Send(Addr_NB,Addr_TFT,Command_KEY,0,"");
				Command_KEY = 0;
			}
			break;
		case 40:	//400ms 	�������ݵ�TFT����ʾ
			if(RFID_Data[0])
			{
				Rs485_Send(Addr_NB,Addr_TFT,RFID_All,20,RFID_Data);
				memset(RFID_Data,0,20);
			}
			break;
		case 50:	//500ms 	���Ϳ������TFT��
			Rs485_Send(Addr_NB,Addr_TFT,Command_Relay,0,"");
			break;
		case 60:	//600ms 	���Ƽ̵���
			Rs485_Send(Addr_NB,Addr_Relay,Command_Relay,0,"");
			switch(Command_Relay)
			{
				case Relay1_ON:	//����LOCK״̬����ƽ̨
					Realy_State[0] = 0x31;
					break;
				case Relay2_ON:	//����LOCK״̬����ƽ̨
					Realy_State[0] = 0x30;
					break;
				default: break;
			}
			Command_Relay = 0;
			Task_Count = 0;
			break;
		default: break;
	}
	
	switch(Task_Count2)
	{
		case 85:	//850ms 
			m5310_notify_upload(&Lock_uri,NBIOT_STRING,(char*)Realy_State,1,0);	//�ϴ�LOCK״̬
			break;
		case 155:	//1550ms 
			m5310_notify_upload(&RFID_uri,NBIOT_STRING,(char*)&SendData[0],1,0);	//�ϴ�RFID����
			Task_Count2 = 0;
			break;
		default: break;
	}
	
	HAL_TIM_IRQHandler(&TIM2_Handler);
}





