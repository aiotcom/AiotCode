#include "delay.h"
#include "timer.h"
#include "EM4095.h"
#include "string.h"

#define SET_EM4095_MODE_OPERATION()     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET)	
#define SET_EM4095_MODE_SLEEP()         HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET)	

#define EM4095_MOD_DISABLE()            HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET)
#define EM4095_MOD_ENABLE()             HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET)

#define READ_RDY_CLK()                  HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15)

//==========================================================
//	�������ƣ�	EM4095_IO_Init
//
//	�������ܣ�	EM4095-IO�ڳ�ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void EM4095_IO_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��
		__HAL_RCC_GPIOG_CLK_ENABLE();           	//����GPIOGʱ��
	
    GPIO_Initure.Pin   = GPIO_PIN_6; 	        //GPIO_PIN_6 MOD
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP; //�������
    GPIO_Initure.Pull  = GPIO_PULLUP;         //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    EM4095_MOD_DISABLE();
    
    GPIO_Initure.Pin   = GPIO_PIN_5; 	        //GPIO_PIN_5 SHD
    GPIO_Initure.Mode  = GPIO_MODE_OUTPUT_PP; //�������
    GPIO_Initure.Pull  = GPIO_PULLUP;         //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    SET_EM4095_MODE_SLEEP();
    
    GPIO_Initure.Pin   = GPIO_PIN_12; 	      //GPIO_PIN_12  DEMOD
    GPIO_Initure.Mode  = GPIO_MODE_INPUT;  	  //����
    GPIO_Initure.Pull  = GPIO_PULLUP;         //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	//����
    HAL_GPIO_Init(GPIOG,&GPIO_Initure);
    
    
    GPIO_Initure.Pin   = GPIO_PIN_15; 	      //GPIO_PIN_15 RDY_CLK
    GPIO_Initure.Mode  = GPIO_MODE_INPUT;    	//����
    GPIO_Initure.Pull  = GPIO_PULLUP;         //����
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;    	//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);    
}

//==========================================================
//	�������ƣ�	DEMOD_InputFilter
//
//	�������ܣ�	��DEMODE ��IO������м򵥵��˲�
//
//	��ڲ�����	void
//
//	���ز�����	���� 0,����Ϊ�͵�ƽ������ 1������Ϊ�ߵ�ƽ��
//
//	˵����		
//==========================================================
uint8_t DEMOD_Input(void)
{
    static uint8_t ret = 1;
    if(READ_DEMOD())
    {
        __us();           //��ʱһ��΢��
        __us();           //��ʱһ��΢��        
        if(READ_DEMOD())
        {
            ret =  1;
        }
    }

    if(!READ_DEMOD())
    {
        __us();           //��ʱһ��΢��
        __us();           //��ʱһ��΢��        
        if(!READ_DEMOD())
        {
            ret = 0;
        }
    }
    return ret;
}

