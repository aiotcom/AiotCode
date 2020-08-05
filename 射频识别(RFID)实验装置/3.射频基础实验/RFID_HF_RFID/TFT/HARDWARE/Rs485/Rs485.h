#ifndef __Rs485_H
#define __Rs485_H
#include "stm32f1xx_hal.h"

#define 		Send_REC_LEN  				200  			//�����������ֽ��� 200
#define 		Receive_REC_LEN  			200  			//�����������ֽ��� 200

#define			Receiving_Completion	0x8000		//�������

/*		ģʽ����		*/ 
#define RS485_TX_EN()		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_SET)		//485����ģʽ
#define RS485_RX_EN()		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_RESET)	//485����ģʽ

/*		�豸��ַ		*/
#define			Addr_Power						0x1001			//��Դ�е�ַ
#define			Addr_LED							0x1101			//LEDģ���ַ
#define			Addr_Matrixkey				0x1201			//�������ģ���ַ
#define			Addr_Fan							0x1301			//����ģ���ַ
#define			Addr_Relay						0x1401			//�̵�����ַ
#define			Addr_LCD							0x1501			//LCD����ַ
#define			Addr_SHT20						0x1601			//��ʪ��ģ���ַ
#define			Addr_Pre							0x1701			//ѹ��������ģ���ַ
#define			Addr_HF_RFID					0x1801			//HF_RFIDģ���ַ
#define			Addr_Gyr							0x1901			//������ģ���ַ
#define			Addr_PIR							0x1A01			//�������ģ���ַ
#define			Addr_NB								0x1B01			//NB-IoTģ���ַ
#define			Addr_BLE							0x1C01			//����ģ���ַ
#define			Addr_ZigBee						0x1D01			//ZigBeeģ���ַ
#define			Addr_GPS							0x1E01			//GPSģ���ַ
#define			Addr_WiFi							0x1F01			//WiFiģ���ַ
#define			Addr_Ultrasonic				0x2001			//������ģ���ַ
#define			Addr_StepperMotor			0x2101			//�������ģ���ַ
#define			Addr_PM2_5						0x2201			//PM2.5ģ���ַ
#define			Addr_IPV4							0x2301			//IPV4ģ���ַ
#define			Addr_Flame						0x2401			//���洫����ģ���ַ
#define			Addr_Shock						0x2501			//�𶯴�����ģ���ַ
#define			Addr_Heart						0x2601			//���ʴ�������ַ
#define			Addr_LF_RFID					0x2701			//LF_RFIDģ���ַ
#define			Addr_A_P							0x2801			//����ѹ��ģ���ַ
#define			Addr_LORA							0x2901			//LORAģ���ַ
#define			Addr_MP3							0x2A01			//MP3ģ���ַ
#define			Addr_PH								0x2B01			//��翪��ģ���ַ
#define			Addr_Touch_Key				0x2C01			//��������ģ���ַ
#define			Addr_TF								0x2D01			//TF��ģ���ַ
#define			Addr_Alcohol					0x2E01			//�ƾ�������ģ���ַ
#define			Addr_Formaldehyde			0x2F01			//��ȩ������ģ���ַ
#define			Addr_Smoke						0x3001			//��������ģ���ַ
#define			Addr_Color						0x3101			//��ɫ������ģ���ַ
#define			Addr_Noncontact_Temp	0x3201			//�ǽӴ��¶Ȳ���������ģ���ַ
#define			Addr_Moisture					0x3301			//����ʪ�ȴ�����ģ���ַ
#define			Addr_Gesture					0x3401			//����ʶ�𴫸���ģ���ַ
#define         Addr_NFC                     0x3701             //NFCģ��

/*		������		*/

#define			LED_Control						0x1100		//����LED
#define			LED_ON1								0x1111		//��LED1
#define			LED_ON2								0x1121		//��LED2
#define			LED_ON3								0x1131		//��LED3
#define			LED_ON4								0x1141		//��LED4
#define			LED_OFF1							0x1110		//�ر�LED1
#define			LED_OFF2							0x1120		//�ر�LED2
#define			LED_OFF3							0x1130		//�ر�LED3
#define			LED_OFF4							0x1140		//�ر�LED4

#define			Matrixkey_Get_value		0x1200		//�������-����ȡ����ֵ
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
#define			Relay2_ON							0x1421		//�򿪼̵���2
#define			Relay1_OFF						0x1410		//�رռ̵���1
#define			Relay2_OFF						0x1420		//�رռ̵���2

