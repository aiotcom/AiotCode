#ifndef __LED_H
#define __LED_H 			   

#include <ioCC2530.h>
#include "hal_cc8051.h"

#define   LED1  P0_2        //����P0.2��ΪLED1���ƶ�
#define   LED2  P0_3        //����P0.3��ΪLED2���ƶ�
#define   LED3  P1_6        //����P1.6��ΪLED3���ƶ�
#define   LED4  P1_7        //����P1.7��ΪLED4���ƶ�

#define   LED1_SET()    MCU_IO_SET_HIGH(0,2);      //����P0.2��ΪLED1���ƶ�
#define   LED1_RESET()  MCU_IO_SET_LOW(0,2);       //����P0.2��ΪLED1���ƶ�

#define   LED2_SET()    MCU_IO_SET_HIGH(0,3);      //����P0.3��ΪLED2���ƶ�
#define   LED2_RESET()  MCU_IO_SET_LOW(0,3);       //����P0.3��ΪLED2���ƶ�

#define   LED3_SET()    MCU_IO_SET_HIGH(1,6);      //����P1.6��ΪLED3���ƶ�
#define   LED3_RESET()  MCU_IO_SET_LOW(1,6);       //����P1.6��ΪLED3���ƶ�

#define   LED4_SET()    MCU_IO_SET_HIGH(1,7);      //����P1.7��ΪLED4���ƶ�
#define   LED4_RESET()  MCU_IO_SET_LOW(1,7);       //����P1.7��ΪLED4���ƶ�

extern void LED_Init(void); //LED��ʼ��
extern void LED_Set(void);  //LED����

#endif

