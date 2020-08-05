#include "Atmosphere.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "RS485.h"
#include "delay.h"

unsigned  int hum_raw,temp_raw,pres_raw;
signed  int t_fine;

uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;
uint16_t dig_P1;
int16_t dig_P2;
int16_t dig_P3;
int16_t dig_P4;
int16_t dig_P5;
int16_t dig_P6;
int16_t dig_P7;
int16_t dig_P8;
int16_t dig_P9;
int8_t  dig_H1;
int16_t dig_H2;
int8_t  dig_H3;
int16_t dig_H4;
int16_t dig_H5;
int8_t  dig_H6;
//==========================================================
//	�������ƣ�	IIC_Init
//
//	�������ܣ�	IIC��ʼ��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
static void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_Initure;    

	ATMOS_IIC_GPIO_RCC_EN();           				          //IICʱ��

	GPIO_Initure.Pin    = ATMOS_IIC_SDA_GPIO_PIN;				
	GPIO_Initure.Mode   = GPIO_MODE_OUTPUT_PP;				  //�������
	GPIO_Initure.Speed  = GPIO_SPEED_FREQ_LOW; 					//����
	GPIO_Initure.Pull   = GPIO_PULLUP;
	HAL_GPIO_Init(ATMOS_IIC_SDA_GPIO_PORT, &GPIO_Initure);
	
	GPIO_Initure.Pin    = ATMOS_IIC_SCL_GPIO_PIN;				
	GPIO_Initure.Mode   = GPIO_MODE_OUTPUT_PP;				  //�������
	GPIO_Initure.Speed  = GPIO_SPEED_FREQ_LOW; 					//����
	GPIO_Initure.Pull   = GPIO_PULLUP;
	HAL_GPIO_Init(ATMOS_IIC_SCL_GPIO_PORT, &GPIO_Initure);
    
	IIC_SDA(1);	  	  
	IIC_SCL(1);    
}
//==========================================================
//	�������ƣ�	IIC_Start
//
//	�������ܣ�	IIC ����
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����	
//����IIC��ʼ�ź�
//==========================================================
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA(1);	  	  
	IIC_SCL(1);
	delay_us(4);
 	IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}
//==========================================================
//	�������ƣ�	IIC_Stop
//
//	�������ܣ�	IIC ֹͣ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//����IICֹͣ�ź�
//==========================================================
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL(0);
	IIC_SDA(0);
 	delay_us(4); 
	IIC_SCL(1);//STOP:when CLK is high DATA change form low to high
 	delay_us(4); 
	IIC_SDA(1);//����I2C���߽����ź� 						   	
}

//==========================================================
//	�������ƣ�	IIC_Wait_Ack
//
//	�������ܣ�	�ȴ�ACK
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
//==========================================================
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA(1);delay_us(1);	   
	IIC_SCL(1);delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL(0);//ʱ�����0 	   
	return 0;  
}

//==========================================================
//	�������ƣ�	IIC_Ack
//
//	�������ܣ�	ACK
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����	
//����ACKӦ��
//==========================================================
void IIC_Ack(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(0);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}

//==========================================================
//	�������ƣ�	IIC_NAck
//
//	�������ܣ�	NACK
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����	
//������ACKӦ��	
//==========================================================	    
void IIC_NAck(void)
{
	IIC_SCL(0);
	SDA_OUT();
	IIC_SDA(1);
	delay_us(2);
	IIC_SCL(1);
	delay_us(2);
	IIC_SCL(0);
}

//==========================================================
//	�������ƣ�	IIC_Send_Byte
//
//	�������ܣ�	IIC��������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����	
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
//==========================================================			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_OUT(); 	    
    IIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA((txd&0x80)>>7);
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL(1);
		delay_us(2); 
		IIC_SCL(0);	
		delay_us(2);
    }	 
}

