#ifndef __TEXT_H
#define __TEXT_H			  	 
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"    
#include "stdlib.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//OLED������ʾ��������
//������ʽ:8080����
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/03/25
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved	   
////////////////////////////////////////////////////////////////////////////////// 	

void LCD_Show_Font(unsigned int x,unsigned int y,unsigned char index);
void LCD_one_DrawPoint(unsigned int x,unsigned int y,unsigned int COLOR);
#endif  
	 



