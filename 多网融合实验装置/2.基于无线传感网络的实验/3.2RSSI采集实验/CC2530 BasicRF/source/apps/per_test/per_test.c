/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-12-27
*
*	�汾�� 		V2.0
*
*	˵���� 		RSSI�ɼ�ʵ��
*                       #define MODE_SEND    //����ʱ��appReceiver            
*                                            //������ʱ��appTransmitter 
*                       ��¼���򵽵���1�����κ���¼���򵽵���2     
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_int.h"
#include "hal_timer_32k.h"
#include "hal_joystick.h"
#include "hal_button.h"
#include "hal_board.h"
#include "hal_rf.h"
#include "hal_assert.h"
#include "util_lcd.h"
#include "basic_rf.h"
#include "per_test.h"
#include "string.h"
#include "delay.h"
#include "OLED.h"
#include "IIC.h"

#define IDLE                      0
#define TRANSMIT_PACKET           1

/*****************************important select or shelt***********************************/
//#define MODE_SEND              //����ʱ��  appReceiver
                                 //������ʱ��appTransmitter
/*******************************************************************************/

static basicRfCfg_t basicRfConfig;
static perTestPacket_t txPacket;
static perTestPacket_t rxPacket;
static volatile uint8 appState;
static volatile uint8 appStarted;

static void appTimerISR(void);
//static void appStartStop(void);
static void appTransmitter();
static void appReceiver();
void initUART(void);
void UartTX_Send_String(int8 *Data,int len);

/****************************************************************
���ڳ�ʼ������
****************************************************************/
void initUART(void)
{
    PERCFG = 0x00;		      //λ��1 P0��
    P0SEL = 0x0c;		      //P0_2,P0_3�������ڣ��ⲿ�豸���ܣ�
    P2DIR &= ~0XC0;                   //P0������ΪUART0

    U0CSR |= 0x80;		      //����ΪUART��ʽ
    U0GCR |= 11;				       
    U0BAUD |= 216;		      //��������Ϊ115200
    UTX0IF = 0;                       //UART0 TX�жϱ�־��ʼ��λ0
}
/****************************************************************
���ڷ����ַ�������			
****************************************************************/
void UartTX_Send_String(int8 *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}

/***********************************************************************************
* @fn          appTimerISR
*
* @brief       32KHz timer interrupt service routine. Signals PER test transmitter
*              application to transmit a packet by setting application state.
*
* @param       none
*
* @return      none
*/
static void appTimerISR(void)
{
    appState = TRANSMIT_PACKET;
}

//==========================================================
//	�������ƣ�	appStartStop()
//
//	�������ܣ�	��ʼ�ͽ���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
//static void appStartStop(void)
//{
//    appStarted ^= 1;
//
//    if(appStarted) {
//        halTimer32kIntEnable();
//    }
//    else {
//        halTimer32kIntDisable();
//    }
//}


/***********************************************************************************
* @fn          appConfigTimer
*
* @brief       Configure timer interrupts for application. Uses 32KHz timer
*
* @param       uint16 rate - Frequency of timer interrupt. This value must be
*              between 1 and 32768 Hz
*
* @return      none
*/
static void appConfigTimer(uint16 rate)
{
    halTimer32kInit(TIMER_32K_CLK_FREQ/rate);
    halTimer32kIntConnect(&appTimerISR);
}

