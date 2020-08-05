#include "stm32f1xx.h"
#include "CC2500.h"
#include "CC2500_reg.h"
#include "delay.h"
#include "USART.h"
#include "Rs485.h"
#include "string.h"

#define MAXPACKETSIZE   20
#define MAXROUTERDEEP   3
#define MAXLABELNUM     15

uint8_t  gCC2500RxBuf[20]={0};
uint8_t  gCC2500TxBuf[] = {0x06,0x31,0x32,0x33,0x34,0x35,0x36};

#define CC2500_MI  (GPIOA->IDR & GPIO_PIN_6)//HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)
#define CC_MISO    GPIO_PIN_6 

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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi1.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode            = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial     = 7;
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
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin  = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
      
    GPIO_InitStruct.Pin   = GPIO_PIN_4;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_PULLUP;     
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 
     CC_CSn_H;
  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }

}

HAL_StatusTypeDef error;
uint8_t  SPI1_ReadWriteByte(uint8_t  TxData)
{
    uint8_t  Rxdata;
    delay_us(10);
    error  =  HAL_SPI_TransmitReceive(&hspi1,&TxData,&Rxdata,1, 1000); 
 	return Rxdata;          		    //�����յ�������		
}

uint8_t  paTable[8] = {0xFB,0xFE};
void ClearDataBuf(uint8_t  * pBuf,uint8_t  Len)
{
    uint8_t  cnt;
    for(cnt=0;cnt<Len;cnt++)
    {
        pBuf[cnt] = 0x00;
    }
}

RF_SETTINGS RFSettings = {
    0x06,   //IOCFG2    ��GDO2��Ϊ�շ�״ָ̬ʾ����
    0x2E,   //IOCFG1    High impedance (3-state) 
    0x06,   //IOCFG0    ��GDO0��Ϊ�շ�״ָ̬ʾ����
    0x06,   //FIFOTHR   ����TX FIFO��RX FIFO����ֵ���ֱ�Ϊ33��32
    0xD3,   //SYNC1     16λͬ���ֵĸ߰�λ
    0x91,   //SYNC0     16λͬ���ֵĵͰ�λ
    0xFF,   //PKTLEN    ���ݰ�����ָ���Ĵ���,��󳤶�Ϊ255�ֽ�
    0x04,   //PKTCTRL1  ����״̬�ֽڸ��������ݰ�����Ч�غ���
    0x45,   //PKTCTRL0  ���ÿɱ䳤���ݰ�ģʽ
    0x00,   //ADDR      �㲥��ַ��0x00��
    0x00,   //CHANNR    ������Ƶͨ�Źʹ����ŵ�
//    0x01,   //CHANNR    ������Ƶͨ�Źʹ����ŵ�    
    0x09,   //FSCTRL1   ����IFƵ��Ϊ260kHz
    0x00,   //FSCTRL0   ����Ƶ��ƫ������С������Ƶƫ��ȥĬ��ֵ0x00
    0x5D,   //FREQ2     ���FREQ1��FREQ0�����ز�Ƶ��Ϊ2438MHz
    0x93,   //FREQ1     
    0xB1,   //FREQ0
    0x2D,   //MDMCFG4   �����˲�����Ϊ203kHz
    0x3B,   //MDMCFG3   ���MDMCFG4�����ݴ�����������Ϊ250bps
    0x73,   //MDMCFG2   ѡ��MSK����,Manchester Disable,30/32ͬ����ģʽ
    0x22,   //MDMCFG1   FEC Disable,ǰ���ֽ�Ϊ4�ֽ�
    0xF8,   //MDMCFG0   ��MDMCFG1һ�������ŵ�����
    0x47,   //DEVIATN   �ŵ�����Ƶ������
    0x00,   //MCSM2
    0x00,   //MCSM1     RX��TX���̽����󣬶��ص�IDLE״̬,�յ�һ�����ݰ���������CCA
//    0x0C,   //MCSM1     RX���̽���������RX
    0x18,   //MCSM0     ��IDLE��TX����RXʱ���Զ��ز�Ƶ��У׼,64�κ��Ʋ���������ֹ
    0x1D,   //FOCCFG    ��SmartRF Studio����������Ƶ��ƫ�Ʋ���
    0x1C,   //BSCFG     ��SmartRF Studio������λͬ������
    0xC7,   //AGCCTRL2  ��SmartRF Studio������AGC���ƼĴ���
    0x00,   //AGCCTRL1  
    0xB2,   //AGCCTRL0
    0x00,   //WOREVT1   �¼� 0 ������ͣ�Ĵ����ĸ��ֽ�
    0x00,   //WOREVT0   �¼� 0 ������ͣ�Ĵ����ĵ��ֽ�
    0x00,   //WORCTRL
    0xB6,   //FREND1    ǰ�� RX ���ã���Ҫ�ǵ����������
    0x10,   //FREND0    �趨PA���ʣ�ΪPATABLE�����������ֵ��000��
    0xEA,   //FSCAL3    Ƶ�ʺϳ���У׼�����Լ�����洢
    0x0A,   //FSCAL2    ���������ȡֵ���õ���ѽ��
    0x00,   //FSCAL1
    0x11,   //FSCAL0
    0x00,   //RCCTRL1
    0x00,   //RCCTRL0
    0x59,   //FSTEST    �����ã�����Ҫд����Ĵ���
    0x00,   //PTEST     ����IDLE״̬��д��0xBF��Ƭ�ڵ��¶ȴ���������
    0x00,   //AGCTEST
    0x88,   //TEST2
    0x31,   //TEST1
    0x0B,   //TEST0    
};
#define READ_GDO0() HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)
#define READ_GDO2() HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)
void CC2500_GD0x_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();      
    
    GPIO_Initure.Pin    = GPIO_PIN_1|GPIO_PIN_0;											
    GPIO_Initure.Mode   = GPIO_MODE_INPUT;
    GPIO_Initure.Pull   = GPIO_PULLDOWN; 
    GPIO_Initure.Speed  = GPIO_SPEED_FREQ_LOW; 					
    HAL_GPIO_Init(GPIOA, &GPIO_Initure); 
}
void POWER_UP_RESET_CCxxx0(void)
{
    CC2500_ModeIdle();
    CC_CSn_H;
	

	delay_us(30);

	CC_CSn_L;
//	while(1);
	delay_us(30);

	CC_CSn_H;

	delay_us(45);

	 CC2500_WriteStrobe(SRES);
}
uint8_t get_state_for_clear;
void CC2500_Init()
{
    /*****Power-On Reset with SRES---RFCSn_wave****
    ***_(30us)__           ___(45us)_____          
    ***         |_(30us)__|              |________
    **********************************************/
    
    MX_SPI1_Init();
    CC2500_GD0x_Init();    
    CC_CSn_L;
    delay_us(500);//�ȴ������ȶ�
   
    
    delay_us(100);
    while(CC2500_MI&CC_MISO);             //CC_MISO == 0�������ȶ�
    delay_us(200);
    CC_CSn_H;

//	 POWER_UP_RESET_CCxxx0();    
    CC2500_WriteSettings(&RFSettings);
    delay_us(100);
    CC2500_ModeIdle();    
    CC2500_WriteStrobe(SFRX);
    delay_us(1);
    CC2500_WriteStrobe(SFTX);
    delay_us(1);
    CC2500_SetPA();
    CC2500_ModeIdle();
}

