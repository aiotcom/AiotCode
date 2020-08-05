#ifndef __LED_H
#define __LED_H 			   

#include <ioCC2530.h>

#define   Relay1  P0_2    //����P0.2��Ϊ�̵���1���ƶ�
#define   Relay2  P0_3    //����P0.3��Ϊ�̵���2���ƶ�

#define   Relay1_ON()   Relay1 = 0    //�򿪼̵���1
#define   Relay1_OFF()	Relay1 = 1    //�رռ̵���1

#define   Relay2_ON()	Relay2 = 0    //�򿪼̵���2
#define   Relay2_OFF()	Relay2 = 1    //�رռ̵���2

extern void Relay_Init(void); //LED��ʼ��

#endif

