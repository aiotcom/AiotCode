#ifndef __HC_SR04_H
#define __HC_SR04_H 			   

#include <ioCC2530.h> 
#include "delay.h"

#define		Trigl1			P1_6
#define		Trigl2			P1_5		
#define		Trigl3			P0_0		
#define		Trigl4			P1_1		

#define		Echo1			P1_7		
#define		Echo2			P1_4
#define		Echo3			P0_1
#define		Echo4			P1_0	

#define 	Trigl1_HIGH()		Trigl1 = 1;
#define 	Trigl1_LOW()		Trigl1 = 0;

#define 	Trigl2_HIGH()		Trigl2 = 1;
#define 	Trigl2_LOW()		Trigl2 = 0;

#define 	Trigl3_HIGH()		Trigl3 = 1;
#define 	Trigl3_LOW()		Trigl3 = 0;

#define 	Trigl4_HIGH()		Trigl4 = 1;
#define 	Trigl4_LOW()		Trigl4 = 0;

#define 	Echo1_STATE()    	Echo1           //��ȡ���ص�ƽ
#define 	Echo2_STATE()    	Echo2	        //��ȡ���ص�ƽ
#define 	Echo3_STATE()    	Echo3	        //��ȡ���ص�ƽ
#define 	Echo4_STATE()    	Echo4           //��ȡ���ص�ƽ

extern void HCSR04_Init(void); 				//��ʼ��������ģ��
extern void HCSR04_StartMeasure(uint8_t number);	//������ģ����

#endif

