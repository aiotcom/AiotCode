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
#include "RS485.h"
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


extern uint8_t client_sel;
static uint8_t rEIR=0;
uint8_t uip_udp_client_send_buf[50];
uint8_t uip_udp_client_send_len = 0;
uint32_t UIP_RunTimeCounter = 0;
uint32_t UIP_HanlderCounter = 0;

uint32_t uip_udp_client_send_counter = 0;
uint32_t uip_tcp_client_send_counter = 0;
uint8_t uip_tcp_client_send_buf[50];
uint8_t uip_tcp_client_send_len;

uint8_t UpdataFlg,TxBuffer[5];
#define TCP_Client_Test 1  //TCP�ͻ���ʵ��
void RS485_HandlerCb(void);//����485�����ϵ�����
int main(void)
{
    uip_ipaddr_t ipaddr;
    HAL_Init();          //��ʼ��HAL��    
    
    UART1_Init(115200);
    UART2_Init(115200);
    USART3_Init(115200);
    Rs485_Init();
    
    TIM3_Init(10000-1,640-1,RS485_HandlerCb);
    SPI_Enc28j60_Init();
    uIP_Net_Init();//��ʼ��UIP,��ʼ��оƬ

	uip_ipaddr(&ipaddr, 192,168,3,31);		 //���ñ���IP��ַ
	uip_sethostaddr(&ipaddr);
	uip_ipaddr(&ipaddr, 192,168,3,1);		 //����Ĭ��·����IP��ַ  ����
	uip_setdraddr(&ipaddr);	
	uip_ipaddr(&ipaddr, 255,255,255,0);		 //������������
	uip_setnetmask(&ipaddr);
    
#if TCP_Client_Test    
	uip_ipaddr(&ipaddr,192,168,3,33);	//����IPΪ192.168.3.33 
    //��pxConnectServerConn ���������ڱ������ӷ������ı��ض˿ں� pxConnectServerConn->lport(local port)
	pxConnectServerConn = uip_connect(&ipaddr,htons(1200));//����һ��TCP Client ���ӣ�Զ��IP192.168.3.33,�˿���1200
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
#if TCP_Client_Test 
        //TCP�ͻ�����������    ÿ5000ms����һ������     
        if(UpdataFlg)
        {//���յ�����
            UpdataFlg = 0;
            memcpy((void*)uip_tcp_client_send_buf,TxBuffer,4);
            uip_tcp_client_send_len = 4;
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
struct uip_conn *client_link_uip_conn[2];
uint8_t count=0; 
void tcp_appcall(void)
{//��ʱ��ѯ��ÿ��conn
    if(((uip_conn->lport) == pxConnectServerConn->lport)&&(pxConnectServerConn))
    {
        if (uip_aborted())
        {
            printf("uip_aborted!\r\n");
            //aborted();
        }

        else if (uip_timedout())
        {
            printf("uip_timedout!\r\n");
            //timedout();
        }

        else if (uip_closed())//�������Ͽ�
        {
            printf("uip_closed!\r\n");
           // closed();
        }

        else if (uip_connected())
        {
            printf("uip_connected!\r\n");//�����Ϸ�����
            //connected();
        }

        else if (uip_acked())//�յ����ݻظ���ACK
        {
            printf("uip_acked!\r\n");
            //acked();
        }

        /* ���յ�һ���µ�TCP���ݰ�*/
        else if (uip_newdata())
        {//���յ������ݷ���
            memcpy((void*)uip_tcp_client_send_buf,(const void*)uip_appdata,uip_len);
            uip_tcp_client_send_len = uip_len;
            uip_send(uip_tcp_client_send_buf,uip_tcp_client_send_len);
            uip_tcp_client_send_len = 0;
        }
        /* ����Ҫ�ط��������ݵ�����ݰ��ʹ���ӽ���ʱ��֪ͨuip�������� */
        if (uip_rexmit() ||	uip_newdata() || uip_acked() ||	uip_connected() || uip_poll())
        {
            
        }
        
        if(uip_tcp_client_send_len)
        {
            uip_send(uip_tcp_client_send_buf,uip_tcp_client_send_len);
            uip_tcp_client_send_len = 0;
        }
    }
    switch(uip_conn->lport) //���ض˿�
    {
        case HTONS(1200):
            if(uip_connected())
            {//����пͻ��˽��룬�ߵ����client_link_uip_conn ����ͻ��˵�����
                client_link_uip_conn[count++] = uip_conn;
            }
            if(uip_newdata())
            {
                memcpy((void*)uip_tcp_client_send_buf,(const void*)"server return this\r\n",uip_len);
                uip_tcp_client_send_len = uip_len;
                uip_send(uip_tcp_client_send_buf,uip_tcp_client_send_len);
                uip_tcp_client_send_len = 0;  
            } 
            if(uip_tcp_client_send_len)
            {
                if(uip_conn == client_link_uip_conn[0])
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
    static uint32_t PollCounter=0;
    static uint8_t state = 0;
    
    if(state == 0)
    {
        if((++PollCounter) >= 20)
        {//2000ms����һ����ѯָ��
            PollCounter = 0;
            Rs485_Send(Addr_IPV4,Addr_SHT20,SHT20_Get_All,  0,(void*)0); 
            state = 1;
        }
    }
    else if(state == 1)
    {
        if(!DataHandling_485(Addr_IPV4))
        {
            memcpy((void*)TxBuffer,Rx_Stack.Data,4);
            UpdataFlg = 1;
        }
        state = 0;    
    }       
}


