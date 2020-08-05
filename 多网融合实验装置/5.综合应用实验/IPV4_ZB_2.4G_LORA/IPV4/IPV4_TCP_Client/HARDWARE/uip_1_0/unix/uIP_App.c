#include "uIP_App.h"
#include "stm32f1xx.h"
#include "uIP_AppCall.h"
#include "uip.h"
#include "tapdev.h"
#include "clock-arch.h"
#include "timer.h"
#include "uip_arp.h"

/*uIP  stack*/
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
#define uIP_INT_Statue GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)          //ENC28J60����֡����жϽ� 

struct uip_conn *pxConnectServerConn = 0;
struct uip_udp_conn *pxUDP_Conn = 0;
struct timer periodic_timer, arp_timer;//��ʱʱ��0.5s,10s

FlagStatus *ETH_INT;




/****************************************************************************
* ��    �ƣ�void eth_poll(void)
* ��    �ܣ���ʱ��ѯTCP�����շ�״̬	ARP����£� ����Ӧ
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void eth_poll(void)
{
	unsigned char i=0;
	if(timer_expired(&periodic_timer))	/* 0.5�붨ʱ����ʱ */
	{
        
		timer_reset(&periodic_timer);
		/* ��������ÿ��TCP����, UIP_CONNSȱʡ��10�� */
		for(i = 0; i < UIP_CONNS; i++)
		{
			uip_periodic(i);/* ��ѯÿ��TCPͨ���¼�(���10��) */
			/*
				������ĺ���ִ�к������Ҫ�������ݣ���ȫ�ֱ��� uip_len > 0
				��Ҫ���͵�������uip_buf, ������uip_len  (����2��ȫ�ֱ���)
			*/
			if(uip_len > 0)
			{
				uip_arp_out();		//����̫��ͷ�ṹ������������ʱ����Ҫ����ARP����
				tapdev_send();		//�������ݵ���̫�����豸��������
			}
		}

	#if UIP_UDP
		/* ��������ÿ��UDP����, UIP_UDP_CONNSȱʡ��10�� */
		for(i = 0; i < UIP_UDP_CONNS; i++)
		{
			uip_udp_periodic(i);	/*����UDPͨ���¼� */
			/* �������ĺ������õ�������Ӧ�ñ����ͳ�ȥ��ȫ�ֱ���uip_len�趨ֵ> 0 */
			if(uip_len > 0)
			{
				uip_arp_out();		//����̫��ͷ�ṹ������������ʱ����Ҫ����ARP����
				tapdev_send();		//�������ݵ���̫�����豸��������
			}
		}
	#endif /* UIP_UDP */

		/* ÿ��10�����1��ARP��ʱ������ ���ڶ���ARP����,ARP��10�����һ�Σ��ɵ���Ŀ�ᱻ����*/
		if(timer_expired(&arp_timer))
		{
			timer_reset(&arp_timer);
			uip_arp_timer();
		}
	}
}

/*******************************************************************************
*	��������UipPro
*	��  ��:
*	��  ��:
*	����˵�����жϴ�����ȡ������ջ���
*	ע�⣺��ʹ��uCOSʱ�����ʺ����жϡ�����ؽ��ǡ�
********************************************************************/
void UipPro(void)
{
//	uint8_t err;
/*	//ע�⣺�����Ҫд����ǰ�治Ӧ���ں�����
uIP_INT_Mbox = OSMboxCreate((void *)0); // ��������*/

//	ETH_INT=OSMboxPend(uIP_INT_Mbox,0, &err);//������Ϣ
//	if(*ETH_INT==SET)
	{					//��������յ�����ʱ��������ж�
//	rep:
//		*ETH_INT=RESET;
		uip_len = tapdev_read();	//�������豸��ȡһ��IP��,�������ݳ���
		if(uip_len > 0)			    //�յ�����ʱ���Ȼ�仯
		{
			/* ����IP���ݰ�(ֻ��У��ͨ����IP���Żᱻ����) */
			if(BUF->type == htons(UIP_ETHTYPE_IP))   //�յ�IP��
			{
				uip_arp_ipin();		   //ȥ����̫��ͷ�ṹ������ARP��
				uip_input();		   //IP������
				/*
					��Ϊuip_input();���������˻ص�����UIP_APPCALL(),��tcp_server_appcall
					������ĺ���ִ�к�����ص�������Ҫ�������ݣ���ȫ�ֱ��� uip_len > 0
					��Ҫ���͵�������uip_buf, ������uip_len  (����2��ȫ�ֱ���)
				*/
				if (uip_len > 0)		//�д����Ӧ����
				{
					uip_arp_out();		//����̫��ͷ�ṹ������������ʱ����Ҫ����ARP����
					tapdev_send();		//�������ݵ���̫�����豸��������
				}
			}
			/* ����arp���� */
			else if (BUF->type == htons(UIP_ETHTYPE_ARP))	//��ARP�����
			{
				uip_arp_arpin();		//������ARP��Ӧ������ARP����������󣬹����Ӧ���ݰ�
				/*
					������ĺ���ִ�к������Ҫ�������ݣ���ȫ�ֱ��� uip_len > 0
					��Ҫ���͵�������uip_buf, ������uip_len  (����2��ȫ�ֱ���)
				*/
				if (uip_len > 0)		//��ARP����Ҫ���ͻ�Ӧ
				{
					tapdev_send();		//��ARP��Ӧ����̫����
				}
			}
		}
  	}
//  	else
//	{//��ֹ�����ɽ�������,��û�в����жϣ���ENC28J60�ж��ź�ʼ��Ϊ��˵����������
//  	  if(uIP_INT_Statue==0) 
//		goto rep; 	
//  	}
}

/*******************************************************************************
*	��������InitNet
*	��  ��:
*	��  ��:
*	����˵������ʼ������Ӳ����UIPЭ��ջ�����ñ���IP��ַ
************************************************************/
#if 0
#define TCP_Client 0
#define TCP_Server 0
#define UDP_client 1
#define UDP_SERVER 0
#define HTTP       0
#endif
void uIP_Net_Init(void)
{
	uip_ipaddr_t ipaddr;	
    
	timer_set(&periodic_timer, CLOCK_SECOND / 10);
	timer_set(&arp_timer, CLOCK_SECOND); 

	tapdev_init();//��̫������������ENC28J60��ʼ��
	uip_init();								 //UIPЭ��ջ��ʼ��
}







