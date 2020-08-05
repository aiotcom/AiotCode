#include "stm32f1xx.h"
#include "usart.h"	
#include "Rs485.h"	
#include "timer.h"
#include "delay.h"
#include "WiFi.h"

#if UART1   //ʹ�ܽ���

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
unsigned char USART1_RX_BUF[USART1_REC_LEN];     	//���ջ���,���USART_REC_LEN���ֽ�.

unsigned int 	USART1_RX_STA=0;       							//����״̬���	  

unsigned char UART1_RxBuffer[UART1_RXBUFFERSIZE];	//HAL��ʹ�õĴ��ڽ��ջ���

UART_HandleTypeDef UART1_Handler; 								//UART���
  

//==========================================================
//	�������ƣ�	UART1_Init()
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
	UART1_Handler.Instance=USART1;					    			//USART1
	UART1_Handler.Init.BaudRate=bound;				    		//������
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; //�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    	//�շ�ģʽ
	HAL_UART_Init(&UART1_Handler);					    			//HAL_UART_Init()��ʹ��UART1
	
	HAL_UART_Receive_IT(&UART1_Handler, (unsigned char *)UART1_RxBuffer, UART1_RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
}

//==========================================================
//	�������ƣ�	USART1_IRQHandler()
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
			RS485_RX_EN();					//����485����
			Rs485_Receive(Res);			//����485���պ���
		}
	}
}

#endif

#if UART2

//����2�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
unsigned char  USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

unsigned int USART2_RX_STA=0;       							//����״̬���	  

uint8_t Temp = 0;																	//�¶�����
uint8_t Humi = 0;																	//ʪ������
uint8_t PIR_Sta = 0;															//�������״̬
uint8_t Flame_Sta = 0;														//���洫����״̬
uint8_t Shock_Sta = 0;														//�𶯴�����״̬
uint8_t Smoke_Value = 10;													//������������
uint16_t A_P_Data = 0;														//����ѹ������
uint16_t LDR_Data = 0;														//��ǿ����
uint16_t PM2_5_Data = 0;													//PM2.5����

uint8_t Send_OneNET[50];													//���͵���ƽ̨T��ʾ����

unsigned char UART2_RxBuffer[UART2_RXBUFFERSIZE];	//HAL��ʹ�õĴ��ڽ��ջ���

UART_HandleTypeDef UART2_Handler; 								//UART���


//==========================================================
//	�������ƣ�	UART2_Init()
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
	UART2_Handler.Instance=USART2;					    						//USART2
	UART2_Handler.Init.BaudRate=bound;				    					//������
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;   		//�ֳ�Ϊ8λ���ݸ�ʽ
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    			//һ��ֹͣλ
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    			//����żУ��λ
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   		//��Ӳ������
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    				//�շ�ģʽ
  UART2_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART2_Handler);					    						//HAL_UART_Init()��ʹ��UART1
	
	HAL_UART_Receive_IT(&UART2_Handler, (unsigned char *)UART2_RxBuffer, UART2_RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
  
}

//==========================================================
//	�������ƣ�	USART2_IRQHandler()
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
			if(WiFi_AT_STA)									//ATָ������
			{	
				USART2_Receive(Res);					//���ڶ����ݴ���
			}
			else														//ATָ��δ�������
			{
				USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
				USART2_RX_STA++;
				if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����		
			}
		}
	}
	HAL_UART_IRQHandler(&UART2_Handler);
}

