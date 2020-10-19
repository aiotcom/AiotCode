#include "SHT20.h"
#include "IIC.h"

SHT2x_PARAM g_sht2x_param;

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
    u8 tmp1, tmp2;
    u16 ST;
    
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
    u8 tmp1, tmp2;    
    u16 SRH;

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
    u8 ack, tmp1, tmp2;
    u16 ST;
    
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
    u8 ack, tmp1, tmp2;    
    u16 SRH;
    
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
void SHT2x_GetSerialNumber(u8 *buf)
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

//    g_sht2x_param.TEMP_POLL = SHT2x_MeasureTempPoll();              //������ģʽ�µ��¶�����
//    g_sht2x_param.HUMI_POLL = SHT2x_MeasureHumiPoll();	      //������ģʽ�µ�ʪ������
//    
//    SHT2x_GetSerialNumber(g_sht2x_param.SerialNumber);	      //���к�
}