#define			LCD_Display						0x1511		//�������ݵ�LCD����ʾ

#define			SHT20_Temp						0x1601		//��ʪ��-�¶�
#define			SHT20_Humi						0x1611		//��ʪ��-ʪ��
#define			SHT20_Light						0x1621		//��ʪ��-����ǿ��
#define			SHT20_All							0x1631		//��ʪ��-ȫ������
#define			SHT20_Get_Temp				0x1600		//��ʪ��-����ȡ�¶�
#define			SHT20_Get_Humi				0x1610		//��ʪ��-����ȡʪ��
#define			SHT20_Get_Light				0x1620		//��ʪ��-����ȡ����ǿ��
#define			SHT20_Get_All					0x1630		//��ʪ��-����ȡȫ������

#define			Pre_Weight						0x1701		//ѹ��-����
#define			Pre_Get_Weight				0x1700		//ѹ��-����ȡ����

#define			HF_RFID_ID						0x1801		//HF_RFID-����
#define			HF_RFID_Block					0x1811		//HF_RFID-������
#define			HF_RFID_All						0x1821		//HF_RFID-����+������
#define			HF_RFID_Get_ID				0x1800		//HF_RFID-����ȡ����
#define			HF_RFID_Get_Block			0x1810		//HF_RFID-����ȡ������
#define			HF_RFID_Get_All				0x1820		//HF_RFID-����ȡ����+������

#define			Gyr_Angle							0x1901		//������-�Ƕ�
#define			Gyr_Get_Angle					0x1900		//������-����ȡ�Ƕ�

#define			PIR_State							0x1A01		//�������-�Ƿ��⵽����
#define			PIR_Get_State					0x1A00		//�������-����ȡ�Ƿ��⵽����

#define			GPS_Location					0x1E01		//GPS-λ������(��γ��)
#define			GPS_Get_Location			0x1E00		//GPS-����ȡλ������(��γ��)

#define			Ultrasonic_Dis				0x2001		//������-����(cm)
#define			Ultrasonic_Get_Dis		0x2000		//������-����ȡ����(cm)

#define			Motor_OFF							0x2100		//�������-�ر�
#define			Motor_ON							0x2101		//�������-����

#define			PM2_5_Conc						0x2201		//PM2.5-PM2.5Ũ��
#define			PM2_5_Get_Conc				0x2200		//PM2.5-����ȡPM2.5Ũ��

#define			Flame_State						0x2401		//���洫����-�Ƿ����״̬
#define			Flame_Get_State				0x2400		//���洫����-����ȡ�Ƿ����״̬

#define			Shock_Count						0x2501		//��-�𶯴���
#define			Shock_Get_Count				0x2500		//��-����ȡ�𶯴���

#define			Heart_Count						0x2601		//����-ÿ������������
#define			Heart_Get_Count				0x2600		//����-����ȡÿ������������

#define			LF_RFID_ID						0x2701		//LF_RFID-����
#define			LF_RFID_Block					0x2711		//LF_RFID-������
#define			LF_RFID_All						0x2721		//LF_RFID-����+������
#define			LF_RFID_Get_ID				0x2700		//LF_RFID-����ȡ����
#define			LF_RFID_Get_Block			0x2710		//LF_RFID-����ȡ������
#define			LF_RFID_Get_All				0x2720		//LF_RFID-����ȡ����+������

#define			A_P_Altitude					0x2801		//����ѹ��-���θ߶�
#define			A_P_Get_Altitude			0x2800		//����ѹ��-����ȡ���θ߶�

#define			MP3_TO_MP3						0x2A00		//MP3-���͸�MP3ģ�鲥��

#define			PH_State							0x2B01		//��翪��-����״̬
#define			PH_Get_State					0x2B00		//��翪��-����ȡ����״̬

#define			Touch_Key_State				0x2C01		//��������-����״̬
#define			Touch_Key_Get_State		0x2C00		//��������-����ȡ����״̬

#define			TF_Data								0x2D01		//TF��-����
#define			TF_Get_Data						0x2D00		//TF��-����ȡ����

