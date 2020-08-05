#include "stm32f1xx.h"
#include "delay.h"
#include "RS485.h"
#include "string.h"
#include "USART.h"
#include "uip.h"
#include "uIP_AppCall.h"
#include "uIP_App.h"
#include "tapdev.h"
#include "clock-arch.h"
#include "enc28j60.h"
#include "spi_enc28j60.h"
#include "clock-arch.h"
#include "_timer.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2018-01-01
*
*	�汾�� 		V1.0
*
*	˵���� 		IPV4ģ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/



uint8_t client_sel;
static uint8_t rEIR=0;
uint8_t uip_udp_client_send_buf[50];
uint8_t uip_udp_client_send_len = 0;
uint32_t UIP_RunTimeCounter = 0;
uint32_t UIP_HanlderCounter = 0;

uint32_t uip_udp_client_send_counter = 0;
uint32_t uip_tcp_client_send_counter = 0;
uint8_t uip_tcp_client_send_buf[50];
uint8_t uip_tcp_client_send_len;

extern uint8_t uip_tcp_client_send_buf[50];
extern uint8_t uip_tcp_client_send_len;
struct uip_conn *client_link_uip_conn[2];

#define TCP_Server_Test 1  //TCP������ʵ��

void RS485_HandlerCb(void); //����485�����ϵ�����
int main(void)
{
    uip_ipaddr_t ipaddr;
    HAL_Init();          //��ʼ��HAL��    
    Rs485_Init();        //��ʼ��RS485����IO
    UART1_Init(115200);
    UART2_Init(115200);
    USART3_Init(115200);
    
    TIM3_Init(10000-1,640-1,RS485_HandlerCb);
    SPI_Enc28j60_Init();
    uIP_Net_Init();//��ʼ��UIP,��ʼ��оƬ

    printf("IPV4:usart3 print\r\n");
	uip_ipaddr(&ipaddr, 192,168,3,33);		 //���ñ���IP��ַ
	uip_sethostaddr(&ipaddr);
	uip_ipaddr(&ipaddr, 192,168,3,1);		 //����Ĭ��·����IP��ַ  ����
	uip_setdraddr(&ipaddr);	
	uip_ipaddr(&ipaddr, 255,255,255,0);		 //������������
	uip_setnetmask(&ipaddr);
    
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

            if((GPIOB->IDR&GPIO_PIN_9) == 0)
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
#if TCP_Server_Test
        //TCP�������������� ÿ5000ms����һ������
        if(HAL_GetTick() > uip_tcp_client_send_counter)
        {
            uip_tcp_client_send_counter = HAL_GetTick()+2500;
            sprintf(&uip_tcp_client_send_buf[0],"uwTick=%d\r\n",HAL_GetTick());
            uip_tcp_client_send_len = strlen((const char*)&uip_tcp_client_send_buf[0]);
        }
#endif        
	}
}
//==========================================================
//	�������ƣ�	void TCP_ServerReceive_Handler(uint8_t data,uint)
//
//	�������ܣ�	TCP������ѯ����
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		��ʱ��ѯÿһ����������
//==========================================================
uint8_t count=0; 
void tcp_appcall(void)
{//��ʱ��ѯ��ÿ��conn
    switch(uip_conn->lport) //���ض˿�
    {
        case HTONS(1200):
            if(uip_connected())
            {//����пͻ��˽��룬�ߵ����client_link_uip_conn ����ͻ��˵�����
                client_link_uip_conn[count++] = uip_conn;
            }
            if(uip_newdata())
            {//���յ����ݣ�ͨ��485ת����LCD
                memcpy((void*)uip_tcp_client_send_buf,uip_appdata,uip_len);
                //uip_tcp_client_send_len = uip_len;
                //uip_send(uip_tcp_client_send_buf,uip_tcp_client_send_len);
                //uip_tcp_client_send_len = 0;
                Rs485_Send(Addr_IPV4,Addr_LCD,SHT20_All,uip_len,uip_tcp_client_send_buf);
                
            } 
            if(uip_tcp_client_send_len)
            {
                if(uip_conn == client_link_uip_conn[client_sel])
                {
                    uip_send(uip_tcp_client_send_buf,uip_tcp_client_send_len);
                    uip_tcp_client_send_len = 0;
                }           
            }            
        break;
    }
}
//==========================================================
//	�������ƣ�	void RS485_HandlerCb(void)
//
//	�������ܣ�	ͨ��485���߻�ȡ���ݴ�����
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		��ʱ��3�жϣ��ص�������ÿ100ms����һ��
//==========================================================
void RS485_HandlerCb(void)
{
    
}


