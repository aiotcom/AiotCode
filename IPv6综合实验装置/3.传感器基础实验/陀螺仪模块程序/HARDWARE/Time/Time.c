#include "Time.h"
#include "Rs485.h"

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
//  if(!DataHandling_485(Addr_HF_RFID)) //����485����
//  {
//    switch(Rx_Stack.Command)
//    {
//      case HF_RFID_Get_ID:	//��ȡID����
//        Rs485_Send(Addr_HF_RFID,Rx_Stack.Src_Adr,HF_RFID_ID,4,ucArray_ID);	//����ID����
//        break;
//      case HF_RFID_Get_Block:	//��ȡData����
//        Rs485_Send(Addr_HF_RFID,Rx_Stack.Src_Adr,HF_RFID_Block,16,Block_Date);	//����Data����
//        break;
//      case HF_RFID_Get_All:	//��ȡID+Data����
//        Rs485_Send(Addr_HF_RFID,Rx_Stack.Src_Adr,HF_RFID_All,20,Data_Send);	//����ID+Data����
//        break;
//      default:break;
//    }
//  }
  T1STAT &= ~0x01; //�����ʱ��1ͨ��0�жϱ�־ 
}
