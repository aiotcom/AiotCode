#ifndef __LED_H
#define __LED_H 			   

#include <ioCC2530.h>

#define   LED1  P0_2        //����P0.2��ΪLED1���ƶ�
#define   LED2  P0_3        //����P0.3��ΪLED1���ƶ�
#define   LED3  P1_6        //����P1.6��ΪLED1���ƶ�
#define   LED4  P1_7        //����P1.7��ΪLED1���ƶ�

#define   LED1_ON()     LED1 = 0	//����LED1
#define   LED1_OFF()	LED1 = 1        //�ر�LED1

#define   LED2_ON()	LED2 = 0        //����LED2
#define   LED2_OFF()	LED2 = 1	//�ر�LED2

#define   LED3_ON()	LED3 = 0        //����LED3
#define   LED3_OFF()	LED3 = 1	//�ر�LED3

#define   LED4_ON()	LED4 = 0	//����LED4
#define   LED4_OFF()	LED4 = 1	//�ر�LED4

#define   LED_ON()	LED1=0;LED2=0;LED3=0;LED4=0;  //����ȫ��LED
#define   LED_OFF()	LED1=1;LED2=1;LED3=1;LED4=1;  //�ر�ȫ��LED

extern void LED_Init(void); //LED��ʼ��
extern void LED_Set(void);  //LED����
extern void LED_Type(uint8_t type);

#endif

