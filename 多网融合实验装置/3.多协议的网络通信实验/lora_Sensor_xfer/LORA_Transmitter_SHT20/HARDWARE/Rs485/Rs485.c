#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "Rs485.h"
#include "usart.h"

Send_Stack Tx_Stack;										//485�������ݽṹ��
Receive_Stack Rx_Stack;									//485�������ݽṹ��

uint8_t  Send_Data[Send_REC_LEN]; 			//���ͻ���,���Send_REC_LEN���ֽ�
uint8_t  Receive_Data[Receive_REC_LEN]; //���ջ���,���Send_REC_LEN���ֽ�

//==========================================================
//	�������ƣ�	Rs485_Init()
//
//	�������ܣ�	��ʼ��485
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			 
//==========================================================
void Rs485_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
	
    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��

		GPIO_Initure.Pin = GPIO_PIN_8;						//PA8
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;	//�������
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; //����
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);

		RS485_RX_EN();   													//��ʼ��Ϊ����ģʽ

		Rx_Stack_Init();													//��ʼ�����սṹ��
		Tx_Stack_Init();													//��ʼ�����ͽṹ��
}

//==========================================================
//	�������ƣ�	Tx_Stack_Init
//
//	�������ܣ�	RFIDģ���Ϸ����ݽṹ���ʼ��
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����			 
//==========================================================
void Tx_Stack_Init(void)
{
	Tx_Stack.Head = 0xE1E2E3E4;					//֡ͷ
	Tx_Stack.Pack_Num = 0x00;						//�����
	Tx_Stack.Src_Adr = 0x0000;					//Դ��ַ
	Tx_Stack.Dst_Adr = 0x0000;					//Ŀ�ĵ�ַ
	Tx_Stack.State = 0x0000;						//״̬��
	Tx_Stack.Data_Len = 0x00;						//���ݳ���
	memset(Tx_Stack.Data, 0, sizeof(Tx_Stack.Data));//��������ȫ�����
	Tx_Stack.CrcCheck = 0x0000;					//CRCУ����
	Tx_Stack.Tail = 0xEAEBECED;					//֡β
}

//==========================================================
//	�������ƣ�	Rx_Stack_Init
//
//	�������ܣ�	��λ���·����ݽṹ���ʼ��
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rx_Stack_Init(void)
{
	Rx_Stack.Head = 0xE1E2E3E4;					//֡ͷ
	Rx_Stack.Pack_Num = 0x00;						//�����
	Rx_Stack.Src_Adr = 0x0000;					//Դ��ַ
	Rx_Stack.Dst_Adr = 0x0000;					//Ŀ�ĵ�ַ
	Rx_Stack.Command = 0x0000;					//������
	Rx_Stack.Data_Len = 0x00;						//���ݳ���						
	memset(Rx_Stack.Data, 0, sizeof(Rx_Stack.Data));//��������ȫ�����
	Rx_Stack.CrcCheck = 0x0000;					//CRCУ����
	Rx_Stack.Tail = 0xEAEBECED;					//֡β
}

