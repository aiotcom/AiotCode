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
*	˵���� 		��ʪ�Ȳɼ�_��Զ�
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

#include <hal_joystick.h>
#include <hal_assert.h>
#include <hal_board.h>
#include <ioCC2530.h>
#include <hal_int.h>
#include <hal_lcd.h>
#include <hal_led.h>
#include "hal_button.h"
#include "util_lcd.h"
#include "basic_rf.h"
#include "hal_mcu.h"
#include "OLEDIIC.h"
#include "hal_rf.h"
#include "TM1640.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "Usart.h"	
#include "delay.h"
#include "SHT20.h"
#include "OLED.h"
#include "IIC.h"

#define NUMBER  360000

// Application parameters
#define RF_CHANNEL                25      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                0x2007
#define Coordinator_ADDR      0x2520
#define Coordinator_ADDR2     0x2521
#define SHT20_ADDR            0xBEEF

#define APP_PAYLOAD_LENGTH        30
#define LIGHT_TOGGLE_CMD          0

// Application states
#define IDLE                      0
#define SEND_CMD                  1

// Application role
#define NONE                      0
#define SWITCH                    1
#define LIGHT                     2
#define APP_MODES                 2

/***********************************************************************************
* LOCAL VARIABLES
*/
static uint8 pTxData[APP_PAYLOAD_LENGTH];
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;

// Mode menu
static menuItem_t pMenuItems[] =
{
#ifdef ASSY_EXP4618_CC2420
  // Using Softbaugh 7-seg display
  " L S    ", SWITCH,
  " LIGHT  ", LIGHT
#else
  // SRF04EB and SRF05EB
  "Switch",   SWITCH,
  "Light",    LIGHT
#endif
};

static menu_t pMenu =
{
  pMenuItems,
  N_ITEMS(pMenuItems)
};


#ifdef SECURITY_CCM
// Security key
static uint8 key[]= {
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
    0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
};
#endif

static void SHT20_Node(void);       //��ʪ�Ƚڵ�
static void Coordinator_Node(void); //Э�����ڵ�
static void Coordinator_Node2(void);//Э�����ڵ�2

//==========================================================
//	�������ƣ�	SHT20_Node()
//
//	�������ܣ�	��ʪ�Ƚڵ�
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void SHT20_Node(void)
{
    long int Number = NUMBER;

    IIC_Init();           //��ʼ��IIC 
    TM1640_Init();        //��ʼ��TM1640
  
#ifdef ASSY_EXP4618_CC2420
    halLcdClearLine(1);
    halLcdWriteSymbol(HAL_LCD_SYMBOL_RX, 1);
#endif

    // ���ñ�����ַ
    basicRfConfig.myAddr = SHT20_ADDR;

    if(basicRfInit(&basicRfConfig)==FAILED)
    {
      HAL_ASSERT(FALSE);
    }

    //�رս���
    basicRfReceiveOff();

    // Main loop
    while (TRUE)
    {
        SHT2x_GetTempHumi(); 	//��ȡ��ʪ��ֵ
        send_LED_Display(0xC0,(uint16_t)g_sht2x_param.TEMP_HM,1);   //��ʾ�¶�
        Number = NUMBER/2;
        while(Number--);
        send_LED_Display(0xC0,(uint16_t)g_sht2x_param.HUMI_HM,2);  //��ʾʪ��
        Number = NUMBER/2;
        while(Number--);

        sprintf((char *)pTxData,"Temp:%d,\tHumi:%d.\r\n",(uint16_t)g_sht2x_param.TEMP_HM,(uint16_t)g_sht2x_param.HUMI_HM);

        basicRfSendPacket(Coordinator_ADDR,pTxData,APP_PAYLOAD_LENGTH);  //������ʪ�����ݵ�Э�����ڵ�
        basicRfSendPacket(Coordinator_ADDR2,pTxData,APP_PAYLOAD_LENGTH); //������ʪ�����ݵ�Э�����ڵ�2

        memset(pTxData,0,APP_PAYLOAD_LENGTH);

        // �õ�Ƭ������˯��״̬���������ж�������
        halIntOff();
        halMcuSetLowPowerMode(HAL_MCU_LPM_3); 
        // interrupt enable
        halIntOn();
    }
}

