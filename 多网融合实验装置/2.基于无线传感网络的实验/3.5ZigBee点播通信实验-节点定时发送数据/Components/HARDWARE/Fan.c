#include "Fan.h"
void FanOff(void);
/*
��ʼ�����ȿ���IO
*/
void Fan_Init(void)
{
   P0DIR |= 0x02;      //P0.1����Ϊ���
   FanOff();
}
/*
���Ʒ���ת��
*/
void FanOn(void)
{
  Fan = 1;
}
/*
���Ʒ���ֹͣ
*/
void FanOff(void)
{
  Fan = 0;
}