#include "Usart.h"
#include "Rs485.h"	
#include "Time.h"

#if UART1   //使能接收

//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
unsigned char  USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

unsigned int USART1_RX_STA=0;       //接收状态标记	  

unsigned char UART1_RxBuffer[UART1_RXBUFFERSIZE];//HAL库使用的串口接收缓冲

UART_HandleTypeDef UART1_Handler; //UART句柄
  

//==========================================================
//	函数名称：	UART1_Init
//
//	函数功能：	串口1初始化
//
//	入口参数：	bound:波特率
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
void UART1_Init(int bound)
{	
	//UART 初始化设置
	UART1_Handler.Instance=USART1;					    			//USART1
	UART1_Handler.Init.BaudRate=bound;				    		//波特率
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B; //字长为8位数据格式
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //无硬件流控
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    	//收发模式
	HAL_UART_Init(&UART1_Handler);					    			//HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&UART1_Handler, (unsigned char *)UART1_RxBuffer, UART1_RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
  
}


//==========================================================
//	函数名称：	USART1_IRQHandler
//
//	函数功能：	串口1中断服务程序
//
//	入口参数：	无
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
uint8_t GetMsg = 0;
void USART1_IRQHandler(void)                	
{ 
	unsigned char Res;
	//HAL_StatusTypeDef err;

	if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_RXNE)!=RESET))  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
        __HAL_UART_CLEAR_FLAG(&UART1_Handler,UART_FLAG_RXNE);
		Res=USART1->DR;           
	}
    if((__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TXE)!=RESET))
    {
        __HAL_UART_CLEAR_FLAG(&UART1_Handler,UART_FLAG_TXE);
    }
} 

#endif

#if UART2

//串口2中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
unsigned char  USART2_RX_BUF[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
unsigned char  USART2_TX_BUF[USART2_MAX_SEND_LEN];//发送缓冲,最大USART2_MAX_SEND_LEN字节

unsigned int USART2_RX_STA=0;       							//接收状态标记	  

unsigned char UART2_RxBuffer[UART2_RXBUFFERSIZE];	//HAL库使用的串口接收缓冲

UART_HandleTypeDef UART2_Handler; 								//UART句柄

  
//==========================================================
//	函数名称：	UART2_Init
//
//	函数功能：	串口2初始化
//
//	入口参数：	bound:波特率
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
void UART2_Init(int bound)
{	
	//UART 初始化设置
	UART2_Handler.Instance=USART2;					    			//USART1
	UART2_Handler.Init.BaudRate=bound;				    		//波特率
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B; //字长为8位数据格式
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    //一个停止位
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    //无奇偶校验位
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE; //无硬件流控
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    	//收发模式
    UART2_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART2_Handler);					    			//HAL_UART_Init()会使能UART1
	
	HAL_UART_Receive_IT(&UART2_Handler, (unsigned char *)UART2_RxBuffer, UART2_RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
  
}

//==========================================================
//	函数名称：	USART2_IRQHandler
//
//	函数功能：	串口2中断服务程序
//
//	入口参数：	无
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
void USART2_IRQHandler(void)                	
{ 
	unsigned char Res;
//	HAL_StatusTypeDef err;

	if((__HAL_UART_GET_FLAG(&UART2_Handler,UART_FLAG_RXNE)!=RESET))  //接收中断
	{
		Res=USART2->DR; 
		if((USART2_RX_STA&(1<<15))==0)					//接收完的一批数据,还没有被处理,则不再接收其他数据
		{ 
			if(USART2_RX_STA<USART2_REC_LEN)			//还可以接收数据
			{
				//TIM_ESP8266_FIG(1);									//开始计数
				//number = 0;													//清零计数值
				if(USART2_RX_STA==0) 								//使能定时器7的中断 
				{
					//TIM_ESP8266_FIG(0);								//关闭计数
				}
				USART2_RX_BUF[USART2_RX_STA++]=Res;	//记录接收到的值	 
			}else 
			{
				USART2_RX_STA|=1<<15;								//强制标记接收完成
			} 
		}	 
	}
	HAL_UART_IRQHandler(&UART2_Handler);	
} 

#endif


//==========================================================
//	函数名称：	HAL_UART_MspInit
//
//	函数功能：	UART底层初始化，时钟使能，引脚配置，中断配置
//
//	入口参数：	huart:串口句柄
//              
//	返回参数：	无
//
//	说明：		
//==========================================================
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    //GPIO端口设置
	GPIO_InitTypeDef GPIO_Initure;
    
    if (huart->Instance==USART1)   							//如果是串口1，进行串口1 MSP初始化
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();						//使能GPIOA时钟
        __HAL_RCC_USART1_CLK_ENABLE();					//使能USART1时钟
        __HAL_RCC_AFIO_CLK_ENABLE();

        GPIO_Initure.Pin=GPIO_PIN_9;						//PA9
        GPIO_Initure.Mode=GPIO_MODE_AF_PP;			//复用推挽输出
        GPIO_Initure.Pull=GPIO_PULLUP;					//上拉
        GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
        HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA9

        GPIO_Initure.Pin=GPIO_PIN_10;						//PA10
        GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;		//模式要设置为复用输入模式！	
        HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA10
        
    #if EN_USART1_RX
        HAL_NVIC_EnableIRQ(USART1_IRQn);				//使能USART1中断通道
        HAL_NVIC_SetPriority(USART1_IRQn,3,3);	//抢占优先级3，子优先级3
    #endif	
    }
    else if(huart->Instance==USART2)						//如果是串口2，进行串口2 MSP初始化
	{

            __HAL_RCC_GPIOA_CLK_ENABLE();				//使能GPIOA时钟
            __HAL_RCC_USART2_CLK_ENABLE();			//使能USART2时钟
            
           // __HAL_RCC_AFIO_CLK_ENABLE();

            GPIO_Initure.Pin=GPIO_PIN_2;				//PA2
            GPIO_Initure.Mode=GPIO_MODE_AF_PP;	//复用推挽输出
            GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
            GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
            HAL_GPIO_Init(GPIOA,&GPIO_Initure);	//初始化PA2

            GPIO_Initure.Pin=GPIO_PIN_3;				//PA3
            GPIO_Initure.Mode=GPIO_MODE_AF_INPUT;	//模式要设置为复用输入模式！	
            HAL_GPIO_Init(GPIOA,&GPIO_Initure);	//初始化PA3
            
        #if EN_USART2_RX
            HAL_NVIC_EnableIRQ(USART2_IRQn);		//使能USART2中断通道
            HAL_NVIC_SetPriority(USART2_IRQn,3,3);			//抢占优先级3，子优先级3
        #endif	
    }
}

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (unsigned char) ch;      
	return ch;
}
#endif 

