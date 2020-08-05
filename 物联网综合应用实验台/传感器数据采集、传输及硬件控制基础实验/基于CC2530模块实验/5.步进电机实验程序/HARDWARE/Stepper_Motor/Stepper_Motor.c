#include "Stepper_Motor.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

//==========================================================
//	�������ƣ�	Stepper_Motor_Init()
//
//	�������ܣ�	���������ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Stepper_Motor_Init(void)
{
   P0DIR |= 0x03;      //P0.0��P0.1����Ϊ���
   P1DIR |= 0x03;      //P1.0��P1.1����Ϊ���
	
  A1LOW();A0LOW();B1LOW();B0LOW();//��ʼ������
}

//==========================================================
//	�������ƣ�	Stepper_Motor_Set()
//
//	�������ܣ�	���ò������ת������
//
//	��ڲ�����	A1:	A+
//			A0:	A-
//			B1:	B+
//			B0:	B-
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Stepper_Motor_Set(uint8_t A1,uint8_t A0,uint8_t B1,uint8_t B0)
{
    if(A1) A1HIGH();
    else A1LOW();
    
    if(A0) A0HIGH();
    else A0LOW();
    
    if(B1) B1HIGH();
    else B1LOW();
    
    if(B0) B0HIGH();
    else B0LOW();
}

//==========================================================
//	�������ƣ�	Stepper_Motor_Turn()
//
//	�������ܣ�	���ò������ת��
//
//	��ڲ�����	Direction:��ת���� 1��˳ʱ��  0����ʱ��
//			Cycle_Number��ת��Ȧ��
//			Delay: 	תһȦ��ʱ(ms)
//
//	���ز�����	��
//
//	˵����			angle
//==========================================================
void Stepper_Motor_Turn(uint8_t Direction,uint16_t Cycle_Number,uint16_t Delay)
{
    static uint32_t i = 0;
    static uint16_t Time = 0;
    
    if(Delay>=40)
      Time = Delay/20;
    else
      Time = 2;
    
    if(Direction)
    {
        for(i=0;i<(Cycle_Number*5);i++)
        {
            Stepper_Motor_Set(1,0,0,0);//��һ��
            delay_ms(Time);

            Stepper_Motor_Set(0,0,1,0);//�ڶ���
            delay_ms(Time);

            Stepper_Motor_Set(0,1,0,0);//������
            delay_ms(Time);

            Stepper_Motor_Set(0,0,0,1);//������
            delay_ms(Time);
        }
    }
    else
    {
        for(i=0;i<(Cycle_Number*5);i++)
        {
            Stepper_Motor_Set(0,0,0,1);//��һ��
            delay_ms(Time);

            Stepper_Motor_Set(0,1,0,0);//�ڶ���
            delay_ms(Time);

            Stepper_Motor_Set(0,0,1,0);//������
            delay_ms(Time);

            Stepper_Motor_Set(1,0,0,0);//������
            delay_ms(Time);
        }
    }
    A1LOW();A0LOW();B1LOW();B0LOW();//��ʼ������
}


