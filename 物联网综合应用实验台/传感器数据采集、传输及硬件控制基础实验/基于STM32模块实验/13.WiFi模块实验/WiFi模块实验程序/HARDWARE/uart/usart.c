#include "usart.h"	
#include "delay.h"
#include "Rs485.h"
#include "timer.h"
#include "WiFi.h"

#if UART1

//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
unsigned char  USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

unsigned int USART1_RX_STA=0;       							//����״̬���	  

uint8_t Temp = 0;																	//�¶�����
uint8_t Humi = 0;																	//ʪ������
uint8_t Send_OneNET[30];													//���͵�OneNET��ʾ����

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
	UART1_Handler.Instance=USART1;					    						//USART1
	UART1_Handler.Init.BaudRate=bound;				    					//������
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   		//�ֳ�Ϊ8λ���ݸ�ʽ
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    			//һ��ֹͣλ
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    			//����żУ��λ
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   		//��Ӳ������
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    				//�շ�ģʽ
  UART1_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART1_Handler);					    						//HAL_UART_Init()��ʹ��UART1

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
	unsigned char Res;

	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�
	{
		Res=USART1->RDR; 
		if((USART1_RX_STA&0x8000)==0)			//����δ���
		{
			if(WiFi_AT_STA)									//ATָ������
			{	
				USART1_Receive(Res);					//����1���ݴ���
			}
			else														//ATָ��δ�������
			{
				USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
				USART1_RX_STA++;
				if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����		
			}
		}
	}
	HAL_UART_IRQHandler(&UART1_Handler);
}

//==========================================================
//	�������ƣ�	USART1_Receive()
//
//	�������ܣ�	����1����
//
//	��ڲ�����	data:����1����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART1_Receive(uint8_t data)
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
		USART1_RX_BUF[0] = 0x43;//������ֵ�浽����������
		USART1_RX_STA = 1;	//������������±�����
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
		if(USART1_RX_STA>=(USART1_REC_LEN-1))
		{
			End_Flag = 0;
			Receive_Flag = 0;
			USART1_RX_STA = 0;
		}
		
		USART1_RX_BUF[USART1_RX_STA++] = data;	//���ݽ���
	
		/*֡β1  ����֡β�е�һ���ֽ�*/
		if(!End_Flag && data == 0x53)
		{
			End_Flag = 1;
		}
		/*֡β2  ����֡β�еڶ����ֽ�*/
		else if(End_Flag && data == 0x57)
		{
			USART1_RX_STA = 0x8000;		//�������
			Receive_Flag = 0;
			End_Flag = 0;
		}

		/*���մ��� ���½���*/
		else End_Flag = 0;
	}
}

#endif


#if USART7

