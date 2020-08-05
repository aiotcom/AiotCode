#include "uIP_AppCall.h"
#include "stm32f1xx.h"
#include "enc28j60.h"
#include "uip.h"

/*uIP��ʼ������*/
#include "httpd.h"//httpd_appcall();
#include "uIP_AppCall.h"//tcp_test_appcall(); 
#include "uip_arch.h"
#include "uip-conf.h"
#include "uIP_App.h"
//���ڹ̶�IP��ַ���ش򿪺��IP���ã�������û�������
#define UIP_DRIPADDR0   192
#define UIP_DRIPADDR1   168
#define UIP_DRIPADDR2   1
#define UIP_DRIPADDR3   15

#define ETH_ADDR_LEN	6
static unsigned char mymac[6] = {0x04,0x02,0x35,0x00,0x00,0x01};  //MAC��ַ	   
/*uIP��ʼ���������*/

#include <string.h>
#include <stdio.h>
extern short CRC16_now( unsigned char *pBuffer, int length );
static uint8_t test_data[2048];   /* 1K�������� */
static uint8_t DataFromServerBuf[200];
static void aborted(void);
static void timedout(void);
static void closed(void);
static void connected(void);
static void newdata(void);
static void acked(void);
static void senddata(void);
static uint16_t CRCValue;
static uint8_t  OpenGateCmdFromPC = 0x01;
uip_tcp_appstate_t *pxDataFromServer;
/*******************************************************************************
*	������: tcp_test_appcall
*	��  ��: ��
*	��  ��: ��
*	����˵��������һ���ص���������h�ļ��У����Ƕ��� UIP_APPCALL�ĺ���� tcp_server_appcall
*	��tcp_test_appcall������tcp_server_appcall�� 
*	��uip�¼�����ʱ��UIP_APPCALL �����ᱻ���á�
*	���� : ��һ��TCP���ӱ�����ʱ�����µ����ݵ�������Ѿ���Ӧ��������Ҫ�ط����¼�
*
***************************************************************************/
void tcp_test_appcall(void)
{
	if (uip_aborted())
	{
		printf("uip_aborted!\r\n");
		aborted();
	}

	else if (uip_timedout())
	{
		printf("uip_timedout!\r\n");
		timedout();
	}

	else if (uip_closed())//�������Ͽ�
	{
		printf("uip_closed!\r\n");
		closed();
	}

	else if (uip_connected())
	{
		printf("uip_connected!\r\n");//�����Ϸ�����
		//connected();
	}

	else if (uip_acked())//�յ����ݻظ���ACK
	{
        printf("uip_acked!\r\n");
		acked();
	}

	/* ���յ�һ���µ�TCP���ݰ���׼����Ҫ�������� */
	else if (uip_newdata())
	{
		pxDataFromServer = (struct tcp_test_appstate *)&uip_conn->appstate;		
		pxDataFromServer->textptr = uip_appdata;   	
		pxDataFromServer->textlen = uip_len;
		memcpy((void*)DataFromServerBuf,(const void*)uip_appdata,uip_len);
	}
	/* ����Ҫ�ط��������ݵ�����ݰ��ʹ���ӽ���ʱ��֪ͨuip�������� */
	if (uip_rexmit() ||	uip_newdata() || uip_acked() ||	uip_connected() || uip_poll())
	{
		//senddata();
	}
}

/*******************************************************************************
*	������: aborted
*	��  ��: ��
*	��  ��: ��
*	����˵������TCP�����쳣��ֹʱ�����ô˺�����
***************************************************************************/
static void aborted(void)
{
	;
}

static void timedout(void)
{
	;
}

static void closed(void)
{
	;
}