//==========================================================
//	�������ƣ�	Coordinator_Node()
//
//	�������ܣ�	Э�����ڵ�
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void Coordinator_Node(void)
{
    uint8_t i = 0,Temp_Count = 0,Humi_Count = 0,Temp_Flag = 0,Humi_Flag = 0,Temp_Data[30],Humi_Data[30];
  
    OLED_IIC_Init();  //��ʼ��OLED��IIC
    OLED_Init();      //��ʼ��OLED��
    OLED_Init_UI();   //��ʼ����Ļ��ʾ
   
    // ���ñ�����ַ
    basicRfConfig.myAddr = Coordinator_ADDR;
    
    if(basicRfInit(&basicRfConfig)==FAILED) 
    {
      HAL_ASSERT(FALSE);
    }

    pTxData[0] = LIGHT_TOGGLE_CMD;

    //��������
    basicRfReceiveOn();

    //���������ѭ��
    while (TRUE)
    {
        if(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL)>0)  //���շ��͵��õ�ַ������
        {
          Temp_Count = 0,Humi_Count = 0,Temp_Flag = 0,Humi_Flag = 0;
          
          UR0SendString(pRxData); //�����ݷ��͵�������ʾ
          
          for(i=0;i<APP_PAYLOAD_LENGTH;i++)
          {
             //�¶�����
            if(pRxData[i] == ',')
              Temp_Flag = 2;
            
            if(Temp_Flag == 1)
            {
              Temp_Data[Temp_Count] = pRxData[i];
              Temp_Count++;
            }
            
            if(pRxData[i] == ':' && Temp_Flag == 0)
              Temp_Flag = 1;

            //ʪ������
            if(Temp_Flag == 2)
            {
              if(pRxData[i] == '.')
                Humi_Flag = 2;
              
              if(Humi_Flag == 1)
              {
                Humi_Data[Humi_Count] = pRxData[i];
                Humi_Count++;
              }
              
              if(pRxData[i] == ':')
                Humi_Flag = 1;
            }
          }

          Temp_Data[2] = '\0';Humi_Data[2] = '\0';
          OLED_P8x16Str(45,3,Temp_Data);
          OLED_P8x16Str(45,6,Humi_Data);
          memset(Temp_Data,'\0',30);
          memset(Humi_Data,'\0',30);
        }
    }
}

//==========================================================
//	�������ƣ�	Coordinator_Node2()
//
//	�������ܣ�	Э�����ڵ�2
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void Coordinator_Node2(void)
{
    uint8_t i = 0,Temp_Count = 0,Humi_Count = 0,Temp_Flag = 0,Humi_Flag = 0,Temp_Data[30],Humi_Data[30];

    OLED_IIC_Init();  //��ʼ��OLED��IIC
    OLED_Init();      //��ʼ��OLED��
    OLED_Init_UI();   //��ʼ����Ļ��ʾ
    OLED_P8x16Str(90,1,"2");

    // ���ñ�����ַ
    basicRfConfig.myAddr = Coordinator_ADDR2;
    
    if(basicRfInit(&basicRfConfig)==FAILED) 
    {
      HAL_ASSERT(FALSE);
    }

    pTxData[0] = LIGHT_TOGGLE_CMD;

    //��������
    basicRfReceiveOn();

    //���������ѭ��
    while (TRUE)
    {
        if(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL)>0)  //���շ��͵��õ�ַ������
        {
          Temp_Count = 0,Humi_Count = 0,Temp_Flag = 0,Humi_Flag = 0;
          
          UR0SendString(pRxData); //�����ݷ��͵�������ʾ
          
          for(i=0;i<APP_PAYLOAD_LENGTH;i++)
          {
             //�¶�����
            if(pRxData[i] == ',')
              Temp_Flag = 2;
            
            if(Temp_Flag == 1)
            {
              Temp_Data[Temp_Count] = pRxData[i];
              Temp_Count++;
            }
            
            if(pRxData[i] == ':' && Temp_Flag == 0)
              Temp_Flag = 1;

            //ʪ������
            if(Temp_Flag == 2)
            {
              if(pRxData[i] == '.')
                Humi_Flag = 2;
              
              if(Humi_Flag == 1)
              {
                Humi_Data[Humi_Count] = pRxData[i];
                Humi_Count++;
              }
              
              if(pRxData[i] == ':')
                Humi_Flag = 1;
            }
          }

          Temp_Data[2] = '\0';Humi_Data[2] = '\0';
          OLED_P8x16Str(45,3,Temp_Data);
          OLED_P8x16Str(45,6,Humi_Data);
          memset(Temp_Data,'\0',30);
          memset(Humi_Data,'\0',30);
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
void main(void)
{
    uint8 appMode = NONE; //������ģ���ģʽ
    
    Init_Uart0();         //��ʼ������0
    
    // Config basicRF
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
#ifdef SECURITY_CCM //��Կ��ȫͨ�ţ������̲�����
    basicRfConfig.securityKey = key; 
#endif

    // Initalise board peripherals ��ʼ����Χ�豸
    halBoardInit();
    halJoystickInit();

    // Initalise hal_rf Ӳ�������� rf ���г�ʼ��
    if(halRfInit()==FAILED)
    {
      HAL_ASSERT(FALSE);
    }

    /******ѡ�������س���Э�����ڵ����ʪ�Ƚڵ�******/

    SHT20_Node();       //��ʪ�Ƚڵ�
    //Coordinator_Node();   //Э�����ڵ�
    //Coordinator_Node2();  //Э�����ڵ�2

    HAL_ASSERT(FALSE);
}
