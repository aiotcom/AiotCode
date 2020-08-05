#include "LORA.h"
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
#define msleep(n) usleep(n*1000)

#define SX1278_MAGIC 'k'
#define IOCTRL_CMD_CS _IOW(SX1278_MAGIC, 1, int)
#define IOCTRL_CMD_RST _IOW(SX1278_MAGIC, 2, int)

#define IOCTRL_CMD_SHOW_HUMI _IOW(SX1278_MAGIC, 3, int)
#define IOCTRL_CMD_SHOW_TEMP _IOW(SX1278_MAGIC, 4, int)
const unsigned int arg_0=0,arg_1=1;
int sx1278_fd;
void SX1278_CS_L(void)
{
	ioctl(sx1278_fd, IOCTRL_CMD_CS, &arg_0);
}
void SX1278_CS_H(void)
{
	ioctl(sx1278_fd, IOCTRL_CMD_CS, &arg_1);
}
void sx1278_write_buffer( unsigned char addr, unsigned char buffer)
{ 
	unsigned tmp;
	ioctl(sx1278_fd, IOCTRL_CMD_CS, &arg_0);//SX1278_CS_L(); //NSS = 0;ѡ��оƬ
//	SPI1_ReadWriteByte( addr | 0x80 );
//	SPI1_ReadWriteByte( buffer);
	tmp = addr | 0x80;
	if(write(sx1278_fd, (void*)&tmp, 1)){
		
	}
	else{
		printf("write:error\r\n");
	}
	usleep(100);
	tmp = buffer;
	if(write(sx1278_fd, (void*)&tmp, 1)){
		
	}
	else{
		printf("write:error\r\n");
	}
	usleep(100);	
	//SX1278_CS_H(); //NSS = 1;
	ioctl(sx1278_fd, IOCTRL_CMD_CS, &arg_1); 
}

unsigned char sx1278_read_buffer(unsigned char addr)
{
	unsigned char Value,tmp;
	//SX1278_CS_L(); //NSS = 0;
	ioctl(sx1278_fd, IOCTRL_CMD_CS, &arg_0); 
	//SPI1_ReadWriteByte( addr & 0x7f  );
	tmp = addr & 0x7f;
	if(write(sx1278_fd, (void*)&tmp, 1)){
		
	}
	else{
		printf("write:error\r\n");
	}
	//Value = SPI1_ReadWriteByte(0xff);
	tmp = 0xff;
	if(read(sx1278_fd, (void*)&Value, 1)){
		
	}
	else{
		printf("read:error\r\n");
	}	
	//SX1278_CS_H();//NSS = 1;
	usleep(100);
	ioctl(sx1278_fd, IOCTRL_CMD_CS, &arg_1);	
	return Value; 
}
void SX1278Reset(void)
{
	ioctl(sx1278_fd, IOCTRL_CMD_RST, &arg_0);
	msleep(200);	
	ioctl(sx1278_fd, IOCTRL_CMD_RST, &arg_1); 
	msleep(200);	
}

unsigned char SX1278_RLEN;

void LORA_Init(int fd)
{
    sx1278_fd = fd;
	SX1278Reset();
	 	
	SX1276LORA_INT();
	printf("id=%d\r\n",sx1278_read_buffer(0x42));
	SX1278_RLEN = 0;     
}
void lora_close(void)
{
	close(sx1278_fd);
}
unsigned char Frequency[3] = {0x6c,0x80,0x00};//Ƶ�ʼ���ֵ 434M * 16384 = Fre

//unsigned char Frequency[3] = {0x69,0x00,0x00};//Ƶ�ʼ���ֵ 420M

unsigned char SpreadingFactor=11;             //7-12 ��Ƶ���Ӳ���
unsigned char CodingRate=2;
unsigned char Bw_Frequency=7;      //6-9��Ƶ�������
unsigned char powerValue=7;//0-7 ���书�ʲ���
unsigned char power_data[8]={0X80,0X80,0X80,0X83,0X86,0x89,0x8c,0x8f}; //
unsigned char RF_EX0_STATUS;
unsigned char CRC_Value;


