#ifndef __Fan_H
#define __Fan_H 			   

#include "hal_types.h"
#define Fan P0_1            //����P0.1��ΪLED7���ƶ�
#include <ioCC2530.h>

extern void Fan_Init(void); //���ȳ�ʼ��
extern void FanOn(void);
extern void FanOff(void);
#endif

