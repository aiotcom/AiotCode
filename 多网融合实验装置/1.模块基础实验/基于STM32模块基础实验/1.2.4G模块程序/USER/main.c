#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "string.h"
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "timer.h"
#include "main.h"
#include "24l01.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2019-03-18
*
*	�汾�� 		V1.2
*
*	˵���� 		2.4Gģ�����
*
*	�޸ļ�¼��
************************************************************
************************************************************
************************************************************
**/

#define NRF24L01_CH  0x50  //ȡֵ��Χ0~0x70
enum{
    NRF24L01_TX,//����ģʽ
    NRF24L01_RX //����ģʽ
};

uint8_t NRF24L01_MODE = NRF24L01_RX;//NRF24L01_TX->����ģʽ,NRF24L01_RX->����ģʽ
uint8_t NRF_TxBuffer[32]={"on"},NRF_RxBuffer[32];//NRF24L01 ÿ�η�������ֽ��� ��32���ֽ�

void Platform_RGB_LED_Init(void);
int main(void)
{
    uint8_t cmdsel=1;
    HAL_Init();             	    //��ʼ��HAL��  
	Rs485_Init();				    //��ʼ��485
	UART1_Init(115200);				//��ʼ������1
    USART3_Init(115200);            //printf ��ӡ��Ϣ��PB10->TX,PB11->RX,ͨ��ֻʹ�ã�TX����
    NRF24L01_Init(NRF24L01_CH);                //��ʼ��NRF24L01����оƬ
    Platform_RGB_LED_Init();        //��ʼ������RGB��
    if(NRF24L01_MODE == NRF24L01_RX){
        printf("���ǽ��Ͷ�\r\n");
    }
    else{
        printf("���Ƿ��Ͷ�\r\n");    
    }
    while(NRF24L01_Check())
    {//nrf24l01Ӳ��������ʾ����
        printf("nrf24l01 check  error\r\n");
        HAL_Delay(1000);
    }
    printf("nrf24l01 check  ok\r\n");
    
    if (NRF24L01_MODE == NRF24L01_TX) 
    { //����ģʽ   
        while(1)
        {
            NRF24L01_TX_Mode();
            if(NRF24L01_TxPacket(NRF_TxBuffer)==TX_OK)
            {//���ͳɹ�	

            }
            cmdsel = 1 - cmdsel;
            NRF_TxBuffer[0] = cmdsel?0x55:0xAA;
            HAL_Delay(500);	//ÿ500ms ����һ������
        }        
    }    
    
    if (NRF24L01_MODE == NRF24L01_RX) 
    {//����ģʽ
        NRF24L01_RX_Mode();
        while(1)
        {        
            if(NRF24L01_RxPacket(NRF_RxBuffer)==0)
            {//���յ�����
                if(NRF_RxBuffer[0] == 0x55)
                {
                    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4
                                            |GPIO_PIN_3
                                            |GPIO_PIN_15,GPIO_PIN_RESET/*����״̬ �����*/);//����RGB��
                }
                else if(NRF_RxBuffer[0] == 0xAA)
                {            
                    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4
                                            |GPIO_PIN_3
                                            |GPIO_PIN_15,GPIO_PIN_SET/*����״̬ �����*/);//�ر�RGB��
                }
            }
            HAL_Delay(5);	        
        }         
    }      
}
//==========================================================
//	�������ƣ�	void Platform_RGB_LED_Init(void)
//
//	�������ܣ�	��ʼ��������RGB��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================	
void Platform_RGB_LED_Init(void)
{    
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_AFIO_CLK_ENABLE();	
    __HAL_AFIO_REMAP_SWJ_NOJTAG(); //GPIO_PIN_3,GPIO_PIN_4 ΪJTAG�ܽŵĲ���
    
    __HAL_RCC_GPIOB_CLK_ENABLE();           	                
    __HAL_RCC_GPIOA_CLK_ENABLE();           	              

    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;  	                
    GPIO_Initure.Pull  = GPIO_PULLUP;          	                
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	 	       
    
    GPIO_Initure.Pin   = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_15; 	
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

    GPIO_Initure.Pin   = GPIO_PIN_15; 	                        	 	            
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_15,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15                      ,GPIO_PIN_SET);        
}


