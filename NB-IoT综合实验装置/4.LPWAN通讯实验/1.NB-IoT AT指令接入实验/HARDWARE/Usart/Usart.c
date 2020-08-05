#include "stm32f1xx.h"
#include "usart.h"	
#include "Rs485.h"	
#include "delay.h"

#if UART1   //ʹ�ܽ���

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
unsigned char  USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

unsigned int USART1_RX_STA=0;       							//����״̬���	  

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
			Rs485_Receive(Res);			//����485���պ���
		}
	}
}

#endif

#if UART2

//����2�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
//����2�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
//unsigned char  USART2_RX_BUF[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

//unsigned int USART2_RX_STA=0;       //����״̬���	  

//unsigned char UART2_RxBuffer[UART2_RXBUFFERSIZE];//HAL��ʹ�õĴ��ڽ��ջ���

UART_HandleTypeDef UART2_Handler; //UART���


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
	UART2_Handler.Instance          = USART2;					    	//USART1
	UART2_Handler.Init.BaudRate     = bound;				    		//������
	UART2_Handler.Init.WordLength   = UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART2_Handler.Init.StopBits     = UART_STOPBITS_1;	    //һ��ֹͣλ
	UART2_Handler.Init.Parity       = UART_PARITY_NONE;		  //����żУ��λ
	UART2_Handler.Init.HwFlowCtl    = UART_HWCONTROL_NONE;  //��Ӳ������
	UART2_Handler.Init.Mode         = UART_MODE_TX_RX;		  //�շ�ģʽ
  UART2_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART2_Handler);					    						//HAL_UART_Init()��ʹ��UART1	

	/* Process Unlocked */
	__HAL_UNLOCK(&UART2_Handler);

	/* Enable the UART Parity Error Interrupt */
	__HAL_UART_ENABLE_IT(&UART2_Handler, UART_IT_PE);

	/* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
	__HAL_UART_ENABLE_IT(&UART2_Handler, UART_IT_ERR);

	/* Enable the UART Data Register not empty Interrupt */
	__HAL_UART_ENABLE_IT(&UART2_Handler, UART_IT_RXNE);    
}

