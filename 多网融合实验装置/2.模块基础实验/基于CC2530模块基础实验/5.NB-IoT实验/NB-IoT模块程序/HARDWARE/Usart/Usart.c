#include "Usart.h"	
#include "delay.h"
#include "M5310.h"
#include "Rs485.h"
#include "Time.h"

#if UART0   //ʹ�ܽ���

uint8_t USART0_RecvBuffer[USART0_RECV_BUFFER_LENGTH]={0};
uint16_t USART0_RecvIndex =0;

//==========================================================
//	�������ƣ�	USRT0_Init()
//
//	�������ܣ�	��ʼ������0
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void USRT0_Init(void)
{
  PERCFG = 0x00;    //����0������ӳ�䵽λ��1����P0_2��P0_3
  P0SEL = 0x0C;     //��P0_2��P0_3�˿����ó����蹦��
  U0BAUD = 59;      //32MHz��ϵͳʱ�Ӳ���9600BPS�Ĳ�����
  U0GCR = 8;
  U0UCR |= 0x80;    //��ֹ���أ�8λ���ݣ����������
  U0CSR |= 0xC0;    //ѡ��UARTģʽ��ʹ�ܽ�����
  UTX0IF = 0;       //���TX�����жϱ�־
  URX0IF = 0;       //���RX�����жϱ�־
  URX0IE = 1;       //ʹ��URAT0�Ľ����ж�
  EA = 1;           //ʹ�����ж�
}

//==========================================================
//	�������ƣ�	UR0_RecvInt()
//
//	�������ܣ�	����0�����жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
#pragma vector = URX0_VECTOR
__interrupt void UR0_RecvInt()
{
  URX0IF = 0;                     //���RX�����жϱ�־

  USART0_RecvBuffer[USART0_RecvIndex++] = U0DBUF;//��ȡ���ݼĴ����е����ݡ�

  if((USART0_RecvIndex>=2)&&(USART0_RecvBuffer[USART0_RecvIndex-2] == '\r')&&(USART0_RecvBuffer[USART0_RecvIndex-1] == '\n'))
  {
      USART0_RecvIndex = 0;
  }
  if(USART0_RecvIndex >= (USART0_RECV_BUFFER_LENGTH-1))//USART0_RecvIndex ���ڻ��ߵ���USART0_RECV_BUFFER_LENGTH������USART0_RecvBuffer[]���ݵķ�Χ
  {
      USART0_RecvIndex = 0;
  }
}

//==========================================================
//	�������ƣ�	USART0_SendByte()
//
//	�������ܣ�	����0���͵��ֽں���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART0_SendByte(unsigned char dat)
{
  U0DBUF = dat;         //��Ҫ���͵�1�ֽ�����д��U0DBUF
  while(!UTX0IF);       //�ȴ�TX�жϱ�־�������ݷ������
  UTX0IF = 0;           //���TX�жϱ�־��׼����һ�η���
}

//==========================================================
//	�������ƣ�	USART0_SendBytes()
//
//	�������ܣ�	����0�����ַ�������
//
//	��ڲ�����	*str: ���͵�����
//                      Len:  ���ݳ���
//          
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART0_SendBytes(char *pdata,uint16_t lenght)
{
  while(lenght--)
  {
    USART0_SendByte(*pdata++);    //��������ַ����е��ֽ�
  }
}


#endif


#if UART1   //ʹ�ܽ���

unsigned char USART1_RX_BUF[USART1_REC_LEN];    //���ջ���,���USART1_REC_LEN���ֽ�.
unsigned int  USART1_RX_STA=0;       		//����״̬���	

//==========================================================
//	�������ƣ�	USRT1_Init()
//
//	�������ܣ�	����1��ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void USRT1_Init(void)
{
  P2DIR = 0x40;
  PERCFG = 0x00;    //����1������ӳ�䵽λ��1����P0_4��P0_5
  P0SEL |= 0x30;    //��P0_4��P0_5�˿����ó����蹦��
  U1BAUD = 216;     //32MHz��ϵͳʱ�Ӳ���115200BPS�Ĳ�����
  U1GCR = 11;
  U1UCR = 0x80;     //��ֹ���أ�8λ���ݣ����������
  U1CSR = 0xC0;     //ѡ��UARTģʽ��ʹ�ܽ�����
  UTX1IF = 0;       //���TX�����жϱ�־
  URX1IF = 0;       //���RX�����жϱ�־
  URX1IE = 1;       //ʹ��URAT1�Ľ����ж�
  EA = 1;           //ʹ�����ж�
}

//==========================================================
//	�������ƣ�	UR1_RecvInt()
//
//	�������ܣ�	UR1�����жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
#pragma vector = URX1_VECTOR
__interrupt void UR1_RecvInt()
{
  URX1IF = 0;                   //���RX�����жϱ�־
  
  if((USART1_RX_STA&0x8000)==0)	//����δ���
  {
      Rs485_Receive(U1DBUF);	//����485���պ���
  } 
}

//==========================================================
//	�������ƣ�	USART1_SendByte()
//
//	�������ܣ�	����1���͵��ֽں���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART1_SendByte(unsigned char dat)
{
  U1DBUF = dat;         //��Ҫ���͵�1�ֽ�����д��U1DBUF
  while(!UTX1IF);       //�ȴ�TX�жϱ�־�������ݷ������
  UTX1IF = 0;           //���TX�жϱ�־��׼����һ�η���
}

//==========================================================
//	�������ƣ�	USART1_SendString()
//
//	�������ܣ�	����1�����ַ�������
//
//	��ڲ�����	*str: ���͵�����
//                      Len:  ���ݳ���
//          
//	���ز�����	��
//
//	˵����          
//==========================================================
void USART1_SendString(unsigned char *str,uint16_t Len)
{
  while(Len--)
  {
    USART1_SendByte(*str++);    //��������ַ����е��ֽ�
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
  static uint8_t SendOneNET[10];
  static uint16_t Light_Intensity;
  
  if(!DataHandling_485(Addr_NB))	//����485�д����NBģ�������
  {
    if(Rx_Stack.Src_Adr == Addr_SHT20)	//������ʪ�ȹ�ǿ����
    {
      memset((void*)SendOneNET,0,10);
      sprintf((char *)SendOneNET,"%0.2f",(float)Rx_Stack.Data[0]);
      m5310_notify_upload(&temp_uri,NBIOT_FLOAT,(char*)&SendOneNET[0],1,0);//�ϴ��¶�����
      
      memset((void*)SendOneNET,0,10);
      sprintf((char *)SendOneNET,"%0.2f",(float)Rx_Stack.Data[1]);
      m5310_notify_upload(&humi_uri,NBIOT_FLOAT,(char*)&SendOneNET[0],1,0);//�ϴ�ʪ������
      
      memset((void*)SendOneNET,0,10);
      Light_Intensity = Rx_Stack.Data[2]*256+Rx_Stack.Data[3];
      sprintf((char *)SendOneNET,"%0.0f",(float)Light_Intensity);
      m5310_notify_upload(&illum_uri,NBIOT_FLOAT,(char*)&SendOneNET[0],1,0);//�ϴ���ǿ����
    }
  }
}

#endif

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
  if(Task_Count>=500)   //500ms	��ȡ��ʪ�ȡ���ǿ����
  {
    Rs485_Send(Addr_NB,Addr_SHT20,SHT20_Get_All,0,"");
    Task_Count = 0;
  }
}