//==========================================================
//	�������ƣ�	delay_us
//
//	�������ܣ�	�������ݵ�485������
//
//	��ڲ�����	��ʱ�ĺ�����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void delay_us(unsigned int nus)
{		
	unsigned int j = 0;
	while(nus--)
	{
        j = 2;
		while(j--)
		{;}
	}
}
//==========================================================
//	�������ƣ�	Rs485_Send()
//
//	�������ܣ�	�������ݵ�485������
//
//	��ڲ�����	SrcAdr:Դ��ַ
//							DstAdr:Ŀ�ĵ�ַ
//							Cmd		:������
//							Len		:���ݳ���
//							*pData:����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rs485_Send(uint16_t SrcAdr,uint16_t DstAdr,uint16_t Cmd,uint8_t Len,uint8_t *pData)
{
	uint16_t i = 0;																			//Forѭ��ʹ��	
	
	for(i=0;i<4;i++)
	{
		Send_Data[i] = (0xE1+i);													//֡ͷ
	}

	if(Tx_Stack.Pack_Num>=255)
	{
		Tx_Stack.Pack_Num = 0;	
	}
	Send_Data[4] = Tx_Stack.Pack_Num;										//�����	
	Tx_Stack.Pack_Num++;
	Send_Data[5] = SrcAdr>>8;
	Send_Data[6] = SrcAdr;															//Դ��ַ
	Send_Data[7] = DstAdr>>8;
	Send_Data[8] = DstAdr;															//Ŀ�ĵ�ַ
	Send_Data[9] = Cmd>>8;
	Send_Data[10] = Cmd;																//������
	Send_Data[11] = Len;																//���ݳ���
	for(i=12;i<(Len+12);i++)
	{
		Send_Data[i] = pData[i-12];												//����
	}
	Tx_Stack.CrcCheck = CRC_16(Send_Data,(12+Len));			//CRCУ����
	Send_Data[12+Len] = Tx_Stack.CrcCheck>>8;
	Send_Data[13+Len] = Tx_Stack.CrcCheck;							//CRCУ����
	for(i=(14+Len);i<(18+Len);i++)
	{
		Send_Data[i] = (0xEA+(i-14-Len));									//֡β
	}

	RS485_TX_EN();		//����485����
	delay_us(5);
	HAL_UART_Transmit(&UART1_Handler,Send_Data,(18+Len),1000);//485��������
	delay_us(5);
	RS485_RX_EN();		//����485����
}
//==========================================================
//	�������ƣ�	Rs485_Receive()
//
//	�������ܣ�	485����
//
//	��ڲ�����	data		:485����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rs485_Receive(uint8_t data)
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
	if(data == 0xE1 && Header_Flag < 4)	Header_Flag = 1;

	/*֡ͷ2 ����֡ͷ�еڶ����ֽ�*/
	else if(Header_Flag == 1 && data == 0xE2)	Header_Flag = 2;

	/*֡ͷ3 ����֡ͷ�е������ֽ�*/
	else if(Header_Flag == 2 && data == 0xE3)	Header_Flag = 3;

	/*֡ͷ4 ����֡ͷ�е��ĸ��ֽ�*/
	else if(Header_Flag == 3 && data == 0xE4)
	{
		Receive_Data[0] = 0xE1;
		Receive_Data[1] = 0xE2;
		Receive_Data[2] = 0xE3; //֡ͷ������ɣ�����֡ͷ����
		USART1_RX_STA = 3;			//������������±�����
		Receive_Flag = 1;				//��ʼ�������ݱ�־λ
	}

	else Header_Flag = 0;

/*
*
*				����+֡β����
*
*/
	if(Receive_Flag)	//֡ͷ�������
	{
		if(USART1_RX_STA>(Receive_REC_LEN-1))
		{
			End_Flag = 0;
			Receive_Flag = 0;
			USART1_RX_STA = 0;
		}

		Receive_Data[USART1_RX_STA++] = data;	//���ݽ���

		/*֡β1 ����֡β�е�һ���ֽ�*/
		if(data == 0xEA)	End_Flag = 1;

		/*֡β2  ����֡β�еڶ����ֽ�*/
		else if(End_Flag == 1 && data == 0xEB)	End_Flag = 2;

		/*֡β3  ����֡β�е������ֽ�*/
		else if(End_Flag == 2 && data == 0xEC)	End_Flag = 3;

		/*֡β4  ����֡β�е��ĸ��ֽ�*/
		else if(End_Flag == 3 && data == 0xED)
		{
			USART1_RX_STA = Receiving_Completion;		//�������
			Receive_Flag = 0;
			End_Flag = 0;
		}

		/*���մ��� ���½���*/
		else End_Flag = 0;
	}
}

