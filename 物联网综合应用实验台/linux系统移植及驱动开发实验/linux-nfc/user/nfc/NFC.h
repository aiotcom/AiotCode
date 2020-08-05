#ifndef __NFC_H__
#define __NFC_H__
 
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
#define	Spending_NFC			0xB404			//NFC RFIDģ������
#define	Top_Up_NFC				0xB405			//NFC RFIDģ���ֵ
#define	UsartSend_NFC			0xB406			//NFC RFIDģ�鴮�ڷ���

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
#define	Balance_Nenough		0x008B			//��ʾ����

void nfc_init(void);											//��ʼ��PN532
void nfc_close(void);
void  CleanBuffer(unsigned short num);									 	//���� ǰ ���ٸ��ֽڵ�����
void PN532_CSn_H(void);
void PN532_CSn_L(void);

unsigned char  SAMConfiguration(unsigned char mode,unsigned char timeout,unsigned char irq); 			 					//���ò���
unsigned char  nfc_InListPassiveTarget(unsigned char maxTag,unsigned char brty,unsigned char *CardID); 						//Ѱ��
unsigned char  nfc_PsdVerify(unsigned char AuthenticationType,unsigned char BlockNo,unsigned char * KeyData,unsigned char *SerialNum); //����֤��Կ    
unsigned char  nfc_read(unsigned char BlockNO,unsigned char *BlockData);											//����
unsigned char  nfc_write(unsigned char BlockNO,unsigned char *WriteData);										//д��
unsigned char  nfc_getIdentityID(unsigned char *identityid);											//��ȡ���֤
unsigned char  SPI1_ReadWriteByte(unsigned char TxData);
extern   unsigned char UID[4];		   
extern   unsigned char flag_nfc_status;
extern   unsigned char UID_backup[4];
extern   unsigned char KeyBuf[6];
extern   unsigned char BlockBuf[16];

#endif /* __NFC_H__ */


