#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include "delay.h"
#include "usart.h"
#include "Rs485.h"
#include "TFT.h"
#include "timer.h"
/**
************************************************************
************************************************************
************************************************************
*
*	���ߣ� 		����˳ǿƼ�
*
*	���ڣ� 		2018-01-01
*
*	�汾�� 		V1.0
*
*	˵���� 		TFT����ʵ��-HAL��汾
*
*	�޸ļ�¼��	
************************************************************

************************************************************
************************************************************
**/
enum{
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_ENTER,
    KEY_CANNCEL,
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_NULL //û�а�������
};
#define BOX_W      144
#define BOX_H      32
#define BOX_X_START     ((240-BOX_W)*0.5+8)

#define BOX_1_X_START   BOX_X_START
#define BOX_1_Y_START   60
#define BOX_1_Y_String  BOX_1_Y_START + (BOX_H*0.5)-8//8�������һ��

#define BOX_2_X_START   BOX_X_START
#define BOX_2_Y_START   (BOX_1_Y_START+32+32)
#define BOX_2_Y_String   (BOX_2_Y_START+(BOX_H*0.5)-8)//8�������һ��

#define BOX_3_X_START   BOX_X_START
#define BOX_3_Y_START   (BOX_2_Y_START+32+32)
#define BOX_3_Y_String   (BOX_3_Y_START+(BOX_H*0.5)-8)//8�������һ��

void RS485_HandlerCb(void);
uint8_t LCD_ReceiverNFC[32],LCD_ReceiveNFCFlg=0;
uint8_t LCD_DisplayIdBuffer[32]={""};
uint8_t LCD_NFC_Blockmem[34];
uint8_t BlockmemInputBuffer[32],InputIndex = 0;
uint32_t CardId;
uint8_t GUI_Message = KEY_NULL;
uint8_t SetNFC_Blockmem = 0;
uint8_t SetNFC_BlockBuffer[32];
uint8_t GetKeyMessage = 0;
int main(void)
{
    uint8_t i = 0;
    uint8_t *pbm;           //���յ�NFC block memory �ڴ�ָ��
    HAL_Init();             //��ʼ��HAL��
    TFT_Init();             //��ʼ��TFT��ʾ���˿�
    Rs485_Init();			//��ʼ��485
    UART1_Init(115200);		//��ʼ������
    USART3_Init(115200);		//��ʼ������
    
    Lcd_Init();				//��ʼ��LCD
    LCD_UI();				//����UI

    TIM3_Init(20000-1,64-1,RS485_HandlerCb);					//��ʼ����ʱ���ж����� 50 HZ 
    
	LCD_Clear(BLUE);       //��Ļ�����ɫ
	BACK_COLOR = WHITE;     //���屳��ɫ��ɫ
	POINT_COLOR = BLACK;   //�����ɫ									
	//LCD_DrawRectangle(1,60,239,150);			//������ʾ��
	
    memcpy((void*)BlockmemInputBuffer,"----------------",17);
    LCD_Fill(BOX_1_X_START,BOX_1_Y_START,BOX_1_X_START+BOX_W,BOX_1_Y_START+BOX_H,WHITE);
    LCD_ShowString(BOX_1_X_START-3*8,BOX_1_Y_String,"ID:",1); 
    LCD_Fill(BOX_2_X_START,BOX_2_Y_START,BOX_2_X_START+BOX_W,BOX_2_Y_START+BOX_H,WHITE); 
    LCD_ShowString(BOX_2_X_START-10*8,BOX_2_Y_String,"memory:",1);     
    LCD_Fill(BOX_3_X_START,BOX_3_Y_START,BOX_3_X_START+BOX_W,BOX_3_Y_START+BOX_H,WHITE);
    LCD_ShowString(BOX_3_X_START-6*8,BOX_3_Y_String,"input:",1);


    BACK_COLOR = WHITE;     //���屳��ɫ��ɫ
	POINT_COLOR = BLACK;   //�����ɫ	 
    printf("this is usart3 print\r\n");   
    while(1)
    {
        if(LCD_ReceiveNFCFlg)
        {
            LCD_ReceiveNFCFlg = 0;
            
            /*��ʾID��*/
            if(LCD_ReceiverNFC[0]||LCD_ReceiverNFC[1]||LCD_ReceiverNFC[2]||LCD_ReceiverNFC[3])
            {
                sprintf((void*)&LCD_DisplayIdBuffer[0], \
                        "%02X %02X %02X %02X", \
                         LCD_ReceiverNFC[3],LCD_ReceiverNFC[2],LCD_ReceiverNFC[1],LCD_ReceiverNFC[0]);
                
                LCD_ShowString(BOX_1_X_START+5,BOX_1_Y_String,LCD_DisplayIdBuffer,0);
            
                pbm = &LCD_ReceiverNFC[4];
                /*��ʾ�ڲ��洢������*/
                if(   pbm[0]&&pbm[1]&&pbm[2]&&pbm[3]&&pbm[4]&&pbm[5]
                    &&pbm[6]&&pbm[7]&&pbm[8]&&pbm[9]&&pbm[10]&&pbm[11]
                    &&pbm[12]&&pbm[13]&&pbm[14]&&pbm[15])
                {
                    
                    sprintf((void*)&LCD_NFC_Blockmem[0], \
                            "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", /*��16��*/
                             pbm[0],pbm[1],pbm[2],pbm[3],pbm[4],pbm[5],pbm[6],pbm[7],pbm[8],pbm[9],pbm[10],pbm[11],pbm[12],pbm[13],pbm[14],pbm[15]);
                    LCD_ShowString(BOX_2_X_START+5,BOX_2_Y_String,LCD_NFC_Blockmem,0);    
                }
                else
                {//ȫ��
                    LCD_ShowString(BOX_2_X_START+5,BOX_2_Y_String,"0000000000000000",0);              
                }
            }
        }
        
/********************���������룬��д���ڲ��洢��������********************************/        
        if(GUI_Message != KEY_NULL)
        {
            printf("key message=%d\r\n",GUI_Message);
            if(GUI_Message <= KEY_9)
            {
                if(InputIndex != 16)
                {
                    if( InputIndex == 0)
                    {
                        memcpy((void*)BlockmemInputBuffer,"----------------",17);
                    }
                    BlockmemInputBuffer[InputIndex++] = GUI_Message+0x30; 
                    LCD_ShowString(BOX_3_X_START,BOX_3_Y_String,BlockmemInputBuffer,0);   
                }                      
           }
           else if(GUI_Message == KEY_CANNCEL)
           {
                if(InputIndex)
                {
                    BlockmemInputBuffer[--InputIndex] = '-'; 
                    LCD_ShowString(BOX_3_X_START,BOX_3_Y_String,BlockmemInputBuffer,0);   
                }                     
           }
           else if(GUI_Message == KEY_ENTER)
           {
                //if(InputIndex == 16)
                {
                    InputIndex = 0;
                    SetNFC_Blockmem = 1;
                }
            }
            GUI_Message =  KEY_NULL;          
        }//if(GetKeyMessage)
/********************���������룬��д���ڲ��洢��������********************************/          
    }
}
//==========================================================
//	�������ƣ�	void RS485_HandlerCb(void)
//
//	�������ܣ�	ͨ��485���߻�ȡ���ݴ�����
//
//	��ڲ�����	void
//
//	���ز�����	��
//
//	˵����		��ʱ��3�жϣ��ص�������ÿ100ms����һ��
//==========================================================
void RS485_HandlerCb(void)
{  
    static uint8_t state = 0,nextstate = 0,_10Hz_Count=0;
    switch(state)
    {
        case 0:
            Rs485_Send(Addr_LCD,Addr_Matrixkey,Matrixkey_Get_value,0,(void*)0);//485�������󰴼�ֵ
            state     = 1;
            break;
        case 1:
            if(!DataHandling_485(Addr_LCD))
            {
                if(Rx_Stack.Command == MatrixkeyKeyValue)
                {
                    GUI_Message = Rx_Stack.Data[0];
                }
            } 
            state = 2;           
            break;           
        case 2:
            if(SetNFC_Blockmem)
            {
                SetNFC_Blockmem = 0;
                Rs485_Send(Addr_LCD,Addr_HF_RFID,HF_RFID_Set_Memblock,16,BlockmemInputBuffer);//485��������NFC��ƬID
                state     = 0;
                return;
            }
            else
            {
                Rs485_Send(Addr_LCD,Addr_HF_RFID,HF_RFID_Get_All,0,(void*)0);//485��������NFC��ƬID
                state     = 3;
            }                
            break;
        case 3:
            if(!DataHandling_485(Addr_LCD))
            {
                if(Rx_Stack.Command == HF_RFID_All)
                {
                    memcpy((void*)&LCD_ReceiverNFC,(const void*)Rx_Stack.Data,20);
                    LCD_ReceiveNFCFlg = 1;
                }
            } 
            state = 0;           
            break;   
    }
}



