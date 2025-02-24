#include "delay.h"
#include "KEY.h"
#include "LED.h"

//==========================================================
//	函数名称：	KEY_Init()
//
//	函数功能：	按键初始化函数
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void KEY_Init(void)
{
    P0SEL &= ~0x03;     //设置P0.0、P0.1为普通IO口  
    P0DIR &= ~0x03;     //按键接在P0.0、P0.1口上，设P0.0、P0.1为输入模式 
    P0INP &= ~0x03;     //打开P0.0、P0.1上拉电阻
    
    P1SEL &= ~0x30;     //设置P1.4、P1.5为普通IO口  
    P1DIR &= ~0x30;     //按键接在P1.4、P1.5口上，设P1.4、P1.5为输入模式 
    P1INP &= ~0x30;     //打开P1.4、P1.5上拉电阻
}

//==========================================================
//	函数名称：	KEY_Scan()
//
//	函数功能：	按键处理函数
//
//	入口参数：	mode:	0,不支持连续按;
//				1,支持连续按;
//
//	返回参数：	返回按键值
//				0，没有任何按键按下
//				1、2、3、4对应相应的按键
//	说明：			注意此函数有响应优先级,KEY1>KEY2>KEY3>KEY4!!
//==========================================================
uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t key_up=1;    //按键松开标志
    if(mode==1)key_up=1;    	//支持连按
    if(key_up&&(S1_Read()==0||S2_Read()==0||S3_Read()==0||S4_Read()==0))
    {
        delay_ms(10);
        key_up=0;
        if(S1_Read()==0)       return S1_PRES;
        else if(S2_Read()==0)  return S2_PRES;
        else if(S3_Read()==0)  return S3_PRES;  
	else if(S4_Read()==0)  return S4_PRES;
    }else if(S1_Read()==1&&S2_Read()==1&&S3_Read()==1&&S4_Read()==1)key_up=1;
		
    return 0;   //无按键按下
}

//==========================================================
//	函数名称：	key_Operatio()
//
//	函数功能：	按键操作-控制LED灯亮灭
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void key_Operatio(void)
{
    static uint8_t key = 0,Key_Flag = 0;
    
    key = KEY_Scan(0);//获取按键
    
    switch(key)
    {
        case 1:
            Key_Flag = 1;
            break;
        case 2:
            Key_Flag = 2;
            break;
        case 3:
            Key_Flag = 3;
            break;
        case 4:
            Key_Flag = 4;
            break;
        default:break;
    }
    
    LED_Type(Key_Flag);	//根据按键进行相应的灯光效果
}


