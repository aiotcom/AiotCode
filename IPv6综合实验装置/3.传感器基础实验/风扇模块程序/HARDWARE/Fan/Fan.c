#include "delay.h"
#include "Fan.h"

//==========================================================
//	函数名称：	Fan_Init()
//
//	函数功能：	初始化风扇
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void Fan_Init(void)
{
   P0DIR |= 0x02;   //P0.1定义为输出
   Fan = 0;         //初始化关闭风扇
}

//==========================================================
//	函数名称：	Fan_Set()
//
//	函数功能：	风扇档位调节
//
//	入口参数：	Num：0~1000 数值越大 转速越快
//
//	返回参数：	无
//
//	说明：		调节占空比
//==========================================================
void Fan_Set(uint32_t Num)
{
    for(int j = 0;j<Num;j++)
    {
      Fan = 1;
    }
    for(int k = 0;k<(1000-Num);k++)
    {
      Fan = 0;
    }
}