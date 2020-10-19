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
void RS485_HandlerCb(void);

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
uint8_t ConndecServerFlg=0;
uint32_t SendCount = 0;
#define TCP_Client_Test 1  //TCP�ͻ���ʵ��
uint8_t LoraChReceiveRxLen = 0,loraChReceive=0,loraChReceiveBuffer[64];
uint8_t _24GChReceiveRxLen = 0,_24GChReceive=0,_24GChReceiveBuffer[64];
uint8_t zigBeeChReceiveRxLen = 0,zigBeeChReceive=0,zigBeeChReceiveBuffer[64];

#define NBR_OF_TARGET 3
uint8_t  PollTargetIndex = 0;
uint16_t PollTarget[NBR_OF_TARGET]={Addr_2_4G,Addr_LORA,Addr_ZigBee};
int main(void)
{
    uip_ipaddr_t ipaddr;
    HAL_Init();          //��ʼ��HAL��    
    HAL_Delay(1000);
    UART1_Init(115200);
    UART2_Init(115200);
    USART3_Init(115200);
    Rs485_Init();
    
    TIM3_Init(10000-1,640-1,RS485_HandlerCb);//10HZ �ж�Ƶ��
    SPI_Enc28j60_Init();
    uIP_Net_Init();//��ʼ��UIP,��ʼ��оƬ

	uip_ipaddr(&ipaddr, 192,168,3,31);		 //���ñ���IP��ַ
	uip_sethostaddr(&ipaddr);
	uip_ipaddr(&ipaddr, 192,168,3,1);		 //����Ĭ��·����IP��ַ  ����
	uip_setdraddr(&ipaddr);	
	uip_ipaddr(&ipaddr, 255,255,255,0);		 //������������
	uip_setnetmask(&ipaddr);
    
#if TCP_Client_Test    
	uip_ipaddr(&ipaddr,192,168,3,3);	//����IPΪ192.168.3.33 
    //��pxConnectServerConn ���������ڱ������ӷ������ı��ض˿ں� pxConnectServerConn->lport(local port)
	pxConnectServerConn = uip_connect(&ipaddr,htons(1200));//����һ��TCP Client ���ӣ�Զ��IP192.168.3.33,�˿���1200
#endif    

    UIP_RunTimeCounter = HAL_GetTick()+50;
    UIP_HanlderCounter = HAL_GetTick()+50;  
    uip_udp_client_send_counter = HAL_GetTick()+1000;    
    uip_tcp_client_send_counter = HAL_GetTick()+1000;
    SendCount = HAL_GetTick()+500;
    printf("START\r\n");
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
        if(HAL_GetTick() >= SendCount)
        {//���յ�����
            SendCount = HAL_GetTick()+100;
            if(ConndecServerFlg)
            {
                if(loraChReceive)
                {
                    printf("send lora data\r\n");
                    loraChReceive = 0;
                    memcpy((void*)uip_tcp_client_send_buf,loraChReceiveBuffer,LoraChReceiveRxLen);
                    uip_tcp_client_send_len = strlen((char const*)uip_tcp_client_send_buf);
                }
                else if(_24GChReceive)
                {
                    printf("send 24G data\r\n");
                    _24GChReceive = 0;
                    memcpy((void*)uip_tcp_client_send_buf,_24GChReceiveBuffer,_24GChReceiveRxLen);
                    uip_tcp_client_send_len = strlen((char const*)uip_tcp_client_send_buf);
                } 
                else if(zigBeeChReceive) 
                {
                    printf("send ZigBee data\r\n");
                    zigBeeChReceive = 0;
                    sprintf((void*)uip_tcp_client_send_buf,"Temp=%d,Humi=%d\r\n",zigBeeChReceiveBuffer[0],zigBeeChReceiveBuffer[1]);
                    uip_tcp_client_send_len = strlen((const char*)uip_tcp_client_send_buf);                                
                }                    
            }
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
            ConndecServerFlg = 1;
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
        if((++PollCounter) >= 5)
        {//500ms����һ����ѯָ��
            PollCounter = 0;
            Rs485_Send(Addr_IPV4,PollTarget[PollTargetIndex],SHT20_Get_All,  0,(void*)0); 
            printf("send:%d\r\n",PollTargetIndex);
            if((++PollTargetIndex) == NBR_OF_TARGET)
            {
                PollTargetIndex = 0;
            }
            
            state = 1;
        }
    }
    else if(state == 1)
    {
        if(!DataHandling_485(Addr_IPV4))
        {
            if(Rx_Stack.Src_Adr == Addr_LORA)
            {
                printf("get lora\r\n");
                LoraChReceiveRxLen = Rx_Stack.Data_Len;
                memcpy((void*)loraChReceiveBuffer,Rx_Stack.Data,Rx_Stack.Data_Len);   
                loraChReceive = 1;
            }
            else if(Rx_Stack.Src_Adr == Addr_2_4G)
            {
                printf("get 2.4G\r\n");
                _24GChReceiveRxLen = Rx_Stack.Data_Len;
                memcpy((void*)_24GChReceiveBuffer,Rx_Stack.Data,Rx_Stack.Data_Len);   
                _24GChReceive = 1;
            }
            else if(Rx_Stack.Src_Adr == Addr_ZigBee)
            {
                printf("get zigbee\r\n");
                zigBeeChReceiveRxLen = Rx_Stack.Data_Len;
                memcpy((void*)zigBeeChReceiveBuffer,Rx_Stack.Data,Rx_Stack.Data_Len);   
                zigBeeChReceive = 1;
            }  
        }        
        state = 0;    
    }       
}


