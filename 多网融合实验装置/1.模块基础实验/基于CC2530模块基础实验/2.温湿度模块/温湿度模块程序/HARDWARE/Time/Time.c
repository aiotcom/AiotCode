#include "Time.h"
#include "Rs485.h"

uint32_t Display_Count = 0;		//�������ʾ����ֵ
uint8_t Temp[10],Humi[10],Sum_Data[10]; //�¶ȡ�ʪ�ȡ����ݼ���

//==========================================================
//	�������ƣ�	Init_Timer1()
//
//	�������ܣ�	��ʱ��1��ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����
//==========================================================
void Init_Timer1(void)
{
  T1CC0L = 0xC4;        //����������ֵ�ĵ�8λ
  T1CC0H = 0x09;        //����������ֵ�ĸ�8λ
  T1CCTL0 |= 0x04;      //����ͨ��0������Ƚ�ģʽ
  T1IE = 1;             //ʹ�ܶ�ʱ��1�ж�
  T1OVFIM = 1;          //ʹ�ܶ�ʱ��1����ж�
  EA = 1;               //ʹ�����ж�
  T1CTL = 0x0e;         //��Ƶϵ����128,ģģʽ
}

//==========================================================
//	�������ƣ�	Timer1_Sevice()
//
//	�������ܣ�	��ʱ��1������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
#pragma vector = T1_VECTOR
__interrupt void Timer1_Sevice()
{
  Display_Count++;
  if(!DataHandling_485(Addr_SHT20))//����485����
  {
    switch(Rx_Stack.Command)
    {
      case SHT20_Get_Temp:      //��ȡ�¶�����
        Rs485_Send(Addr_SHT20,Rx_Stack.Src_Adr,SHT20_Temp,1,Temp);  //�����¶�����
        break;
      case SHT20_Get_Humi:	//��ȡʪ������
        Rs485_Send(Addr_SHT20,Rx_Stack.Src_Adr,SHT20_Humi,1,Humi);  //����ʪ������
        break;
      case SHT20_Get_All:	//��ȡ��ʪ��
        Rs485_Send(Addr_SHT20,Rx_Stack.Src_Adr,SHT20_All,2,Sum_Data);//������ʪ��+��ǿ����
        break;
      default:break;
    }
  }
  T1STAT &= ~0x01;              //�����ʱ��1ͨ��0�жϱ�־ 
}
