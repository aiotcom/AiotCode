#ifndef __Fan_H
#define __Fan_H 			   

#include <ioCC2530.h>

#define Fan P0_1            //����P0.1��ΪLED7���ƶ�

extern void Fan_Init(void); //���ȳ�ʼ��
extern void Fan_Set(uint32_t Num);  //���ȵ�λ����

#endif

