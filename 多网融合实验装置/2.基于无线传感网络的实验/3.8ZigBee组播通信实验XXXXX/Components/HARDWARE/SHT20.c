#include "SHT20.h"
#include "TM1640.h"
#include <ioCC2530.h>
#include "OLED.h"
SHT2x_PARAM g_sht2x_param;
//==========================================================
//	�������ƣ�	IIC_Delay
//
//	�������ܣ�	IIC��ʱ����
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================

static void IIC_Delay(uint32 n)
{
  while(0);
}

//==========================================================
//	�������ƣ�	SHT20_IIC_Init
//
//	�������ܣ�	��ʼ��IIC
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void SHT20_IIC_Init(void)
{
    P0SEL &= ~0x03;     //����P0.0��P0.1Ϊ��ͨIO��  
    P0DIR |= 0x03;      //P0.0��P0.1����Ϊ���
}

//==========================================================
//	�������ƣ�	IIC_SCL_OUTPUT
//
//	�������ܣ�	IICʱ�������ģʽ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void IIC_SCL_OUTPUT(void)
{
    P0SEL &= ~0x02;     //����P0.1Ϊ��ͨIO��  
    P0DIR |= 0x02;      //P0.1����Ϊ���
}

//==========================================================
//	�������ƣ�	IIC_SCL_INPUT
//
//	�������ܣ�	IICʱ��������ģʽ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void IIC_SCL_INPUT(void)
{
    P0SEL &= ~0x02;     //����P0.1Ϊ��ͨIO��  
    P0DIR &= ~0x02;     //��������P0.6���ϣ���P0.6Ϊ����ģʽ 
    P0INP &= ~0x02;     //��P0.1��������
}

//==========================================================
//	�������ƣ�	IIC_SDA_OUTPUT
//
//	�������ܣ�	IIC���������ģʽ 
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void IIC_SDA_OUTPUT(void)
{
    P0SEL &= ~0x01;     //����P0.0Ϊ��ͨIO��  
    P0DIR |= 0x01;      //P0.0����Ϊ���
}
//==========================================================
//	�������ƣ�	IIC_SDA_INPUT
//
//	�������ܣ�	IIC����������ģʽ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void IIC_SDA_INPUT(void)
{
    P0SEL &= ~0x01;     //����P0.0Ϊ��ͨIO��  
    P0DIR &= ~0x01;     //��������P0.0���ϣ���P0.7Ϊ����ģʽ 
    P0INP &= ~0x01;     //��P0.0��������
}
//==========================================================
//	�������ƣ�	IIC_Start
//
//	�������ܣ�	IIC����ʱ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void IIC_Start(void)
{
    IIC_SDA_OUTPUT();	//ʱ�������ģʽ
    IIC_SCL_OUTPUT();	//���������ģʽ
    SDA_HIGH();		//����������
    SCL_HIGH();		//����ʱ����
    SDA_LOW();		//����������			
    SCL_LOW();		//����ʱ����
}
//==========================================================
//	�������ƣ�	IIC_Stop
//
//	�������ܣ�	IICֹͣʱ�� 
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void IIC_Stop(void)
{
    IIC_SDA_OUTPUT();
    IIC_SCL_OUTPUT();
    SCL_LOW();
    SDA_LOW();
    SCL_HIGH();
    SDA_HIGH();
}

//==========================================================
//	�������ƣ�	IIC_Wait_Ack
//
//	�������ܣ�	�ȴ�Ӧ���źŵ���
//
//	��ڲ�����	��
//
//	���ز�����	����ֵ��1������Ӧ��ʧ��
//        							0������Ӧ��ɹ�
//
//	˵����		
//==========================================================
//static uint8 IIC_Wait_Ack(void)
//{
//    uint8 Time=0;
//    IIC_SCL_OUTPUT();
//    IIC_SDA_OUTPUT();
//    SDA_HIGH();
//    SCL_HIGH();
//    IIC_SDA_INPUT();
//    while(SDA_STATE())
//    {
//      Time++;
//      if(Time>250)
//      {
//        IIC_Stop();
//        return 1;
//      }
//    }
//    SCL_LOW();
//    return 0;
//}
//==========================================================
//	�������ƣ�	IIC_Ack
//
//	�������ܣ�	IIC ACKӦ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void IIC_Ack(void)
{
    IIC_SCL_OUTPUT();
    SCL_LOW();
    IIC_SDA_OUTPUT();
    SDA_LOW();
    SCL_HIGH();
    SCL_LOW();
}