void CC2500_WriteByte(uint8_t  Addr,uint8_t  data)
{
    CC_CSn_L;    
    while(CC2500_MI&CC_MISO);
    //CC2500_SPI_Write(Addr+WRITE_SINGLE);
    SPI1_ReadWriteByte(Addr+WRITE_SINGLE);
    __NOP();
    __NOP();
    __NOP();
    //CC2500_SPI_Write(data);
    SPI1_ReadWriteByte(data);
    CC_CSn_H;

}

void CC2500_BustWrite(uint8_t  Addr,uint8_t  * pData,uint8_t  len)
{
    uint8_t  i;
    CC_CSn_L;
    
    while(CC2500_MI&CC_MISO);
    //CC2500_SPI_Write(Addr+WRITE_BURST); 
    SPI1_ReadWriteByte(Addr+WRITE_BURST);
    __NOP();
    __NOP();
    __NOP();
    for(i=0;i<len;i++)
    {
        SPI1_ReadWriteByte(pData[i]);
    }
//    for(i=0;i<len;i++)
//    {
//        temp = pData[i];
//        for(cnt=0;cnt<8;cnt++)
//        {
//            if(temp&0x80)
//                CC_MO_H;
//            else
//                CC_MO_L;
//            temp<<=1;
//            CC_SLK_L;
//            delay_nus(1);
//            CC_SLK_H;
//            delay_nus(1);
//        }
//    }
//    
    CC_CSn_H;
}

