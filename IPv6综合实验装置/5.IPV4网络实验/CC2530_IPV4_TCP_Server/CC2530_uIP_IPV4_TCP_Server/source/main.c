#include <ioCC2530.h>
#include "enc28j60.h"
#include "spi_enc28j60.h"
#include "uIP_App.h"
#include "UIP.h"
#include "TIM.h"
#include "UART.h"
#include "stdio.h"
#include "string.h"
#include "type.h"
#include "clock-arch.h"
#include "app_basicrf.h"

//****�궨��*******************
#define TCP_Server_Test 1  //TCP������ʵ��

#define PAN_ID              0x2007
#define LOCAL_SHORT_ADDR    0x2520
#define RF_CHANNEL          25 /*11~26*/     
//****�궨��*******************

//****��������*****************
void System_clockInit(void);
//****��������*****************

//****��������*******************
extern uint8_t client_sel;
static uint8_t rEIR=0;
uint8_t RxSensorData[5];
uint8_t uip_udp_client_send_buf[50];
uint8_t uip_udp_client_send_len = 0;
uint32_t UIP_RunTimeCounter = 0;
uint32_t UIP_HanlderCounter = 0;
uint32_t uip_udp_client_send_counter = 0;
uint32_t uip_tcp_client_send_counter = 0;
uint8_t uip_tcp_client_send_buf[50];
uint8_t uip_tcp_client_send_len;

uint8_t uIP_TCP_Server_RxBuffer[50];
uint8_t uIP_TCP_Server_RxLen;
uint8_t AnswerClientReq = 0;
//****��������*******************

//==========================================================
//	�������ƣ�	void main(void)
//
//	�������ܣ�	������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void main(void)
{
  	uip_ipaddr_t ipaddr;
  	System_clockInit();
	UART_Init(UART_0);//��ʼ������0
	
	Rf_Init(RF_CHANNEL,PAN_ID,LOCAL_SHORT_ADDR);   //��ʼ������ͨ��
	TIM1_Init(); //��ʼ����ʱ�����ж�����1000Hz 	
	
	printf("this is uart0 print\r\n");
    
	SPI_Enc28j60_Init();
    uIP_Net_Init();//��ʼ��UIP,��ʼ��оƬ

	uip_ipaddr(ipaddr, 192,168,3,33);		 //���ñ���IP��ַ
	uip_sethostaddr(ipaddr);
	uip_ipaddr(ipaddr, 192,168,3,1);		 //����Ĭ��·����IP��ַ  ����
	uip_setdraddr(ipaddr);	
	uip_ipaddr(ipaddr, 255,255,255,0);		 //������������
	uip_setnetmask(ipaddr);
    
#if TCP_Server_Test
    uip_listen(HTONS(1200));//TCP����
#endif
	
    UIP_RunTimeCounter = HAL_GetTick()+50;
    UIP_HanlderCounter = HAL_GetTick()+50;  
    uip_udp_client_send_counter = HAL_GetTick()+1000;    
    uip_tcp_client_send_counter = HAL_GetTick()+1000;

	while(1)
	{
        if(HAL_GetTick() > UIP_RunTimeCounter)
        {//50ms
            UIP_RunTimeCounter = HAL_GetTick()+50;
            uIP_RunTime++;
            if (uIP_RunTime == 0x80000000)
            {
                uIP_RunTime=0;
            }

            if((ENC28J60_INT) == 0)
            {
                rEIR = enc28j60ReadOp(ENC28J60_READ_CTRL_REG, EIR);
                if(rEIR&0x10)
                {

                }
                ENC28J60_ReadPhy(PHIR);
            }
        }//if(HAL_GetTick() > UIP_RunTimeCounter)
        if(HAL_GetTick() > UIP_HanlderCounter)
        {
            UIP_HanlderCounter = HAL_GetTick()+10;
            eth_poll();
            UipPro();	
        }
		
		if(Rf_Receive(RxSensorData))
		{
			sprintf(&uip_tcp_client_send_buf[0],(uint8_t*)"Temp=%d,Humidity=%d\r\n",RxSensorData[0],RxSensorData[1]);			
		}
		
		if(uIP_TCP_Server_RxLen)
		{
		  	uIP_TCP_Server_RxBuffer[49] = 0;
			if(strstr((const void*)uIP_TCP_Server_RxBuffer,(const void*)"req:temp"))
			{
				AnswerClientReq = 1;
			}
			else if(strstr((const void*)uIP_TCP_Server_RxBuffer,(const void*)"req:humidity"))
			{
				AnswerClientReq = 2;
			}	
			uIP_TCP_Server_RxLen  = 0;
		}
/*
void myudp_appcall(void) ;UDP���ݽ���uIP_AppCall.c
void tcp_appcall(void)   ;UDP���ݽ���uIP_AppCall.c
*/	
		//�������ظ��ͻ��˵�����
		if(AnswerClientReq)
		{
		  if(AnswerClientReq == 1)
		  {
			sprintf((void*)uip_tcp_client_send_buf,"temp:=%d",RxSensorData[0]);	
			uip_tcp_client_send_len = strlen((const void*)uip_tcp_client_send_buf);
		  }		
		  else if(AnswerClientReq == 2)
		  {
			sprintf((void*)uip_tcp_client_send_buf,"humidity:=%d",RxSensorData[1]);	
			uip_tcp_client_send_len = strlen((const void*)uip_tcp_client_send_buf);
		  }		  
			AnswerClientReq = 0;	
		}      
	}
}	
//==========================================================
//	�������ƣ�	void System_clockInit(void)
//
//	�������ܣ�	��ʼ��ϵͳʱ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		��ʱ��ʱ��16MHz���ж�����1000HZ
//==========================================================
void System_clockInit(void)
{
  CLKCONCMD &= ~(1<<6);        /*ѡ��32MHz����*/  
  while(!(CLKCONSTA & (1<<6))); /*�ȴ������ȶ�*/  
  CLKCONCMD &= ~0x47;          /* ����Ƶ,ϵͳʱ��32MHZ����ʱ��ʱ��16MHZ*/             
}