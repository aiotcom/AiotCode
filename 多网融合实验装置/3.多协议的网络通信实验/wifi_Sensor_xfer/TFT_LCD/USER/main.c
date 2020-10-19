#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "LCD.h"
#include "lcd.h"
#include "text.h"
#include "gui.h"
#include "protocol.h"
#include "TIMER.h"
#include "usart.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-03-18
*
*	�汾�� 		V1.0
*
*	˵���� 		LCD����
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/
extern void TIM3_Init(uint16_t arr,uint16_t psc,void (*cb)(void));
void Master_do_RS485Bus_Poll(void);
void RS485_HandlerCb(void);

struct _SHT20{
    uint8_t   temp;  //�¶�
    uint8_t   humi;  //ʪ��
    uint16_t  LightIntensity; //��ǿ
};
struct _SHT20 SensorData;

uint32_t SensorDataUpdateIntervalCounter=0;
uint32_t TouchIntervalCounter;
uint8_t  update = 1;
int main(void)
{
    
    HAL_Init();             	//��ʼ��HAL��
	LCD_Init();             	//��ʼ��LCD��ʾ���˿�
	Lcd_Init();								//��ʼ��LCD
	Rs485_Init();							//��ʼ��485
	UART1_Init(115200);				//��ʼ������һ
	UART2_Init(115200);				//��ʼ������һ		
    USART3_Init(115200);				//��ʼ������һ	
	LCD_Clear(WHITE);								//����
    TIM3_Init(10000-1,64-1,RS485_HandlerCb);	//��ʼ����ʱ���ж�����64M/64/10000/ = 100HZ
//	Touch_Init();
//	Touch_Adjust();  //��ĻУ׼ 
	POINT_COLOR = RED;
	GUI_DrawTempTitle(1,10);
    GUI_DrawHumiTitle(1,68);
    GUI_DrawLinghtIntensityTitle(1,126);
    
    printf("TFT_LCD:usart3 printf\r\n");
	while(1)
	{	
        if(update)
        {
            update = 0;
            GUI_DrawTempData(106-32,10,SensorData.temp);
            GUI_DrawHumiData(106-32,68,SensorData.humi);
            GUI_DrawLinghtIntensityData(106-32,126,SensorData.LightIntensity);            
        }
	}
}
//==========================================================
//	�������ƣ�	void RS485_HandlerCb(void)
//
//	�������ܣ�	ͨ��485���߻�ȡ���ݴ�����
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		��ʱ��3�жϣ��ص�������ÿ100ms����һ��
//==========================================================
void RS485_HandlerCb(void)
{  
    if(!DataHandling_485(Addr_LCD))
    {
        //Rs485_Send(Addr_SHT20,Addr_2_4G,SHT20_All,4,(uint8_t*)&SensorData);
        SensorData.temp = Rx_Stack.Data[0];
        SensorData.humi = Rx_Stack.Data[1];
        SensorData.LightIntensity = Rx_Stack.Data[2] + (Rx_Stack.Data[3]<<8);
        update = 1;
    }     
}



