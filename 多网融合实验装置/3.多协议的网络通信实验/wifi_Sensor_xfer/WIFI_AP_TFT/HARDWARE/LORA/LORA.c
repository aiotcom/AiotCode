#include "stm32f1xx.h"
#include "LORA.h"
#include "delay.h"
void SX1278Reset(void);
void SX1278IO_Init(void);
/* SPI1 init function */
SPI_HandleTypeDef hspi1;
static void MX_SPI1_Init(void)
{
  /* SPI1 parameter configuration*/
  hspi1.Instance               = SPI1;
  hspi1.Init.Mode              = SPI_MODE_MASTER;
  hspi1.Init.Direction         = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize          = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity       = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase          = SPI_PHASE_1EDGE;
  hspi1.Init.NSS               = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode            = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial     = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    while(1);
  }

}
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hspi->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**SPI1 GPIO Configuration    
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }

}
HAL_StatusTypeDef error;
u8 SPI1_ReadWriteByte(u8 TxData)
{
    u8 Rxdata;
   error  =  HAL_SPI_TransmitReceive(&hspi1,&TxData,&Rxdata,1, 100);       
 	return Rxdata;          		    //�����յ�������		
}
u8 SX1278_RLEN;
void LORA_Init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();           	//����GPIOBʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��  
    MX_SPI1_Init();
	SX1278IO_Init();

	SX1278Reset();
	SX1276LORA_INT();
	//enableInterrupts();
	SX1278_RLEN = 0;     
}

u8 Frequency[3] = {0x6c,0x80,0x00};//Ƶ�ʼ���ֵ 434M * 16384 = Fre

//u8 Frequency[3] = {0x69,0x00,0x00};//Ƶ�ʼ���ֵ 420M

u8 SpreadingFactor=11;             //7-12 ��Ƶ���Ӳ���
u8 CodingRate=2;
u8 Bw_Frequency=7;      //6-9��Ƶ�������
u8 powerValue=7;//0-7 ���书�ʲ���
u8 power_data[8]={0X80,0X80,0X80,0X83,0X86,0x89,0x8c,0x8f}; //
u8 RF_EX0_STATUS;
u8 CRC_Value;



//��ʼ��SPI FLASH��IO��
void SX1278IO_Init(void)
{	    
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();           	//����GPIOBʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��    

    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull  = GPIO_PULLUP;          	//����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	 	//����
	
    GPIO_Initure.Pin   = GPIO_PIN_0|GPIO_PIN_1; 	//PA0-> CE->reset,PA1->CS
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_SET);	//PA0,PA1
    
    GPIO_Initure.Mode  = GPIO_MODE_INPUT;  	//����ģʽ
    GPIO_Initure.Pull  = GPIO_PULLUP;          	//����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	 	//����
	
    GPIO_Initure.Pin   = GPIO_PIN_0; 	     //SX1278IO IRQ
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);    
} 

void SX1278_Init(void)
{  	
	
}

void SX1278Reset(void)
{
	SX1278_RST_L();
	delay_ms(200);
	SX1278_RST_H();
	delay_ms(500);
}

///
void SX1276WriteBuffer( unsigned char addr, unsigned char buffer)
{ 
	SX1278_CS_L(); //NSS = 0;ѡ��оƬ
	SPI1_ReadWriteByte( addr | 0x80 );
	SPI1_ReadWriteByte( buffer);
	SX1278_CS_H(); //NSS = 1;

}

///
u8 SX1276ReadBuffer(unsigned char addr)
{
	unsigned char Value;
	SX1278_CS_L(); //NSS = 0;
	SPI1_ReadWriteByte( addr & 0x7f  );
	Value = SPI1_ReadWriteByte(0xff);
	SX1278_CS_H();//NSS = 1;
	return Value; 
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
	SX1276WriteBuffer( REG_LR_PADAC, 0x84);  //high power
	SX1276WriteBuffer( REG_LR_PACONFIG,  /*power_data[power]*/0x4f ); //��û����һ�䣬Ƶ���Ǽ����ⲻ���ź�,���ǿ��Խ��������շ���
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
	SX1276LoRaSetPacketCrcOn(true);			 			//CRC У���
	SX1276LoRaSetSignalBandwidth( Bw_Frequency );	 			//������Ƶ����, 125khz
	SX1276LoRaSetImplicitHeaderOn(false);		 	//ͬ��ͷ������ģʽ
	SX1276LoRaSetPayloadLength( 0xff);
	SX1276LoRaSetSymbTimeout( 0x3FF );
	SX1276LoRaSetMobileNode(true); 			 			// �����ݵ��Ż�

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
	SPI1_ReadWriteByte( 0x80 );
	for( ASM_i = 0; ASM_i < LEN; ASM_i++ )
	{
		SPI1_ReadWriteByte( *RF_TRAN_P );RF_TRAN_P++;
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
//	�������ƣ�	uint8_t SX1278_InteruptHandler(uint8_t *pRecv)
//
//	�������ܣ�	����LORAоƬ�������ж�
//
//	��ڲ�����	uint8_t *pRecv�����ڽ������ݣ������ڽ�������ʱpRecv����������ָ�룬�����������(void*)0
//
//	���ز�����	�����ж�����
//
//	˵����	     @1:�����ڽ�������ʱ	
//   uint8_t recv[30]
//    if(SX1278_InteruptHandler(recv) == INT_FLG_RX_DONE)
//    {
//
//    }
//               @2:�������
//               SX1278_InteruptHandler((void*)0)
//==========================================================
uint8_t SX1278_InteruptHandler(uint8_t *pRecv)
{
    uint8_t ret;
	RF_EX0_STATUS=SX1276ReadBuffer( REG_LR_IRQFLAGS ); 
	if((RF_EX0_STATUS&0x40)==0x40)  //�������
	{
		CRC_Value=SX1276ReadBuffer( REG_LR_MODEMCONFIG2 );
		if((CRC_Value&0x04)==0x04) //�Ƿ��CRCУ��
		{
			SX1276WriteBuffer (REG_LR_FIFOADDRPTR,0x00);
			SX1278_RLEN = SX1276ReadBuffer(REG_LR_NBRXBYTES); //��ȡ���һ�������ֽ���
			SX1278_CS_L();
			SPI1_ReadWriteByte( 0x00 );
			if(SX1278_RLEN > 249)  //���ղ�����10���ֽ�
				SX1278_RLEN = 249;			
			for(RF_REC_RLEN_i=0;RF_REC_RLEN_i<SX1278_RLEN;RF_REC_RLEN_i++)
			{
				pRecv[RF_REC_RLEN_i]=SPI1_ReadWriteByte(0xff);		
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
u8 Sx1278SendLong(unsigned char *RF_TRAN_P,unsigned char LEN)
{
	uint8_t  Irq_flag=0;
	uint16_t Wait_FLAG = 500;
	
	FUN_RF_SENDPACKET(RF_TRAN_P,LEN); //��������
	while(((Irq_flag&0x08) != 0x08) && Wait_FLAG)
	{
		HAL_Delay(1);
		Wait_FLAG--;
		Irq_flag=SX1276ReadBuffer( REG_LR_IRQFLAGS ); 
	}
    HAL_Delay(100);
    RF_RECEIVE(); //ת��������ģʽ
    HAL_Delay(10);
	return Wait_FLAG?1:0;
}
uint8_t LR_Version;
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