uint8_t  CC2500_ReadReg(uint8_t  Addr)
{
    uint8_t  data=0xff;
    CC_CSn_L;
    
   while(CC2500_MI&CC_MISO);
    //CC2500_SPI_Write(Addr+READ_SINGLE);
    SPI1_ReadWriteByte(Addr+READ_SINGLE);
    __NOP();
    __NOP();
    __NOP();
    //data = CC2500_SPI_RW(0xFF);
    data = SPI1_ReadWriteByte(0xFF);
    __NOP();
    __NOP();
    __NOP();
    CC_CSn_H;

    return data;
}

void CC2500_BurstRead(uint8_t  Addr,uint8_t  *pBuf,uint8_t  Len)
{
    uint8_t  i;
    CC_CSn_L;

    while(CC2500_MI);
    //CC2500_SPI_Write(Addr+READ_BURST);
    SPI1_ReadWriteByte(Addr+READ_BURST);
    __NOP();
    __NOP();
    __NOP();
    for(i=0;i<Len;i++)
    {
        //pBuf[i] = CC2500_SPI_RW(0xFF);
        pBuf[i] = SPI1_ReadWriteByte(0xFF);
    }

    CC_CSn_H;
}

void CC2500_WriteSettings(RF_SETTINGS *pRfSettings)
{
    CC2500_WriteByte(FSCTRL1,pRfSettings->sFSCTRL1);
    CC2500_WriteByte(FSCTRL0,pRfSettings->sFSCTRL0);
    CC2500_WriteByte(FREQ2,pRfSettings->sFREQ2);
    CC2500_WriteByte(FREQ1,pRfSettings->sFREQ1);
    CC2500_WriteByte(FREQ0,pRfSettings->sFREQ0);
    CC2500_WriteByte(MDMCFG4,pRfSettings->sMDMCFG4);
    CC2500_WriteByte(MDMCFG3,pRfSettings->sMDMCFG3);
    CC2500_WriteByte(MDMCFG2,pRfSettings->sMDMCFG2);
    CC2500_WriteByte(MDMCFG1,pRfSettings->sMDMCFG1);
    CC2500_WriteByte(MDMCFG0,pRfSettings->sMDMCFG0);
    CC2500_WriteByte(CHANNR,pRfSettings->sCHANNR);
    CC2500_WriteByte(DEVIATN,pRfSettings->sDEVIATN);
    CC2500_WriteByte(FREND1,pRfSettings->sFREND1);
    CC2500_WriteByte(FREND0,pRfSettings->sFREND0);
    CC2500_WriteByte(MCSM0,pRfSettings->sMCSM0);
    CC2500_WriteByte(FOCCFG,pRfSettings->sFOCCFG);
    CC2500_WriteByte(BSCFG,pRfSettings->sBSCFG);
    CC2500_WriteByte(AGCCTRL2,pRfSettings->sAGCCTRL2);
    CC2500_WriteByte(AGCCTRL1,pRfSettings->sAGCCTRL1);
    CC2500_WriteByte(AGCCTRL0,pRfSettings->sAGCCTRL0);
    CC2500_WriteByte(FSCAL3,pRfSettings->sFSCAL3);
    CC2500_WriteByte(FSCAL2,pRfSettings->sFSCAL2);
    CC2500_WriteByte(FSCAL1,pRfSettings->sFSCAL1);
    CC2500_WriteByte(FSCAL0,pRfSettings->sFSCAL0);
    CC2500_WriteByte(FSTEST,pRfSettings->sFSTEST);
    CC2500_WriteByte(TEST2,pRfSettings->sTEST2);
    CC2500_WriteByte(TEST1,pRfSettings->sTEST1);
    CC2500_WriteByte(TEST0,pRfSettings->sTEST0);    
    CC2500_WriteByte(IOCFG2,pRfSettings->sIOCFG2);
    CC2500_WriteByte(IOCFG0,pRfSettings->sIOCFG0);
    //CC2500_WriteByte(FIFOTHR,pRfSettings->sFIFOTHR);0x07
    //CC2500_WriteByte(SYNC1,pRfSettings->sSYNC1);0xD3
    //CC2500_WriteByte(SYNC0,pRfSettings->sSYNC0);0x91    
    CC2500_WriteByte(PKTCTRL1,pRfSettings->sPKTCTRL1); 
    CC2500_WriteByte(PKTCTRL0,pRfSettings->sPKTCTRL0);    
    CC2500_WriteByte(ADDR,pRfSettings->sADDR);
    CC2500_WriteByte(PKTLEN,pRfSettings->sPKTLEN);    
}

void CC2500_Disable_Interrupt(void)
{
    NVIC_DisableIRQ(EXTI9_5_IRQn);
}

void CC2500_Enable_Interrupt(void)
{
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}