#define			Alcohol_Data					0x2E01		//�ƾ�������-�ƾ�Ũ������
#define			Alcohol_Get_Data			0x2E00		//�ƾ�������-����ȡ�ƾ�Ũ������
#define			Alcohol_State					0x2E11		//�ƾ�������-�Ƿ��⵽�ƾ�
#define			Alcohol_Get_State			0x2E10		//�ƾ�������-����ȡ�Ƿ��⵽�ƾ�

#define			Formaldehyde_Data			0x2F01		//��ȩ������-��ȩŨ������
#define			Formaldehyde_Get_Data	0x2F00		//��ȩ������-����ȡ��ȩŨ������

#define			Smoke_Data						0x3001		//��������-����Ũ������
#define			Smoke_Get_Data				0x3000		//��������-����ȡ����Ũ������
#define			Smoke_State						0x3011		//��������-����Ƿ�������
#define			Smoke_Get_State				0x3010		//��������-����ȡ�Ƿ�������

#define			Color_Data						0x3101		//��ɫ������-RGB��ɫ����
#define			Color_Get_Data				0x3100		//��ɫ������-����ȡRGB��ɫ����

#define			Noncontact_Temp_Data	0x3201		//�ǽӴ��¶ȼ�⴫����-�¶�ֵ
#define			Noncontact_Temp_Get_Data	0x3200//�ǽӴ��¶ȼ�⴫����-����ȡ�¶�ֵ

#define			Moisture_Data					0x3301		//����ʪ�ȴ�����-ʪ������
#define			Moisture_Get_Data			0x3300		//����ʪ�ȴ�����-����ȡʪ������

#define			Gesture_Get_Action		0x3400		//���ƴ�����-��ȡ����
#define			Gesture_Up_Down				0x3411		//���ƴ�����-���ϵ���
#define			Gesture_Down_Up				0x3410		//���ƴ�����-���µ���
#define			Gesture_Left_Right		0x3421		//���ƴ�����-������
#define			Gesture_Right_Left		0x3420		//���ƴ�����-���ҵ���
#define			Gesture_Beyond				0x3431		//���ƴ�����-Զ��
#define			Gesture_Near					0x3430		//���ƴ�����-����
#define			NFC_Get_ID					0x3440		//��ȡNFC��ȡ��ID
#define			NFC_ID					0x3441		//��ȡNFC��ȡ��ID
/*
		����485�������ݽṹ��
*/
typedef struct
{
    uint32_t Head;					//Э��֡ͷ
		uint8_t Pack_Num;				//�����
		uint16_t Src_Adr;				//Դ��ַ
		uint16_t Dst_Adr;				//Ŀ�ĵ�ַ
    uint16_t State;					//״̬��
		uint8_t Data_Len;				//���ݳ���
    uint8_t Data[Send_REC_LEN];//����
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
		uint16_t Src_Adr;				//Դ��ַ
		uint16_t Dst_Adr;				//Ŀ�ĵ�ַ
    uint16_t Command;				//������
		uint8_t Data_Len;				//���ݳ���
    uint8_t Data[Receive_REC_LEN];//����
		uint16_t CrcCheck;			//CRCУ����
		uint32_t Tail;					//Э��֡β
}Receive_Stack;

/*
		����485�������ݽṹ��
*/
extern Send_Stack Tx_Stack;														//485�������ݽṹ��
extern Receive_Stack Rx_Stack;												//485�������ݽṹ��

/*
		����485����/��������
*/
extern uint8_t Send_Data[Send_REC_LEN]; 							//���ͻ���,���Send_REC_LEN���ֽ�
extern uint8_t Receive_Data[Receive_REC_LEN]; 				//���ջ���,���Send_REC_LEN���ֽ�

/*
		��������
*/
extern void Rs485_Init(void);  		//��ʼ��485
extern void Tx_Stack_Init(void);	//485�������ݽṹ���ʼ��
extern void Rx_Stack_Init(void);	//485�������ݽṹ���ʼ��
void Rs485_delay_ms(unsigned int nms);								//485��ʱ����
extern void Rs485_Receive(uint8_t data);							//485���պ���
extern uint16_t CRC_16(void *p, int length);					//CRC_16���㺯��
extern uint8_t DataHandling_485(uint16_t DesAddr);		//485���ݴ���
extern uint16_t calcByte(uint16_t crc, uint8_t b);		//CRC_16�ֽڼ��㺯��
extern void Rs485_Send(uint16_t SrcAdr,uint16_t DstAdr,uint16_t Cmd,uint8_t Len,uint8_t *pData);//485���ͺ���

#endif



