#include "Ble.h"	
#include "delay.h"
#include "Usart.h"

void Ble_Init(void)
{
	delay_ms(3000);												/*��ʱ�ȴ�*/		
	ble_send_cmd("AT+TXPW0\r\n","OK",2000);						/*���÷��书��4dBm*/
    HAL_Delay(100);
    ble_send_cmd("AT+ROLE0\r\n","OK",2000);						/*����Ϊ���豸*/   
    HAL_Delay(100);    
    ble_send_cmd("AT+MODE0\r\n","OK",2000);						/*����Ϊ���豸*/
	USART_AT_STA = 1;										    /*ATָ�����ɱ�־λ*/
}


