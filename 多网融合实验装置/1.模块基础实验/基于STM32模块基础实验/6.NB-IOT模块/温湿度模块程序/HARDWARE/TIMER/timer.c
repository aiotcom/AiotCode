#include "ADC.h"
#include "timer.h"
#include "Usart.h"
#include "SHT20.h"	
#include "Rs485.h"

uint32_t Display_Count = 0;					//�������ʾ����ֵ
uint8_t Temp[10],Humi[10],Light[10],Sum_Data[10];//�¶ȡ�ʪ�ȡ���ǿ�����ݼ���
TIM_HandleTypeDef TIM3_Handler;   	//��ʱ����� 

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
	Display_Count++;
	if(!DataHandling_485(Addr_SHT20))		//����485����
	{
		switch(Rx_Stack.Command)
		{
			case SHT20_Get_Temp:	//��ȡ�¶�����
				Rs485_Send(Addr_SHT20,Rx_Stack.Src_Adr,SHT20_Temp,1,Temp);		//�����¶�����
				break;
			case SHT20_Get_Humi:	//��ȡʪ������
				Rs485_Send(Addr_SHT20,Rx_Stack.Src_Adr,SHT20_Humi,1,Humi);		//����ʪ������
				break;
			case SHT20_Get_Light:	//��ȡ��ǿ����
				Rs485_Send(Addr_SHT20,Rx_Stack.Src_Adr,SHT20_Light,2,Light);	//���͹�ǿ����
				break;
			case SHT20_Get_All:		//��ȡ��ʪ��+��ǿ����
				Rs485_Send(Addr_SHT20,Rx_Stack.Src_Adr,SHT20_All,4,Sum_Data);	//������ʪ��+��ǿ����
				break;
			default:break;
		}
	}
	HAL_TIM_IRQHandler(&TIM3_Handler);
}









