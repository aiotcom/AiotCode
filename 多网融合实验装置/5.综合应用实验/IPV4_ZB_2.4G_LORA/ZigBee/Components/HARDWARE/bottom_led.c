//#include "delay.h"
#include "bottom_led.h"
#include "delay.h"
#include <ioCC2530.h> 
long int rgb = 0x070707;  //��Ҫ�任����ɫ
uint16 fig = 0,num = 23;    
void RGB_REST(void);
void Set_White(void);
void bottom_led(void);
void _delayunit(void);
void RGB_Set_UP();
void RGB_Set_Down(void);
void Bottom_Green(void);
void Bottom_Red(void);
void Bottom_Blue(void);
void Bottom_Yellow(void);
void Bottom_BlackOut(void);
void RGB_Set_UP(void);
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
void bottom_led_init(void)
{
    P2DIR |= 0x01;      //P1.0����Ϊ���
    RGB_REST();
}
void _delayunit(void)
{
  uint8 i=0;
  for(i=0;i<2;i++)
  {
  
  }
}
/*  1�� 850ns�� 400ns��*/
void RGB_Set_UP(void)
{
      LED = 1;      //1
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      asm("NOP");
      LED = 0;
}

/*  0��  400ns��  850ns��*/
void RGB_Set_Down(void)
{
      LED = 1;     //0
      asm("NOP");
      asm("NOP");
      LED = 0;
      asm("NOP");
      asm("NOP");
}

#define SEND_HI {LED = 1;LED = 1;LED = 1;LED = 1;LED = 1;LED = 1;LED = 1;LED = 1;LED = 1;LED = 0;LED = 0;LED = 0;LED = 0;LED = 0;}

#define SEND_LO {LED = 1;LED = 1;LED = 1;LED = 1;LED = 1;LED = 0;LED = 0;LED = 0;LED = 0;LED = 0;LED = 0;LED = 0;LED = 0;LED = 0;}
//#define SEND_HI {LED = 1;LED = 1;LED = 1;LED = 1;LED = 0;LED = 0;LED = 0; }
//
//#define SEND_LO {LED = 1;LED = 1;LED = 1;LED = 0;LED = 0;LED = 0;LED = 0; }
void Bottom_White(void)
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

void Bottom_Green(void)
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

void Bottom_Red(void)
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
void Bottom_Blue(void)
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
void Bottom_Yellow(void)
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
void Bottom_BlackOut(void)
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
