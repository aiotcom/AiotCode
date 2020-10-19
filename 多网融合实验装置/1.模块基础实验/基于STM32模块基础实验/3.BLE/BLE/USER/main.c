#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "timer.h"
#include "delay.h"
#include "Usart.h"
#include "Rs485.h"
#include "Ble.h"
#include "stdio.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2018-01-01
*
*	�汾�� 		V1.0
*
*	˵���� 		�����⺯������ʵ��-HAL��汾
*
*	�޸ļ�¼��
97 7B F3 62 C4 84
************************************************************
************************************************************
************************************************************
**/


int main(void)
{ 
    uint8_t ledstete = 0;
    HAL_Init();             					//��ʼ��HAL��  
    USART3_Init(115200);
    printf("this is usart3 print\r\n");    
	UART2_Init(9600);							//��ʼ������2
	Rs485_Init();   							//��ʼ��485
	TIM3_Init(1000-1 ,64-1);						//��ʼ����ʱ��3
	Ble_Init();									//��ʼ������
    
    USART2_RX_STA = 0;
    while(!(strstr((const char*)USART2_RX_BUF,(const char*)"Connected")));//����ģ����������ӣ������ַ� Connected
    printf("connected\r\n");
	while(1)
	{
        if(USART2_RX_STA)
        {//�������           
            HAL_Delay(50);//��ʱһ��ȴ��������
            
            if(strstr((const char*)USART2_RX_BUF,(const char*)"blue"))
            {
                 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_RESET);
                 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_SET);
                 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
            }

            if(strstr((const char*)USART2_RX_BUF,(const char*)"red"))
            {
                 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 ,GPIO_PIN_SET);
                 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_RESET);
                 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);                
            }            
            USART2_RX_STA=0;
            memset((void*)USART2_RX_BUF,0,USART1_REC_LEN);
         
        }//if(USART2_RX_STA&UART_RX_DONE_MASK)        
	}
}

