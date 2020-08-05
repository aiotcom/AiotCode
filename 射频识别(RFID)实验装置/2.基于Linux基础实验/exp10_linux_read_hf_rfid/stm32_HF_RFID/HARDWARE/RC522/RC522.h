#ifndef __RC522_H
#define	__RC522_H

#include "stm32f1xx.h"
#include "delay.h"

/*********************************** RC522 IO�ڶ���*********************************************/

#define			RC522_CS_PORT								GPIOA
#define			RC522_SCK_PORT							GPIOA
#define			RC522_LED_PORT							GPIOB
#define			RC522_MOSI_PORT							GPIOA
#define			RC522_MISO_PORT							GPIOA
#define			RC522_Reset_PORT						GPIOA

#define			RC522_CS_PIN								GPIO_PIN_4
#define			RC522_LED_PIN								GPIO_PIN_14
#define			RC522_SCK_PIN								GPIO_PIN_5
#define			RC522_MOSI_PIN							GPIO_PIN_7
#define			RC522_MISO_PIN							GPIO_PIN_6	
#define			RC522_Reset_PIN							GPIO_PIN_0

#define     macRC522_CS_Enable()       	HAL_GPIO_WritePin ( RC522_CS_PORT, RC522_CS_PIN,GPIO_PIN_RESET )
#define     macRC522_CS_Disable()       HAL_GPIO_WritePin ( RC522_CS_PORT, RC522_CS_PIN,GPIO_PIN_SET )

#define     macRC522_LED_ON()           HAL_GPIO_WritePin ( RC522_LED_PORT, RC522_LED_PIN,GPIO_PIN_RESET)
#define     macRC522_LED_OFF()          HAL_GPIO_WritePin ( RC522_LED_PORT, RC522_LED_PIN,GPIO_PIN_SET )

#define     macRC522_SCK_0()            HAL_GPIO_WritePin ( RC522_SCK_PORT, RC522_SCK_PIN,GPIO_PIN_RESET)
#define     macRC522_SCK_1()            HAL_GPIO_WritePin ( RC522_SCK_PORT, RC522_SCK_PIN,GPIO_PIN_SET )

#define     macRC522_MOSI_0()           HAL_GPIO_WritePin ( RC522_MOSI_PORT, RC522_MOSI_PIN,GPIO_PIN_RESET )
#define     macRC522_MOSI_1()           HAL_GPIO_WritePin ( RC522_MOSI_PORT, RC522_MOSI_PIN,GPIO_PIN_SET )

#define     macRC522_Reset_Enable()     HAL_GPIO_WritePin ( RC522_Reset_PORT, RC522_Reset_PIN,GPIO_PIN_RESET )
#define   	macRC522_Reset_Disable()    HAL_GPIO_WritePin ( RC522_Reset_PORT, RC522_Reset_PIN,GPIO_PIN_SET )

#define     macRC522_MISO_GET()         HAL_GPIO_ReadPin ( RC522_MISO_PORT, RC522_MISO_PIN ) 

/////////////////////////////////////////////////////////////////////
//���ݵ�ַ
/////////////////////////////////////////////////////////////////////
#define	Addr_125k					0xB1				// 125K���ݵ�ַ
#define Addr_UHF					0xB2				// UHF���ݵ�ַ
#define Addr_MF						0xB3				// 13.56���ݵ�ַ
#define Addr_Books				0xB5				// ͼ��������ݵ�ַ
#define Addr_EP						0xB6				// ����Ǯ�����ݵ�ַ
#define Addr_2_4G					0xB7				// 2.4G���ݵ�ַ
#define Addr_Uc						0xC0				// ��λ�����ݵ�ַ

/////////////////////////////////////////////////////////////////////
//125K������
/////////////////////////////////////////////////////////////////////
#define	FindCard_125K			0xB101			//125K RFIDģ��Ѱ��
#define	HomCard_125K			0xB102			//125K RFIDģ���Զ�Ѱ��
#define	UsartSend_125K		0xB103			//125K RFIDģ�鴮�ڷ���

/////////////////////////////////////////////////////////////////////
//UHF������
/////////////////////////////////////////////////////////////////////
#define FindCard_UHF 			0xB201			//UHF RFIDģ��Ѱ��				
#define HomCard_UHF 			0xB202			//UHF RFIDģ���Զ�Ѱ��	
#define ReadPower_UHF 		0xB203			//UHF RFIDģ���ȡ����	
#define SetPower_UHF 			0xB204			//UHF RFIDģ�鹦������	
#define OpenPA_UHF 				0xB205			//UHF RFIDģ��򿪹���	
#define ClosePA_UHF 			0xB206			//UHF RFIDģ��رչ��š�	
#define ReadData_UHF 			0xB207			//UHF RFIDģ���ȡ	
#define WriteData_UHF 		0xB208			//UHF RFIDģ��д��	
#define AutKey_UHF 				0xB209			//UHF RFIDģ�������Կ	
#define LockData_UHF 			0xB20A			//UHF RFIDģ����������	
#define UsartSend_UHF 		0xB20B			//UHF RFIDģ�鴮�ڷ���	 
 