//==========================================================
//	�������ƣ�	IIC_Read_Byte
//
//	�������ܣ�	IIC������
//
//	��ڲ�����	ack=1ʱ������ACK��ack=0������nACK 
//
//	���ز�����	��
//
//	˵����	 
//==========================================================	
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
	
  for(i=0;i<8;i++ )
	{
    IIC_SCL(0); 
    delay_us(2);
		IIC_SCL(1);
    receive<<=1;
		if(READ_SDA)
		{
				receive++;
		}
		delay_us(1); 
    }					 
    if (!ack)
    {
        IIC_NAck();//����nACK
    }
    else
    {
        IIC_Ack(); //����ACK   
    }
    return receive;
}


//==========================================================
//	�������ƣ�	AT24CXX_ReadNumBytes
//
//	�������ܣ�	IIC������
//
//	��ڲ�����	uint8_t DevAddr �豸��ַ
//              uint8_t MemAddr �ڴ��ַ
//              uint8_t *pDst   ָ�򱣴��������ָ��
//              uint8_t len     ���ݳ���
//
//����ֵ  :���������� 
//
//	˵����	
//==========================================================	
void AT24CXX_ReadNumBytes(uint8_t DevAddr,uint8_t MemAddr,uint8_t *pDst,uint8_t len)
{				  		  	    																 
    IIC_Start(); 
    IIC_Send_Byte(DevAddr|0);   //����������ַ0XA0,д���� 	   
    if(!IIC_Wait_Ack())
    {
        IIC_Send_Byte(MemAddr);
        IIC_Wait_Ack();        
        IIC_Start(); 
        IIC_Send_Byte(DevAddr|1);           //�������ģʽ			   
        if(!IIC_Wait_Ack())
        {            
            while(len)
            {
                *pDst = IIC_Read_Byte((len>1)?1:0);
                pDst++;
                len--;
            }
        }            
    }       
 
    IIC_Stop();//����һ��ֹͣ����	       
}

//==========================================================
//	�������ƣ�	AT24CXX_WriteSingleBytes
//
//	�������ܣ�	IIC������
//
//	��ڲ�����	uint8_t DevAddr �豸��ַ
//              uint8_t MemAddr �ڴ��ַ
//              uint8_t *pDst   ָ��ȴ�д�������ָ��
//
//  ����ֵ  :���������� 
//
//	˵����	
//==========================================================
void AT24CXX_WriteSingleBytes(uint8_t DevAddr,uint8_t MemAddr,uint8_t *pDst)
{				    	    																 
    IIC_Start(); 
    IIC_Send_Byte(DevAddr|0);   //����������ַ0XA0,д���� 	   
    if(!IIC_Wait_Ack())
    {
        IIC_Send_Byte(MemAddr);	   
        if(!IIC_Wait_Ack())
        {
            IIC_Send_Byte(*pDst);
            IIC_Wait_Ack();
        }             
    }          
    IIC_Stop();//����һ��ֹͣ����	       
}

//==========================================================
//	�������ƣ�	readTrim
//
//	�������ܣ�	����������
//
//	��ڲ�����  ��
//
//  ����ֵ  :   �� 
//
//	˵��		��
//==========================================================
void readTrim(void)
{
    uint8_t data[32];

    AT24CXX_ReadNumBytes(ATMOS_DEVICE_ADDR,0X88,&data[0],24);
    AT24CXX_ReadNumBytes(ATMOS_DEVICE_ADDR,0xA1,&data[24],1);  
    AT24CXX_ReadNumBytes(ATMOS_DEVICE_ADDR,0xE1,&data[25],7);

    dig_T1 = (data[1] << 8) | data[0];
    dig_T2 = (data[3] << 8) | data[2];
    dig_T3 = (data[5] << 8) | data[4];
    dig_P1 = (data[7] << 8) | data[6];
    dig_P2 = (data[9] << 8) | data[8];
    dig_P3 = (data[11]<< 8) | data[10];
    dig_P4 = (data[13]<< 8) | data[12];
    dig_P5 = (data[15]<< 8) | data[14];
    dig_P6 = (data[17]<< 8) | data[16];
    dig_P7 = (data[19]<< 8) | data[18];
    dig_P8 = (data[21]<< 8) | data[20];
    dig_P9 = (data[23]<< 8) | data[22];
    dig_H1 = data[24];
    dig_H2 = (data[26]<< 8) | data[25];
    dig_H3 = data[27];
    dig_H4 = (data[28]<< 4) | (0x0F & data[29]);
    dig_H5 = (data[30] << 4) | ((data[29] >> 4) & 0x0F);
    dig_H6 = data[31];   
}