//==========================================================
//	�������ƣ�	appReceiver()
//
//	�������ܣ�	���պ����������յ������ݽ������͵�PC��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void appReceiver()
{
  uint32 segNumber=0;                              // ���ݰ����к� 
  int16 perRssiBuf[RSSI_AVG_WINDOW_SIZE] = {0};    // Ring buffer for RSSI �洢RSSI�Ļ��λ�����
  uint8 perRssiBufCounter = 0;                     // Counter to keep track of the ����������RSSI������ͳ��

  perRxStats_t rxStats = {0,0,0,0};      
   int16 rssi;
  uint8 resetStats=FALSE;
  
  int8 Myper[6];        
  int8 Myrssi[3];
  int8 Myreceive[5];
  int32 temp_per;           //��ŵ�����
  int32 temp_receive;       //��Ž��յİ��ĸ���
  int32 temp_rssi;          //���ǰ32��rssiֵ��ƽ��ֵ
  initUART();               // ��ʼ������
  
#ifdef INCLUDE_PA
  uint8 gain;

  gain =appSelectGain();
  halRfSetGain(gain);
#endif
    
   //��ʼ��Basic RF 
  basicRfConfig.myAddr = RX_ADDR;
  if(basicRfInit(&basicRfConfig)==FAILED) 
  {
    HAL_ASSERT(FALSE);
  }
  basicRfReceiveOn();
  OLED_CLS();     //����

  /* ��ѭ�� */
  UartTX_Send_String("PER_test: ",strlen("PER_test: "));

  OLED_P16x16Ch(1,2,5);   //��
  OLED_P16x16Ch(15,2,6);  //��
  OLED_P16x16Ch(30,2,7);  //��
  OLED_P16x16Ch(45,2,8);  //��
  OLED_P16x16Ch(60,2,5);  //��
  OLED_P8x16Str(75,2,":");
  
  OLED_P16x16Ch(1,4,9);    //��
  OLED_P16x16Ch(30,4,7);   //��
  OLED_P16x16Ch(60,4,10);  //��
  OLED_P8x16Str(75,4,":");
  
  OLED_P8x16Str(1,6,"RSSI");
  OLED_P16x16Ch(30,6,11);  //ƽ
  OLED_P16x16Ch(45,6,12);  //��
  OLED_P16x16Ch(60,6,13);  //ֵ
  OLED_P8x16Str(75,6,":");
  while (TRUE)
  {
    while(!basicRfPacketIsReady());     // �ȴ��µ����ݰ�
    if(basicRfReceive((uint8*)&rxPacket, MAX_PAYLOAD_LENGTH, &rssi)>0) {
         halLedSet(3);//P1_4
			
      UINT32_NTOH(rxPacket.seqNumber);  // �ı������ŵ��ֽ�˳��
      segNumber = rxPacket.seqNumber;
            
     // ��ͳ�Ʊ���λ�����������յ������ݰ����Ϊ�Ѿ��յ������ݰ����     
      if(resetStats)
      {
        rxStats.expectedSeqNum = segNumber;
        
        resetStats=FALSE;
      }      

      rxStats.rssiSum -= perRssiBuf[perRssiBufCounter];   // ��sum�м�ȥ�ɵ�RSSIֵ

      perRssiBuf[perRssiBufCounter] =  rssi;              // �洢�µ�RSSIֵ�����λ�������֮������������sum

      rxStats.rssiSum += perRssiBuf[perRssiBufCounter];   // �����µ�RSSIֵ��sum
      if(++perRssiBufCounter == RSSI_AVG_WINDOW_SIZE) {
        perRssiBufCounter = 0;    
      }

      
     // �����յ������ݰ��Ƿ����������յ������ݰ�
      if(rxStats.expectedSeqNum == segNumber)  // ���������յ������ݰ� 
      {
        rxStats.expectedSeqNum++;  
      }
      

      else if(rxStats.expectedSeqNum < segNumber)  // �����������յ������ݰ������������յ������ݰ�����ţ�
      {                                            // ��Ϊ����
        rxStats.lostPkts += segNumber - rxStats.expectedSeqNum;
        rxStats.expectedSeqNum = segNumber + 1;
      }
      
      else  // (С�������յ������ݰ�����ţ�
      {      
        //�µĲ��Կ�ʼ����λͳ�Ʊ���
        rxStats.expectedSeqNum = segNumber + 1;
        rxStats.rcvdPkts = 0;
        rxStats.lostPkts = 0;
      }
      rxStats.rcvdPkts++;
      
           // reset statistics if button 1 is pressed
            temp_receive=(int32)rxStats.rcvdPkts;
            if(temp_receive>=1000)
            {
               if(halButtonPushed()==HAL_BUTTON_1)
               {
                   resetStats = TRUE;
                   rxStats.rcvdPkts = 1;
                   rxStats.lostPkts = 0;
               }
               rxStats.rcvdPkts = 1;
            }

            Myreceive[0]=temp_receive/100+'0';
            Myreceive[1]=temp_receive%100/10+'0';
            Myreceive[2]=temp_receive%10+'0';
            Myreceive[3]='\0';
            UartTX_Send_String("RECE:",strlen("RECE:"));
            UartTX_Send_String(Myreceive,4);
            UartTX_Send_String("    ",strlen("    "));   
            
            temp_per = (int32)((rxStats.lostPkts*1000)/(rxStats.lostPkts+rxStats.rcvdPkts));
            Myper[0]=temp_per/100+'0';
            Myper[1]=temp_per%100/10+'0'; 
            Myper[2]='.';
            Myper[3]=temp_per%10+'0';
            Myper[4]='%';
            Myper[5]='\0';
            UartTX_Send_String("PER:",strlen("PER:"));
            UartTX_Send_String(Myper,5);
            UartTX_Send_String("    ",strlen("    "));
           
            temp_rssi=(0-(int32)rxStats.rssiSum/32);
            Myrssi[0]=temp_rssi/10+'0';
            Myrssi[1]=temp_rssi%10+'0';
            Myrssi[2]='\0';
            UartTX_Send_String("RSSI:-",strlen("RSSI:-"));
            UartTX_Send_String(Myrssi,2);        
            UartTX_Send_String("\n",strlen("\n"));
            
            halLedClear(3);
            
            OLED_P8x16Str(107,2," ");                     //���ݰ�����   
            OLED_P8x16Str(83,2,(uint8_t *)Myreceive);     //���ݰ�����
            
            OLED_P8x16Str(83,4,(uint8_t *)Myper);         //�����
            
            OLED_P8x16Str(98,6,"   ");                    //RSSIƽ��ֵ
            OLED_P8x16Str(83,6,(uint8_t *)Myrssi);        //RSSIƽ��ֵ
            
            halMcuWaitMs(300);
    }                  
  }
}