/////////////////////////////////////////////////////////////////////
//13.56������
/////////////////////////////////////////////////////////////////////
#define	FindCard_MF				0xB301			//13.56M RFIDģ��Ѱ��
#define	HomCard_MF				0xB302			//13.56M RFIDģ���Զ�Ѱ��
#define	AutKeyA_MF				0xB303			//13.56M RFIDģ����֤��ԿA
#define	AutKeyB_MF				0xB304			//13.56M RFIDģ����֤��ԿB
#define	ReadData_MF				0xB305			//13.56M RFIDģ���ȡ����
#define	WriteData_MF			0xB306			//13.56M RFIDģ��д������
#define	UsartSend_MF			0xB307			//13.56M RFIDģ�鴮�ڷ���

/////////////////////////////////////////////////////////////////////
//NFC������
/////////////////////////////////////////////////////////////////////
#define	FindCard_NFC			0xB401			//NFC RFIDģ��Ѱ��
#define	HomCard_NFC				0xB402			//NFC RFIDģ���Զ�Ѱ��
#define	SendCard_NFC			0xB403			//NFC RFIDģ�鷢��
#define	Top_Up_NFC				0xB404			//NFC RFIDģ���ֵ
#define	UsartSend_NFC			0xB405			//NFC RFIDģ�鴮�ڷ���

/////////////////////////////////////////////////////////////////////
//ͼ�����������
/////////////////////////////////////////////////////////////////////
#define FindCard_Books		0xB501			//ͼ����� RFIDģ��Ѱ��
#define HomCard_Books			0xB502			//ͼ����� RFIDģ���Զ�Ѱ��
#define Borrow_Books			0xB503			//ͼ����� RFIDģ�����
#define Also_Books				0xB504			//ͼ����� RFIDģ�黹��
#define UsartSend_Books		0xB505			//ͼ����� RFIDģ�鴮�ڷ���

/////////////////////////////////////////////////////////////////////
//����Ǯ��������
/////////////////////////////////////////////////////////////////////
#define FindCard_EP				0xB601			//����Ǯ�� RFIDģ��Ѱ��
#define HomCard_EP				0xB602			//����Ǯ�� RFIDģ���Զ�Ѱ��
#define AutKeyA_EP				0xB603			//����Ǯ�� RFIDģ����֤��ԿA
#define AutKeyB_EP				0xB604			//����Ǯ�� RFIDģ����֤��ԿB
#define Query_EP					0xB605			//����Ǯ�� RFIDģ���ѯ
#define Top_Up_EP					0xB606			//����Ǯ�� RFIDģ���ֵ
#define Deduction_EP			0xB607			//����Ǯ�� RFIDģ��۷�
#define UsartSend_EP			0xB608			//����Ǯ�� RFIDģ�鴮�ڷ���

/////////////////////////////////////////////////////////////////////
//2.4G������
/////////////////////////////////////////////////////////////////////
#define Set_2_4G					0xB601			//2.4G RFID����
#define UsartSend_2_4G		0xB602			//2.4G RFID���ڷ���

/////////////////////////////////////////////////////////////////////
//״̬��
/////////////////////////////////////////////////////////////////////
#define	Impl_OK						0x0000			//ִ�гɹ�
#define	Impl_Err					0x0001			//ִ��ʧ��

/////////////////////////////////////////////////////////////////////
//������
/////////////////////////////////////////////////////////////////////
#define	Set_OK						0x0080			//��ʾ�������óɹ�
#define	Set_Err						0x0081			//��ʾ��������ʧ��
#define	Com_TimeOut				0x0082			//��ʾͨѶ��ʱ
#define	Car_DissExiste		0x0083			//��ʾ��������
#define	Car_Data_Err			0x0084			//��ʾ���տ����ݴ���
#define	Unknown_Err				0x0085			//��ʾδ֪����
#define	Init_Err					0x0086			//��ʾ��ʼ������
#define	Seq_Err						0x0087			//��ʾ�ڷ���ײ�����еõ��������к�
#define	Key_Pass					0x0088			//��ʾ��Կ��֤δͨ��
#define	Com_DissExiste		0x0089			//��ʾ���������벻����
#define	Write_Err					0x008A			//��ʾд�������ɹ�

#define   macRC522_DELAY()  delay_us (20)
/////////////////////////////////////////////////////////////////////
//MF522������
/////////////////////////////////////////////////////////////////////
#define PCD_IDLE              0x00               //ȡ����ǰ����
#define PCD_AUTHENT           0x0E               //��֤��Կ
#define PCD_RECEIVE           0x08               //��������
#define PCD_TRANSMIT          0x04               //��������
#define PCD_TRANSCEIVE        0x0C               //���Ͳ���������
#define PCD_RESETPHASE        0x0F               //��λ
#define PCD_CALCCRC           0x03               //CRC����

/////////////////////////////////////////////////////////////////////
//Mifare_One��Ƭ������
/////////////////////////////////////////////////////////////////////
#define PICC_REQIDL           0x26               //Ѱ��������δ��������״̬
#define PICC_REQALL           0x52               //Ѱ��������ȫ����
#define PICC_ANTICOLL1        0x93               //����ײ
#define PICC_ANTICOLL2        0x95               //����ײ
#define PICC_AUTHENT1A        0x60               //��֤A��Կ
#define PICC_AUTHENT1B        0x61               //��֤B��Կ
#define PICC_READ             0x30               //����
#define PICC_WRITE            0xA0               //д��
#define PICC_DECREMENT        0xC0               //�ۿ�
#define PICC_INCREMENT        0xC1               //��ֵ
#define PICC_RESTORE          0xC2               //�������ݵ�������
#define PICC_TRANSFER         0xB0               //���滺����������
#define PICC_HALT             0x50               //����

/////////////////////////////////////////////////////////////////////
//MF522 FIFO���ȶ���
/////////////////////////////////////////////////////////////////////
#define DEF_FIFO_LENGTH       64                 //FIFO size=64byte
#define MAXRLEN  18

/////////////////////////////////////////////////////////////////////
//MF522�Ĵ�������
////////////////////////////////////////////////////// ///////////////
// PAGE 0
#define     RFU00                 0x00    
#define     CommandReg            0x01    
#define     ComIEnReg             0x02    
#define     DivlEnReg             0x03    
#define     ComIrqReg             0x04    
#define     DivIrqReg             0x05
#define     ErrorReg              0x06    
#define     Status1Reg            0x07    
#define     Status2Reg            0x08    
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     RFU0F                 0x0F
// PAGE 1     
#define     RFU10                 0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     RFU1A                 0x1A
#define     RFU1B                 0x1B
#define     MifareReg             0x1C
#define     RFU1D                 0x1D
#define     RFU1E                 0x1E
#define     SerialSpeedReg        0x1F
// PAGE 2    
#define     RFU20                 0x20  
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     RFU23                 0x23
#define     ModWidthReg           0x24
#define     RFU25                 0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsCfgReg            0x28
#define     ModGsCfgReg           0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
// PAGE 3      
#define     RFU30                 0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39  
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     RFU3C                 0x3C   
#define     RFU3D                 0x3D   
#define     RFU3E                 0x3E   
#define     RFU3F		  		  			0x3F

/////////////////////////////////////////////////////////////////////
//��MF522ͨѶʱ���صĴ������
/////////////////////////////////////////////////////////////////////
#define 	MI_OK                 0x26
#define 	MI_NOTAGERR           0xcc
#define 	MI_ERR                0xbb

/*********************************** RC522 �����궨��*********************************************/

extern unsigned char ucArray_ID[10];	//HF_RFID-ID
extern unsigned char Block_Date[20];	//HF_RFID-Data
extern unsigned char Data_Send[30];		//HF_RFID-ID+Data
void RC522_Init( void );
uint8_t SearchCard(void);
uint8_t IC_Card_Search(uint8_t *carid,uint8_t *blockdata);
extern uint8_t IC_Card_Exist;
void IC_Card_Read(uint8_t *p);
uint8_t IC_Card_Write(uint8_t *p);
uint8_t Verification_Key( unsigned char ucAuth_mode, unsigned char ucAddr, unsigned char * pKey);
#define          macDummy_Data              0x00

void             PcdReset                   ( void );                       						//��λ
void             M500PcdConfigISOType       ( unsigned char type );                    	//������ʽ
char             PcdRequest                 ( unsigned char req_code, unsigned char * pTagType ); //Ѱ��
char             PcdAnticoll                ( unsigned char * pSnr);                   	//������
char PcdRead ( unsigned char ucAddr, unsigned char * pData );
char PcdWrite ( unsigned char ucAddr, unsigned char * pData );
char PcdSelect ( unsigned char * pSnr );
char PcdAuthState ( unsigned char ucAuth_mode, unsigned char ucAddr, unsigned char * pKey, unsigned char * pSnr );

#endif /* __RC522_CONFIG_H */