//==========================================================
//	�������ƣ�	readData
//
//	�������ܣ�	�����¶ȡ�ʪ�ȡ�ѹ��
//
//	��ڲ�����  ��
//
//  ����ֵ  :   �� 
//
//	˵����	
//==========================================================
void readData(uint32_t *pPress,uint32_t *pTemp,uint32_t *pHumi)
{
    uint8_t data[8];
    AT24CXX_ReadNumBytes(ATMOS_DEVICE_ADDR,0xF7,&data[0],8);
    
    *pPress = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
    *pTemp  = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
    *pHumi  = (data[6] << 8) | data[7];
}

//==========================================================
//	�������ƣ�	calibration_T
//
//	�������ܣ�	�ӼĴ��������¶�ֵ
//
//	��ڲ�����  ��
//
//  ����ֵ  :   �� 
//
//	˵����	
//==========================================================
signed  int calibration_T(signed  int adc_T)
{
    signed  int var1, var2, T;
    var1 = ((((adc_T >> 3) - ((signed  int)dig_T1<<1))) * ((signed  int)dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((signed  int)dig_T1)) * ((adc_T>>4) - ((signed  int)dig_T1))) >> 12) * ((signed  int)dig_T3)) >> 14;
    
    t_fine = var1 + var2;
    T = (t_fine * 5 + 128) >> 8;
    return T; 
}

//==========================================================
//	�������ƣ�	calibration_P
//
//	�������ܣ�	�ӼĴ���������ѹ��ֵ
//
//	��ڲ�����  ��
//
//  ����ֵ  :   �� 
//
//	˵����	
//==========================================================
unsigned  int calibration_P(signed  int adc_P)
{
    signed  int var1, var2;
    unsigned  int P;
    var1 = (((signed  int)t_fine)>>1) - (signed  int)64000;
    var2 = (((var1>>2) * (var1>>2)) >> 11) * ((signed  int)dig_P6);
    var2 = var2 + ((var1*((signed  int)dig_P5))<<1);
    var2 = (var2>>2)+(((signed  int)dig_P4)<<16);
    var1 = (((dig_P3 * (((var1>>2)*(var1>>2)) >> 13)) >>3) + ((((signed  int)dig_P2) * var1)>>1))>>18;
    var1 = ((((32768+var1))*((signed  int)dig_P1))>>15);
    if (var1 == 0)
    {
        return 0;
    }    
    P = (((unsigned  int)(((signed  int)1048576)-adc_P)-(var2>>12)))*3125;
    if(P<0x80000000)
    {
       P = (P << 1) / ((unsigned  int) var1);   
    }
    else
    {
        P = (P / (unsigned  int)var1) * 2;    
    }
    var1 = (((signed  int)dig_P9) * ((signed  int)(((P>>3) * (P>>3))>>13)))>>12;
    var2 = (((signed  int)(P>>2)) * ((signed  int)dig_P8))>>13;
    P = (unsigned  int)((signed  int)P + ((var1 + var2 + dig_P7) >> 4));
    return P;
}

//==========================================================
//	�������ƣ�	calibration_H
//
//	�������ܣ�	signed  int adc_H,�ӼĴ���������ʪ��ֵ
//
//	��ڲ�����  ��
//  ����ֵ  :   �� 
//
//	˵����	
//==========================================================
unsigned int calibration_H(signed  int adc_H)
{
    signed  int v_x1;
    
    v_x1 = (t_fine - ((signed  int)76800));
    v_x1 = (((((adc_H << 14) -(((signed  int)dig_H4) << 20) - (((signed  int)dig_H5) * v_x1)) + 
              ((signed  int)16384)) >> 15) * (((((((v_x1 * ((signed  int)dig_H6)) >> 10) * 
              (((v_x1 * ((signed  int)dig_H3)) >> 11) + ((signed  int) 32768))) >> 10) + (( signed  int)2097152)) * 
              ((signed  int) dig_H2) + 8192) >> 14));
   v_x1 = (v_x1 - (((((v_x1 >> 15) * (v_x1 >> 15)) >> 7) * ((signed  int)dig_H1)) >> 4));
   v_x1 = (v_x1 < 0 ? 0 : v_x1);
   v_x1 = (v_x1 > 419430400 ? 419430400 : v_x1);
   return (unsigned  int)(v_x1 >> 12);   
}

