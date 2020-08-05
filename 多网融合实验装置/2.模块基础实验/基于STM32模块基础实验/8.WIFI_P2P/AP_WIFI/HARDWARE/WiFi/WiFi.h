#ifndef __WiFi_H__
#define __WiFi_H__

#include "stm32f1xx_hal.h"

#define	CLOSE_TCP    (uint8_t*)"+++"																						//�ر�TCP���ӣ��˳�͸��ģʽ
#define AT         	 (uint8_t*)"AT\r\n"
#define CWMODE     	 (uint8_t*)"AT+CWMODE=3\r\n"																//����ģʽΪAP+STA
#define RST        	 (uint8_t*)"AT+RST\r\n"																			//������ģ��
#define CIFSR        (uint8_t*)"AT+CIFSR\r\n"																		//��ѯIP��ַ
#define CWJAP        (uint8_t*)"AT+CWJAP=\"bacheng\",\"f0f0f0f0f0\"\r\n"				//����SID��PWD��������
#define TCP_CIPSTART (uint8_t*)(uint8_t*)"AT+CIPSTART=\"TCP\",\"183.230.40.40\",1811\r\n"	//����ΪTCPЭ�鴫�䲢ָ��IP�Ͷ˿ں�
#define CIPMODE      (uint8_t*)"AT+CIPMODE=1\r\n"																//͸��
#define CIPSEND      (uint8_t*)"AT+CIPSEND\r\n"																	//��ʼ����
#define CIPSTATUS    (uint8_t*)"*238724#0001#sample*"														//ONE.NETƽ̨�����˺�ʶ����

/**
  * @brief  ��ʼ��ESP8266,������·�ɺ�����ƽ̨
  * @param  server:����ATָ�����÷�������ַ�Ͷ˿��ַ���
    * @param  ssid_pwd: ����ATָ������·������SSID��PWD
  * @retval NONE
  **/
extern uint8_t WiFi_AT_STA;    /*ATָ�����ɱ�־λ*/
void WiFi_Init(void);

#endif


