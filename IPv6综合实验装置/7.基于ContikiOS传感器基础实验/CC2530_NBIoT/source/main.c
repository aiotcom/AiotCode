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

//****宏定义*******************
#define TCP_Client_Test 1  //TCP客户端实验
#define TCP_Server_Test 0  //TCP服务器实验
#define UDP_TEST        0  //UDP实验
//****宏定义*******************

//****函数定义*****************
void System_clockInit(void);
//****函数定义*****************

//****变量定义*******************
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
//****变量定义*******************

//==========================================================
//	函数名称：	Init_Timer1()
//
//	函数功能：	定时器1初始化函数
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		定时器时钟16MHz，中断周期1000HZ
//==========================================================
void main(void)
{
  	uip_ipaddr_t ipaddr;
  	System_clockInit();
	TIM1_Init();
  	UART_Init(UART_0);
	printf("this is uart0 print\r\n");
    SPI_Enc28j60_Init();
    uIP_Net_Init();//初始化UIP,初始化芯片

	uip_ipaddr(ipaddr, 192,168,3,33);		 //设置本地IP地址
	uip_sethostaddr(ipaddr);
	uip_ipaddr(ipaddr, 192,168,3,1);		 //设置默认路由器IP地址  网关
	uip_setdraddr(ipaddr);	
	uip_ipaddr(ipaddr, 255,255,255,0);		 //设置网络掩码
	uip_setnetmask(ipaddr);
    
#if TCP_Client_Test    
	uip_ipaddr(&ipaddr,192,168,3,3);	//设置IP为192.168.1.12 
    //在pxConnectServerConn 包括了用于本次连接服务器的本地端口号 pxConnectServerConn->lport(local port)
	pxConnectServerConn = uip_connect(&ipaddr,htons(1400));//创建一个TCP Client 连接，远端IP192.168.0.3,端口是1400
#endif    


#if TCP_Server_Test
    uip_listen(HTONS(1200));//TCP监听
#endif

#if UDP_TEST
    uip_ipaddr(&ipaddr,192,168,3,3);	//设置连接目标端的IP为192.168.3.3
    pxUDP_Conn = uip_udp_new(&ipaddr,htons(1400)); 	//端口为1400
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
/*
void myudp_appcall(void) ;UDP数据接收uIP_AppCall.c
void tcp_appcall(void)   ;UDP数据接收uIP_AppCall.c
*/
#if UDP_TEST     
        //TCP客户端主动发送   每5000ms发送一次数据       
        if(HAL_GetTick() > uip_udp_client_send_counter)
        {
            uip_udp_client_send_counter = HAL_GetTick()+5000;
            sprintf(&uip_udp_client_send_buf[0],"uwTick=%ld\r\n",(unsigned long)HAL_GetTick());
            uip_udp_client_send_len = strlen((const char*)&uip_udp_client_send_buf[0]);
        }
#endif 

#if TCP_Client_Test 
        //TCP客户端主动发送    每5000ms发送一次数据     
        if(HAL_GetTick() > uip_tcp_client_send_counter)
        {
            uip_tcp_client_send_counter = HAL_GetTick()+5000;
            sprintf(&uip_tcp_client_send_buf[0],(uint8_t*)"uwTick=%ld\r\n",(unsigned long)HAL_GetTick());
            uip_tcp_client_send_len = strlen((const char*)&uip_tcp_client_send_buf[0]);
        } 
#endif
		
#if TCP_Server_Test
        //TCP服务器主动发送 每5000ms发送一次数据
        if(HAL_GetTick() > uip_tcp_client_send_counter)
        {
            uip_tcp_client_send_counter = HAL_GetTick()+2500;
            sprintf(&uip_tcp_client_send_buf[0],"uwTick=%ld\r\n",(unsigned long)HAL_GetTick());
            uip_tcp_client_send_len = strlen((const char*)&uip_tcp_client_send_buf[0]);
        }
#endif        
	}
}	
//==========================================================
//	函数名称：	void System_clockInit(void)
//
//	函数功能：	初始化系统时钟
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		定时器时钟16MHz，中断周期1000HZ
//==========================================================
void System_clockInit(void)
{
  CLKCONCMD &= ~(1<<6);        /*选择32MHz晶振*/  
  while(!(CLKCONSTA & (1<<6))); /*等待晶振稳定*/  
  CLKCONCMD &= ~0x47;          /* 不分频,系统时钟32MHZ，定时器时钟16MHZ*/             
}