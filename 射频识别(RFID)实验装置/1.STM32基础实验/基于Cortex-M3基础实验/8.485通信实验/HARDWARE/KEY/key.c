#include "led.h"
#include "key.h"
#include "Rs485.h"
#include "delay.h"
#include "usart.h"

//==========================================================
//	�������ƣ�	KEY_Init()
//
//	�������ܣ�	������ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           //����GPIOAʱ��
		__HAL_RCC_GPIOB_CLK_ENABLE();           //����GPIOBʱ��
    
    GPIO_Initure.Pin=S1_PIN|S2_PIN;
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;        	//����
    GPIO_Initure.Speed=GPIO_SPEED_LOW;     	//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
	
    GPIO_Initure.Pin=S3_PIN|S4_PIN;
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;        	//����
    GPIO_Initure.Speed=GPIO_SPEED_LOW;     	//����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

//==========================================================
//	�������ƣ�	KEY_Scan()
//
//	�������ܣ�	����������
//
//	��ڲ�����	mode:	0,��֧��������;
//										1,֧��������;
//
//	���ز�����	���ذ���ֵ
//										0��û���κΰ�������
//										1��2��3��Ӧ��Ӧ�İ���
//	˵����			ע��˺�������Ӧ���ȼ�,KEY1>KEY2>KEY3!!
//==========================================================
uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t key_up=1;     	//�����ɿ���־
    if(mode==1)key_up=1;    			//֧������
    if(key_up&&(S1_Read()==0||S2_Read()==0||S3_Read()==0||S4_Read()==0))
    {
        delay_ms(10);
        key_up=0;
        if(S1_Read()==0)       return S1_PRES;
        else if(S2_Read()==0)  return S2_PRES;
        else if(S3_Read()==0)  return S3_PRES;  
				else if(S4_Read()==0)  return S4_PRES;
    }else if(S1_Read()==1&&S2_Read()==1&&S3_Read()==1&&S4_Read()==1)key_up=1;
		
    return 0;   //�ް�������
}

//==========================================================
//	�������ƣ�	key_Operatio()
//
//	�������ܣ�	��������-����LED������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void key_Operatio(void)
{
	static uint8_t key = 0;
	
	key = KEY_Scan(0);//��ȡ����
	
	switch(key)
	{
		case 1:
			Command_LED[0] = ~Command_LED[0];				//LED��������
			HAL_GPIO_TogglePin(LED_PORT,LED1_PIN);	//��תLED1��ƽ
			break;
		case 2:
			Command_LED[1] = ~Command_LED[1];				//LED��������
			HAL_GPIO_TogglePin(LED_PORT,LED2_PIN);	//��תLED2��ƽ
			break;
		case 3:
			Command_LED[2] = ~Command_LED[2];				//LED��������
			HAL_GPIO_TogglePin(LED_PORT,LED3_PIN);	//��תLED3��ƽ
			break;
		case 4:
			Command_LED[3] = ~Command_LED[3];				//LED��������
			HAL_GPIO_TogglePin(LED_PORT,LED4_PIN);	//��תLED4��ƽ
			break;
		default:break;
	}
	if(key)
		Rs485_Send(Addr_LED,Addr_LED,LED_Control,4,Command_LED);
}