///
void SX1276WriteBuffer( unsigned char addr, unsigned char buffer)
{ 
	sx1278_write_buffer(addr,buffer);
}

///
unsigned char SX1276ReadBuffer(unsigned char addr)
{
	return sx1278_read_buffer(addr); 
}

void SX1276LoRaSetOpMode( RFMode_SET opMode )
{
	unsigned char opModePrev;
	opModePrev=SX1276ReadBuffer(REG_LR_OPMODE);  //��0x01ģʽ�Ĵ���
	opModePrev &=0xf8;  //�������λ
	opModePrev |= (unsigned char)opMode; //�����β�
	SX1276WriteBuffer( REG_LR_OPMODE, opModePrev); //����д��ȥ	
}

void SX1276LoRaFsk( Debugging_fsk_ook opMode )
{
	unsigned char opModePrev;
	opModePrev=SX1276ReadBuffer(REG_LR_OPMODE); //��0x01ģʽ�Ĵ���
	opModePrev &=0x7F; //�������λ
	opModePrev |= (unsigned char)opMode;  //�����β�
	SX1276WriteBuffer( REG_LR_OPMODE, opModePrev); //����д��ȥ		
}

void SX1276LoRaSetRFFrequency(void)
{
	SX1276WriteBuffer( REG_LR_FRFMSB, Frequency[0]);  //д0x06�Ĵ���
	SX1276WriteBuffer( REG_LR_FRFMID, Frequency[1]);  //д0x07�Ĵ���
	SX1276WriteBuffer( REG_LR_FRFLSB, Frequency[2]);  //д0x08�Ĵ���
}

void SX1276LoRaSetRFPower(unsigned char power )
{
	//Set Pmax to +20dBm for PA_HP, Must turn off PA_LF or PA_HF, and set RegOcp
	//SX1276WriteBuffer( REG_LR_PACONFIG,  power_data[power] ); //��û����һ�䣬Ƶ���Ǽ����ⲻ���ź�,���ǿ��Խ��������շ���
	//SX1276WriteBuffer( REG_LR_OCP, 0x3f);  //add by skay,20160810, д���������Ĵ�����
#if 0    
   	SX1276WriteBuffer( REG_LR_PADAC, 0x87);  //high power
	SX1276WriteBuffer( REG_LR_PACONFIG,  power_data[power] ); //��û����һ�䣬Ƶ���Ǽ����ⲻ���ź�,���ǿ��Խ��������շ���
#else 
	SX1276WriteBuffer( REG_LR_PADAC, 0x84);  //high power
	SX1276WriteBuffer( REG_LR_PACONFIG,  /*power_data[power]*/0x4f ); //��û����һ�䣬Ƶ���Ǽ����ⲻ���ź�,���ǿ��Խ��������շ���
#endif    
}

void SX1276LoRaSetNbTrigPeaks(unsigned char value )
{
	unsigned char RECVER_DAT;
	RECVER_DAT = SX1276ReadBuffer( 0x31);  //Read RegDetectOptimize,
	RECVER_DAT = ( RECVER_DAT & 0xF8 ) | value; //process;
	SX1276WriteBuffer( 0x31, RECVER_DAT );  //write back;
}

void SX1276LoRaSetSpreadingFactor(unsigned char factor )
{
	unsigned char RECVER_DAT;
	SX1276LoRaSetNbTrigPeaks( 3 ); //0x03-->SF7 to SF12
	RECVER_DAT=SX1276ReadBuffer( REG_LR_MODEMCONFIG2); //��0x1E�Ĵ���  
	RECVER_DAT = ( RECVER_DAT & RFLR_MODEMCONFIG2_SF_MASK ) | ( factor << 4 );
	SX1276WriteBuffer( REG_LR_MODEMCONFIG2, RECVER_DAT );	 
}
	
