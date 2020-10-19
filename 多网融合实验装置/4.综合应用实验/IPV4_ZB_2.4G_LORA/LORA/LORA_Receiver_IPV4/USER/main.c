#include "stm32f1xx.h"
#include "string.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"
#include "LORA.h"
#include "led.h"
#include "TIMER.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-01-01
*
*	�汾�� 		V1.0
*
*	˵���� 		LORAģ��
*
*	�޸ļ�¼��	
************************************************************
************************************************************
************************************************************
**/

/*
	LORAģ���ϵİ�����ʼ��
*/
#define MOD_KEY_READ() (HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)?1:0)


void ModKey_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOBʱ��
	
    GPIO_Initure.Pin   = GPIO_PIN_2;
    GPIO_Initure.Mode  = GPIO_MODE_INPUT;  	//�������
    GPIO_Initure.Pull  = GPIO_PULLUP;       //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;   //����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);    
}

/*
LORAģ���ϵ�LED��ʼ��
*/
#define MOD_LED_ON()    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)
#define MOD_LED_OFF()    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)

void ModLed_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           		//����GPIOBʱ��

    GPIO_Initure.Pin   = GPIO_PIN_3;
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull  = GPIO_PULLUP;          	//����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	 	//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);    

    MOD_LED_OFF();
}

uint8_t version;
uint8_t IRQ_RegValue=0,TxLen=0;
uint8_t LoraRecvBuffer[32],UpdataFlg=0,TxBuffer[32];
void RS485_HandlerCb(void);
#define RF_Frequency 433 //��Χ 410~525(��λM)
int main(void)
{
	uint8_t LedState = 1;

	HAL_Init();    //��ʼ��HAL��    
	LORA_Init(RF_Frequency);   //��ʼ��LORAоƬ

	Rs485_Init();				    //��ʼ��485
    TIM3_Init(10000-1,64-1,RS485_HandlerCb);//�ж�Ƶ��64M/640/10000=10HZ���ж�Ƶ��100HZ
	UART1_Init(115200);				//��ʼ������1
    USART3_Init(115200);            //printf ��ӡ��Ϣ��PB10->TX,PB11->RX,ͨ��ֻʹ�ã�TX����
	
	ModLed_Init(); //��ʼ��LORAģ���ϵ�LED�ƿ��ƹܽ�
	ModKey_Init(); //��ʼ��LORAģ���ϵİ����ܽ�
    version = SX1276ReadBuffer(REG_LR_VERSION);
    if(version == 0x12)
    {//���ģ�鰲�����ף���500ms
        MOD_LED_ON();
        HAL_Delay(500);
        MOD_LED_OFF();
    }
	while(1)
	{
        IRQ_RegValue = SX1276ReadBuffer( REG_LR_IRQFLAGS );
        if((IRQ_RegValue)&&(IRQ_RegValue != 0XFF))//�� LORA�жϼĴ��� REG_LR_IRQFLAGS���ж��Ƿ����жϷ���
        {
            if(INT_FLG_RX_DONE == SX1278_InteruptHandler(LoraRecvBuffer))
            {//�ǽ����жϣ������յ����ݱ��浽LoraRecvBuffer��
                TxLen = LoraRecvBuffer[0];
                memcpy((void*)TxBuffer,(const void*)&LoraRecvBuffer[1],LoraRecvBuffer[0]);
                printf("%s\r\n",TxBuffer); //������Ϣ               
            }
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
    if((!DataHandling_485(Addr_LORA))&&(Rx_Stack.Command == SHT20_Get_All))
    {
        if(TxLen)
        {            
            Rs485_Send(Addr_LORA,Addr_IPV4,SHT20_All,TxLen,TxBuffer);
            TxLen = 0;
        }
    }
}