//==========================================================
//	�������ƣ�	USART2_SendBytes()
//
//	�������ܣ�	ͨ������2����ָ��ȵ����ݡ�
//
//	��ڲ�����	uint8_t  *pdata,ָ�򽫷������ݵ�ָ�롣
//              uint16_t lenght,�����͵����ݳ��ȡ�
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART2_SendBytes(char *pdata,uint16_t lenght)
{
    while(lenght)
    {
        while((USART2->SR&0X40) == 0);  //USART_FLAG_TC ������ɱ�־
        USART2->DR = *pdata;   //��USART2��DR�Ĵ���д�����ݣ��������� 
        pdata++;
        lenght--;
    }
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
//void USART2_IRQHandler(void)
//{
//	unsigned char Res;

//	if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�
//	{
//		Res=USART2->DR; 
//		if((USART2_RX_STA&0x8000)==0)			//����δ���
//		{
//			if(WiFi_AT_STA)									//ATָ������
//			{	
//				USART2_Receive(Res);					//���ڶ����ݴ���
//			}
//			else														//ATָ��δ�������
//			{
//				USART2_RX_BUF[USART2_RX_STA&0X3FFF]=Res ;
//				USART2_RX_STA++;
//				if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����		
//			}
//		}
//	}
//	HAL_UART_IRQHandler(&UART2_Handler);
//}

 //==========================================================
//	�������ƣ�	USART2_IRQHandler
//
//	�������ܣ�	����2���жϴ��������
//
//	��ڲ�����	��
//
//	���ز�����	��
// 
//	˵����		
//==========================================================
uint8_t USART2_RecvBuffer[USART2_RECV_BUFFER_LENGTH]={0};
uint16_t USART2_RecvIndex =0;
void USART2_IRQHandler(void)
{
    if((__HAL_UART_GET_FLAG(&UART2_Handler, UART_FLAG_RXNE) != RESET))
    { //USART2�������ݼĴ����ǿգ�����������
        USART2_RecvBuffer[USART2_RecvIndex++] = (uint8_t)UART2_Handler.Instance->DR;//��ȡ���ݼĴ����е����ݡ�

        if((USART2_RecvIndex>=2)&&(USART2_RecvBuffer[USART2_RecvIndex-2] == '\r')&&(USART2_RecvBuffer[USART2_RecvIndex-1] == '\n'))
        {
            USART2_RecvIndex = 0;
        }
        if(USART2_RecvIndex >= (USART2_RECV_BUFFER_LENGTH-1))
        {//USART2_RecvIndex ���ڻ��ߵ���USART2_RECV_BUFFER_LENGTH������USART2_RecvBuffer[]���ݵķ�Χ
            USART2_RecvIndex = 0;
        }
    }
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
//	˵����		
//==========================================================
//void USART2_Receive(uint8_t data)
//{
//	static uint8_t End_Flag 		= 0;	//֡β��־λ
//	static uint8_t Header_Flag 	= 0;	//֡ͷ��־λ
//	static uint8_t Receive_Flag = 0;	//���ձ�־λ

///*
//*
//*				֡ͷ����
//*
//*/
//	/*֡ͷ1 ����֡ͷ�е�һ���ֽ�*/
//	if(Header_Flag == 0 && data == 0x7E)
//	{
//		USART2_RX_BUF[0] = data;
//		Header_Flag = 1;
//	}

//	/*֡ͷ2 ����֡ͷ�еڶ����ֽ�*/
//	else if(Header_Flag == 1 && data == 0x7E)
//	{
//		USART2_RX_STA = 1;	//������������±�����
//		Receive_Flag = 1;		//��ʼ�������ݱ�־λ
//	}

//	else Header_Flag = 0;
//	
///*
//*
//*				����+֡β����
//*
//*/
//	if(Receive_Flag)	//֡ͷ�������
//	{
//		if(USART2_RX_STA>=499)
//		{
//			End_Flag = 0;
//			Receive_Flag = 0;
//			USART1_RX_STA = 0;
//		}
//		
//		USART2_RX_BUF[USART2_RX_STA++] = data;	//���ݽ���
//	
//		/*֡β1  ����֡β�е�һ���ֽ�*/
//		if(data == 0xE7)	End_Flag = 1;

//		/*֡β2  ����֡β�еڶ����ֽ�*/
//		else if(End_Flag == 1 && data == 0xE7)
//		{
//			USART2_RX_STA = 0x8000;		//�������
//			Receive_Flag = 0;
//			End_Flag = 0;
//		}

//		/*���մ��� ���½���*/
//		else End_Flag = 0;
//	}
//}

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
			HAL_NVIC_SetPriority(USART1_IRQn,1,1);		//��ռ���ȼ�1�������ȼ�1
	#endif	
	}
  else if(huart->Instance==USART2)							//����Ǵ���2�����д���2 MSP��ʼ��
	{
				__HAL_RCC_GPIOA_CLK_ENABLE();						//ʹ��GPIOAʱ��
				__HAL_RCC_USART2_CLK_ENABLE();					//ʹ��USART2ʱ��
				
			 // __HAL_RCC_AFIO_CLK_ENABLE();

				GPIO_Initure.Pin=GPIO_PIN_2;						//PA2
				GPIO_Initure.Mode=GPIO_MODE_AF_PP;			//�����������
				GPIO_Initure.Pull=GPIO_PULLUP;					//����
				GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//����
				HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA2

				GPIO_Initure.Pin=GPIO_PIN_3;						//PA3
				GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;		//ģʽҪ����Ϊ��������ģʽ��	
				HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA3
				
		#if EN_USART2_RX
				HAL_NVIC_EnableIRQ(USART2_IRQn);				//ʹ��USART2�ж�ͨ��
				HAL_NVIC_SetPriority(USART2_IRQn,1,2);	//��ռ���ȼ�1�������ȼ�2
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


////==========================================================
////	�������ƣ�	WiFi_Send_Cmd()
////
////	�������ܣ�	��WiFi��������
////
////	��ڲ�����	waittime:�ȴ�ʱ��(��λ:ms)
////							cmd:���͵������ַ���
////							ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
////
////	���ز�����	
////						����ֵ:	��0,���ͳɹ�(�õ����ڴ���Ӧ����)
////       							0,����ʧ��
////
////	˵����		
////==========================================================
//uint8_t* WiFi_Send_Cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime)
//{
//	static uint8_t len = 0;							//������ݳ���
//	static uint32_t j = 0,i = 0;
//	char *strx=0;
//	
//	len = strlen((char *)cmd);					//��ȡ���ݳ���
//	
//	HAL_UART_Transmit(&UART2_Handler,cmd,len,1000);//����2��������
//	
//	for(j=0;j<waittime;j++)
//	{
//		delay_ms(50);
//		strx=strstr((const char*)USART2_RX_BUF,(const char*)ack);
//		if(strx)
//			break;
//	}
//	
//	for(i = 0;i<USART2_REC_LEN;i++){
//		USART2_RX_BUF[i] = 0;							//�������
//	}
//	USART2_RX_STA=0;
//	return (uint8_t*)strx;
//}

////==========================================================
////	�������ƣ�	USART2_IRQHand()
////
////	�������ܣ�	������2����
////
////	��ڲ�����	huart:���ھ��
////              
////	���ز�����	��
////
////	˵����				
////==========================================================
//void USART2_IRQHand(void)
//{
//	static uint16_t i = 0;

//	if(USART2_RX_STA == 0x8000)
//	{
//		Command = USART2_RX_BUF[2]*256+USART2_RX_BUF[3];
//		
////		switch(Command)
////		{
////			case FAN_OFF:
////				Data_TFT[0] = 0;
////				break;
////			case FAN_ON1:
////				Data_TFT[0] = 1;
////				break;
////			case FAN_ON2:
////				Data_TFT[0] = 2;
////				break;
////			case FAN_ON3:
////				Data_TFT[0] = 3;
////				break;
////			default:break;
////		}
//		
//		for(i=0;i<USART2_REC_LEN;i++)
//		{
//			USART2_RX_BUF[i] = 0;
//		}
//		USART2_RX_STA = 0;
//	}
//}