void CC2500_SetPA(void)
{
    CC2500_BustWrite(PATABLE,paTable,1);
    //CC2500_WriteByte(PATABLE,0xFE);
}

void CC2500_WriteStrobe(uint8_t  Strobe)
{
    CC_CSn_L;
    
    while(CC2500_MI);
    //CC2500_SPI_Write(Strobe);
    SPI1_ReadWriteByte(Strobe);
    __NOP();
    
    CC_CSn_H;
}


void CC2500_ModeIdle(void)
{
    CC2500_WriteStrobe(SIDLE);
    delay_us(1000);
}

void CC2500_ModeRx(void)
{
    CC2500_WriteStrobe(SRX);
    delay_us(2000);
}

void CC2500_ModeTx(void)
{
    CC2500_WriteStrobe(STX);
    delay_us(1000);
}

void CC2500_ModePWRdown(void)
{
    CC2500_ModeIdle();
    delay_us(50);
    CC2500_WriteStrobe(SPWD);
    delay_us(50);
}

void CC2500_WaitTX_Done(void)
{
    while(!READ_GDO0());    //wait high--->transitting
    while(READ_GDO0());     //wait low---->finished
}

void CC2500_ClrRXFIFO(void)
{
    CC2500_ModeIdle();
    delay_us(50);
    CC2500_WriteStrobe(SFRX);
    delay_us(1);
}

void CC2500_ClrTXFIFO(void)
{
    CC2500_ModeIdle();
    delay_us(50);
    CC2500_WriteStrobe(SFTX);
    delay_us(1);
}

uint8_t  CC2500_ReadStatus(void)
{
    uint8_t  status;
    CC_CSn_L;
    while(CC2500_MI);
    status = SPI1_ReadWriteByte(SNOP);
    CC_CSn_H;
    return status;
}
uint8_t rxstate;
uint8_t rxdelay=0;
ErrorStatus CC2500_RevPacket(void)
{
    uint8_t  pktlen,ret;
    if(!READ_GDO0())
    {
        return ERROR;
    }
    else
    {
        rxdelay++;
        rxdelay++;
        rxdelay++;
        if(!READ_GDO0())
        {
            return ERROR;
        }
        else
        {
            while(READ_GDO0());
            delay_ms(1);//�ȴ�cc2500״̬��RX �� idle,�ڼ�����Ƶ��У׼
        }
    }
    Rs485_Config(1);
    delay_ms(1);
    printf("throught\r\n");
    ClearDataBuf(gCC2500RxBuf,MAXPACKETSIZE);
    CC2500_BurstRead(RXBYTES,&pktlen,1);
    //rxstate = CC2500_ReadStatus();
    if((pktlen&NUM_RXBYTES))
    {
        printf("get in\r\n");
        pktlen = CC2500_ReadReg(RXFIFO);
        gCC2500RxBuf[0] = pktlen;
        if(pktlen <= MAXPACKETSIZE)
        {
            CC2500_BurstRead(RXFIFO,gCC2500RxBuf+1,pktlen);
            
            rxstate = CC2500_ReadStatus();
            printf("state1=%x\r\n",rxstate);  
            CC2500_WriteStrobe(SFRX);  
            delay_us(100);            
            CC2500_ModeRx(); 
            rxstate = CC2500_ReadStatus();
            printf("state:%x\r\n",rxstate);
            printf("gCC2500RxBuf=%s\r\n",&gCC2500RxBuf[1]);
            Rs485_Config(0);
            ret = SUCCESS;
        }
        else
        {
            CC2500_WriteStrobe(SFRX);  
            delay_us(10); 
            rxstate = CC2500_ReadStatus();
            printf("state2=%x\r\n",rxstate);            
            CC2500_ModeRx(); 
            rxstate = CC2500_ReadStatus();
            printf("state:%x\r\n",rxstate);
            printf("gCC2500RxBuf=%s\r\n",&gCC2500RxBuf[1]);            
            ret = ERROR;
        }
        
    }
    else
    {
        CC2500_ClrRXFIFO();
            ret = ERROR;
    }    
    delay_ms(1);
    Rs485_Config(0);
    return ret;

}

void CC2500_SendPacket(uint8_t *buf,uint8_t len)
{
    memcpy((void*)&gCC2500TxBuf[1],buf,len);
    CC2500_BustWrite(TXFIFO,gCC2500TxBuf,len+1);
    CC2500_ModeTx();       //���뷢��ģʽ
    CC2500_WaitTX_Done();  //�������
    delay_us(1);           
    CC2500_ClrTXFIFO();   //�����ͻ��壬���������ģʽ
}
