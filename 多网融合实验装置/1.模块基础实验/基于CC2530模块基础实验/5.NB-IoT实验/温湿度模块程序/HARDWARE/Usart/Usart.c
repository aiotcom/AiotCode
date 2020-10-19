#include "TM1640.h"
#include "Usart.h"	
#include "delay.h"
#include "Rs485.h"
#include "SHT20.h"
#include "Time.h"
#include "ADC.h"

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
  U0BAUD = 216;     //16MHz��ϵͳʱ�Ӳ���115200BPS�Ĳ�����
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
//  while(*str != '\0')
//  {
//    USART0_SendByte(*str++);    //��������ַ����е��ֽ�
//  }
  while(Len--)
  {
    USART0_SendByte(*str++);    //��������ַ����е��ֽ�
  }
}

//==========================================================
//	�������ƣ�	WiFi_Send_Cmd()
//
//	�������ܣ�	��WiFi��������
//
//	��ڲ�����	waittime:�ȴ�ʱ��(��λ:ms)
//			cmd:���͵������ַ���
//			ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//
//	���ز�����	
//		        ����ֵ:	��0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       			  0,����ʧ��
//
//	˵����		
//==========================================================
uint8_t* WiFi_Send_Cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime)
{
    static uint8_t len = 0;	//������ݳ���
    static uint16_t j = 0;
    char *strx=0;
  
    len = strlen((char *)cmd);	//��ȡ���ݳ���
  
    memset((void*)USART0_RX_BUF,0,USART0_REC_LEN);//�������
    
    USART0_SendString(cmd,len); //����0��������
    
    for(j=0;j<waittime;j++)
    {
        delay_ms(50);
        strx=strstr((const char*)USART0_RX_BUF,(const char*)ack);
        if(strx)
          break;
    }

    USART0_RX_STA=0;
    return (uint8_t*)strx;
}

//==========================================================
//	�������ƣ�	USART0_IRQHand()
//
//	�������ܣ�	������0����
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����				
//==========================================================
void USART0_IRQHand(void)
{
  static uint16_t Command;	//��ƽ̨�·�����
  
  if(USART0_RX_STA == 0x8000)
  {
    Command = ((USART0_RX_BUF[2]-0x30)*1000)+((USART0_RX_BUF[3]-0x30)*100)
    +((USART0_RX_BUF[4]-0x30)*10)+(USART0_RX_BUF[5]-0x30);//��ȡƽ̨�·�������
  }
  switch(Command)
  {
    case LED_ON1:
      Command_LED[0] = 1;	//��������װ�ص�LED��������
      break;
    case LED_OFF1:
      Command_LED[0] = 0;	//��������װ�ص�LED��������
      break;
    case LED_ON2:
      Command_LED[1] = 1;	//��������װ�ص�LED��������
      break;
    case LED_OFF2:
      Command_LED[1] = 0;	//��������װ�ص�LED��������
      break;
    case LED_ON3:
      Command_LED[2] = 1;	//��������װ�ص�LED��������
      break;
    case LED_OFF3:
      Command_LED[2] = 0;	//��������װ�ص�LED��������
      break;
    case LED_ON4:
      Command_LED[3] = 1;	//��������װ�ص�LED��������
      break;
    case LED_OFF4:
      Command_LED[3] = 0;	//��������װ�ص�LED��������
      break;
    default: break;
  }
  memset((void*)USART0_RX_BUF,0,10);//�������
  USART0_RX_STA = 0;
}

#endif


#if UART1   //ʹ�ܽ���

unsigned char USART1_RX_BUF[USART1_REC_LEN];    //���ջ���,���USART1_REC_LEN���ֽ�.
unsigned int  USART1_RX_STA=0;       		//����״̬���	
uint8_t Send_OneNET[30];			//���͵�OneNET��ʾ����

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
  PERCFG = 0x00;  //����1������ӳ�䵽λ��1����P0_4��P0_5
  P0SEL |= 0x30;  //��P0_4��P0_5�˿����ó����蹦��
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
  static uint8_t Display_Flag = 0;		//��ʾ��־λ

  Get_ADC_Value();                              //��ȡ��ǿ����
  SHT2x_GetTempHumi(); 				//��ȡ��ʪ��ֵ
  Temp[0] = (uint8_t)g_sht2x_param.TEMP_HM;	//�¶�����
  Humi[0] = (uint8_t)g_sht2x_param.HUMI_HM;	//ʪ������
  Sum_Data[0] = (uint8_t)g_sht2x_param.TEMP_HM; //�¶�����
  Sum_Data[1] = (uint8_t)g_sht2x_param.HUMI_HM; //ʪ������

  if(Display_Count>=80 && Display_Flag == 0)	//1600ms ��ʾ�¶�
  {
    Display_Flag = 1;
    send_LED_Display(0xC0,(uint16_t)g_sht2x_param.TEMP_HM,1);
  }
  else if(Display_Count>=160 && Display_Flag == 1)//3200ms ��ʾʪ��
  {
    Display_Flag = 2;
    send_LED_Display(0xC0,(uint16_t)g_sht2x_param.HUMI_HM,2);
  }
  else if(Display_Count>=240 && Display_Flag == 2)//4800ms ��ʾ��ǿ
  {
    send_LED_Display(0xC0,ADC_Data,3);
    Display_Count = 0;
    Display_Flag = 0;
  }
}

#endif