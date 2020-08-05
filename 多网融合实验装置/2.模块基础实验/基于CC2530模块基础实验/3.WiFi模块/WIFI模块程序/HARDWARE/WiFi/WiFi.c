#include "Usart.h"	
#include "WiFi.h"

//==========================================================
//	�������ƣ�	WiFi_Init()
//
//	�������ܣ�	��ʼ��WiFi
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void WiFi_Init(void)
{
    P1DIR |= 0x60;      //P1.5��P1.6����Ϊ���
    P1SEL &= ~0x80;     //����P1.7Ϊ��ͨIO��  
    P1DIR &= ~0x80;     //��������P1.7���ϣ���P1.7Ϊ����ģʽ 
    P1INP &= ~0x80;     //��P1.7��������

//    WiFi_Send_Cmd(CLOSE_TCP,"",5);			/*�˳�WiFi͸��ģʽ*/
//
//    delay_ms(3000);

    WiFi_RES = 0;
    delay_ms(1);
    WiFi_RES = 1;

    WiFi_LED_SET(0x17);

    while(!WiFi_Send_Cmd(AT,"OK",20));		        /*����AT����ģʽ*/		

    WiFi_LED_SET(0x1700);

    while(!WiFi_Send_Cmd(CWMODE,"OK",30));		/*����ģ��Ӧ��ģʽ*/	

//    while(!WiFi_Send_Cmd(RST,"",80));		        /*����ģ��*/			
//
//    while(!WiFi_Send_Cmd(CIFSR,"OK",30));;		/*��ѯ�豸IP�ɷ�����Ҫ��λ��*/				

    while(!WiFi_Send_Cmd(CWJAP,"OK",300));		/*����Ҫ���ӵ�·������SSID������*/	

    WiFi_LED_SET(0x170000); //LED��

    while(!WiFi_Send_Cmd(TCP_CIPSTART,"OK",60));	/*�����������TCP����*/								

    while(!WiFi_Send_Cmd(CIPMODE,"OK",60));		/*͸��ģʽ*/

    while(!WiFi_Send_Cmd(CIPSEND,"OK",30));		/*��ʼ����*/									

    while(!WiFi_Send_Cmd(CIPSTATUS,"",30));		/*�����豸*/

    WiFi_LED_SET(0x000000); //�ر�LED��
    
    WiFi_AT_STA = 1;           			        /*ATָ�����ɱ�־λ*/	
}

/***********************************************************************************
* ��������        WiFi_LED_REST()
*
* ��������        ���͵�ƽ�ȴ�
*
* ��ڲ���        ��
*
* ���ز���        �� 
*
* ˵��            
***********************************************************************************/
/* ���͵�ƽ�ȴ���һ������  */
void WiFi_LED_REST(void)
{
    WiFi_LED = 0;
    delay_ms(1);  
}

//==========================================================
//	�������ƣ�	WiFi_LED_SET()
//
//	�������ܣ�	������ɫ
//
//	��ڲ�����	G8R8B8:��ɫ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void WiFi_LED_SET(uint32_t G8R8B8)
{
    static int i = 0;
    static unsigned char byte = 0;
    
    for(i=23;i>=0;i--)
    {
        byte = ((G8R8B8 >> i) & 0x01);
        if(byte == 1)
        {
            WiFi_LED_HI;//1
        }
        else
        {
            WiFi_LED_LO; //0
        }
    }
    WiFi_LED_REST();
}

//==========================================================
//	�������ƣ�	WiFi_Set_White()
//
//	�������ܣ�	��ɫ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void WiFi_Set_White(void)
{
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;

  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;  
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;
  WiFi_LED_HI;  
}