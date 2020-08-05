#ifndef __Rs485_H
#define __Rs485_H
#include "stm32f1xx_hal.h"

#define 		Send_REC_LEN  				500  			//�����������ֽ��� 500
#define 		Receive_REC_LEN  			500  			//�����������ֽ��� 500

/*		�豸��ַ		*/
#define			Addr_Power						0x10			//��Դ�е�ַ
#define			Addr_LED							0x11			//LEDģ���ַ
#define			Addr_Matrixkey				0x12			//�������ģ���ַ
#define			Addr_Fan							0x13			//����ģ���ַ
#define			Addr_Relay						0x14			//�̵�����ַ
#define			Addr_TFT							0x15			//TFT����ַ
#define			Addr_SHT20						0x16			//��ʪ��ģ���ַ
#define			Addr_Pre							0x17			//ѹ��������ģ���ַ
#define			Addr_RFID							0x18			//RFIDģ���ַ
#define			Addr_Gyr							0x19			//������ģ���ַ
#define			Addr_PIR							0x1A			//�������ģ���ַ
#define			Addr_NB								0x1B			//NB-iotģ���ַ
#define			Addr_BLE							0x1C			//����ģ���ַ
#define			Addr_ZigBee						0x1D			//ZigBeeģ���ַ
#define			Addr_GPS							0x1E			//GPSģ���ַ
#define			Addr_WiFi							0x1F			//WiFiģ���ַ
#define			Addr_Ultrasonic				0x20			//������ģ���ַ
#define			Addr_Motor						0x21			//�������ģ���ַ
#define			Addr_PM2_5						0x22			//PM2.5ģ���ַ
#define			Addr_IPV4							0x23			//IPV4ģ���ַ
#define			Addr_Flame						0x24			//���洫����ģ���ַ
#define			Addr_Shock						0x25			//�𶯴�����ģ���ַ
#define			Addr_Heart						0x26			//���ʴ�������ַ
#define			Addr_LF								0x27			//LFģ���ַ
#define			Addr_A_P							0x28			//����ѹ��ģ���ַ

/*		������		*/

#define			Matrixkey0						0x1201		//�������-����0
#define			Matrixkey1						0x1211		//�������-����1
#define			Matrixkey2						0x1221		//�������-����2
#define			Matrixkey3						0x1231		//�������-����3
#define			Matrixkey4						0x1241		//�������-����4
#define			Matrixkey5						0x1251		//�������-����5
#define			Matrixkey6						0x1261		//�������-����6
#define			Matrixkey7						0x1271		//�������-����7
#define			Matrixkey8						0x1281		//�������-����8
#define			Matrixkey9						0x1291		//�������-����9
#define			MatrixkeyEnter				0x12A1		//�������-����Enter
#define			MatrixkeyCanel				0x12B1		//�������-����Canel
#define			MatrixkeyUP						0x12C1		//�������-����UP
#define			MatrixkeyDown					0x12D1		//�������-����Down
#define			MatrixkeyLeft					0x12E1		//�������-����Left
#define			MatrixkeyRight				0x12F1		//�������-����Right

#define			FAN_OFF								0x1310		//�رշ���
#define			FAN_ON1								0x1311		//�򿪷���-1��
#define			FAN_ON2								0x1321		//�򿪷���-2��
#define			FAN_ON3								0x1331		//�򿪷���-3��

#define			Relay1_ON							0x1411		//�򿪼̵���1
#define			Relay1_OFF						0x1410		//�رռ̵���1
#define			Relay2_ON							0x1421		//�򿪼̵���2
#define			Relay2_OFF						0x1420		//�رռ̵���2

#define			TFT_QueryMatrixkey		0x1501		//TFT-��ѯ�������
#define			TFT_QueryRFID					0x1511		//TFT-��ѯRFID
#define			TFT_QueryMotor				0x1521		//TFT-��ѯ���״̬

#define			SHT20_Temp						0x1601		//��ʪ��-�¶�
#define			SHT20_Humi						0x1611		//��ʪ��-ʪ��
#define			SHT20_Light						0x1621		//��ʪ��-����ǿ��
#define			SHT20_All							0x1631		//��ʪ��-ȫ������

