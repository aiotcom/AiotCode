/**
************************************************************
************************************************************
************************************************************
*
*	作者： 		重庆八城科技
*
*	日期： 		2020-01-09
*
*	版本： 		V2.0
*
*	说明： 		风扇模块实验
*
*	修改记录：	
************************************************************
************************************************************
************************************************************
**/

#include <ioCC2530.h>
#include "delay.h"
#include "Rs485.h"
#include "usart.h"
#include "Lamp.h"
#include "Fan.h"

//==========================================================
//	函数名称：	main()
//
//	函数功能：	程序入口函数
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
uint32_t Count = 0;
void main(void)
{
    Hal_Init_32M();   //初始化32M时钟
    LampInit();       //初始化底座灯
    Fan_Init();       //初始化风扇

    while(1)
    {
      Count++;
      if(Count<=1000) //高速
      {
        Fan_Set(999);
      }
      else if(Count>1000 && Count<=2000)  //中速
      {
        Fan_Set(499);
      }
      else if(Count>2000 && Count<=3000)  //低速
      {
        Fan_Set(199);
      }
      else if(Count>3000)
      {
        Fan_Set(0);
        Count = 0;
      }
    }
}
