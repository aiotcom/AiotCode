#include "app_basicrf.h"
#include "stdio.h"
#include "hal_defs.h"
#include "hal_rf.h"

#define APP_PAYLOAD_LENGTH        30

static uint8 TxData[APP_PAYLOAD_LENGTH];
static uint8 RxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;
//==========================================================
//	�������ƣ�	void Rf_Init(uint8 rf_ch,uint16 panid,uint16 short_addr)
//
//	�������ܣ�	��ʼ�� RF ͨ��ģ��
//
//	��ڲ�����	uint8 rf_c,       ͨ���ŵ���
//              uint16 panid,     ���˾���������
//              uint16 short_addr, ����̵�ַ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Rf_Init(uint8 rf_ch,uint16 panid,uint16 short_addr)
{
    // Config basicRF
    basicRfConfig.panId      = panid;
    basicRfConfig.channel    = rf_ch;
    basicRfConfig.ackRequest = TRUE;
	basicRfConfig.myAddr     = short_addr;
    if(halRfInit()==FAILED)
    {
		printf("halRfInit failure!\r\n");
    }
	else
	{
	    if(basicRfInit(&basicRfConfig)==FAILED)
		{
		  printf("basicRfConfig failure!\r\n");
		  while(1);
		}	  
		printf("halRfInit successful!\r\n");
	}
	
   //��������
    basicRfReceiveOn();

}
//==========================================================
//	�������ƣ�	uint8_t Rf_Receive(uint8_t *precv)
//
//	�������ܣ�	��ʼ�� RF ͨ��ģ��
//
//	��ڲ�����	uint8 *precv,�������ݵ����顣
//
//	���ز�����	uint8_t�����յ����ݳ��ȣ��������ݽ��շ��� 0
//
//	˵����		
//==========================================================
uint8_t Rf_Receive(uint8_t *precv)
{
  	uint8_t len=0;
	
	if((len=basicRfReceive(precv, APP_PAYLOAD_LENGTH, NULL))>0)  //���շ��͵��õ�ַ������
	{
		printf("%d,%d\r\n",precv[0],precv[1]);
	}
	
	return len;
}