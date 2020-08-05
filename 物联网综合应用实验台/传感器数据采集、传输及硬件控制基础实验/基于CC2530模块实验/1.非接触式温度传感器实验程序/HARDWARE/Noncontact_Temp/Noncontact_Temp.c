#include "Noncontact_Temp.h"	
#include "delay.h"

//==========================================================
//	�������ƣ�	MLX90615_init()
//
//	�������ܣ�	��ʼ��MLX90615
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void MLX90615_init(void)
{
    mlx_gpio_init();  //IO�ڳ�ʼ��
    mlx_SDA_OUT();    //����Ϊ���ģʽ
    mlx_SCL_HIGH();
    mlx_SDA_HIGH();
}

//==========================================================
//	�������ƣ�	mlx_gpio_init()
//
//	�������ܣ�	��ʼ��IO��
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void mlx_gpio_init(void)
{
    P0SEL &= ~0x03;     //����P0.0��P0.1Ϊ��ͨIO��  
    P0DIR |= 0x03;      //P0.0��P0.1����Ϊ���
}

//==========================================================
//	�������ƣ�	mlx_SCL_OUTPUT()
//
//	�������ܣ�	IICʱ�������ģʽ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void mlx_SCL_OUTPUT(void)
{
    P0SEL &= ~0x01;     //����P0.0Ϊ��ͨIO��  
    P0DIR |= 0x01;      //P0.0����Ϊ���
}

//==========================================================
//	�������ƣ�	mlx_SCL_INPUT()
//
//	�������ܣ�	IICʱ��������ģʽ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void mlx_SCL_INPUT(void)
{
    P0SEL &= ~0x01;     //����P0.0Ϊ��ͨIO��  
    P0DIR &= ~0x01;     //��������P0.0���ϣ���P0.7Ϊ����ģʽ 
    P0INP &= ~0x01;     //��P0.0��������
}

//==========================================================
//	�������ƣ�	mlx_SDA_OUT()
//
//	�������ܣ�	IIC���������ģʽ 
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void mlx_SDA_OUT(void)
{
    P0SEL &= ~0x02;     //����P0.1Ϊ��ͨIO��  
    P0DIR |= 0x02;      //P0.1����Ϊ���
}

//==========================================================
//	�������ƣ�	mlx_SDA_IN()
//
//	�������ܣ�	IIC����������ģʽ
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void mlx_SDA_IN(void)
{
    P0SEL &= ~0x02;     //����P0.1Ϊ��ͨIO��  
    P0DIR &= ~0x02;     //��������P0.6���ϣ���P0.6Ϊ����ģʽ 
    P0INP &= ~0x02;     //��P0.1��������
}

//==========================================================
//	�������ƣ�	start_bit()
//
//	�������ܣ�	IIC  ��ʼʱ��
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void START_bit(void)
{	
    mlx_SDA_OUT();
    mlx_SDA_HIGH();
    delay_us(5);
    mlx_SCL_HIGH();
    delay_us(5);
    
    mlx_SDA_LOW();
    delay_us(4);
    mlx_SCL_LOW();
    delay_us(5);
}

//==========================================================
//	�������ƣ�	stop_bit()
//
//	�������ܣ�	IIC  ֹͣʱ��
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void STOP_bit(void)
{	
    mlx_SDA_OUT();
    mlx_SCL_LOW();
    delay_us(5);
    mlx_SDA_LOW();
    delay_us(5);
    mlx_SCL_HIGH();
    delay_us(5);
    mlx_SDA_HIGH();
}

//==========================================================
//	�������ƣ�	TX_byte()
//
//	�������ܣ�	IIC��������
//
//	��ڲ�����	Tx_buffer������
//
//	���ز�����	��
//
//	˵����			
//==========================================================
unsigned char TX_byte(unsigned char Tx_buffer)
{
    unsigned char	Bit_counter;
    unsigned char	Ack_bit;
    unsigned char	bit_out;

    for(Bit_counter=8; Bit_counter; Bit_counter--)
    {
      if(Tx_buffer&0x80) 
        bit_out=1; // If the current bit of Tx_buffer is 1 set bit_out
      else			   
        bit_out=0; // else clear bit_out
            
      send_bit(bit_out);	// Send the current bit on SDA
      Tx_buffer<<=1;	// Get next bit for checking
    }

    Ack_bit=Receive_bit();// Get acknowledgment bit

    return	
      Ack_bit;
}// End of TX_bite()