//==========================================================
//	�������ƣ�	EM4095_UID_Parse
//
//	�������ܣ�	��������
//
//	��ڲ�����	uint8_t *pdata
//
//	���ز�����	
//
//	˵����		
//==========================================================
uint8_t  RawCardData[11][5],RawCardDataColIdx=0,RawCardDataRowIdx=0;
uint8_t uid[8],uidindex=0;
uint8_t EM4095_UID_Parse(uint8_t* pdata)
{
    uint8_t ret = 0,XOR,colxor0,colxor1,colxor2,colxor3;
    uint8_t parsestate = 0,errflag=0;
    uidindex = 0;
    RawCardDataColIdx = 0;
    RawCardDataRowIdx = 0;
    memset((void*)uid,0,8);

    if(parsestate == 0)
    {
        /*
         �����ݽ����м���
        */
        while(RawCardDataColIdx < 10)
        {
            XOR               = 0;
            RawCardDataRowIdx = 0;
            while(RawCardDataRowIdx < 4)
            {
                XOR ^= RawCardData[RawCardDataColIdx][RawCardDataRowIdx++];
            }

            if(XOR != RawCardData[RawCardDataColIdx][4])
            {
                errflag = 1;
                break;
            }
            RawCardDataColIdx++;
        }
    }

    parsestate = errflag?0xff:(++parsestate);

    if(parsestate == 1)
    {
       /*
       �����ݽ����м���
       */
        colxor0           = 0;
        colxor1           = 0;
        colxor2           = 0;
        colxor3           = 0;
        RawCardDataColIdx = 0;

        while(RawCardDataColIdx < 10)
        {
            colxor0 ^= RawCardData[RawCardDataColIdx][0];
            colxor1 ^= RawCardData[RawCardDataColIdx][1];
            colxor2 ^= RawCardData[RawCardDataColIdx][2];
            colxor3 ^= RawCardData[RawCardDataColIdx][3];
            RawCardDataColIdx++;
        }

        if(  (colxor0 != RawCardData[10][0])||(colxor1 != RawCardData[10][1])
           ||(colxor2 != RawCardData[10][2])||(colxor3 != RawCardData[10][3]))
        {
            errflag = 1;
        }
    }

    parsestate = errflag?0xff:(++parsestate);

    if(parsestate == 2)
    {
        /*
        ��װ����
        */
        uidindex          = 0;
        RawCardDataColIdx = 0;

        while(RawCardDataColIdx < 10)
        {
            uid[uidindex] |= (RawCardData[RawCardDataColIdx][0] << 3) + (RawCardData[RawCardDataColIdx][1] << 2)
                            +(RawCardData[RawCardDataColIdx][2] << 1) + (RawCardData[RawCardDataColIdx][3] << 0);
            RawCardDataColIdx++;
            
            uid[uidindex] = uid[uidindex] << 4;
            
            uid[uidindex] |= (RawCardData[RawCardDataColIdx][0] << 3) + (RawCardData[RawCardDataColIdx][1] << 2)
                            +(RawCardData[RawCardDataColIdx][2] << 1) + (RawCardData[RawCardDataColIdx][3] << 0);
            RawCardDataColIdx++; 
            
            uidindex++;            
        }

        memcpy((void*)pdata,(const void*)uid,5);
        ret = 1;
    }

    return ret;
}

