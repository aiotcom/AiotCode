#include "WiFi.h"
#include "delay.h"
#include "Usart.h"
#include "WS2812b.h"
uint8_t WiFi_AT_STA = 0;
uint8_t* WiFi_Send_Cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime);	//��WiFi��������
/**
  * @brief  WIFI����ONE.NETƽ̨ATָ��
  * @param  void
  * @retval void
  **/
void WiFi_Init()
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��

    GPIO_Initure.Pin   = GPIO_PIN_5;   //GPIO_PIN_4:WIFIģ�鸴λ���ƹܽţ�GPIO_PIN_6:WS2812B�ʵƿ��ƹܽš�
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP;	//�������
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; //����
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);
    
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);//��ʼ��ƽ��Ϊ��
    
    //(�������д���)���2����ĵ͵�ƽ�źŸ�λWIFIģ��
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);
    HAL_Delay(2);//��ʱ2����
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
    
    HAL_Delay(2000);//��ʱ2000���룬��WIFIģ�鸴λ��������ӡ����࿪����Ϣ����ʱ����ܿ���
    
    
    while(!WiFi_Send_Cmd(AT,(uint8_t*)"OK",20));				    /*����AT����ģʽ*/
    WS2812B_SetColour(0x000055);                                    //��ɫ��ʾ
    
    while(!WiFi_Send_Cmd(CWMODE,(uint8_t*)"OK",30));				/*����ģ��Ӧ��ģʽ*/

    while(!WiFi_Send_Cmd(CWJAP,(uint8_t*)"OK",300));				/*����Ҫ���ӵ�·������SSID������*/   
    WS2812B_SetColour(0x005500);                                    //��ɫ��ʾ    
    
    
    while(!WiFi_Send_Cmd(TCP_CIPSTART,(uint8_t*)"OK",60));	/*�����������TCP����*/
    WS2812B_SetColour(0x550000);                                    //��ɫ��ʾ
    
    while(!WiFi_Send_Cmd(CIPMODE,(uint8_t*)"OK",60));				/*͸��ģʽ*/

    while(!WiFi_Send_Cmd(CIPSEND,(uint8_t*)"OK",30));				/*��ʼ����*/

    while(!WiFi_Send_Cmd(CIPSTATUS,(uint8_t*)"",30));				/*�����豸*/

    WiFi_AT_STA = 1;           										/*ATָ�����ɱ�־λ*/
}

//==========================================================
//	�������ƣ�	WiFi_Send_Cmd()
//
//	�������ܣ�	��WiFi��������
//
//	��ڲ�����	waittime:�ȴ�ʱ��(��λ:ms)
//							cmd:���͵������ַ���
//							ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//
//	���ز�����	
//						����ֵ:	��0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       							0,����ʧ��
//
//	˵����		
//==========================================================
uint8_t* WiFi_Send_Cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime)
{
	static uint8_t len = 0;							//������ݳ���
	static uint16_t j = 0;
	char *strx=0;

	len = strlen((char *)cmd);					//��ȡ���ݳ���

	memset((void*)USART2_RX_BUF,0,USART2_REC_LEN);	//�������
	HAL_UART_Transmit(&UART2_Handler,cmd,len,1000);	//����2��������
	
	for(j=0;j<waittime;j++)
	{
		delay_ms(50);
		strx=strstr((const char*)USART2_RX_BUF,(const char*)ack);
		if(strx)
			break;
	}
    
	USART2_RX_STA=0;
	return (uint8_t*)strx;
}