//==========================================================
//	�������ƣ�	IIC_NAck
//
//	�������ܣ�	IIC ��ACKӦ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void IIC_NAck(void)
{
    IIC_SCL_OUTPUT();
    SCL_LOW();
    IIC_SDA_OUTPUT();
    SDA_HIGH();
    SCL_HIGH();
    SCL_LOW();
}
//==========================================================
//	�������ƣ�	IIC_Read_Byte
//
//	�������ܣ�	IIC ��ȡ����
//
//	��ڲ�����	ack:�Ƿ���ACK
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static uint8 IIC_Read_Byte(uint8 ack)
{
    uint8 i,receive=0;
    IIC_SDA_INPUT();
    IIC_SCL_OUTPUT();
    for(i=0;i<8;i++)
    {
        SCL_LOW();
        SCL_HIGH();
        receive<<=1;
        if(SDA_STATE())receive++;
    }
    if(!ack) IIC_NAck();
    else IIC_Ack();
    return receive;
}


//==========================================================
//	�������ƣ�	Write_IIC_Byte
//
//	�������ܣ�	IIC д������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static uint8 Write_IIC_Byte(uint8 byte)
{
    uint8 i, ack;

    IIC_SCL_OUTPUT();
    IIC_SDA_OUTPUT();		//����Ϊ���ģʽ
    
    for(i = 0; i < 8; i++)
    {
        if(byte & 0x80)         //һ�ζ�ȡ���λ ��������
        {
            SDA_HIGH();
        }
        else 
        {
            SDA_LOW();
        }
        
        SCL_HIGH();  		//ʱ��������
        SCL_LOW();   		//ʱ��������
        
        byte <<= 1;
    }

    IIC_SDA_INPUT();  	        //����������ģʽ
    
    SCL_HIGH();			//ʱ��������
    
    if(Bit_SET == SDA_STATE())  //������ܵ������߸��ź�  ACK����
    {
        ack = ACK_ERROR;
    }
    else
    {
        ack = ACK_OK;
    }
    
    SCL_LOW();          //����ʱ����

    IIC_SDA_OUTPUT();	

    SDA_HIGH();		//����������
    
    return (ack);
}
//==========================================================
//	�������ƣ�	SHT2x_I2cReadByte
//
//	�������ܣ�	IIC ��ȡ����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
uint8 SHT2x_I2cReadByte(void)
{
    uint8 i, val = 0;

    IIC_SCL_OUTPUT();  		    //����Ϊ���ģʽ
    IIC_SDA_OUTPUT();

    SDA_HIGH();			    //����������
    
    IIC_SDA_INPUT();		    //����������Ϊ����ģʽ
        
    for(i = 0; i < 8; i++)
    {
        val <<= 1; 
        
        SCL_HIGH();  	 	    //����ʱ����
        
        if(Bit_SET == SDA_STATE())  //��������߱�����
        {
            val |= 0x01;	    //��ȡ�������е�����
        }
        
        SCL_LOW();      	    //����ʱ����
    }

    IIC_SDA_OUTPUT();  		    //���������ģʽ

    SDA_HIGH();			    //����������
    
    return (val);		    //���ض�ȡ��������
}
////==========================================================
////	�������ƣ�	IIC_Send_Byte
////
////	�������ܣ�	IIC д������
////
////	��ڲ�����	txd:д������
////
////	���ز�����	��
////
////	˵����		
////==========================================================
//static void IIC_Send_Byte(uint8 txd)
//{
//    uint8 t;
//    IIC_SCL_OUTPUT();
//    IIC_SDA_OUTPUT();
//    SCL_LOW();
//    for(t=0;t<8;t++)
//    {
//        if(txd & 0x80)
//        {
//            SDA_HIGH();
//        }
//        else 
//        {
//            SDA_LOW();
//        }
//        
//        SCL_HIGH();
//        SCL_LOW();
//        txd<<=1;
//    }
//}