//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
unsigned char  USART7_RX_BUF[USART7_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

unsigned int USART7_RX_STA=0;       //����״̬���	  

unsigned char UART7_RxBuffer[UART7_RXBUFFERSIZE];//HAL��ʹ�õĴ��ڽ��ջ���

UART_HandleTypeDef UART7_Handler; //UART���

  
//==========================================================
//	�������ƣ�	UART7_Init
//
//	�������ܣ�	����7��ʼ��
//
//	��ڲ�����	bound:������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void UART7_Init(int bound)
{	
	//UART ��ʼ������
	UART7_Handler.Instance = UART7;					    				//UART7
	UART7_Handler.Init.BaudRate=bound;				    			//������
	UART7_Handler.Init.WordLength=UART_WORDLENGTH_8B;   //�ֳ�Ϊ8λ���ݸ�ʽ
	UART7_Handler.Init.StopBits=UART_STOPBITS_1;	    	//һ��ֹͣλ
	UART7_Handler.Init.Parity=UART_PARITY_NONE;		    	//����żУ��λ
	UART7_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   //��Ӳ������
	UART7_Handler.Init.Mode=UART_MODE_TX_RX;		    		//�շ�ģʽ
  UART7_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART7_Handler);					    				//HAL_UART_Init()��ʹ��UART7
	
	HAL_UART_Receive_IT(&UART7_Handler, (unsigned char *)UART7_RxBuffer, UART7_RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
	
	RS485_TX_EN();
	delay_ms(5);
	printf("��ӭʹ�÷䳲�׼�--����ͨ��ʵ��\r\n");
	delay_ms(5);
	RS485_RX_EN();
}

//==========================================================
//	�������ƣ�	UART7_IRQHandler
//
//	�������ܣ�	����7�жϷ������
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void UART7_IRQHandler(void)
{
	static unsigned char Res = 0;
	
	if((__HAL_UART_GET_FLAG(&UART7_Handler,UART_FLAG_RXNE)!=RESET))  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res=UART7->RDR; 
		if((USART7_RX_STA&0x8000)==0)			//����δ���
		{
			if(USART7_RX_STA&0x4000)				//���յ���0x0d
			{
				if(Res!=0x0a)USART7_RX_STA=0;	//���մ���,���¿�ʼ
				else USART7_RX_STA|=0x8000;		//��������� 
			}
			else //��û�յ�0X0D
			{
				if(Res==0x0d)USART7_RX_STA|=0x4000;
				else
				{
					USART7_RX_BUF[USART7_RX_STA&0X3FFF]=Res;
					USART7_RX_STA++;
					if(USART7_RX_STA>(USART7_REC_LEN-1))USART7_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}   		 
	}
	HAL_UART_IRQHandler(&UART7_Handler);	
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

    GPIO_Initure.Pin = GPIO_PIN_9|GPIO_PIN_10;//PA9��PA10
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;			//�����������
    GPIO_Initure.Pull = GPIO_NOPULL;					//��������
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//����
    GPIO_Initure.Alternate = GPIO_AF7_USART1;	//����ΪUART1
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);			//PA9��PA10
		
#if EN_USART1_RX
		HAL_NVIC_EnableIRQ(USART1_IRQn);					//ʹ��USART1�ж�ͨ��
		HAL_NVIC_SetPriority(USART1_IRQn,1,2);		//��ռ���ȼ�1�������ȼ�2
#endif	
	}
	else if(huart->Instance==UART7)							//����Ǵ���7�����д���7MSP��ʼ��
	{
		__HAL_RCC_GPIOF_CLK_ENABLE();							//ʹ��GPIOFʱ��
		__HAL_RCC_UART7_CLK_ENABLE();							//ʹ��USART7ʱ��
		
    GPIO_Initure.Pin = GPIO_PIN_6|GPIO_PIN_7;	//PF6��PF7
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;			//�����������
    GPIO_Initure.Pull = GPIO_NOPULL;					//��������
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//����
    GPIO_Initure.Alternate = GPIO_AF8_UART7;	//����ΪUART7
    HAL_GPIO_Init(GPIOF, &GPIO_Initure);			//PF6��PF7
		
#if EN_USART7_RX
		HAL_NVIC_EnableIRQ(UART7_IRQn);					//ʹ��UART7�ж�ͨ��
		HAL_NVIC_SetPriority(UART7_IRQn,1,3);		//��ռ���ȼ�1�������ȼ�3
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
	while((UART7->ISR&0X40)==0);//ѭ������,ֱ���������   
    UART7->TDR = (unsigned char) ch;      
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

	memset((void*)USART1_RX_BUF,0,USART1_REC_LEN);	//�������
	HAL_UART_Transmit(&UART1_Handler,cmd,len,1000);	//����2��������

	for(j=0;j<waittime;j++)
	{
		delay_ms(50);
		strx=strstr((const char*)USART1_RX_BUF,(const char*)ack);
		if(strx)
			break;
	}

	USART1_RX_STA=0;
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
	if(Send_OneNET_Count>=1500)
	{
		sprintf((char *)Send_OneNET,"%d%d",Temp,Humi);
		HAL_UART_Transmit(&UART1_Handler,Send_OneNET,4,1000);	//�������ݵ�OneNET
		Send_OneNET_Count = 0;
	}
}





