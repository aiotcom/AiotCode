#include "WiFi.h"
#include "delay.h"
#include "Usart.h"
#include "WS2812b.h"
#define WIFI_RECEIVE_BUFFER_LEN 128
uint8_t WiFi_ReceiveBuffer[WIFI_RECEIVE_BUFFER_LEN+1],ReceiveLenght=0;
uint8_t WiFi_AT_STA = 0;
uint8_t* WiFi_Send_Cmd(uint8_t *cmd,uint8_t *ack,uint16_t waittime);
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
    HAL_Delay(10);//��ʱ2����
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
    
    HAL_Delay(2000);//��ʱ2000���룬��WIFIģ�鸴λ��������ӡ����࿪����Ϣ����ʱ����ܿ���
    
    
    while(!WiFi_Send_Cmd(AT,(uint8_t*)"OK",20));				    /*����AT����ģʽ*/
    //WS2812B_SetColour(0x000055);                                    //��ɫ��ʾ
    
    while(!WiFi_Send_Cmd(CWMODE,(uint8_t*)"OK",30));				/*����ģ��Ӧ��ģʽ*/

    while(!WiFi_Send_Cmd(CWJAP,(uint8_t*)"OK",1000));				/*����Ҫ���ӵ�·������SSID������*/   
    //WS2812B_SetColour(0x005500);                                    //��ɫ��ʾ    
    
    
    while(!WiFi_Send_Cmd(TCP_CIPSTART,(uint8_t*)"OK",3000));	/*�����������TCP����*/
    //WS2812B_SetColour(0x550000);                                    //��ɫ��ʾ
    
    while(!WiFi_Send_Cmd(CIPMODE,(uint8_t*)"OK",500));				/*͸��ģʽ*/

    while(!WiFi_Send_Cmd(CIPSEND,(uint8_t*)"OK",500));				/*��ʼ����*/

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

	memset((void*)WiFi_ReceiveBuffer,0,WIFI_RECEIVE_BUFFER_LEN);	//�������
	HAL_UART_Transmit(&UART2_Handler,cmd,len,1000);	//����2��������
	ReceiveLenght = 0;
    
    if((*ack) != 0)
    {
        for(j=0;j<waittime;j++)
        {
            HAL_Delay(1);
            strx=strstr((const char*)WiFi_ReceiveBuffer,(const char*)ack);
            if((strx))
            {
                break;
            }
        }
    }
    else
    {
        HAL_Delay(waittime);
        return (uint8_t*)1;
    }
	return (uint8_t*)strx;
}
//==========================================================
//	�������ƣ�	void WiFi_Send(uint8_t *pdata,uint8_t len)
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
void WiFi_Send(uint8_t *pdata,uint8_t len)
{
    HAL_UART_Transmit(&UART2_Handler,pdata,len,1000);	//����2��������
}
//==========================================================
//	�������ƣ�	void WiFi_Send(uint8_t *pdata,uint8_t len)
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
//+IPD,0,23:this is sample data;���յ����ݸ�ʽ���ӵڶ���","��ʼ����:�� Ϊ���ݳ��ȣ���:��֮��Ϊ��������
//==========================================================
uint8_t *pbyte;
uint8_t datalen;
uint8_t WiFi_Receive(uint8_t *precv)
{
    static uint8_t state;
    uint8_t i = 0,len = 0,markcount=0;
    
    if(ReceiveLenght)
    {
        HAL_Delay(20);    
        if(strstr((const void*)WiFi_ReceiveBuffer,"+IPD,"))
        {
            while(i<100)
            {//�ҵ��ڶ�������λ��
                if(WiFi_ReceiveBuffer[i] == ',')
                {
                    markcount++;
                }
                if(markcount == 2)
                {
                    pbyte = &WiFi_ReceiveBuffer[i+1];
                    break;
                }
                i++;
            }
            
            datalen = 0;
            while((*pbyte) != ':')
            {//����ӳ���
                datalen *= 10;
                datalen  = datalen + (*pbyte-0x30);
                pbyte++;
            }
            printf("dl=%d\r\n",datalen);
            
            pbyte++;
            while(datalen--)
            {
                *precv = *(pbyte);
                pbyte++;
                precv++;
                len++;
            }                
        }
        ReceiveLenght = 0;
    }           
    return len;
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
void WiFi_ByteReceive(uint8_t byte)
{
    WiFi_ReceiveBuffer[ReceiveLenght++] = byte;
    if(ReceiveLenght >= WIFI_RECEIVE_BUFFER_LEN)
    {
        ReceiveLenght = 0;
    }
}

