//==========================================================
//	�������ƣ�	SHT2x_MeasureTempHM
//
//	�������ܣ�	����ģʽ�¶ȶ�ȡ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
float SHT2x_MeasureTempHM(void)
{
    float TEMP;
    uint8 tmp1, tmp2;
    uint16 ST;
    
    IIC_SCL_OUTPUT();  					//ʱ��������Ϊ���ģʽ
     
    IIC_Start();    					//����IIC����״̬                       
    Write_IIC_Byte(I2C_ADR_W);				//д��0x80 ��ʾ��ʼд����
    Write_IIC_Byte(TRIG_TEMP_MEASUREMENT_HM); 		//����ģʽ����¶�
  
    IIC_Start();					//����IIC����״̬      
    Write_IIC_Byte(I2C_ADR_R);				//д��0x81 ��ʾ��ʼ������

    SCL_HIGH();   					//����ʱ����

    IIC_SCL_INPUT();					//����Ϊ����ģʽ

    while(Bit_RESET == SCL_STATE())  			//�����ʱ���߱��õ�
    {
        IIC_Delay(20);
    }
    
    tmp1 = SHT2x_I2cReadByte();                         //��ȡ����
    IIC_Ack();						//ACKӦ��
    tmp2 = SHT2x_I2cReadByte();     	                //��ȡ����
    IIC_NAck();						//��Ӧ��
    IIC_Stop();						//�ر�IIC
    
    ST = (tmp1 << 8) | (tmp2 << 0);
    ST &= ~0x0003;
    TEMP = ((float)ST * 0.00268127) - 46.85;  //ת�����õ�������

    IIC_SCL_OUTPUT();  			      //ʱ�������

    return (TEMP);	    		      //�����¶�ֵ
}

//==========================================================
//	�������ƣ�	SHT2x_MeasureHumiHM
//
//	�������ܣ�	����ģʽʪ�ȶ�ȡ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
float SHT2x_MeasureHumiHM(void)
{
    float HUMI;
    uint8 tmp1, tmp2;    
    uint16 SRH;

    IIC_SCL_OUTPUT();
    
    IIC_Start();                               
    Write_IIC_Byte(I2C_ADR_W);
    Write_IIC_Byte(TRIG_HUMI_MEASUREMENT_HM);

    IIC_Start();
    Write_IIC_Byte(I2C_ADR_R);

    SCL_HIGH();

    IIC_SCL_INPUT();

    while(Bit_RESET == SCL_STATE())
    {
        IIC_Delay(20);
    }
    
    tmp1 = SHT2x_I2cReadByte();
    IIC_Ack();
    tmp2 = SHT2x_I2cReadByte();
    IIC_NAck();
    IIC_Stop();
    
    SRH = (tmp1 << 8) | (tmp2 << 0);
    SRH &= ~0x0003;
    HUMI = ((float)SRH * 0.00190735) - 6;

    IIC_SCL_OUTPUT();

    return (HUMI);
}

//==========================================================
//	�������ƣ�	SHT2x_MeasureTempPoll
//
//	�������ܣ�	������ģʽ�¶ȶ�ȡ 
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
float SHT2x_MeasureTempPoll(void)
{
    float TEMP;
    uint8 ack, tmp1, tmp2;
    uint16 ST;
    
    IIC_Start();                            
    Write_IIC_Byte(I2C_ADR_W);
    Write_IIC_Byte(TRIG_TEMP_MEASUREMENT_POLL);

    do {
        IIC_Delay(20);               
        IIC_Start();
        ack = Write_IIC_Byte(I2C_ADR_R);
    } while(ACK_ERROR == ack);
    
    tmp1 = SHT2x_I2cReadByte();
    IIC_Ack();
    tmp2 = SHT2x_I2cReadByte();
    IIC_NAck();
    IIC_Stop();
    
    ST = (tmp1 << 8) | (tmp2 << 0);
    ST &= ~0x0003;
    TEMP = ((float)ST * 0.00268127) - 46.85;

    return (TEMP);	  
}

//==========================================================
//	�������ƣ�	SHT2x_MeasureHumiPoll
//
//	�������ܣ�	������ģʽʪ�ȶ�ȡ 
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
float SHT2x_MeasureHumiPoll(void)
{
    float HUMI;
    uint8 ack, tmp1, tmp2;    
    uint16 SRH;
    
    IIC_Start();                               
    Write_IIC_Byte(I2C_ADR_W);
    Write_IIC_Byte(TRIG_HUMI_MEASUREMENT_POLL);
    
    do {
        IIC_Delay(20);
        IIC_Start();
        ack = Write_IIC_Byte(I2C_ADR_R);
    } while(ACK_ERROR == ack);
    
    tmp1 = SHT2x_I2cReadByte();
    IIC_Ack();
    tmp2 = SHT2x_I2cReadByte();
    IIC_NAck();
    IIC_Stop();
    
    SRH = (tmp1 << 8) | (tmp2 << 0);
    SRH &= ~0x0003;
    HUMI = ((float)SRH * 0.00190735) - 6;

    return (HUMI);
}

