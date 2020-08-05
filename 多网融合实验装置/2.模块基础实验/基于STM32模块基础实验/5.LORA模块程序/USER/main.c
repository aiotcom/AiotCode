#include "stm32f1xx.h"
#include "string.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"
#include "LORA.h"
#include "led.h"

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
uint8_t IRQ_RegValue=0;

int main(void)
{
    uint8_t keystate = 0;
	uint8_t LedState = 1;
	uint8_t LoraRecvBuffer[50];
	uint32_t DelayProbe = 0;

	HAL_Init();    //��ʼ��HAL��    
	LORA_Init();   //��ʼ��LORAоƬ
	
	ModLed_Init(); //��ʼ��LORAģ���ϵ�LED�ƿ��ƹܽ�
	ModKey_Init(); //��ʼ��LORAģ���ϵİ����ܽ�
    version = SX1276ReadBuffer(REG_LR_VERSION);
    if(version == 0x12)
    {//���ģ�鰲�����ף���500ms
        MOD_LED_ON();
        HAL_Delay(500);
        MOD_LED_OFF();
        HAL_Delay(500);
    }
	while(1)
	{
		if((MOD_KEY_READ() == 0)&&(keystate == 0))//��������  
		{
			HAL_Delay(10); //��ʱ10ms��������
			if(MOD_KEY_READ() == 0)//��������
			{
                keystate = 1;
                Sx1278SendLong("toggle led",strlen("toggle led"));
			}
		}
        else if(MOD_KEY_READ() == 1)
        {
            keystate = 0;
        }
             
		if(PollDelay(&DelayProbe,100))//����������ݣ�ÿ���100ms��ѯһ��
		{
			IRQ_RegValue = SX1276ReadBuffer( REG_LR_IRQFLAGS );
			if((IRQ_RegValue)&&(IRQ_RegValue != 0XFF))//�� LORA�жϼĴ��� REG_LR_IRQFLAGS���ж��Ƿ����жϷ���
			{
				if(INT_FLG_RX_DONE == SX1278_InteruptHandler(LoraRecvBuffer))
				{//�ǽ����жϣ������յ����ݱ��浽LoraRecvBuffer��
					if(strstr((const char*)LoraRecvBuffer,(const char*)"toggle led"))
					{
						LedState?MOD_LED_ON():MOD_LED_OFF();
						LedState =  1-LedState;//�л��Ƶ�״̬
					}
				}
			}     
		}      
	}
}

