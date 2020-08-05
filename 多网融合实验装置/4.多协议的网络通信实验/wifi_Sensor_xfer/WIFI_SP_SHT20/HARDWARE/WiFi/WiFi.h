#ifndef __WiFi_H__
#define __WiFi_H__

#include "stm32f1xx_hal.h"

#define	CLOSE_TCP    (uint8_t*)"+++"																						//�ر�TCP���ӣ��˳�͸��ģʽ
#define AT         	 (uint8_t*)"AT\r\n"
#define CWMODE     	 (uint8_t*)"AT+CWMODE=1\r\n"																//����ģʽΪSTA
#define RST        	 (uint8_t*)"AT+RST\r\n"																			//������ģ��
#define CIFSR        (uint8_t*)"AT+CIFSR\r\n"																		//��ѯIP��ַ
#define CWJAP        (uint8_t*)"AT+CWJAP=\"BBCC\",\"12345678\"\r\n"				//����SID��PWD��������
#define TCP_CIPSTART (uint8_t*)"AT+CIPSTART=\"TCP\",\"192.168.4.3\",8080\r\n"	//����ΪTCPЭ�鴫�䲢ָ��IP�Ͷ˿ں�
#define CIPMODE      (uint8_t*)"AT+CIPMODE=1\r\n"																//͸��
#define CIPSEND      (uint8_t*)"AT+CIPSEND\r\n"																	//��ʼ����
/**
  * @brief  ��ʼ��ESP8266,������·�ɺ�����ƽ̨
  * @param  server:����ATָ�����÷�������ַ�Ͷ˿��ַ���
    * @param  ssid_pwd: ����ATָ������·������SSID��PWD
  * @retval NONE
  **/
extern uint8_t WiFi_AT_STA;    /*ATָ�����ɱ�־λ*/
void WiFi_Init(void);
uint8_t WiFi_Receive(uint8_t *precv);
void WiFi_Send(uint8_t *pdata,uint8_t len);
void WiFi_ByteReceive(uint8_t byte);
#endif


