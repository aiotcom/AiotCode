#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include "string.h"
#define msleep(n) usleep(n*1000)
#include "NFC.h"
#include "PN532.h"

#define NFC_MAGIC 'k'
#define IOCTRL_CMD_CS        _IOW(NFC_MAGIC, 1, int)
#define IOCTRL_CMD_RST       _IOW(NFC_MAGIC, 2, int)
#define IOCTRL_CMD_READ_RST  _IOW(NFC_MAGIC, 3, int) 

unsigned char SPI1_WriteByte(unsigned char TxData);
unsigned char SPI1_ReadByte(void);
const unsigned int arg_0=0,arg_1=1;
int nfc_fd;
//==========================================================
//	�������ƣ�	void macnfc_Reset_Disable()
//
//	�������ܣ�	ͣ����λ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void macnfc_Reset_Disable(void)
{
	ioctl(nfc_fd, IOCTRL_CMD_RST, &arg_1);		
}
//==========================================================
//	�������ƣ�	void macnfc_Reset_Enable()
//
//	�������ܣ�	ʹ�ܸ�λ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================	
void macnfc_Reset_Enable(void)
{
	ioctl(nfc_fd, IOCTRL_CMD_RST, &arg_0);		
}
//==========================================================
//	�������ƣ�	void PN532_CSn_H(void)
//
//	�������ܣ�	ֹͣƬѡ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void PN532_CSn_H(void)
{
	ioctl(nfc_fd, IOCTRL_CMD_CS, &arg_1);	
}
//==========================================================
//	�������ƣ�	void PN532_CSn_L(void)
//
//	�������ܣ�	ʹ��Ƭѡ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void PN532_CSn_L(void)
{
	ioctl(nfc_fd, IOCTRL_CMD_CS, &arg_0);	
}
//==========================================================
//	�������ƣ�	SPI1_ReadWriteByte
//
//	�������ܣ�	ͨ��SPI1����һ���ֽڣ������ؽ��յ�һ���ֽڡ�
//
//	��ڲ�����	unsigned char TxData���������͵�����
//
//	���ز�����	unsigned char ���ص�����
//
//	˵����
//==========================================================
unsigned char SPI1_WriteByte(unsigned char TxData)
{
    unsigned char Rxdata;
    usleep(10);
	Rxdata = write(nfc_fd,&TxData,1);
 	return Rxdata;          		    //�����յ�������		
}
unsigned char SPI1_ReadByte(void)
{
    unsigned char Rxdata;
    usleep(10);
	read(nfc_fd,&Rxdata,1);
 	return Rxdata;          		    //�����յ�������		
}
/*****************���϶�������ֲ���������ֵĴ���************************/
/*****************���϶�������ֲ���������ֵĴ���************************/
/*****************���϶�������ֲ���������ֵĴ���************************/
void nfc_init(void)
{
	nfc_fd = open("/dev/nfc", O_RDWR);
	if (nfc_fd < 0) {
		perror("**/dev/nfc\r\n");
		exit(1);
	}
	
	msleep(100);
	PN532_CSn_L();
	msleep(100);
	PN532_CSn_H();
	printf("init nfc\r\n");
}
void nfc_close(void)
{
	close(nfc_fd);
}
unsigned char gStatus = 0xAA;
unsigned char ReadStatus(void)
{
    unsigned char cmd=0x02;//0000 0010
    PN532_CSn_L();
    SPI1_WriteByte(cmd);
    gStatus = SPI1_ReadByte();
	printf("gStatus=%d\r\n",gStatus);
    PN532_CSn_H();
    return gStatus;
} 

unsigned char PN532_RxBuffer[500];	//���ջ���
unsigned short PN532_RXCounter;	//���յ�����������
unsigned char flag_rev_finish;		//���ڽ��յ����ݵı�־�� 1Ϊ���յ�


unsigned char UID[4];		   		//�洢 UID
unsigned char KeyBuf[6] = {0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char BlockBuf[16];

void delay_10ms(unsigned short n10ms)
{
    msleep(10*n10ms);
}

void CleanBuffer(unsigned short num)//���� ǰ ���ٸ��ֽڵ�����
{
    unsigned short i=0;
    
    for(i=0;i<num;i++)PN532_RxBuffer[i]=0x00;
}
/*********************************************************************************************************
��������  SAMConfiguration
�������ܣ�����PN532���ڲ�����
���������
	mode: defines the way of using the SAM
      	0x01:normal mode
      	0x02:virtual mode
      	0x03:wired mode
      	0x04:dual mode
 	timeout:
      	0x00:��ʹ��timeout
      	0x01-0xFF����ʱֵ
 	irq:
      	0x00����ʹ��P70_IRQ
      	0x01��ʹ��P70_IRQ
���������
 	�ɹ���TRUE
 	ʧ�ܣ�FALSE
**********************************************************************************************************/
unsigned char SAMConfiguration(unsigned char mode,unsigned char timeout,unsigned char irq)
{
    unsigned char data[30];
    unsigned char i;
    unsigned char CheckCode=0; //����У����
    unsigned char temp=0;
  
    while(1)
    { 
        flag_rev_finish=0;
        //PN532 wakeup
		data[0]=0x55;
        data[1]=0x55;
        data[2]=0x00;
        data[3]=0x00;
        data[4]=0x00;
        data[5]=0x00;
        data[6]=0x00;
        data[7]=0x00;
        data[8]=0x00;
        data[9]=0x00;
        data[10]=0x00;
        data[11]=0x00;
        data[12]=0x00;
        data[13]=0x00;
        
		data[14]=0x00;	 //֡ͷ
		data[15]=0x00;
        data[16]=0xFF;
       
	    data[17]=0x05; 			 //�� ����
        data[18]=0x100-data[17]; //�� ���� У��  0x100-data[3]
		
		data[19]=0xD4; //�����ʶ
		data[20]=0x14; //�����ʶ��
		data[21]= mode;
		data[22]= timeout;
		data[23]= irq;

		temp = 	data[19]+ data[20] + data[21] + data[22] + data[23];
        data[24]=0x100 - temp; //���� У��   0x100-
        data[25]=0x00;
        
		delay_10ms(18); 
       
   		
		//00 00 FF 00 FF 00 00 00 FF 02 FE D5 15 16 00    
        if(flag_rev_finish)
        {         
            flag_rev_finish=0;
			temp = 0;
            for(i=11;i<13;i++)
            {
                temp+=PN532_RxBuffer[i];
            }
            CheckCode=0x100-temp;
            if(CheckCode==PN532_RxBuffer[13])
            {
                CleanBuffer(40);//��� ���ڽ��ջ�����ǰ30 ���ֽ�����
                return 1; 
            }
			return 0;
        }
		return 0;
		
    }
}

/**************************************************************************************
��������  InListPassiveTarget
�������ܣ�PN532��⿨
���������
	maxTag:
            PN532����ʼ�����ĸ�����PN532һ��ֻ��ͬʱ����2�ſ�         
 	brty:
            0x00 : 106 kbps type A (ISO/IEC14443 Type A),
            0x01 : 212 kbps (FeliCa polling),
            0x02 : 424 kbps (FeliCa polling),
            0x03 : 106 kbps type B (ISO/IEC14443-3B),
            0x04 : 106 kbps Innovision Jewel tag.
	*CardID  
			��Ƭԭʼ���к�
���������
 	�ɹ���TRUE
 	ʧ�ܣ�FALSE
*****************************************************************************************/
unsigned char  nfc_InListPassiveTarget(unsigned char maxTag,unsigned char brty,unsigned char *CardID)
{
    unsigned char data[11];
    unsigned char i;
    unsigned char CheckCode=0; //����У����
    unsigned char temp=0;
    {   
        flag_rev_finish=0;
        data[0]=0x00;  //֡ͷ
        data[1]=0x00;  //��ʼ��־
        data[2]=0xFF;
        data[3]=0x04;  //������
        data[4]=0xFC;  //������ У��  0x100-data[3]
        
		data[5]=0xD4;  //�����ʶ��
        data[6]=0x4A;  //�����ʶ��
        data[7]=maxTag;
        data[8]=brty;
        
		data[9]=0x100 - data[5] - data[6] - data[7] - data[8];  //����У��
        data[10]=0x00;
        
	    delay_10ms(18); 
      
        temp=0;
        if(flag_rev_finish)
        {         
            flag_rev_finish=0;
			if((PN532_RxBuffer[12] == 0x4b) && (PN532_RxBuffer[13] != 0))
            {
				for(i=11;i<23;i++)
	            {
	                temp+=PN532_RxBuffer[i];
	            }
	            CheckCode=0x100-temp;
	            if(CheckCode==PN532_RxBuffer[23])
	            {
	                CardID[0]=PN532_RxBuffer[19];
	                CardID[1]=PN532_RxBuffer[20];
	                CardID[2]=PN532_RxBuffer[21];
	                CardID[3]=PN532_RxBuffer[22]; 
					//IndicateOn(1,1,1);
					CleanBuffer(40);//��� ���ڽ��ջ�����ǰ30 ���ֽ����� 
	                return 1;
	            }
			}
			CleanBuffer(40);
        }
		return 0;
		
    }
}

/**************************************************************************************
��������  nfc_PsdVerify
�������ܣ�Mifare ����֤,��ĳһ����֤ͨ���󶼿��Զ����������������еĿ���ж�д����
���������
    unsigned char AuthenticationType ��0x60 / 0x61 Authentication A / Authentication B
	unsigned char BlockNo��	0~63
	unsigned char * KeyData ��  ����Կ   
	unsigned char *SerialNum: �����к�	  
���������
 	�ɹ���TRUE
 	ʧ�ܣ�FALSE
*****************************************************************************************/
unsigned char  nfc_PsdVerify(unsigned char AuthenticationType,unsigned char BlockNo,unsigned char * KeyData,unsigned char *SerialNum)
{
    unsigned char data[22];
    unsigned char temp=0; 
    unsigned char i;
    unsigned char CheckCode=0; //����У����
    
    
    flag_rev_finish=0;
    data[0]=0x00;
    data[1]=0x00;
    data[2]=0xFF;
    
    data[3]=0x0F; //�� ����
    data[4]=0xF1; //�� ���� У��  0x100-data[3]
    
    data[5]=0xD4; //�����ʶ��
    data[6]=0x40; //�����ʶ��
    
    data[7]=0x01;
    data[8]=AuthenticationType;    //KeyA ��֤
    data[9]=BlockNo;  			   //���
    
    memcpy(&data[10],KeyData,6);   //��Կ
	memcpy(&data[16],SerialNum,4); //��Ƭԭʼ���к�
    for(i=5;i<20;i++)
    {
        temp+=data[i];
    }
    data[20]=0x100-temp;   
    data[21]=0x00;
     
    delay_10ms(18);

    temp=0;
    for(i=11;i<14;i++)
    {
        temp+=PN532_RxBuffer[i];
    }
    CheckCode=0x100-temp;
	//41 00
    if(CheckCode==PN532_RxBuffer[14])
    {
       if((PN532_RxBuffer[13]==0x00) && (PN532_RxBuffer[12]==0x41))	//��֤�ɹ�
       {
		 CleanBuffer(40);//��� ���ڽ��ջ�����ǰ40 ���ֽ�����
		 return 1;
       }
    }
	return 0;
}

/**************************************************************************************
��������  nfc_read
�������ܣ�Mifare ��������
���������
	unsigned char BlockNo��	   0~63
	unsigned char *BlockData ��  ������   
���������
 	�ɹ���TRUE
 	ʧ�ܣ�FALSE
*****************************************************************************************/
unsigned char  nfc_read(unsigned char BlockNO,unsigned char *ReadData)
{
    unsigned char data[12];
    unsigned char temp=0; 
    unsigned char i;
    unsigned char CheckCode=0; //����У����

    flag_rev_finish=0;
    data[0]=0x00;
    data[1]=0x00;
    data[2]=0xFF;
    
    data[3]=0x05; //�� ����
    data[4]=0xFB; //�� ���� У��  0x100-data[3]
    
    data[5]=0xD4; //�����ʶ��
    data[6]=0x40; //�����ʶ��
    
    data[7]=0x01;
    data[8]=0x30;
    data[9]=BlockNO; //���ڶ����16�ֽ����� 
    
    temp=0;
    for(i=5;i<10;i++)
    {
        temp+=data[i];
    }
	data[10]=0x100-temp; 
    data[11]=0x00;
    
    delay_10ms(18);
  
    temp=0;
    for(i=11;i<30;i++)
    {
        temp+=PN532_RxBuffer[i];
    }
    CheckCode=0x100-temp;
    if(CheckCode==PN532_RxBuffer[30])
    {              
        if((PN532_RxBuffer[13]==0x00) && (PN532_RxBuffer[12]==0x41))
		{
			memcpy(ReadData,&PN532_RxBuffer[14],16);
			CleanBuffer(40);
			return 1;
		}
    }
	CleanBuffer(40);
	return 0;
}
/**************************************************************************************
��������  nfc_write
�������ܣ�Mifare д������
���������
	unsigned char BlockNo��	   0~63
	unsigned char * BlockData ��  ������   
���������
 	�ɹ���TRUE
 	ʧ�ܣ�FALSE
*****************************************************************************************/
unsigned char  nfc_write(unsigned char BlockNO,unsigned char *WriteData)
{
    unsigned char data[28];
    unsigned char temp=0;
    unsigned char i;
    unsigned char CheckCode=0;
    
    data[0]=0x00;
    data[1]=0x00;
    data[2]=0xFF;
    
    data[3]=0x15; //�� ����
    data[4]=0xEB; //�� ���� У��  0x100-data[3]
    
    data[5]=0xD4; //�����ʶ��
    data[6]=0x40; //�����ʶ��
    
    data[7]=0x01; //��д����6�ֽ� ����1�����ֲ�
    data[8]=0xA0; //д
    data[9]=BlockNO; //д�ڶ����16�ֽ����� 
    
    memcpy(&data[10],WriteData,16);

    
    for(i=5;i<26;i++)
    {
        temp+=data[i];
    }
    data[26]=0x100-temp; 
    data[27]=0x00;
    
    delay_10ms(18);

    temp=0;
    for(i=11;i<14;i++)
    {
        temp+=PN532_RxBuffer[i];
    }
    CheckCode=0x100-temp;
    if(CheckCode==PN532_RxBuffer[14])
    {
         if((PN532_RxBuffer[13]==0x00) && (PN532_RxBuffer[12]==0x41))
         {
			 CleanBuffer(40);//��� ���ڽ��ջ�����ǰ40 ���ֽ�����
			 return 1;
         }
    }
	CleanBuffer(40);
	return 0;
}

