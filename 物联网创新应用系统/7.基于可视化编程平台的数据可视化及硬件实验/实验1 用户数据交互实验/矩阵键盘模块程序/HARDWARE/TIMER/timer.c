#include "Martix_Key.h"
#include "stm32f1xx.h"
#include "timer.h"
#include "Usart.h"
#include "delay.h"
#include "Rs485.h"

TIM_HandleTypeDef TIM3_Handler;      	//��ʱ����� 
	
//==========================================================
//	�������ƣ�	TIM3_Init
//
//	�������ܣ�	ͨ�ö�ʱ��3�жϳ�ʼ��
//
//	��ڲ�����	
//							arr���Զ���װֵ��
//							psc��ʱ��Ԥ��Ƶ��
//							��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//							Ft=��ʱ������Ƶ��,��λ:Mhz
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void TIM3_Init(uint16_t arr,uint16_t psc)
{  
    TIM3_Handler.Instance=TIM3;                          //ͨ�ö�ʱ��3
    TIM3_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM3_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE   
}

//==========================================================
//	�������ƣ�	HAL_TIM_Base_MspInit
//
//	�������ܣ�	��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
//
//	��ڲ�����	
//
//	���ز�����	��
//
//	˵����			�˺����ᱻHAL_TIM_Base_Init()��������
//==========================================================
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,1,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //����ITM3�ж�   
	}
}

//==========================================================
//	�������ƣ�	TIM3_IRQHandler
//
//	�������ܣ�	��ʱ��3�жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void TIM3_IRQHandler(void)
{
	if(!DataHandling_485(Addr_Matrixkey)) //���յ�����󷵻ذ���ֵ
	{
		if(Key_value)
		{
			Rs485_Send(Addr_Matrixkey,Rx_Stack.Src_Adr,Key_value,0,0);
			Key_value = 0;
		}
	}
	
//	if(Key_value)
//	{
//		switch(Key_value)
//		{
//			case Matrixkey0:
//				printf("KEY-Value:0\r\n");
//			break;
//			case Matrixkey1:
//				printf("KEY-Value:1\r\n");
//			break;
//			case Matrixkey2:
//				printf("KEY-Value:2\r\n");
//			break;
//			case Matrixkey3:
//				printf("KEY-Value:3\r\n");
//			break;
//			case Matrixkey4:
//				printf("KEY-Value:4\r\n");
//			break;
//			case Matrixkey5:
//				printf("KEY-Value:5\r\n");
//			break;
//			case Matrixkey6:
//				printf("KEY-Value:6\r\n");
//			break;
//			case Matrixkey7:
//				printf("KEY-Value:7\r\n");
//			break;
//			case Matrixkey8:
//				printf("KEY-Value:8\r\n");
//			break;
//			case Matrixkey9:
//				printf("KEY-Value:9\r\n");
//			break;
//			case MatrixkeyEnter:
//				printf("KEY-Value:Enter\r\n");
//			break;
//			case MatrixkeyCanel:
//				printf("KEY-Value:Canel\r\n");
//			break;
//			case MatrixkeyUP:
//				printf("KEY-Value:UP\r\n");
//			break;
//			case MatrixkeyDown:
//				printf("KEY-Value:Down\r\n");
//			break;
//			case MatrixkeyLeft:
//				printf("KEY-Value:Left\r\n");
//			break;
//			case MatrixkeyRight:
//				printf("KEY-Value:Right\r\n");
//			break;
//			default:break;
//		}
//		Key_value = 0;
//	}
	
  HAL_TIM_IRQHandler(&TIM3_Handler);
}










