#include "Noncontact_Temp.h"
#include "Rs485.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"

/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2020-03-11
*
*	�汾�� 		V1.0
*
*	˵���� 		STM32F767-�ǽӴ��¶�ģ��
*
*	�޸ļ�¼��
************************************************************
************************************************************
************************************************************
**/

int main(void)
{
  unsigned char SlaveAddress;	//Contains device address
  unsigned char	command;	  	//Contains the access command
  unsigned int 	data;		  		//Contains data value	
	float temp;
  SlaveAddress=SA<<1;					//Set device address
  command=RAM_Access|RAM_To; 	   

  HAL_Init();             		//��ʼ��HAL��
	Rs485_Init();								//��ʼ��485
	UART7_Init(115200);					//��ʼ��������
	mlx_gpio_init();						//��ʼ���ǽӴ��¶ȴ�����

	while(1)
	{
		data=MemRead(SlaveAddress,command); //Read memory
		temp=CalcTemp(data);
		//sprintf((char *)buf," tmp:%0.2f      ",temp);

		RS485_TX_EN();		//����485����
		Rs485_delay_ms(5);
		printf("tmp:%0.2f\r\n",temp);
		Rs485_delay_ms(5);
		RS485_RX_EN();		//����485����
		
		delay_ms(1000);	
	}
}