//==========================================================
//	�������ƣ�	DataHandling_485()
//
//	�������ܣ�	485���ݴ�����
//
//	��ڲ�����	DesAddr	:Ŀ�ĵ�ַ
//              
//	���ز�����	0:���ݽ������
//							1:���ݽ��մ���
//
//	˵����		
//==========================================================
uint8_t DataHandling_485(uint16_t DesAddr)
{
	static uint16_t i = 0;
	static uint8_t Return_Value = 0;
	static uint16_t Crc16Check = 0;			//���CRCУ������

  if(USART1_RX_STA == Receiving_Completion)
	{
			Return_Value = 0;
			if((Receive_Data[7]*256+Receive_Data[8]) == DesAddr)	//�Ա�Դ��ַ����Ҫ�����ݣ�ȫ����������
			{
				/*�����*/
				Rx_Stack.Pack_Num = Receive_Data[4];

				/*Դ��ַ*/
				Rx_Stack.Src_Adr = Receive_Data[5]*256+Receive_Data[6];

				/*Ŀ�ĵ�ַ*/
				Rx_Stack.Dst_Adr = Receive_Data[7]*256+Receive_Data[8];

				/*������*/
				Rx_Stack.Command = Receive_Data[9]*256+Receive_Data[10];

				/*���ݳ���*/
				Rx_Stack.Data_Len = Receive_Data[11];

				/*����*/
				for(i=12;i<(Rx_Stack.Data_Len+12);i++)
				{
					Rx_Stack.Data[(i-12)] = Receive_Data[i];
				}

				/*CRCУ����߰�λ*/
				Rx_Stack.CrcCheck = Receive_Data[(12+Rx_Stack.Data_Len)]*256;

				/*CRCУ����Ͱ�λ*/
				Rx_Stack.CrcCheck += Receive_Data[(13+Rx_Stack.Data_Len)];
				
				Crc16Check = CRC_16(Receive_Data,(12+Rx_Stack.Data_Len));
				if(Crc16Check != Rx_Stack.CrcCheck)
				{
					Return_Value = 1;
				}
			}
			else Return_Value = 1;
			
			memset(Receive_Data,0,Receive_REC_LEN);//��ս�������
			
			USART1_RX_STA = 0;
	}
	else Return_Value = 1;

	return Return_Value;	//���ؽ������
}

//==========================================================
//	�������ƣ�	calcByte()
//
//	�������ܣ�	CRC_16�ֽڼ��㺯��
//
//	��ڲ�����	crc:CRCУ����
//							b:
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
uint16_t calcByte(uint16_t crc, uint8_t b)
{
		uint16_t i = 0;			//�������ʱForѭ��ʹ��	

    crc = crc ^ (int)b << 8;
    for (i = 0; i < 8; i++)
    {
        if ((crc & 0x8000) == 0x8000)
        {
            crc = crc << 1 ^ 0x1021;
        }
        else
        {
            crc = crc << 1;
        }
    }
    return crc & 0xffff;
}

//==========================================================
//	�������ƣ�	CRC_16()
//
//	�������ܣ�	CRC_16���㺯��
//
//	��ڲ�����	*p:	��ҪУ�������
//							length: У�����ݳ���
//              
//	���ز�����	wCRC16:16λCRCУ����
//
//	˵����			
//==========================================================
uint16_t CRC_16(void *p, int length)
{
		short wCRC16=0;
    uint8_t *pBuffer;
		uint16_t i = 0;			//�������ʱForѭ��ʹ��	

    if (( p==0 )||( length==0 ))
    {
        return 0xFFFF;
    }

    pBuffer=(uint8_t *)p;
    for ( i = 0; i < length; i++)
    {
        wCRC16 = calcByte(wCRC16, pBuffer[i]);
    }

    return wCRC16;
}

//==========================================================
//	�������ƣ�	Rs485_delay_ms()
//
//	�������ܣ�	������ʱ����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rs485_delay_ms(unsigned int nms)
{		
	unsigned int i = 0,j = 0;
	
	for(i = 0;i<nms;i++)
	{
		for(j = 0;j<9600;j++)
		{;}
	}
}


