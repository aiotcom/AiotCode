#ifndef __WiFi_H
#define __WiFi_H 			   

#include <ioCC2530.h>
#include "delay.h"

#define WiFi_RES P1_5  //����P1.5��ΪRES���ƶ�
#define WiFi_LED P1_6  //����P1.6��ΪLED���ƶ�
#define WiFi_KEY P1_7  //����P1.7��ΪKEY���ƶ�

#define WiFi_KEY_Read()   WiFi_KEY  //����

#define WiFi_LED_HI {WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;\
        WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0; }

#define WiFi_LED_LO {WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 1;WiFi_LED = 0;\
        WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0;WiFi_LED = 0; }

#define	CLOSE_TCP     "+++"						//�ر�TCP���ӣ��˳�͸��ģʽ
#define AT            "AT\r\n"
#define CWMODE        "AT+CWMODE=3\r\n"					//����ģʽΪAP+STA
#define RST           "AT+RST\r\n"					//������ģ��
#define CIFSR         "AT+CIFSR\r\n"					//��ѯIP��ַ
#define CWJAP         "AT+CWJAP=\"bacheng\",\"f0f0f0f0f0\"\r\n"		//����SID��PWD��������
#define TCP_CIPSTART  "AT+CIPSTART=\"TCP\",\"183.230.40.40\",1811\r\n"	//����ΪTCPЭ�鴫�䲢ָ��IP�Ͷ˿ں�
#define CIPMODE       "AT+CIPMODE=1\r\n"				//͸��
#define CIPSEND       "AT+CIPSEND\r\n"					//��ʼ����
#define CIPSTATUS     "*238724#0001#sample*"				//ONE.NETƽ̨�����˺�ʶ����

extern void WiFi_Init(void); //WiFi��ʼ��
extern void WiFi_LED_REST(void);
extern void WiFi_Set_White(void);
extern void WiFi_LED_SET(uint32_t G8R8B8);

#endif

