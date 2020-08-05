#include "ADC.h"
#include "Rs485.h"	
#include "timer.h"
#include "delay.h"
#include "Usart.h"
#include "delay.h"
#include "SHT20.h"	
#include "TM1640.h"	

#if UART1   																			//ʹ�ܽ���

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
unsigned char  USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

unsigned int USART1_RX_STA=0;       							//����״̬���	  

unsigned char UART1_RxBuffer[UART1_RXBUFFERSIZE];	//HAL��ʹ�õĴ��ڽ��ջ���

uint16_t LDR_Data = 0;														//��ǿ����

UART_HandleTypeDef UART1_Handler; 								//UART���
  
//==========================================================
//	�������ƣ�	UART1_Init
//
//	�������ܣ�	����1��ʼ��
//
//	��ڲ�����	bound:������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void UART1_Init(int bound)
{	
	//UART ��ʼ������
	UART1_Handler.Instance=USART1;					    				//USART1
	UART1_Handler.Init.BaudRate=bound;				    			//������
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	   		//һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    	//����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    		//�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);					    				//HAL_UART_Init()��ʹ��UART1
	
	HAL_UART_Receive_IT(&UART1_Handler, (unsigned char *)UART1_RxBuffer, UART1_RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
  
}


//==========================================================
//	�������ƣ�	USART1_IRQHandler
//
//	�������ܣ�	����1�жϷ������
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART1_IRQHandler(void)                	
{ 
	static unsigned char Res = 0;

	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�
	{
		Res=USART1->DR; 
		if(USART1_RX_STA!=0x8000)
		{
			Rs485_Receive(Res);	//����485���պ���
		}
	}
	
	HAL_UART_IRQHandler(&UART1_Handler);	
} 

#endif

#if UART2

//����2�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
unsigned char  USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

unsigned int USART2_RX_STA=0;       							//����״̬���	  

unsigned char UART2_RxBuffer[UART2_RXBUFFERSIZE];	//HAL��ʹ�õĴ��ڽ��ջ���

UART_HandleTypeDef UART2_Handler; 								//UART���

  
//==========================================================
//	�������ƣ�	UART2_Init
//
//	�������ܣ�	����2��ʼ��
//
//	��ڲ�����	bound:������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void UART2_Init(int bound)
{	
	//UART ��ʼ������
	UART2_Handler.Instance=USART2;					    								//USART1
	UART2_Handler.Init.BaudRate=bound;				    							//������
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   				//�ֳ�Ϊ8λ���ݸ�ʽ
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    					//һ��ֹͣλ
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    					//����żУ��λ
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   				//��Ӳ������
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    						//�շ�ģʽ
  UART2_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART2_Handler);					    								//HAL_UART_Init()��ʹ��UART1
	
	HAL_UART_Receive_IT(&UART2_Handler, (unsigned char *)UART2_RxBuffer, UART2_RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
  
}

//==========================================================
//	�������ƣ�	USART2_IRQHandler
//
//	�������ܣ�	����2�жϷ������
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART2_IRQHandler(void)                	
{ 
	unsigned char Res;

	if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�
	{
		Res=USART2->DR; 
		if((USART2_RX_STA&0x8000)==0)			//����δ���
		{
			if(USART2_RX_STA&0x4000)				//���յ���0x62
			{
				if(Res!=0x63)USART2_RX_STA=0;	//���մ���,���¿�ʼ
				else USART2_RX_STA|=0x8000;		//��������� 
			}
			else 														//��û�յ�0X62
			{	
				if(Res==0x62)USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}	   		 
	}
	
	HAL_UART_IRQHandler(&UART2_Handler);	
} 

#endif


//==========================================================
//	�������ƣ�	HAL_UART_MspInit
//
//	�������ܣ�	UART�ײ��ʼ����ʱ��ʹ�ܣ��������ã��ж�����
//
//	��ڲ�����	huart:���ھ��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  //GPIO�˿�����
	GPIO_InitTypeDef GPIO_Initure;
    
	if (huart->Instance==USART1)   								//����Ǵ���1�����д���1 MSP��ʼ��
	{
			__HAL_RCC_GPIOA_CLK_ENABLE();							//ʹ��GPIOAʱ��
			__HAL_RCC_USART1_CLK_ENABLE();						//ʹ��USART1ʱ��
			__HAL_RCC_AFIO_CLK_ENABLE();

			GPIO_Initure.Pin=GPIO_PIN_9;							//PA9
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;				//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;						//����
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	//����
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		//��ʼ��PA9

			GPIO_Initure.Pin=GPIO_PIN_10;							//PA10
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;			//ģʽҪ����Ϊ��������ģʽ��	
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		//��ʼ��PA10
			
	#if EN_USART1_RX
			HAL_NVIC_EnableIRQ(USART1_IRQn);					//ʹ��USART1�ж�ͨ��
			HAL_NVIC_SetPriority(USART1_IRQn,1,1);		//��ռ���ȼ�1�������ȼ�1
	#endif	
	}
  else if(huart->Instance==USART2)								//����Ǵ���2�����д���2 MSP��ʼ��
	{
			__HAL_RCC_GPIOA_CLK_ENABLE();							//ʹ��GPIOAʱ��
			__HAL_RCC_USART2_CLK_ENABLE();						//ʹ��USART2ʱ��
			
		 // __HAL_RCC_AFIO_CLK_ENABLE();

			GPIO_Initure.Pin=GPIO_PIN_2;							//PA2
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;				//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;						//����
			GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;	//����
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		//��ʼ��PA2

			GPIO_Initure.Pin=GPIO_PIN_3;							//PA3
			GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;			//ģʽҪ����Ϊ��������ģʽ��	
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	  		//��ʼ��PA3
				
		#if EN_USART2_RX
			HAL_NVIC_EnableIRQ(USART2_IRQn);					//ʹ��USART2�ж�ͨ��
			HAL_NVIC_SetPriority(USART2_IRQn,1,2);		//��ռ���ȼ�1�������ȼ�2
		#endif	
    }
}

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0); //ѭ������,ֱ���������   
	USART1->DR = (uint8_t) ch;  
	
	return ch;
}
#endif