void SX1276LoRaSetErrorCoding(unsigned char value )
{	
	unsigned char RECVER_DAT;
	RECVER_DAT=SX1276ReadBuffer( REG_LR_MODEMCONFIG1); //��0x1D�Ĵ���
	RECVER_DAT = ( RECVER_DAT & RFLR_MODEMCONFIG1_CODINGRATE_MASK ) | ( value << 1 );
	SX1276WriteBuffer( REG_LR_MODEMCONFIG1, RECVER_DAT);
}

void SX1276LoRaSetPacketCrcOn(BOOL_t enable )
{	
	unsigned char RECVER_DAT;
	RECVER_DAT= SX1276ReadBuffer( REG_LR_MODEMCONFIG2);  //��0x1E�Ĵ��� 
	RECVER_DAT = ( RECVER_DAT & RFLR_MODEMCONFIG2_RXPAYLOADCRC_MASK ) | ( enable << 2 );
	SX1276WriteBuffer( REG_LR_MODEMCONFIG2, RECVER_DAT );
}

void SX1276LoRaSetSignalBandwidth(unsigned char bw )
{
	unsigned char RECVER_DAT;
	RECVER_DAT=SX1276ReadBuffer( REG_LR_MODEMCONFIG1);  //��0x1D�Ĵ���
	RECVER_DAT = ( RECVER_DAT & RFLR_MODEMCONFIG1_BW_MASK ) | ( bw << 4 );
	SX1276WriteBuffer( REG_LR_MODEMCONFIG1, RECVER_DAT );
}

void SX1276LoRaSetImplicitHeaderOn(BOOL_t enable )
{
	unsigned char RECVER_DAT;
	RECVER_DAT=SX1276ReadBuffer( REG_LR_MODEMCONFIG1 );  //��0x1D�Ĵ���
	RECVER_DAT = ( RECVER_DAT & RFLR_MODEMCONFIG1_IMPLICITHEADER_MASK ) | ( enable );
	SX1276WriteBuffer( REG_LR_MODEMCONFIG1, RECVER_DAT );
}
	
void SX1276LoRaSetSymbTimeout(unsigned int value )
{
	unsigned char RECVER_DAT[2];
	RECVER_DAT[0]=SX1276ReadBuffer( REG_LR_MODEMCONFIG2 );    //��0x1E�Ĵ���
	RECVER_DAT[1]=SX1276ReadBuffer( REG_LR_SYMBTIMEOUTLSB );  //��0x1F�Ĵ���
	RECVER_DAT[0] = ( RECVER_DAT[0] & RFLR_MODEMCONFIG2_SYMBTIMEOUTMSB_MASK ) | ( ( value >> 8 ) & ~RFLR_MODEMCONFIG2_SYMBTIMEOUTMSB_MASK );
	RECVER_DAT[1] = value & 0xFF;
	SX1276WriteBuffer( REG_LR_MODEMCONFIG2, RECVER_DAT[0]);
	SX1276WriteBuffer( REG_LR_SYMBTIMEOUTLSB, RECVER_DAT[1]);
}
	
void SX1276LoRaSetPayloadLength(unsigned char value )
{
	SX1276WriteBuffer( REG_LR_PAYLOADLENGTH, value );  //д0x22�Ĵ���
} 

	
#if 0
void SX1276LoRaSetPreamLength(unsigned int value )
{
	unsigned char a[2];
	a[0]=(value&0xff00)>>8;
	a[1]=value&0xff;
	SX1276WriteBuffer( REG_LR_PREAMBLEMSB, a[0] );
	SX1276WriteBuffer( REG_LR_PREAMBLELSB, a[1] );
}
#endif

void SX1276LoRaSetMobileNode(BOOL_t enable )
{	 
	unsigned char RECVER_DAT;
	RECVER_DAT=SX1276ReadBuffer( REG_LR_MODEMCONFIG3 );  //��0x26�Ĵ���
	RECVER_DAT = ( RECVER_DAT & RFLR_MODEMCONFIG3_MOBILE_NODE_MASK ) | ( enable << 3 );
	SX1276WriteBuffer( REG_LR_MODEMCONFIG3, RECVER_DAT );
}