//==========================================================
//	�������ƣ�	USART2_Receive()
//
//	�������ܣ�	���ڶ�����
//
//	��ڲ�����	data:���ڶ�����
//
//	���ز�����	��
//
//	˵����			֡ͷ��CG  ֡β��SW
//==========================================================
void USART2_Receive(uint8_t data)
{
	static uint8_t End_Flag 		= 0;	//֡β��־λ
	static uint8_t Header_Flag 	= 0;	//֡ͷ��־λ
	static uint8_t Receive_Flag = 0;	//���ձ�־λ

/*
*
*				֡ͷ����
*
*/
	/*֡ͷ1 ����֡ͷ�е�һ���ֽ�*/
	if(Header_Flag == 0 && data == 0x43)
	{
		Header_Flag = 1;
	}

	/*֡ͷ2 ����֡ͷ�еڶ����ֽ�*/
	else if(Header_Flag == 1 && data == 0x47)
	{
		USART2_RX_BUF[0] = 0x43;//������ֵ�浽����������
		USART2_RX_STA = 1;	//������������±�����
		Receive_Flag = 1;		//��ʼ�������ݱ�־λ
	}

	else Header_Flag = 0;
	
/*
*
*				����+֡β����
*
*/
	if(Receive_Flag)	//֡ͷ������ɣ�׼������֡β
	{
		if(USART2_RX_STA>=(USART2_REC_LEN-1))
		{
			End_Flag = 0;
			Receive_Flag = 0;
			USART2_RX_STA = 0;
		}
		
		USART2_RX_BUF[USART2_RX_STA++] = data;	//���ݽ���
	
		/*֡β1  ����֡β�е�һ���ֽ�*/
		if(!End_Flag && data == 0x53)
		{
			End_Flag = 1;
		}
		/*֡β2  ����֡β�еڶ����ֽ�*/
		else if(End_Flag && data == 0x57)
		{
			USART2_RX_STA = 0x8000;		//�������
			Receive_Flag = 0;
			End_Flag = 0;
		}

		/*���մ��� ���½���*/
		else End_Flag = 0;
	}
}

#endif


//==========================================================
//	�������ƣ�	HAL_UART_MspInit()
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
  /*	GPIO�˿�����	*/
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
			HAL_NVIC_SetPriority(USART1_IRQn,1,2);		//��ռ���ȼ�1�������ȼ�2
	#endif	
	}
  else if(huart->Instance==USART2)							//����Ǵ���2�����д���2 MSP��ʼ��
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
			HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   		//��ʼ��PA3
			
	#if EN_USART2_RX
			HAL_NVIC_EnableIRQ(USART2_IRQn);					//ʹ��USART2�ж�ͨ��
			HAL_NVIC_SetPriority(USART2_IRQn,1,1);		//��ռ���ȼ�1�������ȼ�1
	#endif	
  }
}


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
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
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (unsigned char) ch;
	return ch;
}
#endif

//==========================================================
//	�������ƣ�	WiFi_Send_Cmd()
//
//	�������ܣ�	��WiFi��������
//
//	��ڲ�����	waittime:�ȴ�ʱ��(��λ:ms)
//							cmd:���͵������ַ���
//							ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//
//	���ز�����	
//						����ֵ:	��0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       							0,����ʧ��
//
//	˵����		
//==========================================================
uint8_t* WiFi_Send_Cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime)
{
	static uint8_t len = 0;							//������ݳ���
	static uint16_t j = 0;
	char *strx=0;

	len = strlen((char *)cmd);					//��ȡ���ݳ���

	memset((void*)USART2_RX_BUF,0,USART2_REC_LEN);	//�������
	HAL_UART_Transmit(&UART2_Handler,cmd,len,1000);	//����2��������
	
	for(j=0;j<waittime;j++)
	{
		delay_ms(50);
		strx=strstr((const char*)USART2_RX_BUF,(const char*)ack);
		if(strx)
			break;
	}

	USART2_RX_STA=0;
	return (uint8_t*)strx;
}

//==========================================================
//	�������ƣ�	USART_Data_Send()
//
//	�������ܣ�	�������ݷ��ͺ���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����
//==========================================================
void USART_Data_Send(void)
{
	if(Task_Count>=200)	//200ms 	��ȡ�������״̬
	{
		Rs485_Send(Addr_WiFi,Addr_PIR,PIR_Get_State,0,0);
		Task_Count = 0;
	}

	if(Send_OneNET_Count>=500)
	{
		sprintf((char *)Send_OneNET,"Sensor:%d",PIR_Sta);
		HAL_UART_Transmit(&UART2_Handler,Send_OneNET,8,1000);	//�������ݵ���ƽ̨
		memset(Send_OneNET,0x30,10);
		Send_OneNET_Count = 0;
	}
}

//==========================================================
//	�������ƣ�	USART1_IRQHand()
//
//	�������ܣ�	����485����
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����				
//==========================================================
void USART1_IRQHand(void)
{
	if(!DataHandling_485(Addr_WiFi))			//485���ݴ���
	{
		switch(Rx_Stack.Src_Adr)
		{
			case Addr_PIR:		//�������ģ������
				PIR_Sta = Rx_Stack.Data[0];			//������⴫����״̬
				break;
			default: break;
		}
	}
}