/*******************************************************************************
*	������: connected
*	��  ��: ��
*	��  ��: ��
*	����˵������TCP���ӽ���ʱ�����ô˺�����
***************************************************************************/
static void connected(void)
{  
	/*
		uip_conn�ṹ����һ��"appstate"�ֶ�ָ��Ӧ�ó����Զ���Ľṹ�塣
		����һ��sָ�룬��Ϊ�˱���ʹ�á�

		����Ҫ�ٵ���Ϊÿ��uip_conn�����ڴ棬����Ѿ���uip�з�����ˡ�
		��uip.c �� ����ش������£�
		struct uip_conn *uip_conn;
		struct uip_conn uip_conns[UIP_CONNS]; //UIP_CONNSȱʡ=10
		������1�����ӵ����飬֧��ͬʱ�����������ӡ�
		uip_conn��һ��ȫ�ֵ�ָ�룬ָ��ǰ��tcp��udp���ӡ�
	*/
	struct tcp_test_appstate *s = (struct tcp_test_appstate *)&uip_conn->appstate;

	memset(test_data, 0x45, 2048);
	//memset(void *s,int c,size_t n) :
	//��s��ָ���ĳһ���ڴ��е�ÿ���ֽڵ�����ȫ������Ϊchָ����ASCIIֵ
	s->state = STATE_CMD;  //����״̬
	s->textlen = 0;

	s->textptr = "Connect STM32-RC Board Success!";
	s->textlen = strlen((char *)s->textptr);
}

/*******************************************************************************
*	������: TCPCmd
*	��  ��: ��
*	��  ��: ��
*	����˵��������PC������������͵������������Ӧ�Ĵ���
*	s->state ���������ı�
***************************************************************************/
uint8_t TestBuf[50];
void TCP_Cmd(struct tcp_test_appstate *s)
{
	uint8_t led;
	
	/* ����LED
		�﷨��ledon n  (n : 1 - 3) 
		���� �� 
		ledon 2 ��ʾ����LED2
		���յ�����ϢΪledon 1 ��uip_len����Ϊ7		
	*/
  memcpy((void*)TestBuf,(const void*)uip_appdata,uip_len);
	if ((uip_len == 7) && (memcmp("ledon ", uip_appdata, 6) == 0))
	{
		led = ((uint8_t *)uip_appdata)[6]; /* ������LED��� */
		if (led == '1')
		{
			//LED1_ON();
			s->textptr = "MyLed 1 On!";
		}
		else if (led == '2')
		{
			//LED2_ON();
			s->textptr = "Led 2 On!";			
		}
		else if (led == '3')
		{
			//LED3_ON();
			s->textptr = "Led 3 On!";
		}
	
		s->textlen = strlen((char *)s->textptr);
	}
	/* �ر�LED
		�﷨��ledoff n  (n : 1 - 4) 
		���� �� 
		ledon 2 ��ʾ����LED2	
	*/
	else if ((uip_len == 8) && (memcmp("ledoff ", uip_appdata, 7) == 0))
	{
		led = ((uint8_t *)uip_appdata)[7]; /* ������LED��� */
		if (led == '1')
		{
			//LED1_OFF();
			s->textptr = "Led 1 off!";
		}
		else if (led == '2')
		{
			//LED2_OFF();
			s->textptr = "Led 2 Off!";				
		}
		else if (led == '3')
		{
			//LED3_OFF();
			s->textptr = "Led 3 Off!";
		}
		
		s->textlen = strlen((char *)s->textptr);
	}
	/* �������ݲ��� txtest
		�﷨��txtest
		���� �� 
		
	*/
	else if ((uip_len == 6) && (memcmp("txtest", uip_appdata, 6) == 0))
	{
		s->state = STATE_TX_TEST;

		s->textptr = test_data;
		s->textlen = 1400;
	}
	/* �������ݲ��� rxtest
		�﷨��rxtest
		���� �� 
		
	*/
	else if ((uip_len == 6) && (memcmp("rxtest", uip_appdata, 6) == 0))
	{
		s->state = STATE_RX_TEST;
		s->textptr = "Ok";
		s->textlen = 2;
	}
	else
	{
		s->textptr = "Unknow Command!\r\n";
		s->textlen = strlen((char *)s->textptr);
	}
}

