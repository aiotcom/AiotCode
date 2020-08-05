#ifndef __UART2RS485_H
#define __UART2RS485_H

#include "hal_types.h"
void UART2RS485_Init(void);
/*		ģʽ����		*/ 
#define RS485_TX_EN()	P1_3 = 1;//RS485���������� 		//485����ģʽ
#define RS485_RX_EN()	P1_3 = 0;//RS485���������� 	//485����ģʽ

/*		�豸��ַ		*/
#define			Addr_Light						0x1001		//���մ�������ַ
#define			Addr_WS							0x1101		//��ʪ�ȴ�������ַ
#define			Addr_Motor						0x1201		//ֱ�������ַ
#define			Addr_Lock						0x1301		//�������ַ
#define			Addr_Siren						0x1401		//��������ַ
#define			Addr_Fan						0x1501		//���ȵ�ַ
#define			Addr_NULL						0xFFFF		//�յ�ַ-�޶����ַʱ���ݴ���õ�ַ

/*		������		*/
#define			Get_Light_Data					0x1000		//��ȡ���մ���������
#define			Light_Data						0x1001		//���մ���������

#define			Get_WS_Data						0x1100		//��ȡ��ʪ�ȴ���������
#define			WS_Data							0x1101		//��ʪ�ȴ���������

#define			Motor_OFF						0x1200		//�ر�ֱ�����
#define			Motor_ON						0x1201		//��ֱ�����

#define			Lock_OFF						0x1300		//�رյ����
#define			Lock_ON							0x1301		//�򿪵����

#define			Siren_OFF						0x1400		//�رվ�����
#define			Siren_ON						0x1401		//�򿪾�����

#define			Fan_OFF							0x1500		//�رշ���
#define			Fan_ON							0x1501		//�򿪷���

/*
		����485�������ݽṹ��
*/
#define 		Send_REC_LEN  				200  			//�����������ֽ��� 200
#define 		Receive_REC_LEN  			200  			//�����������ֽ��� 200

#define			Receiving_Completion	0x8000		//�������
typedef struct
{
	uint32_t Head;					//Э��֡ͷ
	uint8_t Pack_Num;				//�����
	uint16_t Src_Adr;				//Դ��ַ
	uint16_t Dst_Adr;				//Ŀ�ĵ�ַ
	uint16_t State;					//״̬��
	uint8_t Data_Len;				//���ݳ���
	uint8_t Data[Send_REC_LEN];     //����
	uint16_t CrcCheck;			    //CRCУ����
	uint32_t Tail;					//Э��֡β
}Send_Stack;

/*
		����485�������ݽṹ��
*/
typedef struct
{
	uint32_t Head;					//Э��֡ͷ
	uint8_t Pack_Num;				//�����
	uint16_t Src_Adr;				//Դ��ַ
	uint16_t Dst_Adr;				//Ŀ�ĵ�ַ
	uint16_t Command;				//������
	uint8_t Data_Len;				//���ݳ���
	uint8_t Data[Receive_REC_LEN];  //����
	uint16_t CrcCheck;			    //CRCУ����
	uint32_t Tail;					//Э��֡β
}Receive_Stack;

/*
		����485�������ݽṹ��
*/
extern Send_Stack Tx_Stack;							//485�������ݽṹ��
extern Receive_Stack Rx_Stack;						//485�������ݽṹ��

/*
		����485����/��������
*/
extern uint8_t Send_Data[Send_REC_LEN]; 			//���ͻ���,���Send_REC_LEN���ֽ�
extern uint8_t Receive_Data[Receive_REC_LEN]; 		//���ջ���,���Send_REC_LEN���ֽ�

/*
		��������
*/
extern void Rs485_Init(void);  		      //��ʼ��485
extern void Tx_Stack_Init(void);	      //485�������ݽṹ���ʼ��
extern void Rx_Stack_Init(void);	      //485�������ݽṹ���ʼ��
void Rs485_delay_ms(unsigned int nms);	  //485��ʱ����
extern void Rs485_Receive(uint8_t data);				//485���պ���
extern uint16_t CRC_16(void *p, int length);			//CRC_16���㺯��
extern uint8_t DataHandling_485(uint16_t DesAddr);		//485���ݴ���
extern uint16_t calcByte(uint16_t crc, uint8_t b);		//CRC_16�ֽڼ��㺯��
extern void Rs485_Send(uint16_t SrcAdr,uint16_t DstAdr,uint16_t Cmd,uint8_t Len,uint8_t *pData);//485���ͺ���
extern void Rs485_ClearReceiveBuffer(void);
#endif