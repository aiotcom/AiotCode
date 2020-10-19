#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "mp3.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-04-22
*
*	�汾�� 		V1.0
*
*	˵���� 		����ģ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

void RS485_HandlerCb(void);
unsigned char _Start[5] 	= {0x7E,0X03,0XAA,0XAD,0XEF};  	//��ʼ/��ͣ����
unsigned char _Cycle3[6] = {0x7E,0X04,0XAF,0X02,0XB5,0XEF};  //������Ŀѭ������
uint16_t Cmd_MP3[2];
int main(void)
{
    HAL_Init();             					//��ʼ��HAL��  
	Rs485_Init();							    //��ʼ��485
	UART1_Init(115200);						    //��ʼ������1
	UART2_Init(9600);						    //��ʼ������2
	TIM3_Init(10000-1,64-1,RS485_HandlerCb);	//��ʼ����ʱ���ж�����64M/64/10000/ = 100HZ
    
    USART3_Init(115200);
    printf("this usart3 print\r\n");
    HAL_Delay(3000);    
    HAL_Delay(1000);
	while(1)
	{
        if(Cmd_MP3[0])
        {            
            switch(Cmd_MP3[0])
            {
                case MP3_Start_Pause:
                    MP3_StopDisplay();
                    printf("pause\r\n");
                    break;
                case MP3_Last_Song:
                    MP3_NextItemDisplay();
                    printf("nexit item\r\n");
                    break;
                case MP3_Next_Song:
                    MP3_PreItemDisplay();
                    printf("lash item\r\n");
                    break;
                case MP3_Target:
                    MP3_DispalyTarget(Cmd_MP3[1]);
                    printf("item=%d\r\n",Cmd_MP3[1]);
                    break;
            }
            Cmd_MP3[0] = 0;
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
//	˵����		����ͨ��485���߷��͹�������������
//==========================================================
void RS485_HandlerCb(void)
{
    static uint8_t state = 0;
    if(state == 0)
    {
        Rs485_Send(Addr_MP3,Addr_UHF_RFID,Matrixkey_Get_value,0,(void*)0);
        state = 1;
    }
    else
    {
        if(!DataHandling_485(Addr_MP3))	//485���ݴ���
        {
            Cmd_MP3[0] = Rx_Stack.Command;
            Cmd_MP3[1] = Rx_Stack.Data[0];            
        }
        state = 0;
    }
}