//==========================================================
//	�������ƣ�	EM4095_SearchHdr
//
//	�������ܣ�	��������
//
//	��ڲ�����	uint8_t *pcardid,pcardid��������ݽ��������������
//
//	���ز�����	���� GET_ID,��ȡ���ݣ����� NOT_ID
//
//	˵����			
//==========================================================
uint16_t TimerCnt=0;
uint8_t  HdrBitSetCounter=0;
uint8_t  CardID_Buffer[100],CardID_Index=0;
uint16_t Hdr_LevelCounter = 0;
uint16_t timeout;
uint8_t EM4095_SearchHdr(uint8_t *pcardid)
{
    static uint8_t Is_CardExist;
    uint8_t state    = 0;
    Hdr_LevelCounter = 0;
    RawCardDataColIdx = 0;
    RawCardDataRowIdx = 0;    

    if(!DEMOD_Input())
    {
        TIM2_Delay(100);
        if(DEMOD_Input())
        {
            return NOT_ID;
        }
    }
    else
    {
        Is_CardExist = 0;
        return NOT_ID;
    }

    while(1)
    {
        if(READ_DEMOD())
        {
            TIM2_IntFlag = 0;
            __HAL_TIM_SET_COUNTER(&TIM2_Handler,0); 
            __HAL_TIM_SET_AUTORELOAD(&TIM2_Handler,550);
            __HAL_TIM_ENABLE(&TIM2_Handler);
            while(READ_DEMOD()&&(TIM2_IntFlag == 0));
            
            __HAL_TIM_DISABLE(&TIM2_Handler);
            TimerCnt = __HAL_TIM_GET_COUNTER(&TIM2_Handler);
            
            if(TimerCnt >= 484)//512*(3/4)
            {
                state = 1;                                    //�ҵ�һ������ͷ
                __HAL_TIM_SET_COUNTER(&TIM2_Handler,0);       //�����������ֵ
                __HAL_TIM_SET_AUTORELOAD(&TIM2_Handler,500);  //�����ж�����
                __HAL_TIM_ENABLE(&TIM2_Handler);              //ʹ�ö�ʱ��
                timeout = 380;
                TIM2_IntFlag     = 0;
                HdrBitSetCounter = 0;
                memset((void*)CardID_Buffer,0,50);
                CardID_Index = 0;
                Is_CardExist = 1;
                break;
            }
            else
            {
                Is_CardExist = 0;
                return NOT_ID;
            }
        }
    }

    if(Is_CardExist)
    {
        if(state == 1) //�ȴ�����ͷ
        {
            while(1)
            {
                if((__HAL_TIM_GET_COUNTER(&TIM2_Handler) >= timeout))
                {
                    TIM2_IntFlag = 0;

                    if(READ_DEMOD())
                    {
                        HdrBitSetCounter++;
                        while(READ_DEMOD());
                    }
                    else
                    {
                        break;
                    }
                    __HAL_TIM_DISABLE(&TIM2_Handler); 
                    __HAL_TIM_SET_COUNTER(&TIM2_Handler,0);       //�����������ֵ
                    __HAL_TIM_SET_AUTORELOAD(&TIM2_Handler,1000); //����Ԥ�Ƶĳ�ʱ��ʱ��
                    __HAL_TIM_ENABLE(&TIM2_Handler);              //ʹ�ö�ʱ��  
                    timeout = 384;
                    if(HdrBitSetCounter == 8)
                    {
                        state = 2;        //��ʼ��������
                        break;
                    }
                }
            }
        }

        if(state == 2)
        {
            while(1)
            {
                if((__HAL_TIM_GET_COUNTER(&TIM2_Handler) >= timeout))
                {
                    TIM2_IntFlag = 0;
                    if(READ_DEMOD())
                    {
                        CardID_Buffer[CardID_Index++] = 1;
                        RawCardData[RawCardDataColIdx][RawCardDataRowIdx++] = 1;
                        while(READ_DEMOD());
                    }
                    else
                    {
                        CardID_Buffer[CardID_Index++] = 0;
                        RawCardData[RawCardDataColIdx][RawCardDataRowIdx++] = 0;
                        while(!READ_DEMOD());
                    }

                    if(RawCardDataRowIdx == 5)
                    {
                        RawCardDataRowIdx = 0;
                        RawCardDataColIdx++;
                    }
                    __HAL_TIM_DISABLE(&TIM2_Handler); 
                    __HAL_TIM_SET_COUNTER(&TIM2_Handler,0);       //�����������ֵ
                    __HAL_TIM_SET_AUTORELOAD(&TIM2_Handler,1000); //�����ж�����
                    __HAL_TIM_ENABLE(&TIM2_Handler);              //ʹ�ö�ʱ��  
                    timeout = 384;
                }

                if(CardID_Index >= 55)
                {
                    __HAL_TIM_DISABLE(&TIM2_Handler);
                    state = 3;
                    break;
                }
            }
        }

        if(state == 3)
        {
            if(EM4095_UID_Parse(pcardid))
            {
                return GET_ID;
            }
        }
        return NOT_ID;
    }
    return NOT_ID;
}

//==========================================================
//	�������ƣ�	EM4095_Init
//
//	�������ܣ�	EM4095��ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void EM4095_Init(void)
{
    EM4095_IO_Init();
    SET_EM4095_MODE_SLEEP();
    delay_ms(5);
    SET_EM4095_MODE_OPERATION();
    EM4095_MOD_DISABLE();
    delay_ms(5);
}