/*******************************************************************************
*	������: newdata
*	��  ��: ��
*	��  ��: ��
*	����˵�������յ��µ�TCP��ʱ�����ô˺�����׼�����ݣ�������ʱ�����͡�
***************************************************************************/
static void newdata(void)
{
//	struct tcp_test_appstate *s = (struct tcp_test_appstate *)&uip_conn->appstate;
//				
//	s->textptr = uip_appdata;   	
//	s->textlen = uip_len;

}

/*******************************************************************************
*	������: acked
*	��  ��: ��
*	��  ��: ��
*	����˵���������͵�TCP���ɹ��ʹ�ʱ�����ô˺�����
***************************************************************************/
static void acked(void)
{
	struct tcp_test_appstate *s = (struct tcp_test_appstate *)&uip_conn->appstate;

	switch(s->state)
	{
		case STATE_CMD:		 /* ������״̬ */
			s->textlen = 0;

			/* 
				ֻ������״̬��ӡ������Ϣ 
				���ⷢ�Ͳ���ʱ��Ӱ��ͨ���ٶ�		
			*/
			//USART_OUT(USART1,"uip_acked!\r\n");
			break;

		case STATE_TX_TEST:
			s->textptr = test_data;	/* �������� */
			s->textlen = 1400;
			break;

		case STATE_RX_TEST:
			s->textlen = 0;
			break;
	}
}

/*******************************************************************************
*	������: senddata
*	��  ��: ��
*	��  ��: ��
*	����˵��������tcp���ݡ�
***************************************************************************/
static void senddata(void)
{
	struct tcp_test_appstate *s = (struct tcp_test_appstate *)&uip_conn->appstate;

	if (s->textlen > 0)
	{
		/*
			��������������緢��TCP���ݰ�,
				s->textptr : ���͵����ݰ�������ָ��
				s->textlen �����ݰ��Ĵ�С����λ�ֽڣ�
		*/
		uip_send(s->textptr, s->textlen);
	}
}


/*************UDP����****************************/

/*******************************************************************************
*	������: void myudp_appcall(void) ) 
*	��  ��: 
*	��  ��: ��
*	��  ��: UDP�ص� ����
*	����#define UIP_UDP_APPCALL  myudp_appcall
**************************************************************************/
extern uint8_t uip_udp_client_send_buf[50];
extern uint8_t uip_udp_client_send_len;
void myudp_appcall(void) 
{ 
    /*
    uip ����ѯ��ǰUDP���ӣ�uip_udp_connָ��ǰ��ѯ��������
    */
    //printf("udp get data\r\n");
    if(uip_udp_conn == pxUDP_Conn)//udp�����������ݲο�
    {
        if(uip_udp_client_send_len > 0)
        {
            memcpy((void*)uip_appdata,(const void*)&uip_udp_client_send_buf[0],uip_udp_client_send_len);
            uip_send((char *)uip_appdata, uip_udp_client_send_len);
            uip_udp_client_send_len = 0;
        }
    }
   if(uip_newdata()/*��������*/&&(uip_udp_conn->lport == pxUDP_Conn->lport))//pxUDP_Conn udp�������ݲο�,���ܻ���ڶ��Ӧ�á�						
   { 
        memcpy((void*)&uip_udp_client_send_buf[0],(const void*)uip_appdata,uip_len);//��������
        uip_udp_client_send_len = uip_len;
        uip_send((char *)uip_udp_client_send_buf,uip_udp_client_send_len); 
        uip_udp_client_send_len = 0;
       
   } 
} 

/*******************************************************************************
*	������: void myudp_send(char *str,short n) 
*	��  ��: 
*	��  ��: ��
*	��  ��: UDP ���ݰ�����
**************************************************************************/
void myudp_send(char *str,short n) 
{ 
   char   *nptr;   
   nptr = (char *)uip_appdata;       
   memcpy(nptr, str, n); 
   uip_udp_send(n);   				//����n������ 
} 

