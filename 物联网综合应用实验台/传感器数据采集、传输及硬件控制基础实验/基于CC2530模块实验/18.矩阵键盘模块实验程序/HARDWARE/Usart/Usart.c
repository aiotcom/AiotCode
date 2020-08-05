#include "Martix_Key.h"	
#include "Usart.h"	
#include "delay.h"
#include "Rs485.h"
#include "OLED.h"

#if UART0   //ʹ�ܽ���

unsigned char WiFi_AT_STA = 0;                  //WiFi��ʼ����ɱ�־λ
unsigned char USART0_RX_BUF[USART0_REC_LEN];    //���ջ���,���USART0_REC_LEN���ֽ�.
unsigned int  USART0_RX_STA = 0;       		//����״̬���	
uint8_t Command_LED[10];		        //����LED��������

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
  U0BAUD = 216;     //32MHz��ϵͳʱ�Ӳ���115200BPS�Ĳ�����
  U0GCR = 11;
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
  URX0IF = 0;                             //���RX�����жϱ�־

  if((USART0_RX_STA&0x8000)==0)	          //����δ���
  {
    if(WiFi_AT_STA)                       //WiFi��ʼ�����
    {
        USART0_Receive(U0DBUF);		  //����0���ݴ���
    }
    else
    {
        USART0_RX_BUF[USART0_RX_STA&0X3FFF]=U0DBUF ;
        USART0_RX_STA++;
        if(USART0_RX_STA>(200-1))USART0_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
    }
  } 
}

//==========================================================
//	�������ƣ�	USART0_Receive()
//
//	�������ܣ�	����0����
//
//	��ڲ�����	data:����0����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART0_Receive(uint8_t data)
{
  static uint8_t End_Flag 	= 0;	//֡β��־λ
  static uint8_t Header_Flag 	= 0;	//֡ͷ��־λ
  static uint8_t Receive_Flag   = 0;	//���ձ�־λ

/*
*
*	֡ͷ����
*
*/
  /*֡ͷ1 ����֡ͷ�е�һ���ֽ�*/
  if(Header_Flag == 0 && data == 0x45)
  {
      USART0_RX_BUF[0] = data;
      Header_Flag = 1;
  }

  /*֡ͷ2 ����֡ͷ�еڶ����ֽ�*/
  else if(Header_Flag == 1 && data == 0x41)
  {
      USART0_RX_STA = 1;  //������������±�����
      Receive_Flag = 1;	  //��ʼ�������ݱ�־λ
  }

  else Header_Flag = 0;
  
/*
*
*	����+֡β����
*
*/
  if(Receive_Flag)	//֡ͷ�������
  {
      if(USART0_RX_STA>=199)
      {
          End_Flag = 0;
          Receive_Flag = 0;
          USART0_RX_STA = 0;
      }
      
      USART0_RX_BUF[USART0_RX_STA++] = data;//���ݽ���

      /*֡β1  ����֡β�е�һ���ֽ�*/
      if(!End_Flag && data == 0x41)
      {	
          End_Flag = 1;
      }
      /*֡β2  ����֡β�еڶ����ֽ�*/
      else if(End_Flag && data == 0x45)
      {
          USART0_RX_STA = 0x8000;	//�������
          Receive_Flag = 0;
          End_Flag = 0;
      }

      /*���մ��� ���½���*/
      else End_Flag = 0;
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
//	�������ƣ�	USART0_SendString()
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
void USART0_SendString(unsigned char *str,uint16_t Len)
{
  while(Len--)
  {
    USART0_SendByte(*str++);    //��������ַ����е��ֽ�
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
  
  Rs485_Send("����һ��ʼ�����\r\n",18);
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

#endif


//==========================================================
//	�������ƣ�	Key_Feedback
//
//	�������ܣ�	��⵽���������ݴ�ӡ��������
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void Key_Feedback(void)
{
  if(Key_value)
  {
    switch(Key_value)
    {
      case Matrixkey0:
        OLED_P8x16Str(3,10,"KEY-Value:0    ");
        Rs485_Send("KEY-Value:0\r\n",13);     //485��������
      break;
      case Matrixkey1:
        OLED_P8x16Str(3,10,"KEY-Value:1    ");
        Rs485_Send("KEY-Value:1\r\n",13);     //485��������
      break;
      case Matrixkey2:
        OLED_P8x16Str(3,10,"KEY-Value:2    ");
        Rs485_Send("KEY-Value:2\r\n",13);     //485��������
      break;
      case Matrixkey3:
        OLED_P8x16Str(3,10,"KEY-Value:3    ");
        Rs485_Send("KEY-Value:3\r\n",13);     //485��������
      break;
      case Matrixkey4:
        OLED_P8x16Str(3,10,"KEY-Value:4    ");
        Rs485_Send("KEY-Value:4\r\n",13);     //485��������
      break;
      case Matrixkey5:
        OLED_P8x16Str(3,10,"KEY-Value:5    ");
        Rs485_Send("KEY-Value:5\r\n",13);     //485��������
      break;
      case Matrixkey6:
        OLED_P8x16Str(3,10,"KEY-Value:6    ");
        Rs485_Send("KEY-Value:6\r\n",13);     //485��������
      break;
      case Matrixkey7:
        OLED_P8x16Str(3,10,"KEY-Value:7    ");
        Rs485_Send("KEY-Value:7\r\n",13);     //485��������
      break;
      case Matrixkey8:
        OLED_P8x16Str(3,10,"KEY-Value:8    ");
        Rs485_Send("KEY-Value:8\r\n",13);     //485��������
      break;
      case Matrixkey9:
        OLED_P8x16Str(3,10,"KEY-Value:9    ");
        Rs485_Send("KEY-Value:9\r\n",13);     //485��������
      break;
      case MatrixkeyEnter:
        OLED_P8x16Str(3,10,"KEY-Value:Enter");
        Rs485_Send("KEY-Value:Enter\r\n",17); //485��������
      break;
      case MatrixkeyCanel:
        OLED_P8x16Str(3,10,"KEY-Value:Canel");
        Rs485_Send("KEY-Value:Canel\r\n",17); //485��������
      break;
      case MatrixkeyUP:
        OLED_P8x16Str(3,10,"KEY-Value:UP   ");
        Rs485_Send("KEY-Value:UP\r\n",14);    //485��������
      break;
      case MatrixkeyDown:
        OLED_P8x16Str(3,10,"KEY-Value:Down ");
        Rs485_Send("KEY-Value:Down\r\n",16);  //485��������
      break;
      case MatrixkeyLeft:
        OLED_P8x16Str(3,10,"KEY-Value:Left ");
        Rs485_Send("KEY-Value:Left\r\n",16);  //485��������
      break;
      case MatrixkeyRight:
        OLED_P8x16Str(3,10,"KEY-Value:Right");
        Rs485_Send("KEY-Value:Right\r\n",17); //485��������
      break;
      default:break;
    }
    Key_value = 0;
  }
}