//==========================================================
//	�������ƣ�	Display_Data
//
//	�������ܣ�	��ȡ��ʪ�����ݲ���ʾ�������
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void Display_Data(void)
{
	static uint8_t Display_Flag = 0;						//��ʾ��־λ

	SHT2x_GetTempHumi(); 								//��ȡ��ʪ��ֵ
	LDR_Data = Get_Adc_Average(ADC_CHANNEL_0,50);  		//��ȡ����ǿ��
	Temp[0] = g_sht2x_param.TEMP_HM;		//�¶�����
	Humi[0] = g_sht2x_param.HUMI_HM;		//ʪ������
	Light[0] = LDR_Data>>8;							//��ǿ����
	Light[1] = LDR_Data;								//��ǿ����
	Sum_Data[0] = g_sht2x_param.TEMP_HM;//�¶�����
	Sum_Data[1] = g_sht2x_param.HUMI_HM;//ʪ������
	Sum_Data[2] = LDR_Data>>8;					//��ǿ����
	Sum_Data[3] = LDR_Data;							//��ǿ����

	if(Display_Count>=80 && Display_Flag == 0)				//1600ms ��ʾ�¶�
	{
		Display_Flag = 1;
		send_LED_Display(0xC0,g_sht2x_param.TEMP_HM,1);
	}
	else if(Display_Count>=160 && Display_Flag == 1)	//3200ms ��ʾʪ��
	{
		Display_Flag = 2;
		send_LED_Display(0xC0,g_sht2x_param.HUMI_HM,2);
	}
	else if(Display_Count>=240 && Display_Flag == 2)	//4800ms ��ʾ��ǿ
	{
		send_LED_Display(0xC0,LDR_Data,3);							
		Display_Count = 0;
		Display_Flag = 0;
	}
}