#define			Pre_Weight						0x1701		//ѹ��-����

#define			RFID_ID								0x1801		//RFID-����
#define			RFID_Block						0x1811		//RFID-������
#define			RFID_All							0x1821		//RFID-����+������

#define			Gyr_Angle							0x1901		//������-�Ƕ�

#define			PIR_Flag							0x1A01		//�������-�Ƿ��⵽����

#define			NB_SHT20							0x1B11		//NB-IoTģ���ȡ��ʪ��ģ������
#define			NB_RFID								0x1B21		//NB-IoTģ���ȡRFIDģ������
#define			NB_TFT								0x1B31		//NB-IoTģ���ȡTFTģ������

#define			GPS_Location					0x1E01		//GPS-��γ��

#define			Ultrasonic_Distance		0x2001		//������-���루cm��

#define			Motor_OFF							0x2100		//�������-�ر�
#define			Motor_ON							0x2101		//�������-����
#define			Motor_Stop						0x2111		//�������-��ͣ

#define			PM2_5_Conc						0x2201		//PM2.5-PM2.5Ũ��

#define			Flame_Flag						0x2401		//���洫����-�Ƿ����

#define			Shock_Count						0x2501		//��-�𶯴���

#define			Heart_Count						0x2601		//����-ÿ������������

#define			Lf_Flag								0x2701		//Lf-������

#define			A_P_Altitude					0x2801		//����ѹ��-���θ߶�

/*		ģʽ����		*/ 
#define RS485_TX_EN()		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_SET);		//485ģʽ���Ʒ���.
#define RS485_RX_EN()		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_RESET);	//485ģʽ���ƽ���;

/*
		����485�������ݽṹ��
*/
typedef struct
{
    uint32_t Head;					//Э��֡ͷ
		uint8_t Pack_Num;				//�����
		uint8_t Src_Adr;				//Դ��ַ
		uint8_t Dst_Adr;				//Ŀ�ĵ�ַ
    uint16_t State;					//״̬��
		uint8_t Data_Len;				//���ݳ���
    uint8_t Data[500];			//����
		uint16_t CrcCheck;			//CRCУ����
		uint32_t Tail;					//Э��֡β
}Send_Stack;

/*
		����485�������ݽṹ��
*/
typedef struct
{
    uint32_t Head;					//Э��֡ͷ
		uint8_t Pack_Num;				//�����
		uint8_t Src_Adr;				//Դ��ַ
		uint8_t Dst_Adr;				//Ŀ�ĵ�ַ
    uint16_t Command;				//������
		uint8_t Data_Len;				//���ݳ���
    uint8_t Data[500];			//����
		uint16_t CrcCheck;			//CRCУ����
		uint32_t Tail;					//Э��֡β
}Receive_Stack;

extern Send_Stack Tx_Stack;														//485�������ݽṹ��
extern Receive_Stack Rx_Stack;												//485�������ݽṹ��

extern unsigned char  Send_Data[Send_REC_LEN]; 				//���ͻ���,���Send_REC_LEN���ֽ�
extern unsigned char  Receive_Data[Receive_REC_LEN]; 	//���ջ���,���Send_REC_LEN���ֽ�

extern void Rs485_Init(void);  		//��ʼ��485
extern void Tx_Stack_Init(void);	//485�������ݽṹ���ʼ��
extern void Rx_Stack_Init(void);	//485�������ݽṹ���ʼ��
extern void Rs485_Receive(uint8_t data);							//485���պ���
extern uint16_t CRC_16(void *p, int length);					//CRC_16���㺯��
extern uint8_t DataHand_485(uint8_t DesAddr);					//485���ݴ���
extern uint16_t calcByte(uint16_t crc, uint8_t b);		//CRC_16�ֽڼ��㺯��
extern void Rs485_Send(uint8_t SrcAdr,uint8_t DstAdr,uint16_t Cmd,uint8_t Len,uint8_t *pData);			//485���ͺ���

#endif



