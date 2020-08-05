#include "mp3.h"
uint8_t Start[5] 	= {0x7E,0X03,0XAA,0XAD,0XEF};  			//��ʼ/��ͣ����
uint8_t Stop[5]  	= {0x7E,0X03,0XAB,0XAE,0XEF};  			//ֹͣ����
uint8_t Last[5]  	= {0x7E,0X03,0XAC,0XAF,0XEF};  			//��һ��
uint8_t Next[5]  	= {0x7E,0X03,0XAD,0XB0,0XEF};  			//��һ��
uint8_t Cycle1[6] = {0x7E,0X04,0XAF,0X00,0XB3,0XEF};  //������ѭ������
uint8_t Cycle2[6] = {0x7E,0X04,0XAF,0X01,0XB4,0XEF};  //����ѭ������
uint8_t Cycle3[6] = {0x7E,0X04,0XAF,0X02,0XB5,0XEF};  //������Ŀѭ������
uint8_t Cycle4[6] = {0x7E,0X04,0XAF,0X03,0XB6,0XEF};  //�������
uint8_t VOL05[6] 	= {0x7E,0X04,0XAE,0X05,0XB7,0XEF}; 	//5����
uint8_t VOL10[6] 	= {0x7E,0X04,0XAE,0X0A,0XBC,0XEF}; 	//10����
uint8_t VOL15[6] 	= {0x7E,0X04,0XAE,0X0F,0XC1,0XEF}; 	//15����
uint8_t VOL20[6] 	= {0x7E,0X04,0XAE,0X14,0XC6,0XEF}; 	//20����
uint8_t VOL25[6] 	= {0x7E,0X04,0XAE,0X19,0XCB,0XEF}; 	//25����
uint8_t VOL30[6] 	= {0x7E,0X04,0XAE,0X1E,0XD0,0XEF}; 	//30����
uint8_t Insert[8] = {0x7E,0x06,0xB1,0x01,0x00,0x01,0x00,0xEF};
uint8_t bySeqence[7] = {0x7E,0x05,0xA2,0x00,0x00,0xff,0xEF};//�����ļ���
uint8_t byName[20] = {0x7E,0x07,0xA3,0x00,0x00,0x00,0x00,0xff,0xEF};//�����ļ���
//==========================================================
//	�������ƣ�	uint8_t MP3_DispalyTarget(uint16_t item)
//
//	�������ܣ�	����ָ��˳��ŵ���Ŀ
//
//	��ڲ�����	@uint16_t item,ָ������Ŀ ˳���
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void MP3_StartDisplay(void)
{
    HAL_UART_Transmit(&UART2_Handler,Start,5,1000);	//�����
}
//==========================================================
//	�������ƣ�	uint8_t MP3_DispalyTarget(uint16_t item)
//
//	�������ܣ�	����ָ��˳��ŵ���Ŀ
//
//	��ڲ�����	@uint16_t item,ָ������Ŀ ˳���
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void MP3_DispalyTarget(uint16_t item)
{
    uint8_t sum;
    bySeqence[3] = (item>>8);
    bySeqence[4] = (uint8_t)item;
    sum = bySeqence[1]+bySeqence[2]+bySeqence[3]+bySeqence[4];
    bySeqence[5] = sum;
    HAL_UART_Transmit(&UART2_Handler,bySeqence,7,1000);	//�����
}
//==========================================================
//	�������ƣ�	uint8_t MP3_DispalyTargetByname(uint16_t *name)
//
//	�������ܣ�	����ָ��˳��ŵ���Ŀ
//
//	��ڲ�����	@uint16_t item,ָ������Ŀ ˳���
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void MP3_DispalyTargetByname(uint8_t *name)
{
    uint8_t sum,i=0,j,len;
    for(i=0;i<strlen((const void*)name);i++)
    {
        byName[3+i] = name[i];
    }
    len = i+3+2;
    byName[1] = 3 + i;
    sum = 0;
    for(j=1;j < (len-2);j++)
    {
        sum += byName[j];
    }
    byName[len-2] = sum;
    byName[len-1] = 0xEF;
    HAL_UART_Transmit(&UART2_Handler,byName,i+5,1000);	//�����
}
//==========================================================
//	�������ƣ�	uint8_t MP3_NextItemDisplay(void)
//
//	�������ܣ�	������һ��
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void MP3_NextItemDisplay(void)
{
    HAL_UART_Transmit(&UART2_Handler,Next,5,1000);	//�����
}
//==========================================================
//	�������ƣ�	void MP3_PreItemDisplay(void)
//
//	�������ܣ�	������һ��
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		����ͨ��485���߷��͹�������������
//==========================================================
void MP3_PreItemDisplay(void)
{
    HAL_UART_Transmit(&UART2_Handler,Last,5,1000);	//�����
}
//==========================================================
//	�������ƣ�	void MP3_StopDisplay(void)
//
//	�������ܣ�	ͣ�²���
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void MP3_StopDisplay(void)
{
    HAL_UART_Transmit(&UART2_Handler,Start,5,1000);	//�����
}
//==========================================================
//	�������ƣ�	void MP3_Init(void)
//
//	�������ܣ�	��ʼ��оƬ
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void MP3_Init(void)
{
    MP3_StopDisplay();
}






