#ifndef _KEY_H
#define _KEY_H

#include <ioCC2530.h>
#include "hal_cc8051.h"

#define   S1    P1_5        //����P1.5��ΪS1���ƶ�
#define   S2    P1_4        //����P1.4��ΪS2���ƶ�
#define   S3    P0_0        //����P0.0��ΪS3���ƶ�
#define   S4    P0_1        //����P0.1��ΪS4���ƶ�

#define   S1_Read()   P1_5  //S1����P1_5
#define   S2_Read()   P1_4  //S2����P1_4
#define   S3_Read()   P0_0  //S3����P0_0
#define   S4_Read()   P0_1  //S4����P0_1

#define   S1_PRES     1
#define   S2_PRES     2
#define   S3_PRES     3
#define   S4_PRES     4

extern void KEY_Init(void);
extern void key_Operatio(void);
extern uint8_t KEY_Scan(uint8_t mode);

#endif