void SX1276LORA_INT(void)
{
	SX1276LoRaSetOpMode(Sleep_mode);  //����˯��ģʽ
	SX1276LoRaFsk(LORA_mode);	     		// ������Ƶģʽ
	SX1276LoRaSetOpMode(Stdby_mode);  // ����Ϊ��ͨģʽ
	SX1276WriteBuffer( REG_LR_DIOMAPPING1,GPIO_VARE_1); //д0x40�Ĵ���,DIO����ӳ������
	SX1276WriteBuffer( REG_LR_DIOMAPPING2,GPIO_VARE_2); //д0x41�Ĵ���
	SX1276LoRaSetRFFrequency();  			//Ƶ������
	SX1276LoRaSetRFPower(powerValue); //��������
	SX1276LoRaSetSpreadingFactor(SpreadingFactor);	 		// ��Ƶ��������
	SX1276LoRaSetErrorCoding(CodingRate);		 	//��Ч���ݱ�
    SX1276LoRaSetPacketCrcOn(TRUE);			 			//CRC У���
	SX1276LoRaSetSignalBandwidth( Bw_Frequency );	 			//������Ƶ����, 125khz
    SX1276LoRaSetImplicitHeaderOn(FALSE);		 	//ͬ��ͷ������ģʽ
	SX1276LoRaSetPayloadLength( 0xff);
	SX1276LoRaSetSymbTimeout( 0x3FF );
    SX1276LoRaSetMobileNode(TRUE); 			 			// �����ݵ��Ż�

	RF_RECEIVE();
}

void FUN_RF_SENDPACKET(unsigned char *RF_TRAN_P,unsigned char LEN)
{	
	unsigned char ASM_i;
	
	SX1276LoRaSetOpMode( Stdby_mode );
	SX1276WriteBuffer( REG_LR_HOPPERIOD, 0 );			//����Ƶ������
	SX1276WriteBuffer(REG_LR_IRQFLAGSMASK,IRQN_TXD_Value);	//�򿪷����ж�
	SX1276WriteBuffer( REG_LR_PAYLOADLENGTH, LEN);//������ݰ�
	SX1276WriteBuffer( REG_LR_FIFOTXBASEADDR, 0); //дTx FIFO��ַ
	SX1276WriteBuffer( REG_LR_FIFOADDRPTR, 0 ); 	//SPI interface address pointer in FIFO data buffer
	SX1278_CS_L();   //��Ƭѡ
	//SPI1_ReadWriteByte( 0x80 );
	unsigned char tmp = 0x80;
	write(sx1278_fd,(void*)&tmp,1);
	for( ASM_i = 0; ASM_i < LEN; ASM_i++ )
	{
		//SPI1_ReadWriteByte( *RF_TRAN_P );
		write(sx1278_fd,(void*)RF_TRAN_P,1);
		RF_TRAN_P++;
	}
	SX1278_CS_H();  //��Ƭѡ
	SX1276WriteBuffer(REG_LR_DIOMAPPING1,0x40);  //�����ж�ӳ�䵽DIO0����
	SX1276WriteBuffer(REG_LR_DIOMAPPING2,0x00);
	SX1276LoRaSetOpMode( Transmitter_mode );     //����Ϊ����ģʽ
	
}
void RF_RECEIVE (void)
{
	SX1276LoRaSetOpMode(Stdby_mode );
	SX1276WriteBuffer(REG_LR_IRQFLAGSMASK,IRQN_RXD_Value);  //0x11,�򿪽����ж�
	SX1276WriteBuffer(REG_LR_HOPPERIOD,	PACKET_MIAX_Value );//0x24�Ĵ���
	SX1276WriteBuffer( REG_LR_DIOMAPPING1, 0X00 ); 					//DIO����ӳ�����ã���Ĭ��
	SX1276WriteBuffer( REG_LR_DIOMAPPING2, 0X00 );	
	SX1276LoRaSetOpMode( Receiver_mode );  //����Ϊ��������ģʽ
}