/*******************************************************************************
*	������: void UDP_newdata(void) 
*	��  ��: 
*	��  ��: ��
*	��  ��: UDP ���ݰ�����
**************************************************************************/
void UDP_newdata(void) 
{ 
} 

/*******************************************************************************
*	������: etherdev_init
*	��  ��: ��
*	��  ��: ��
*	��  ��: uIP �ӿں���,��ʼ������
********************************************************************************/
void etherdev_init(void)
{	 
    uint8_t i;	 
	/*��ʼ�� enc28j60*/
	enc28j60Init(mymac);					  
	//��IP��ַ��MAC��ַд����ԵĻ�����	ipaddr[] macaddr[]
	//init_ip_arp_udp_tcp(mymac,myip,mywwwport);
	for (i = 0; i < 6; i++)
	{
		uip_ethaddr.addr[i] = mymac[i];
	}
    //ָʾ��״̬:0x476 is PHLCON LEDA(��)=links status, LEDB(��)=receive/transmit
    //enc28j60PhyWrite(PHLCON,0x7a4);
	//PHLCON��PHY ģ��LED ���ƼĴ���	
	enc28j60PhyWrite(PHLCON,0x0476);	
	enc28j60clkout(2); // change clkout from 6.25MHz to 12.5MHz
}

/*******************************************************************************
*	������: void tcp_server_appcall(void)
*	��  ��: 
*	��  ��: ��
*	��  ��: Ӧ�ýӿں���--���TCP��������HTTP������
**************************************************************************/
extern uint8_t uip_tcp_client_send_buf[50];
extern uint8_t uip_tcp_client_send_len;
struct uip_conn *client_link_uip_conn[2];
uint8_t client_sel = 0;
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
            acked();
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
                if(uip_conn == client_link_uip_conn[client_sel])
                {
                    uip_send(uip_tcp_client_send_buf,uip_tcp_client_send_len);
                    uip_tcp_client_send_len = 0;
                }
                if(uip_conn == client_link_uip_conn[client_sel])
                {
                    uip_send(uip_tcp_client_send_buf,uip_tcp_client_send_len);
                    uip_tcp_client_send_len = 0;
                }                
            }            
            break;
    }
}
void tcp_server_appcall(void)
{
    /*
    UIP ����ѯ����TCP���ӣ�
    */
/*  MCU����ΪTCP������ʱ��ʹ�ã������˿�*/
	switch(uip_conn->lport) //���ض˿�
	{
		case HTONS(80):			           //http������
			httpd_appcall(); //��uip/app/httpd.c�ļ��ж���
			break;
		case HTONS(1200):				   //TCP������ 
            printf("port 1200 get message\r\n");
		    httpd_appcall();
            //tcp_test_appcall(); 
		case HTONS(1500):				   //TCP������
		    tcp_test_appcall(); 		
			break;
	}
	
    /*MCU����ΪTCP�ͻ���ʱ��ʹ�ã�uip_conn->lport���յ���Ϣ��Ŀ��˿ڣ�pxConnectServerConn->lport�����ǽ�����һ��
    ���ӱ��ض˿ڣ�ԭ�����ǿ�����MUC�˽������TCP�ͻ������ӣ���Ҫ���ֱ�����Ϣ�Ƿ��͸��Ǹ�����*/   
    if(((uip_conn->lport) == pxConnectServerConn->lport)&&(pxConnectServerConn))
    {
        tcp_test_appcall();
    }
    
    //appstate �û��Լ��ӵ�
    if((uip_conn->appstate.state == STATE_CMD) && (uip_conn == pxConnectServerConn))
    {//�統ǰ��ѯ����TCP���Ӽ������������������������Ǹ�����
        uip_send("tcp client send data\r\n",sizeof("tcp client send data\r\n"));
    }
}

/* uip_log
uIP�ĵ��Դ�ӡ��䡣
����ͨ��ע�� #define UIP_CONF_LOGGING     ���رյ������

void uip_log(char *m)
{
	//USART_OUT(USART1,"uIP log message: %s\r\n", m);
}*/