//==========================================================
//	�������ƣ�	appTransmitter()
//
//	�������ܣ�	���ͺ���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void appTransmitter()
{
  uint32 burstSize=0;
  uint32 pktsSent=0;
  //uint8 appTxPower;
  uint8 n;
  
  /* ��ʼ��Basic RF */
  basicRfConfig.myAddr = TX_ADDR;
  if(basicRfInit(&basicRfConfig)==FAILED)
  {
    HAL_ASSERT(FALSE);
  }

   /* ����������� */
  halRfSetTxPower(2);

  /* ���ý���һ�β��������͵����ݰ����� */
  burstSize = 1000;

  basicRfReceiveOff();

   /* ���ö�ʱ����IO *************************/
  appConfigTimer(0xC8);

  /* ��ʼ�����ݰ��غ� */
  txPacket.seqNumber = 0;
  for(n = 0; n < sizeof(txPacket.padding); n++) 
  {
    txPacket.padding[n] = n;
  }
  
   /* ��ѭ�� */
  while (TRUE)
  {
   // �ȴ��û�����Ӧ��  

    while(appStarted)
      {

      if (pktsSent < burstSize) 
      {
          UINT32_HTON(txPacket.seqNumber);  // �ı䷢����ŵ��ֽ�˳��
          basicRfSendPacket(RX_ADDR, (uint8*)&txPacket, PACKET_SIZE);

          /* ���������ǰ���ֽ�˳��Ļ�Ϊ����˳�� */
          UINT32_NTOH(txPacket.seqNumber);
          txPacket.seqNumber++;

          pktsSent++;

          appState = IDLE;
          halLedToggle(1);   //�ı�LED1������״̬
          halMcuWaitMs(500);
      }
      else
        appStarted = !appStarted;
      
      /* ��λͳ�ƺ���� */
     pktsSent = 0;

    }
  }
}

//==========================================================
//	�������ƣ�	main()
//
//	�������ܣ�	������ں���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void main (void)
{
    uint8 appMode;

    IIC_Init();       //IIC��ʼ��
    OLED_Init();      //��ʼ��OLED
	
    OLED_Init_UI();
    
    appState = IDLE;
    appStarted = TRUE;
	
    // ���� Basic RF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.ackRequest = FALSE;

    // ��ʼ����ΧӲ��
    halBoardInit();

    // ��ʼ�� hal_rf
    if(halRfInit()==FAILED) {
      HAL_ASSERT(FALSE);
    }
    
    // Indicate that device is powered
    halLedSet(1);

    // Print Logo and splash screen on LCD
    utilPrintLogo("PER Tester");

    halMcuWaitMs(350);

    //�����ŵ����淶Ҫ���ŵ�ֻ��ΪΪ 11����25������ѡ���ŵ� 11
    basicRfConfig.channel = 0x0B;

    
    //����ģ���ģʽ��һ����Ϊ���䣬��һ��Ϊ���գ����Ƿ� define MODE_SEND
    #ifdef MODE_SEND
     appMode = MODE_TX;
    #else
     appMode = MODE_RX;
    #endif  
    // Transmitter application
    if(appMode == MODE_TX) {
        // ��� define MODE_SEND ����� appTransmitter();
        appTransmitter(); //����ģʽ
    }
    // ���û�� define MODE_SEND ����� appReceiver ();
    else if(appMode == MODE_RX) {      
        appReceiver(); //����ģʽ
    }
    // Role is undefined. This code should not be reached
    HAL_ASSERT(FALSE);
}