//==========================================================
//	�������ƣ�	Atmosphere_GetPress
//
//	�������ܣ�	��ȡѹ��ֵ
//
//	��ڲ�����  ��
//
//  ����ֵ  :   �� 
//
//	˵����	
//==========================================================
float Atmosphere_GetPress(void)
{
    float temp_act = 0.0, press_act = 0.0,hum_act=0.0;
    
    readData(&pres_raw,&temp_raw,&hum_raw);//�ӼĴ��������¶ȡ�ʪ�ȡ�ѹ��
   
    press_act = (float)calibration_P(pres_raw) / 100.0;
    
    return press_act;
}
//==========================================================
//	�������ƣ�	Atmosphere_Init
//
//	�������ܣ�	��ʼ��IIC
//
//	��ڲ�����  ��
//
//  ����ֵ  :   �� 
//
//	˵����	
//==========================================================
void Atmosphere_Init(void)
{
    uint8_t osrs_t = 1;             //Temperature oversampling x 1
    uint8_t osrs_p = 1;             //Pressure oversampling x 1
    uint8_t osrs_h = 1;             //Humidity oversampling x 1
    uint8_t mode = 3;               //Normal mode
    uint8_t t_sb = 5;               //Tstandby 1000ms
    uint8_t filter = 0;             //Filter off 
    uint8_t spi3w_en = 0;           //3-wire SPI Disable

    uint8_t ctrl_meas_reg = (osrs_t << 5) | (osrs_p << 2) | mode;
    uint8_t config_reg    = (t_sb << 5) | (filter << 2) | spi3w_en;
    uint8_t ctrl_hum_reg  = osrs_h; 

    IIC_Init(); //��ʼ��IIC
    
    AT24CXX_WriteSingleBytes(ATMOS_DEVICE_ADDR,0xF2,&ctrl_hum_reg);
    AT24CXX_WriteSingleBytes(ATMOS_DEVICE_ADDR,0xF4,&ctrl_meas_reg);
    AT24CXX_WriteSingleBytes(ATMOS_DEVICE_ADDR,0xF5,&config_reg);    
    
    readTrim(); //��ȡ����ֵ 
}

//==========================================================
//	�������ƣ�	Atmosphere_TestFunc
//
//	�������ܣ�	���Գ���
//
//	��ڲ�����  ��
//
//  ����ֵ  :   �� 
//
//	˵����			
//==========================================================
float temp_act = 0.0, press_act = 0.0,hum_act=0.0;
uint8_t Atmosphere_TestFunc(void)
{
		uint8_t A_P[10];//����ѹ��ֵ

    readData(&pres_raw,&temp_raw,&hum_raw);//�ӼĴ��������¶ȡ�ʪ�ȡ�ѹ��

    temp_act  = (float)calibration_T(temp_raw) / 100.0;
    press_act = (float)calibration_P(pres_raw) / 100.0;
    hum_act   = (float)calibration_H(hum_raw) / 1024.0;

		A_P[0] = (uint16_t)press_act>>8;	//����ѹ������
		A_P[1] = (uint16_t)press_act;			//����ѹ������
	
    printf("TEMP : %fDegC\r\n",temp_act);
    printf("PRESS : %fhPa\r\n",press_act);
    printf(" HUM :%f\r\n ",hum_act);      

		if(!DataHandling_485(Addr_A_P))		//����485����
		{
			Rs485_Send(Addr_A_P,Rx_Stack.Src_Adr,A_P_Altitude,2,A_P);		//���ʹ���ѹ��ֵ
			memset(A_P,0,10);
		}

		return 1;
}




