#if 0	
void RF_CAD_RECEIVE (void)
{
	SX1276LoRaSetOpMode( Stdby_mode );
	SX1276WriteBuffer(REG_LR_IRQFLAGSMASK,  IRQN_CAD_Value);	//�򿪷����ж�
	SX1276WriteBuffer( REG_LR_DIOMAPPING1, 0X80 );
	SX1276WriteBuffer( REG_LR_DIOMAPPING2, 0X00 );	
	SX1276LoRaSetOpMode( CAD_mode );
}
#endif

#if 0
void RF_SEELP(void)
{
	SX1276LoRaSetOpMode( Stdby_mode );
	SX1276WriteBuffer(REG_LR_IRQFLAGSMASK,  IRQN_SEELP_Value);  //�򿪷����ж�
	SX1276WriteBuffer( REG_LR_DIOMAPPING1, 0X00 );
	SX1276WriteBuffer( REG_LR_DIOMAPPING2, 0X00 );	
	SX1276LoRaSetOpMode( Sleep_mode );
}
#endif

//**************�������ж����洦��Ĵ���*******************************
unsigned char RF_REC_RLEN_i;
//==========================================================
//	�������ƣ�	unsigned char SX1278_InteruptHandler(unsigned char *pRecv)
//
//	�������ܣ�	����LORAоƬ�������ж�
//
//	��ڲ�����	unsigned char *pRecv�����ڽ������ݣ������ڽ�������ʱpRecv����������ָ�룬�����������(void*)0
//
//	���ز�����	�����ж�����
//
//	˵����	     @1:�����ڽ�������ʱ	
//   unsigned char recv[30]
//    if(SX1278_InteruptHandler(recv) == INT_FLG_RX_DONE)
//    {
//
//    }
//               @2:�������
//               SX1278_InteruptHandler((void*)0)
//==========================================================
unsigned char SX1278_InteruptHandler(unsigned char *pRecv)
{
    unsigned char ret;
	RF_EX0_STATUS=SX1276ReadBuffer( REG_LR_IRQFLAGS ); 
	if((RF_EX0_STATUS&0x40)==0x40)  //�������
	{
		CRC_Value=SX1276ReadBuffer( REG_LR_MODEMCONFIG2 );
		if((CRC_Value&0x04)==0x04) //�Ƿ��CRCУ��
		{
			SX1276WriteBuffer (REG_LR_FIFOADDRPTR,0x00);
			SX1278_RLEN = SX1276ReadBuffer(REG_LR_NBRXBYTES); //��ȡ���һ�������ֽ���
			SX1278_CS_L();
			//SPI1_ReadWriteByte( 0x00 );
			unsigned char tmp = 0x00;
			unsigned char value;
			write(sx1278_fd,(void*)&tmp,1);
			if(SX1278_RLEN > 249)  //���ղ�����10���ֽ�
				SX1278_RLEN = 249;			
			for(RF_REC_RLEN_i=0;RF_REC_RLEN_i<SX1278_RLEN;RF_REC_RLEN_i++)
			{
				read(sx1278_fd,(void*)&value,1);
				pRecv[RF_REC_RLEN_i] = value;////SPI1_ReadWriteByte(0xff);		
			}
			SX1278_CS_H();
		}
		SX1276LoRaSetOpMode( Stdby_mode );
		SX1276WriteBuffer(REG_LR_IRQFLAGSMASK, IRQN_RXD_Value);  //�򿪷����ж�
		SX1276WriteBuffer(REG_LR_HOPPERIOD,    PACKET_MIAX_Value);
		SX1276WriteBuffer( REG_LR_DIOMAPPING1, 0X00 );
		SX1276WriteBuffer( REG_LR_DIOMAPPING2, 0x00 );	
		SX1276LoRaSetOpMode( Receiver_mode );
        
    ret = INT_FLG_RX_DONE;
	}
	else if((RF_EX0_STATUS&0x08)==0x08)  //�������
	{
		SX1276LoRaSetOpMode( Stdby_mode );
		SX1276WriteBuffer(REG_LR_IRQFLAGSMASK,IRQN_RXD_Value);	//�򿪷����ж�
		SX1276WriteBuffer(REG_LR_HOPPERIOD,   PACKET_MIAX_Value );
		SX1276WriteBuffer( REG_LR_DIOMAPPING1, 0X00 );
		SX1276WriteBuffer( REG_LR_DIOMAPPING2, 0x00 );	
		SX1276LoRaSetOpMode( Receiver_mode );
        
		ret = INT_FLG_TX_DONE;
	}
	else if((RF_EX0_STATUS&0x04)==0x04)  //cad���
	{  
		if((RF_EX0_STATUS&0x01)==0x01)
		{	 
		//��ʾCAD ��⵽��Ƶ�ź� ģ������˽���״̬����������
			SX1276LoRaSetOpMode( Stdby_mode );
			SX1276WriteBuffer(REG_LR_IRQFLAGSMASK,IRQN_RXD_Value);	//�򿪷����ж�
			SX1276WriteBuffer(REG_LR_HOPPERIOD,   PACKET_MIAX_Value );
			SX1276WriteBuffer( REG_LR_DIOMAPPING1, 0X02 );
			SX1276WriteBuffer( REG_LR_DIOMAPPING2, 0x00 );	
			SX1276LoRaSetOpMode( Receiver_mode );
            
			ret = INT_FLG_CAD_DONE;
		}
		else
		{						   
		// û��⵽
			SX1276LoRaSetOpMode( Stdby_mode );
			SX1276WriteBuffer(REG_LR_IRQFLAGSMASK,	IRQN_SEELP_Value);	//�򿪷����ж�
			SX1276WriteBuffer( REG_LR_DIOMAPPING1, 0X00 );
			SX1276WriteBuffer( REG_LR_DIOMAPPING2, 0X00 );	
			SX1276LoRaSetOpMode( Sleep_mode );
            
			ret = INT_FLG_CAD_FAIL;
		}
	}
	else
	{
		SX1276LoRaSetOpMode( Stdby_mode );
		SX1276WriteBuffer(REG_LR_IRQFLAGSMASK,IRQN_RXD_Value);	//�򿪷����ж�
		SX1276WriteBuffer(REG_LR_HOPPERIOD,   PACKET_MIAX_Value );
		SX1276WriteBuffer( REG_LR_DIOMAPPING1, 0X02 );
		SX1276WriteBuffer( REG_LR_DIOMAPPING2, 0x00 );	
		SX1276LoRaSetOpMode( Receiver_mode );
		
	}
	SX1276WriteBuffer( REG_LR_IRQFLAGS, 0xff  );
    
    return ret;

}
//
unsigned char Sx1278SendLong(unsigned char *RF_TRAN_P,unsigned char LEN)
{
	unsigned char  Irq_flag=0;
	unsigned short Wait_FLAG = 500;
	
	FUN_RF_SENDPACKET(RF_TRAN_P,LEN); //��������
	while(((Irq_flag&0x08) != 0x08) && Wait_FLAG)
	{
		msleep(1);
		Wait_FLAG--;
		Irq_flag=SX1276ReadBuffer( REG_LR_IRQFLAGS ); 
	}
    msleep(100);
    RF_RECEIVE(); //ת��������ģʽ
    msleep(10);
	return Wait_FLAG?1:0;
}
unsigned char LR_Version;
void ProcessRecv(void)
{
#if  0  
    LR_Version = SX1276ReadBuffer( REG_LR_IRQFLAGS );
	if(SX1278_IRQ_INPUT())  //��0x12״̬�Ĵ���
    {
				SX1278_InteruptHandler((void*)0);
    }
#endif    
}
