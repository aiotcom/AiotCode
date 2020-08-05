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

uint8_t Send_Lcd[30];															//���͵�LCD��������
uint8_t Send_OneNET[30];													//���͵�OneNET��ʾ����
uint8_t Matrixkey_Data[20];												//��Ű���ֵ

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
			Usart2_Rx_Flag = 1;
			RX_Count = 0;		//�������ֵ

			USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
			USART2_RX_STA++;
			if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����		
		}
	}
	HAL_UART_IRQHandler(&UART2_Handler);
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
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
    USART2->DR = (unsigned char) ch;
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
	if(Task_Count>=80)	//80ms 	��ȡ������̰�������
	{
		Rs485_Send(Addr_WiFi,Addr_Matrixkey,Matrixkey_Get_value,0,0);
		Task_Count = 0;
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
	static uint8_t Key_Count = 0;

	if(!DataHandling_485(Addr_WiFi))				//485���ݴ���
	{
		if(Rx_Stack.Src_Adr == Addr_Matrixkey)//���հ���ֵ
		{
			switch(Rx_Stack.Command)
			{
				case Matrixkey0:	//����0
					Send_Lcd[Key_Count] = 0x30;
				break;
				case Matrixkey1:	//����1
					Send_Lcd[Key_Count] = 0x31;
				break;
				case Matrixkey2:	//����2
					Send_Lcd[Key_Count] = 0x32;
				break;
				case Matrixkey3:	//����3
					Send_Lcd[Key_Count] = 0x33;
				break;
				case Matrixkey4:	//����4
					Send_Lcd[Key_Count] = 0x34;
				break;
				case Matrixkey5:	//����5
					Send_Lcd[Key_Count] = 0x35;
				break;
				case Matrixkey6:	//����6
					Send_Lcd[Key_Count] = 0x36;
				break;
				case Matrixkey7:	//����7
					Send_Lcd[Key_Count] = 0x37;
				break;
				case Matrixkey8:	//����8
					Send_Lcd[Key_Count] = 0x38;
				break;
				case Matrixkey9:	//����9
					Send_Lcd[Key_Count] = 0x39;
				break;
				case MatrixkeyEnter:	//����Enter
					HAL_UART_Transmit(&UART2_Handler,Send_Lcd,strlen((char *)Send_Lcd),2000);			//�������ݵ���ƽ̨
					memset(Matrixkey_Data,0,20);	//��������
					Key_Count = 0;	//����ֵ����
					Key_Count--;
				break;
				case MatrixkeyCanel:	//����Canel
					memset(Send_Lcd,' ',20);
					Rs485_Send(Addr_WiFi,Addr_LCD,LCD_Display,20,Send_Lcd);	//�������ݵ�LCD��
					memset(Matrixkey_Data,0,20);	//��������
					Key_Count = 0;	//����ֵ����
					Key_Count--;
				break;
				case MatrixkeyUP:			//����UP
					Send_Lcd[Key_Count] = 0x3C;
				break;
				case MatrixkeyDown:		//����Down
					Send_Lcd[Key_Count] = 0x3D;
				break;
				case MatrixkeyLeft:		//����Left
					Send_Lcd[Key_Count] = 0x3E;
				break;
				case MatrixkeyRight:	//����Right
					Send_Lcd[Key_Count] = 0x3F;
				break;
				default:break;
			}
			Rs485_Send(Addr_WiFi,Addr_LCD,LCD_Display,strlen((char *)Send_Lcd),Send_Lcd);	//�������ݵ�LCD��
			Key_Count++;	//����ֵ�ۼ�
		}
	}
}

//==========================================================
//	�������ƣ�	USART2_IRQHand()
//
//	�������ܣ�	�����ڶ�����
//
//	��ڲ�����	huart:���ھ��
//              
//	���ز�����	��
//
//	˵����			
//==========================================================
void USART2_IRQHand(void)
{
	if(USART2_RX_STA == 0x8000)
	{
		Rs485_Send(Addr_WiFi,Addr_LCD,LED_Control,strlen((char *)USART2_RX_BUF),USART2_RX_BUF);	//�������ݵ�LCD��
		Usart2_Rx_Flag = 0;
		RX_Count = 0;		//�������ֵ 
		memset((void*)USART2_RX_BUF,0,10);	//�������
		USART2_RX_STA = 0;
	}
}




