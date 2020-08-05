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
*	˵���� 		ʵ�������
*                       ��һ���� �ҵ��������ݣ���appLight();  ע�͵������ص�����ģ�顣
*                          appSwitch();         //�ڵ�Ϊ����
*                       // appLight();          //�ڵ�ΪLEDָʾ��
*
*                       �ڶ������ҵ���ͬλ�ã���ΰ�appSwitch();ע�͵������ص�����ģ�顣 
*                       //appSwitch();          //�ڵ�Ϊ����
*                       appLight();             //�ڵ�ΪLEDָʾ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
#include <hal_lcd.h>
#include <hal_led.h>
#include <hal_joystick.h>
#include <hal_assert.h>
#include <hal_board.h>
#include <ioCC2530.h>
#include <hal_int.h>
#include "hal_mcu.h"
#include "hal_button.h"
#include "hal_rf.h"
#include "util_lcd.h"
#include "basic_rf.h"
#include "stdlib.h"
#include "string.h"
#include "delay.h"
#include "stdio.h"
#include "KEY.h"
#include "LED.h"

#define RF_CHANNEL                25      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                0x2007
#define SWITCH_ADDR           0x2520
#define LIGHT_ADDR            0xBEEF

#define APP_PAYLOAD_LENGTH        2
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

static void appLight();
static void appSwitch();
static uint8 appSelectMode(void);

//==========================================================
//	�������ƣ�	appLight()
//
//	�������ܣ�	���ݽ��պ�������������ģ�鷢�͵�����
//
//	��ڲ�����	@ PARAM BaseCfFiFig--�ļ���Χ������������Ƶ��������
//                        RX���ݻ�����ָ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void appLight()
{

#ifdef ASSY_EXP4618_CC2420
    halLcdClearLine(1);
    halLcdWriteSymbol(HAL_LCD_SYMBOL_RX, 1);
#endif
        
    basicRfConfig.myAddr = LIGHT_ADDR;  // ���ñ�����ַ
    
    if(basicRfInit(&basicRfConfig)==FAILED) 
    {
      HAL_ASSERT(FALSE);
    }

    //����RF����
    basicRfReceiveOn();
    
    //��ʼ��LED��
    LED1_SET();LED2_SET();LED3_SET();LED4_SET(); 

    // Main loop
    while (TRUE)
    {
        while(!basicRfPacketIsReady());   //��������

        if(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL)>0)  //���շ��͵��õ�ַ������
        {
            switch(pRxData[0])
            {
              case S1_PRES:  //����1
                MCU_IO_TGL_PREP(0,2);
                break;
              case S2_PRES:  //����2
                MCU_IO_TGL_PREP(0,3);
                break;
              case S3_PRES:  //����3
                MCU_IO_TGL_PREP(1,6);
                break;
              case S4_PRES:  //����4
                MCU_IO_TGL_PREP(1,7);
                break;
              default: break;
            }
            pRxData[0] = 0;
        }
    }
}

//==========================================================
//	�������ƣ�	appSwitch()
//
//	�������ܣ�	���ݷ��ͺ�����������������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void appSwitch()
{

#ifdef ASSY_EXP4618_CC2420
    halLcdClearLine(1);
    halLcdWriteSymbol(HAL_LCD_SYMBOL_TX, 1);
#endif

    KEY_Init();   //��ʼ������
    
    // ���÷��͵�ַ
    basicRfConfig.myAddr = SWITCH_ADDR;
    
    if(basicRfInit(&basicRfConfig)==FAILED) 
    {
      HAL_ASSERT(FALSE);
    }

    pTxData[0] = LIGHT_TOGGLE_CMD;

    //����������
    basicRfReceiveOff();

    //���������ѭ��
    while (TRUE)
    {
        pTxData[0] = KEY_Scan(0);

        switch(pTxData[0])
        {
          case S1_PRES:  //����1
            MCU_IO_TGL_PREP(0,2);
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH); //��������
            break;
          case S2_PRES:  //����2
            MCU_IO_TGL_PREP(0,3);
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH); //��������
            break;
          case S3_PRES:  //����3
            MCU_IO_TGL_PREP(1,6);
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH); //��������
            break;
          case S4_PRES:  //����4
            MCU_IO_TGL_PREP(1,7);
            basicRfSendPacket(LIGHT_ADDR, pTxData, APP_PAYLOAD_LENGTH); //��������
            break;
          default: break;
        }
        
        delay_ms(100);

        // �õ�Ƭ������˯��״̬���������ж�������
        halIntOff();
        halMcuSetLowPowerMode(HAL_MCU_LPM_3); 
        // interrupt enable
        halIntOn(); 
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

    LED_Init();   //��ʼ��LED��
    
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
    
    /******ѡ�������س��򣬷���ģ��ͽ���ģ��******/
      //appSwitch();        //�ڵ�Ϊ����
      appLight();         //�ڵ�Ϊָʾ��LED
     
   // Role is undefined. This code should not be reached
    HAL_ASSERT(FALSE);
}

/****************************************************************************************
* @fn          appSelectMode
*
* @brief       Select application mode
*
* @param       none
*
* @return      uint8 - Application mode chosen
*/
static uint8 appSelectMode(void)
{
    halLcdWriteLine(1, "Device Mode: ");

    return utilMenuSelect(&pMenu);
}
