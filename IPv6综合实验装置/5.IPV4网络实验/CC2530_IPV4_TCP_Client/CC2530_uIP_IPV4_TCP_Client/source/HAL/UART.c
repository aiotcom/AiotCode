#include "UART.H"
/*
    U0BAUD = 59;     32M 9600bps
    U0GCR  = 8;
*/
void UART_Init(unsigned char port)
{
  if(UART_0 == port)
  {
    PERCFG = 0x00;    //����0������ӳ�䵽λ��1����P0_2��P0_3
    P0SEL  |= 0x0C;     //��P0_2��P0_3�˿����ó����蹦��   
    U0BAUD = 59;      //16MHz��ϵͳʱ�Ӳ���115200BPS�Ĳ�����
    U0GCR  = 8;
    U0UCR |= 0x80;    //��ֹ���أ�8λ���ݣ����������
    U0CSR |= 0xC0;    //ѡ��UARTģʽ��ʹ�ܽ�����
    UTX0IF = 0;       //���TX�����жϱ�־
    URX0IF = 0;       //���RX�����жϱ�־
    URX0IE = 1;       //ʹ��URAT0�Ľ����ж�
    EA = 1;           //ʹ�����ж�
  }
  else if(UART_1 == port)
  {
    P2DIR   = 0X40;
    PERCFG  = 0x00;    //����0������ӳ�䵽λ��1����P0_4��P0_5
    P0SEL  |= 0x30;     //��P0_4��P0_5�˿����ó����蹦��
    U1BAUD  = 216;     //32MHz��ϵͳʱ�Ӳ���115200BPS�Ĳ�����
    U1GCR   = 11;
    U1UCR   = 0x80;    //��ֹ���أ�8λ���ݣ����������
    U1CSR  = 0xC0;    //ѡ��UARTģʽ��ʹ�ܽ�����
    UTX1IF = 0;       //���TX�����жϱ�־
    URX1IF = 0;       //���RX�����жϱ�־
    URX1IE = 1;       //ʹ��URAT1�Ľ����ж�
    EA     = 1;           //ʹ�����ж�  
  }
}
unsigned char UART0_RxByte;
#pragma vector = URX0_VECTOR
__interrupt void UR0_RecvIntISR()
{
  URX0IF = 0;                             //���RX�����жϱ�־ 
  UART0_RxByte = U0DBUF;
}
//==========================================================
//	�������ƣ�	UR0_RecvInt()
//
//	�������ܣ�	UR0�����жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
unsigned char UART1_RxByte;
#pragma vector = URX1_VECTOR
__interrupt void UR1_RecvIntISR()
{
  URX1IF = 0;                             //���RX�����жϱ�־ 
  UART1_RxByte = U1DBUF;
}
//==========================================================
//	�������ƣ�	UR0_RecvInt()
//
//	�������ܣ�	UR0�����жϷ�����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
__near_func int putchar(int c)
{
#if 1  
    UTX0IF = 0;
    U0DBUF = (char)c;
    while(UTX0IF == 0);
    return(c);
#else
    UTX1IF = 0;
    U1DBUF = (char)c;
    while(UTX1IF == 0);
    return(c);    
#endif    
}