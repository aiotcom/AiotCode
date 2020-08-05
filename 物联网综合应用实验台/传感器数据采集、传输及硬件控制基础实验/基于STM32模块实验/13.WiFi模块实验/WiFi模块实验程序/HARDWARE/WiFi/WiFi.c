#include "WiFi.h"
#include "delay.h"
#include "Usart.h"

uint8_t WiFi_AT_STA = 0;

//==========================================================
//	�������ƣ�	WiFi_Init()
//
//	�������ܣ�	WIFI����ONE.NETƽ̨ATָ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void WiFi_Init()
{
		WiFi_RST_Init();	//��ʼ��WiFiģ��RST
		WiFi_LED_Init();	//��ʼ��WiFiģ��LED��
		WiFi_KEY_Init();	//��ʼ��WiFiģ�鰴��
	
		while(!WiFi_Send_Cmd(AT,"OK",20));						/*����AT����ģʽ*/
	
		WiFi_RGB_SET(0x3300);													//���
		
		while(!WiFi_Send_Cmd(CWMODE,"OK",30));				/*����ģ��Ӧ��ģʽ*/
	
		while(!WiFi_Send_Cmd(CWJAP,"OK",300));				/*����Ҫ���ӵ�·������SSID������*/
	
		WiFi_RGB_SET(0x33);														//����
	
		while(!WiFi_Send_Cmd(TCP_CIPSTART,"OK",60));	/*�����������TCP����*/
	
		WiFi_RGB_SET(0x330000);												//�̵�
	
		while(!WiFi_Send_Cmd(CIPMODE,"OK",60));				/*͸��ģʽ*/
	
		while(!WiFi_Send_Cmd(CIPSEND,"OK",30));				/*��ʼ����*/
		
		while(!WiFi_Send_Cmd(CIPSTATUS,"",30));				/*�����豸*/
		WiFi_RGB_SET(0x000000);												//���
		WiFi_RGB_REST();															//���
	
		WiFi_AT_STA = 1;           										/*ATָ�����ɱ�־λ*/
}

//==========================================================
//	�������ƣ�	WiFi_RST_Init()
//
//	�������ܣ�	WiFiģ��RST��ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void WiFi_RST_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	WiFi_RST_GPIO_RCC_EN();           				//����GPIOAʱ��

	GPIO_Initure.Pin=WiFi_RST_PIN; 						//PA5
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
	GPIO_Initure.Pull=GPIO_PULLUP;          	//����
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	 	//����
	HAL_GPIO_Init(WiFi_RST_PORT,&GPIO_Initure);

	WiFi_RST_High();	//RST�ø�
}

//==========================================================
//	�������ƣ�	WiFi_LED_Init()
//
//	�������ܣ�	WiFiģ����LED�Ƴ�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void WiFi_LED_Init(void)
{
	GPIO_InitTypeDef GPIO_Initure;
	WiFi_LED_GPIO_RCC_EN();           				//����GPIOAʱ��

	GPIO_Initure.Pin=WiFi_LED_PIN; 						//PA7
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
	GPIO_Initure.Pull=GPIO_PULLUP;          	//����
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;    	 	//����
	HAL_GPIO_Init(WiFi_LED_PORT,&GPIO_Initure);

	HAL_GPIO_WritePin(WiFi_LED_PORT,WiFi_LED_PIN,GPIO_PIN_RESET);	//PA7��0 
}

//==========================================================
//	�������ƣ�	WiFi_KEY_Init()
//
//	�������ܣ�	������ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void WiFi_KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    WiFi_KEY_GPIO_RCC_EN();           //����GPIOAʱ��
    
    GPIO_Initure.Pin=WiFi_KEY_PIN;
    GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
    GPIO_Initure.Pull=GPIO_PULLUP;        	//����
    GPIO_Initure.Speed=GPIO_SPEED_LOW;     	//����
    HAL_GPIO_Init(WiFi_KEY_PORT,&GPIO_Initure);
}

//==========================================================
//	�������ƣ�	WiFi_RGB_Set_UP()
//
//	�������ܣ�	1��  850ns�ߵ�ƽ  400ns�͵�ƽ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void WiFi_RGB_Set_UP()
{
	/*
			д�ߵ�ƽ
	*/
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
	/*
			д�͵�ƽ
	*/
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
}

//==========================================================
//	�������ƣ�	WiFi_RGB_Set_Down()
//
//	�������ܣ�	0��  400ns�ߵ�ƽ  850ns�͵�ƽ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void WiFi_RGB_Set_Down()
{
	/*
			д�ߵ�ƽ
	*/
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
		WiFi_LED_High();
	/*
			д�͵�ƽ
	*/
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
		WiFi_LED_Low();
}

//==========================================================
//	�������ƣ�	WiFi_RGB_SET()
//
//	�������ܣ�	������ɫ
//
//	��ڲ�����	G8R8B8:��ɫ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void WiFi_RGB_SET(uint32_t G8R8B8)
{
	static int i = 0;
	unsigned char byte = 0;
	
	for(i=23;i>=0;i--)
	{
		byte = ((G8R8B8 >> i) & 0x01);
		if(byte == 1)
		{
			WiFi_RGB_Set_UP();//1
		}
		else
		{
			WiFi_RGB_Set_Down(); //0
		}
	}
}

//==========================================================
//	�������ƣ�	WiFi_RGB_REST()
//
//	�������ܣ�	���͵�ƽ�ȴ���һ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void WiFi_RGB_REST(void)
{
	WiFi_LED_Low();
	delay_us(80);  //��ʱ80us
}





