#include "delay.h"
#include "Lamp.h"

long int rgb = 0x070707;  //��Ҫ�任����ɫ
uint16_t fig = 0,num = 23;    
void RGB_REST(void);
/***********************************************************************************
* ��������        InitLed
*
* ��������        ����LED����Ӧ��IO��
*
* ��ڲ���        ��
*
* ���ز���        �� 
*
* ˵��
***********************************************************************************/
void LampInit(void)
{
    P2DIR |= 0x01;      //P2.0����Ϊ���
    RGB_REST();
    
    Set_Yellow();       //�����ƻ�ɫ
}
void _delayunit(void)
{
  uint8_t i=0;
  for(i=0;i<4;i++)
  {
  
  }
}
/*  1�� 850ns�� 400ns��*/
void RGB_Set_UP()
{
      LED = 1;      //1
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      LED = 0;
}

/*  0��  400ns��  850ns��*/
void RGB_Set_Down()
{
      LED = 1;     //0
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      LED = 0;
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
}

#define SEND_HI {LED = 1;LED = 1;LED = 1;LED = 1;LED = 1;LED = 1;LED = 1;LED = 1;LED = 0;LED = 0;LED = 0;LED = 0; }

#define SEND_LO {LED = 1;LED = 1;LED = 1;LED = 1;LED = 0; LED = 0;LED = 0;LED = 0;LED = 0; LED = 0;LED = 0;LED = 0; }

void Set_White(void)
{
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;

  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;  
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;  
}

void Set_Green(void)
{
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;  
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;  
}

void Set_Red(void)
{ 
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;  
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;  
}
void Set_Blue(void)
{ 
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
   
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;  
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO; 
  
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;  
}
void Set_Yellow(void)
{ 
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;
  SEND_HI;  
  
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;
  SEND_LO;  
}
/***********************************************************************************
* ��������        RGB_SET()
*
* ��������        ������ɫ 
*
* ��ڲ���        G8R8B8�� 24λRGB��ɫ
*
* ���ز���        �� 
*
* ˵��
***********************************************************************************/


/* ���͵�ƽ�ȴ���һ������  */
void RGB_REST(void)
{
    LED = 0;
    delay_ms(1);  
}
