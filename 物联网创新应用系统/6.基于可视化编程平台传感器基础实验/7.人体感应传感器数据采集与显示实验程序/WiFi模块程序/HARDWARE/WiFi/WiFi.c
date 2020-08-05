#include "WiFi.h"
#include "delay.h"
#include "Usart.h"

uint8_t WiFi_AT_STA = 0;

//==========================================================
//	�������ƣ�	WiFi_Init()
//
//	�������ܣ�	WIFI����ONE.NETƽ̨ATָ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void WiFi_Init(void)
{
//		while(!WiFi_Send_Cmd(CLOSE_TCP,"",5));				/*�˳�WiFi͸��ģʽ*/
//		
//		delay_ms(3000);	
		while(!WiFi_Send_Cmd(AT,"OK",20));						/*����AT����ģʽ*/
		
		while(!WiFi_Send_Cmd(CWMODE,"OK",30));				/*����ģ��Ӧ��ģʽ*/
	
		while(!WiFi_Send_Cmd(CWJAP,"OK",300));				/*����Ҫ���ӵ�·������SSID������*/
	
		while(!WiFi_Send_Cmd(TCP_CIPSTART,"OK",60));	/*�����������TCP����*/
	
		while(!WiFi_Send_Cmd(CIPMODE,"OK",60));				/*͸��ģʽ*/
	
		while(!WiFi_Send_Cmd(CIPSEND,"OK",30));				/*��ʼ����*/
	
		WiFi_AT_STA = 1;           										/*ATָ�����ɱ�־λ*/
}