//==========================================================
//	�������ƣ�	send_bit()
//
//	�������ܣ�	IIC д������ʱ��
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void send_bit(unsigned char bit_out)
{       
    mlx_SDA_OUT();
    if(bit_out) 
    {
      mlx_SDA_HIGH();	
    }
    else	
    {
      mlx_SDA_LOW();
    }
    delay_us(1);
    mlx_SCL_HIGH();
    delay_us(5);
    mlx_SCL_LOW();
    delay_us(5);

    return;
}//End of send_bit()

//==========================================================
//	�������ƣ�	Receive_bit()
//
//	�������ܣ�	IIC ��ȡ����ʱ��
//
//	��ڲ�����	ʱ��
//
//	���ز�����	��
//
//	˵����
//==========================================================
unsigned char Receive_bit(void)
{
    unsigned char Ack_bit;
    
    mlx_SDA_IN();	
    delay_us(3);
    mlx_SCL_HIGH();
    delay_us(1);
    if(mlx_SDA_State())
       Ack_bit=1;
    else
       Ack_bit=0;
    mlx_SCL_LOW();	
    delay_us(1);	
    return	
      Ack_bit;
}//End of Receive_bit

//==========================================================
//	�������ƣ�	RX_byte()
//
//	�������ܣ�	IIC ��ȡ����
//
//	��ڲ�����	ack_nack: unsigned char ack_nack (acknowledgment bit)
//							0 - Master device sends ACK
//							1 - Master device sends NACK
//
//	���ز�����	��
//
//	˵����			
//==========================================================
unsigned char RX_byte(unsigned char ack_nack)
{
    unsigned char   RX_buffer=0;
    unsigned char   Bit_Counter;
    
    for(Bit_Counter=8; Bit_Counter; Bit_Counter--)
    {
        if(Receive_bit())	// Get a bit from the SDA line
        {
            RX_buffer <<= 1;	// If the bit is HIGH save 1  in RX_buffer
            RX_buffer |=0x01;
        }
        else
        {
            RX_buffer <<= 1;	// If the bit is LOW save 0 in RX_buffer 
            RX_buffer &=0xfe;	
        }
    }
    
    send_bit(ack_nack);		// Sends acknowledgment bit
    
    return RX_buffer;
}

//==========================================================
//	�������ƣ�	MemRead()
//
//	�������ܣ�	�ӿ��/EEPROM��ȡ����
//
//	��ڲ�����	SlaveAddress����ȡ��ַ
//							command:����
//
//	���ز�����	�¶�ֵ
//
//	˵����			
//==========================================================
unsigned int MemRead(unsigned char SlaveAddress,unsigned char command)
{
    unsigned int  data;			// Data storage (DataH:DataL)
    unsigned char Pec;			// PEC byte storage
    unsigned char DataL;		// Low data byte storage
    unsigned char DataH;		// High data byte storage
    unsigned char arr[6];		// Buffer for the sent bytes
    unsigned char PecReg;		// Calculated PEC byte storage
    unsigned char ErrorCounter;		// Defines the number of the attempts for communication with MLX90614

    ErrorCounter=0x00;			// Initialising of ErrorCounter

    do{
    repeat:
        STOP_bit();			//If slave send NACK stop comunication	
        --ErrorCounter;			//Pre-decrement ErrorCounter
        if(!ErrorCounter){	        //ErrorCounter=0?
            //printf("break 1\r\n");
            break;			//Yes,go out from do-while{}
        }
        START_bit();			//Start condition

        if(TX_byte(SlaveAddress)){	//Send SlaveAddress
            //printf("repeat 1\r\n");
            goto	repeat;		//Repeat comunication again
        }

        if(TX_byte(command)){		//Send command	
            //printf("repeat 2\r\n");
            goto	repeat;		//Repeat comunication again
        }
        START_bit();			//Repeated Start condition

        if(TX_byte(SlaveAddress)){      //Send SlaveAddress-------------------???
            //printf("repeat 3\r\n");
            goto	repeat;         //Repeat comunication again
        }

        DataL=RX_byte(ACK);		//Read low data,master must send ACK
        DataH=RX_byte(ACK); 		//Read high data,master must send ACK
        Pec=RX_byte(NACK);		//Read PEC byte, master must send NACK
        STOP_bit();			//Stop condition

        arr[5]=SlaveAddress;		//
        arr[4]=command;			//
        arr[3]=SlaveAddress;		//Load array arr 
        arr[2]=DataL;			//
        arr[1]=DataH;			//
        arr[0]=0;			//
        PecReg=PEC_calculation(arr);    //Calculate CRC
        
        //printf("DataL:%d\tDataH:%d\r\n",DataL,DataH);
                
    }while(PecReg != Pec);		//If received and calculated CRC are equal go out from do-while{}
    
    *((unsigned char *)(&data))=DataL;	 // 
    *((unsigned char *)(&data)+1)=DataH ;//data=DataH:DataL
    
    return data;							
}