//==========================================================
//	�������ƣ�	SHT2x_GetSerialNumber
//
//	�������ܣ�	���к�
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_GetSerialNumber(uint8 *buf)
{
    /* Read from memory location 1 */
    IIC_Start();
    Write_IIC_Byte(I2C_ADR_W);	                //I2C address
    Write_IIC_Byte(0xFA); 			//Command for readout on-chip memory
    Write_IIC_Byte(0x0F); 			//on-chip memory address
    IIC_Start();
    Write_IIC_Byte(I2C_ADR_R);	                //I2C address
    buf[5] = SHT2x_I2cReadByte();               //Read SNB_3
    IIC_Ack();
    SHT2x_I2cReadByte(); 			//Read CRC SNB_3 (CRC is not analyzed)
    IIC_Ack();
    buf[4] = SHT2x_I2cReadByte(); 	        //Read SNB_2
    IIC_Ack();
    IIC_Read_Byte(0); 				//Read CRC SNB_2 (CRC is not analyzed)
    IIC_Ack();
    buf[3] = SHT2x_I2cReadByte(); 	        //Read SNB_1
    IIC_Ack();
    SHT2x_I2cReadByte(); 			//Read CRC SNB_1 (CRC is not analyzed)
    IIC_Ack();
    buf[2] = SHT2x_I2cReadByte(); 	        //Read SNB_0
    IIC_Ack();
    SHT2x_I2cReadByte(); 			//Read CRC SNB_0 (CRC is not analyzed)
    IIC_Ack();
    IIC_Stop();

    /* Read from memory location 2 */
    IIC_Start();
    Write_IIC_Byte(I2C_ADR_W); 	                //I2C address
    Write_IIC_Byte(0xFC); 			//Command for readout on-chip memory
    Write_IIC_Byte(0xC9); 			//on-chip memory address
    IIC_Start();
    Write_IIC_Byte(I2C_ADR_R); 	                //I2C address
    buf[1] = SHT2x_I2cReadByte(); 	        //Read SNC_1
    IIC_Ack();
    buf[0] = SHT2x_I2cReadByte(); 	        //Read SNC_0
    IIC_Ack();
    IIC_Read_Byte(0); 			        //Read CRC SNC0/1 (CRC is not analyzed)
    IIC_Ack();
    buf[7] = SHT2x_I2cReadByte(); 	        //Read SNA_1
    IIC_Ack();
    buf[6] = SHT2x_I2cReadByte(); 	        //Read SNA_0
    IIC_Ack();
    SHT2x_I2cReadByte(); 			//Read CRC SNA0/1 (CRC is not analyzed)
    IIC_NAck();
    IIC_Stop();
}

//==========================================================
//	�������ƣ�	SHT2x_GetTempHumi
//
//	�������ܣ�	�õ������� 
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_GetTempHumi(void)
{   
    g_sht2x_param.TEMP_HM = SHT2x_MeasureTempHM();			//����ģʽ�µ��¶�����
    g_sht2x_param.HUMI_HM = SHT2x_MeasureHumiHM(); 			//����ģʽ�µ�ʪ������
}
//==========================================================
//	�������ƣ�	SHT2x_GetHumi
//
//	�������ܣ�	�����¶�ֵ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
uint8 SHT2x_GetTemp(void)
{
  return (uint8)g_sht2x_param.TEMP_HM;
}
//==========================================================
//	�������ƣ�	SHT2x_ReadTemp
//
//	�������ܣ�	��SHT20��ȡ�¶�ֵ����ʾ�����ݹ���
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_ReadTemp(void)
{
    g_sht2x_param.TEMP_HM = SHT2x_MeasureTempHM();	
    send_LED_Display(0xc0,(uint8)g_sht2x_param.TEMP_HM,1);    
}
//==========================================================
//	�������ƣ�	SHT2x_GetHumi
//
//	�������ܣ�	����ʪ��ֵ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
uint8 SHT2x_GetHumi(void)
{
  return (uint8)g_sht2x_param.HUMI_HM;
}
//==========================================================
//	�������ƣ�	SHT2x_ReadHumi
//
//	�������ܣ�	��SHT20��ȡʪ��ֵ����ʾ�����ݹ���
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_ReadHumi(void)
{
    g_sht2x_param.HUMI_HM = SHT2x_MeasureHumiHM();	
    send_LED_Display(0xc0,(uint8)g_sht2x_param.HUMI_HM,2);     
}
//==========================================================
//	�������ƣ�	SHT2x_Init
//
//	�������ܣ�	SHT20��ʼ��
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SHT2x_Init(void)
{
  SHT20_IIC_Init();
  TM1640_Init();
  SHT2x_GetTempHumi();
}