//==========================================================
//	�������ƣ�	SendRequest()
//
//	�������ܣ�	���͸�λ
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void SendRequest(void)
{
    mlx_SCL_LOW();	//SCL 1 ____________|<-----80ms------->|______________
    delay_ms(80);	// 	  0	            |__________________|
    mlx_SCL_HIGH();
}

//==========================================================
//	�������ƣ�	DummyCommand()
//
//	�������ܣ�	��������
//
//	��ڲ�����	byte:����
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void DummyCommand(unsigned char byte)
{
    START_bit();	//Start condition
    TX_byte(byte);	//Send Slave Address or whatever,no need ACK checking
    STOP_bit();	        //Stop condition
}

//==========================================================
//	�������ƣ�	CalcTemp()
//
//	�������ܣ�	�¶�ֵ����
//
//	��ڲ�����	value:ֵ
//
//	���ز�����	��
//
//	˵����		
//==========================================================
float CalcTemp(unsigned int value)
{
    float temp;
    
    temp=(value*0.02)-273.15;
//       _NOP();
    delay_us(1);
    return temp;
}

//==========================================================
//	�������ƣ�	PEC_calculation()
//
//	�������ܣ�	����PEC��
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
unsigned char PEC_calculation(unsigned char pec[])
{
    unsigned char 	crc[6];
    unsigned char	BitPosition=47;
    unsigned char	shift;
    unsigned char	i;
    unsigned char	j;
    unsigned char	temp;

    do{
        crc[5]=0;	/* Load CRC value 0x000000000107 */
        crc[4]=0;
        crc[3]=0;
        crc[2]=0;
        crc[1]=0x01;
        crc[0]=0x07;
        BitPosition=47;	/* Set maximum bit position at 47 */
        shift=0;
                        
        //Find first 1 in the transmited message
        i=5;		/* Set highest index */
        j=0;
        while((pec[i]&(0x80>>j))==0 && i>0){
            BitPosition--;
            if(j<7){
                    j++;
            }
            else{
                    j=0x00;
                    i--;
            }
        }/*End of while */
        
        shift=BitPosition-8;	/*Get shift value for crc value*/
        
        
        //Shift crc value 
        while(shift){
            for(i=5; i<0xFF; i--){
                    if((crc[i-1]&0x80) && (i>0)){
                            temp=1;
                    }
                    else{
                            temp=0;
                    }
                    crc[i]<<=1;
                    crc[i]+=temp;
            }/*End of for*/
            shift--;
        }/*End of while*/
        
        
        //Exclusive OR between pec and crc		
        for(i=0; i<=5; i++){
                pec[i] ^=crc[i];
        }/*End of for*/
    }while(BitPosition>8);/*End of do-while*/
    
    return pec[0];
}/*End of PEC_calculation*/





