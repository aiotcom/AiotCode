#include "stdlib.h"
#include "Rs485.h"
#include "delay.h"
#include "TFT.h"
																			//***���������β�ͬ��ԭ��Ĭ�ϵ�У׼����ֵ���ܻ�������ʶ��׼������У׼����ʹ�ã�������ʹ�ù̶���Ĭ��У׼����
u16 vx=15242,vy=11131;  							//�������ӣ���ֵ����1000֮���ʾ���ٸ�ADֵ����һ�����ص�
u16 chx=3898,chy=145;									//Ĭ�����ص�����Ϊ0ʱ��AD��ʼֵ
																			//***���������β�ͬ��ԭ��Ĭ�ϵ�У׼����ֵ���ܻ�������ʶ��׼������У׼����ʹ�ã�������ʹ�ù̶���Ĭ��У׼����

struct tp_pix_  tp_pixad,tp_pixlcd;	 	//��ǰ���������ADֵ,ǰ�������������ֵ   

uint8_t touch_fig = 0;								//�Ӵ���ɱ�־λ
uint8_t ffiigg = 0;										//У׼��ɱ�־λ
uint32_t px = 0,py = 0;								//��Ż�ȡ����������Ϣ		

u16 BACK_COLOR, POINT_COLOR;   				//����ɫ������ɫ	  

//==========================================================
//	�������ƣ�	TFT_Init
//
//	�������ܣ�	TFT��ʾ���˿ڳ�ʼ��
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void TFT_Init(void)
{
		GPIO_InitTypeDef GPIO_Initure;

		__HAL_RCC_GPIOA_CLK_ENABLE();           	//����GPIOAʱ��
		__HAL_RCC_GPIOG_CLK_ENABLE();           	//����GPIOGʱ��	

		GPIO_Initure.Pin=GPIO_PIN_12;    					//PG12
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW;	//����
		GPIO_Initure.Mode =  GPIO_MODE_OUTPUT_PP;	//�������
		GPIO_Initure.Pull = GPIO_PULLDOWN;
		HAL_GPIO_Init(GPIOG,&GPIO_Initure);
	
		//TFT��ʾ��ģ��
		GPIO_Initure.Pin = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_0;   //TFT_CS,TFT_RST,TFT_CLK,
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW;	//����
		GPIO_Initure.Mode =  GPIO_MODE_OUTPUT_PP;	//�������
		GPIO_Initure.Pull = GPIO_PULLDOWN;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);

		GPIO_Initure.Pin=GPIO_PIN_3;    					//PA3
		GPIO_Initure.Mode=GPIO_MODE_INPUT;      	//����
		GPIO_Initure.Pull=GPIO_NOPULL;         		//����
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     	//����
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);

		GPIO_Initure.Pin = GPIO_PIN_10;  //TFT_DC
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_Initure.Pull = GPIO_PULLDOWN;
		HAL_GPIO_Init(GPIOG,&GPIO_Initure);

		GPIO_Initure.Pin = GPIO_PIN_11;  //T_CS
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_Initure.Pull = GPIO_PULLDOWN;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);

		GPIO_Initure.Pin=GPIO_PIN_12;    				//PA12
		GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
		GPIO_Initure.Pull=GPIO_PULLDOWN;        //����
		GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);
}

//==========================================================
//	�������ƣ�	LCD_Writ_Bus
//
//	�������ܣ�	��������д��
//
//	��ڲ�����	da:��Ҫд�������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void  LCD_Writ_Bus(char da)
{
	 static char i;
	 for(i=0;i<8;i++)
	 {
		 if(da &0x80)
		 {
			 LCD_SDI_H;
		 }
		 else LCD_SDI_L;
		 LCD_SCK_L;
		 LCD_SCK_H;
		 da <<=1;
	 }	
}

//==========================================================
//	�������ƣ�	LCD_WR_DATA8
//
//	�������ܣ�	��������-8λ����
//
//	��ڲ�����	da:��Ҫд�������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_WR_DATA8(char da) //��������-8λ����
{
  LCD_DC_H;
	LCD_Writ_Bus(da);
}  

//==========================================================
//	�������ƣ�	LCD_WR_DATA
//
//	�������ܣ�	�������ݲ���
//
//	��ڲ�����	da:��Ҫд�������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_WR_DATA(int da)
{
  LCD_DC_H;
	LCD_Writ_Bus(da>>8);
	LCD_Writ_Bus(da);
}	  

//==========================================================
//	�������ƣ�	LCD_WR_REG
//
//	�������ܣ�	REG����д��
//
//	��ڲ�����	da:��Ҫд�������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_WR_REG(char da)	 
{
  LCD_DC_L;
	LCD_Writ_Bus(da);
}

//==========================================================
//	�������ƣ�	LCD_WR_REG_DATA
//
//	�������ܣ�	REG����д��
//
//	��ڲ�����	da:��Ҫд�������
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
 void LCD_WR_REG_DATA(int reg,int da)
{
  LCD_WR_REG(reg);
	LCD_WR_DATA(da);
}

//==========================================================
//	�������ƣ�	Address_set
//
//	�������ܣ�	REG����д��
//
//	��ڲ�����	x1,y1,x2,y2Ϊ�����
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{  
   LCD_WR_REG(0x2a);
   LCD_WR_DATA8(x1>>8);
   LCD_WR_DATA8(x1);
   LCD_WR_DATA8(x2>>8);
   LCD_WR_DATA8(x2);
  
   LCD_WR_REG(0x2b);
   LCD_WR_DATA8(y1>>8);
   LCD_WR_DATA8(y1);
   LCD_WR_DATA8(y2>>8);
   LCD_WR_DATA8(y2);

   LCD_WR_REG(0x2C);

}

//==========================================================
//	�������ƣ�	Lcd_Init
//
//	�������ܣ�	TFT�Ĵ�����ʼ��
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void Lcd_Init(void)
{

//����һ����Щ��������ñ����ʱ����ʾ����
//   	LCD_CS_H;
// 	if(LCD_CS==0)
// 	{
// 	   LCD_WR_REG_DATA(0,0);
// 	   LCD_ShowString(0,0," ");
// 	   LCD_ShowNum(0,0,0,0);
// 	   LCD_Show2Num(0,0,0,0);
// 	   LCD_DrawPoint_big(0,0);
// 	   LCD_DrawRectangle(0,0,0,0);
// 	   Draw_Circle(0,0,0);
//  	 }    
	LCD_REST_L;
	delay_ms(10);
	LCD_REST_H;
	delay_ms(10);
	LCD_CS_L;  //��Ƭѡʹ��

	LCD_WR_REG(0xCB);  
	LCD_WR_DATA8(0x39); 
	LCD_WR_DATA8(0x2C); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x34); 
	LCD_WR_DATA8(0x02); 

	LCD_WR_REG(0xCF);  
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0XC1); 
	LCD_WR_DATA8(0X30); 
 	
	LCD_WR_REG(0xE8);  
	LCD_WR_DATA8(0x85); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x78); 

	LCD_WR_REG(0xEA);  
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x00); 
 	
	LCD_WR_REG(0xED);  
	LCD_WR_DATA8(0x64); 
	LCD_WR_DATA8(0x03); 
	LCD_WR_DATA8(0X12); 
	LCD_WR_DATA8(0X81); 

	LCD_WR_REG(0xF7);  
	LCD_WR_DATA8(0x20); 
 
	LCD_WR_REG(0xC0);    	//Power control 
	LCD_WR_DATA8(0x23);   //VRH[5:0] 
 
	LCD_WR_REG(0xC1);    	//Power control 
	LCD_WR_DATA8(0x10);   //SAP[2:0];BT[3:0] 

	LCD_WR_REG(0xC5);    	//VCM control 
	LCD_WR_DATA8(0x3e); 	//�Աȶȵ���
	LCD_WR_DATA8(0x28); 

	LCD_WR_REG(0xC7);    	//VCM control2 
	LCD_WR_DATA8(0x86); 	//--

	LCD_WR_REG(0x36);    	// Memory Access Control 
	LCD_WR_DATA8(0x48); 	//	   //48 68����//28 E8 ����

	LCD_WR_REG(0x3A);    
	LCD_WR_DATA8(0x55); 

	LCD_WR_REG(0xB1);    
	LCD_WR_DATA8(0x00);  
	LCD_WR_DATA8(0x18); 

	LCD_WR_REG(0xB6);    // Display Function Control 
	LCD_WR_DATA8(0x08); 
	LCD_WR_DATA8(0x82);
	LCD_WR_DATA8(0x27);  
 	
	LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
	LCD_WR_DATA8(0x00); 
 	
	LCD_WR_REG(0x26);    //Gamma curve selected 
	LCD_WR_DATA8(0x01); 
 
 	LCD_WR_REG(0xE0);    //Set Gamma 
	LCD_WR_DATA8(0x0F); 
	LCD_WR_DATA8(0x31); 
	LCD_WR_DATA8(0x2B); 
	LCD_WR_DATA8(0x0C); 
	LCD_WR_DATA8(0x0E); 
	LCD_WR_DATA8(0x08); 
	LCD_WR_DATA8(0x4E); 
	LCD_WR_DATA8(0xF1); 
	LCD_WR_DATA8(0x37); 
	LCD_WR_DATA8(0x07); 
	LCD_WR_DATA8(0x10); 
	LCD_WR_DATA8(0x03); 
	LCD_WR_DATA8(0x0E); 
	LCD_WR_DATA8(0x09); 
	LCD_WR_DATA8(0x00); 

	LCD_WR_REG(0XE1);    //Set Gamma 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x0E); 
	LCD_WR_DATA8(0x14); 
	LCD_WR_DATA8(0x03); 
	LCD_WR_DATA8(0x11); 
	LCD_WR_DATA8(0x07); 
	LCD_WR_DATA8(0x31); 
	LCD_WR_DATA8(0xC1); 
	LCD_WR_DATA8(0x48); 
	LCD_WR_DATA8(0x08); 
	LCD_WR_DATA8(0x0F); 
	LCD_WR_DATA8(0x0C); 
	LCD_WR_DATA8(0x31); 
	LCD_WR_DATA8(0x36); 
	LCD_WR_DATA8(0x0F); 
 
	LCD_WR_REG(0x2A);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xEF);

	LCD_WR_REG(0x2B);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x3F);
	LCD_WR_REG(0x11);    	//Exit Sleep 
	delay_ms(60); 
			
  LCD_WR_REG(0x29);    	//Display on 
  LCD_WR_REG(0x2c); 
  BACK_COLOR=WHITE; 		//����TFTҺ������ɫ
  POINT_COLOR=RED;  		//����TFTҺ��ǰ��ɫ
}

//==========================================================
//	�������ƣ�	LCD_Clear
//
//	�������ܣ�	��������
//
//	��ڲ�����	Color:Ҫ���������ɫ
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_Clear(u16 Color)
{
	u8 VH,VL;
	u16 i,j;
	VH=Color>>8;
	VL=Color;	
	Address_set(0,0,LCD_W-1,LCD_H-1);
	for(i=0;i<LCD_W;i++)
	 {
		for (j=0;j<LCD_H;j++)
			{
					LCD_WR_DATA8(VH);
					LCD_WR_DATA8(VL);	
			}
		}
}

//==========================================================
//	�������ƣ�	LCD_DrawPoint
//
//	�������ܣ�	����
//
//	��ڲ�����	λ�ù��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_DrawPoint(u16 x,u16 y)
{
	Address_set(x,y,x,y);//���ù��λ�� 
	LCD_WR_DATA(POINT_COLOR); 	    
} 	 

//==========================================================
//	�������ƣ�	LCD_DrawPoint_big
//
//	�������ܣ�	��һ�����
//
//	��ڲ�����	λ�ù��
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_DrawPoint_big(u16 x,u16 y)
{
	LCD_Fill(x-1,y-1,x+1,y+1,POINT_COLOR);
} 

//  (xend-xsta)*(yend-ysta)
//==========================================================
//	�������ƣ�	LCD_Fill
//
//	�������ܣ�	��ָ�����������ָ����ɫ
//
//	��ڲ�����	�����С: (xend-xsta)*(yend-ysta)
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	Address_set(xsta,ysta,xend,yend);      //���ù��λ�� 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)LCD_WR_DATA(color);//���ù��λ�� 	    
	} 					  	    
}  

//==========================================================
//	�������ƣ�	LCD_DrawLine
//
//	�������ܣ�	����
//
//	��ڲ�����	x1,y1:�������
//              x2,y2:�յ�����  
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    

//==========================================================
//	�������ƣ�	LCD_DrawRectangle
//
//	�������ܣ�	������
//
//	��ڲ�����	�����С: (x2-x1)*(y2-y1)
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

//==========================================================
//	�������ƣ�	Draw_Circle
//
//	�������ܣ�	��ָ��λ�û�һ��ָ����С��Բ
//
//	��ڲ�����	(x,y):���ĵ�
//              r    :�뾶
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a);             //3           
		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0-a,y0+b);             //1       
		LCD_DrawPoint(x0-b,y0-a);             //7           
		LCD_DrawPoint(x0-a,y0-b);             //2             
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0-b);             //5
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-b,y0+a);             
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		LCD_DrawPoint(x0+a,y0+b);
	}
} 

//==========================================================
//	�������ƣ�	LCD_ShowChar
//
//	�������ܣ�	��ָ��λ����ʾһ���ַ�
//
//	��ڲ�����	(x,y):��ʾ����
//              num:Ҫ��ʾ���ַ�:" "--->"~"
//              mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 mode)
{
    u8 temp;
    u8 pos,t;
	u16 x0=x;
	u16 colortemp=POINT_COLOR;      
    if(x>LCD_W-16||y>LCD_H-16)return;	    
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	Address_set(x,y,x+8-1,y+16-1);      //���ù��λ�� 
	if(!mode) //�ǵ��ӷ�ʽ
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=asc2_1608[(u16)num*16+pos];		 //����1608����
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_WR_DATA(POINT_COLOR);	
				temp>>=1; 
				x++;
		    }
			x=x0;
			y++;
		}	
	}else//���ӷ�ʽ
	{
		for(pos=0;pos<16;pos++)
		{
		    temp=asc2_1608[(u16)num*16+pos];		 //����1608����
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)LCD_DrawPoint(x+t,y+pos);//��һ����     
		        temp>>=1; 
		    }
		}
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   
//m^n����
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 

//==========================================================
//	�������ƣ�	LCD_ShowNum
//
//	�������ܣ�	��ʾ�������
//
//	��ڲ�����	x,y :�������	 
//              len :���ֵ�λ��
//              num:��ֵ(0~4294967295);
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len)
{         	
	u8 t,temp;
	u8 enshow=0;
	num=(u32)num;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+8*t,y,' ',0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+8*t,y,temp+48,0); 
	}
} 

//==========================================================
//	�������ƣ�	LCD_Show2Num
//
//	�������ܣ�	��ʾ2������
//
//	��ڲ�����	x,y :�������	 
//              len :���ֵ�λ��
//              num:��ֵ(0~99);
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void LCD_Show2Num(u16 x,u16 y,u16 num,u8 len)
{         	
	u8 t,temp;						   
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
	 	LCD_ShowChar(x+8*t,y,temp+'0',0); 
	}
} 

//==========================================================
//	�������ƣ�	LCD_ShowString
//
//	�������ܣ�	��ʾ�ַ���
//
//	��ڲ�����	x,y:�������  
//              *p:�ַ�����ʼ��ַ
//							mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
//              
//	���ز�����	��
//
//	˵����	    ��16����	
//==========================================================
void LCD_ShowString(u16 x,u16 y,const u8 *p,u8 mode)
{
    while(*p!='\0')
    {       
        if(x>LCD_W-16){x=0;y+=16;}
        if(y>LCD_H-16){y=x=0;}
        LCD_ShowChar(x,y,*p,mode);
        x+=8;
        p++;
    } 
}

//==========================================================
//	�������ƣ�	Drow_Touch_Point
//
//	�������ܣ�	��LCD�����йصĺ���  
//
//	��ڲ�����	x,y:�������  
//              
//	���ز�����	��
//
//	˵����	   	����У׼�õ�
//==========================================================
void Drow_Touch_Point(u16 x,u16 y)
{
	LCD_DrawLine(x-12,y,x+13,y);//����
	LCD_DrawLine(x,y-12,x,y+13);//����
	LCD_DrawPoint(x+1,y+1);
	LCD_DrawPoint(x-1,y+1);
	LCD_DrawPoint(x+1,y-1);
	LCD_DrawPoint(x-1,y-1);
	Draw_Circle(x,y,6);//������Ȧ
}	
u16 ReadFromCharFrom7843()             //SPI ������
{
	u8 count=0;
	u16 Num=0;
	for(count=0;count<12;count++)
	{
		Num<<=1;		
		LCD_SCK_H;               //�½�����Ч
		LCD_SCK_L; 
		if(T_OUT)
		{
			Num|=1;
		}
	}

return(Num);
}
//��7846/7843/XPT2046/UH7843/UH7846��ȡadcֵ	  0x90=y   0xd0-x
u16 ADS_Read_AD(unsigned char CMD)          
{
    u16 l;
    T_CS_L;     
    LCD_Writ_Bus(CMD);//�Ϳ����ּ��ò�ַ�ʽ��X���� ��ϸ����й�����
    LCD_SCK_H;
    LCD_SCK_L;
    l=ReadFromCharFrom7843();
    T_CS_H;
    return l;
}	

//==========================================================
//	�������ƣ�	ADS_Read_XY
//
//	�������ܣ�	��ȡһ������ֵ
//
//	��ڲ�����	 
//              
//	���ز�����	��
//
//	˵����	   	������ȡREAD_TIMES������,����Щ������������,
//							Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ 
//==========================================================
#define READ_TIMES 15 //��ȡ����
#define LOST_VAL 5	  //����ֵ
u16 ADS_Read_XY(u8 xy)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)
	{				 
		buf[i]=ADS_Read_AD(xy);	    
	}				    
	for(i=0;i<READ_TIMES-1; i++)//����
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 

//==========================================================
//	�������ƣ�	Read_ADS
//
//	�������ܣ�	���˲��������ȡ
//
//	��ڲ�����	 
//              
//	���ز�����	��
//
//	˵����	   	��Сֵ��������100.
//==========================================================
u8 Read_ADS(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=ADS_Read_XY(CMD_RDX);
	ytemp=ADS_Read_XY(CMD_RDY);	 									   
	if(xtemp<100||ytemp<100)return 0;//����ʧ��
	*x=xtemp;
	*y=ytemp;
	return 1;//�����ɹ�
}

//==========================================================
//	�������ƣ�	Read_ADS2
//
//	�������ܣ�	2�ζ�ȡADS7846,������ȡ2����Ч��ADֵ,�������ε�ƫ��ܳ���
//
//	��ڲ�����	 
//              
//	���ز�����	��
//
//	˵����	   	�ú����ܴ�����׼ȷ��
//==========================================================
#define ERR_RANGE 20 //��Χ 
u8 Read_ADS2(u16 *x,u16 *y)
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=Read_ADS(&x1,&y1);   
    if(flag==0)return(0);
    flag=Read_ADS(&x2,&y2);	
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-ERR_RANGE��
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)>>1;
        *y=(y1+y2)>>1;		
        return 1;
    }else return 0;	  
}

//==========================================================
//	�������ƣ�	Read_TP_Once
//
//	�������ܣ�	��ȷ��ȡһ������,У׼��ʱ���õ�	 
//
//	��ڲ�����	
//              
//	���ز�����	��
//
//	˵����	   	
//==========================================================
u8 Read_TP_Once(void)
{
	u8 re=0;
	u16 x1,y1;
	while(re==0)
	{
		while(!Read_ADS2(&tp_pixad.x,&tp_pixad.y));
		delay_us(300);
		while(!Read_ADS2(&x1,&y1));
		if(tp_pixad.x==x1&&tp_pixad.y==y1)
		{
			re=1; 
		}
	}
	return re;
}

//==========================================================
//	�������ƣ�	Fan_Status_Display
//
//	�������ܣ�	��ʾ����״̬ͼ��
//
//	��ڲ�����	�����С: (xend-xsta)*(yend-ysta)
//							color:	��ɫ
//              Gears:	���ȵ�λ
//
//	���ز�����	��
//
//	˵����	  	
//==========================================================
void Fan_Status_Display(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color,uint8_t Gears)
{
		LCD_Fill(xsta,ysta,xend,yend,color);	//130,158,190,182
		POINT_COLOR = BLACK;									//������ɫ
		switch(Gears)
		{
			case 0:		//���ȹر�״̬
				LCD_ShowString((xsta+(xend-xsta)/3),(ysta+2),"OFF",1);
				break;
			case 1:		//����һ��״̬
				LCD_ShowString((xsta+(xend-xsta)/3),(ysta+2),"One",1); 
				break;
			case 2:		//���ȶ���״̬
				LCD_ShowString((xsta+(xend-xsta)/3),(ysta+2),"Two",1); 
				break;
			case 3:		//��������״̬
				LCD_ShowString((xsta+(xend-xsta)/6),(ysta+2),"Three",1); 
				break;	
			default:	break;
		}
}

//==========================================================
//	�������ƣ�	Fan_Gears
//
//	�������ܣ�	���ȵ�λ��ʾ
//
//	��ڲ�����	Gears�����ȵ�λ����
//									0: ���ȹر�״̬
//									1: ���ȴ���һ��
//									2: ���ȴ��ڶ���
//									3: ���ȴ�������
//              
//	���ز�����	��
//
//	˵����			
//==========================================================
void Fan_Gears(uint8_t Gears)
{
	switch(Gears)
	{
		case 0:		
			Fan_Status_Display(125,78,175,98,RED,0);		//���ȹر�״̬
			break;
		case 1:		
			Fan_Status_Display(125,78,175,98,GREEN,1);	//����һ��״̬
			break;
		case 2:		
			Fan_Status_Display(125,78,175,98,GREEN,2);	//���ȶ���״̬
			break;
		case 3:		
			Fan_Status_Display(125,78,175,98,GREEN,3);	//��������״̬
			break;	
		default:	break;
	}
}

//==========================================================
//	�������ƣ�	TFT_UI
//
//	�������ܣ�	TFT����������
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����			
//==========================================================
void TFT_UI(void)
{
	LCD_Clear(DARKBLUE);									//����
	POINT_COLOR = WHITE;									//������ɫ
	LCD_ShowString(30,30,"Fan Control Experiment",1); //���ȿ���ʵ��
	LCD_ShowString(30,80,"Fan State:",1);	//����״̬
	Fan_Gears(0);		//��ʼ����ʾ���ȹر�
	POINT_COLOR = WHITE;									//������ɫ
	LCD_ShowString(30,130,"Fan Gear Adjustment",1);	//���ȵ�λ����
	Fan_Status_Display(30,158,80,178,LGRAY,1);			//����һ��״̬
	Fan_Status_Display(90,158,140,178,LGRAY,2);			//���ȶ���״̬
	Fan_Status_Display(150,158,200,178,LGRAY,3);		//��������״̬
	
	LCD_Fill(35,220,95,249,BROWN);				//ON��ť
	LCD_Fill(135,220,195,249,BROWN);			//OFF��ť
	LCD_ShowString(58,226,"ON          OFF",1);			//���ط���
}

//==========================================================
//	�������ƣ�	Key_Handler
//
//	�������ܣ�	������������
//
//	��ڲ�����	��
//              
//	���ز�����	��
//
//	˵����			
//==========================================================
void Key_Handler(void)
{
		static uint8_t Gear_Flag = 0;
	
		/*
		*
		*					���ݴ���
		*
		*/
		if(touch_fig)
		{
				if(Read_TP_Once())	//�õ����ΰ���ֵ
				{
						px=tp_pixad.x;
						py=tp_pixad.y;
				}
			
				if(px>2751 && px<3486 && py>1937 && py<2153)				//����"One"
				{
						Gear_Flag = 1;
						Fan_Status_Display(30,158,80,178,GREEN,1);			//����һ��״̬
						Fan_Status_Display(90,158,140,178,LGRAY,2);			//���ȶ���״̬
						Fan_Status_Display(150,158,200,178,LGRAY,3);		//��������״̬
				}
				else if(px>1775 && px<2495 && py>1937 && py<2153)		//����"Two"
				{
						Gear_Flag = 2;
						Fan_Status_Display(90,158,140,178,GREEN,2);			//���ȶ���״̬
						Fan_Status_Display(30,158,80,178,LGRAY,1);			//����һ��״̬
						Fan_Status_Display(150,158,200,178,LGRAY,3);		//��������״̬
				}
				else if(px>873 && px<1562 && py>1937 && py<2153)		//����"Three"
				{
						Gear_Flag = 3;
						Fan_Status_Display(150,158,200,178,GREEN,3);		//��������״̬
						Fan_Status_Display(30,158,80,178,LGRAY,1);			//����һ��״̬
						Fan_Status_Display(90,158,140,178,LGRAY,2);			//���ȶ���״̬
				}
				else if(px>2471 && px<3359 && py>2629 && py<2944)		//����"ON"
				{
						switch(Gear_Flag)
						{
							case 0:
								Fan_Gears(0);																//��ʾ����״̬�ر�
								Rs485_Send(Addr_LCD,Addr_Fan,FAN_OFF,0,0); //�رշ���
								break;
							case 1:
								Fan_Gears(1);																//��ʾ����״̬1��
								Rs485_Send(Addr_LCD,Addr_Fan,FAN_ON1,0,0); //�򿪷���-1��
								break;
							case 2:
								Fan_Gears(2);																//��ʾ����״̬2��
								Rs485_Send(Addr_LCD,Addr_Fan,FAN_ON2,0,0); //�򿪷���-2��
								break;
							case 3:
								Fan_Gears(3);																//��ʾ����״̬3��
								Rs485_Send(Addr_LCD,Addr_Fan,FAN_ON3,0,0); //�򿪷���-3��
								break;
							default: break;
						}
						Gear_Flag = 0;
						Fan_Status_Display(30,158,80,178,LGRAY,1);			//����һ��״̬
						Fan_Status_Display(90,158,140,178,LGRAY,2);			//���ȶ���״̬
						Fan_Status_Display(150,158,200,178,LGRAY,3);		//��������״̬
						LCD_Fill(35,220,95,249,GREEN);									//ON��ť
						LCD_Fill(135,220,195,249,BROWN);								//OFF��ť
						LCD_ShowString(58,226,"ON          OFF",1);			//���ط���
				}
				else if(px>905 && px<1800 && py>2629 && py<2944)		//����"OFF"
				{
						Gear_Flag = 0;
						Fan_Gears(0);																		//��ʾ����״̬�ر�
						Rs485_Send(Addr_LCD,Addr_Fan,FAN_OFF,0,0); 			//�رշ���
						Fan_Status_Display(30,158,80,178,LGRAY,1);			//����һ��״̬
						Fan_Status_Display(90,158,140,178,LGRAY,2);			//���ȶ���״̬
						Fan_Status_Display(150,158,200,178,LGRAY,3);		//��������״̬
						LCD_Fill(135,220,195,249,GREEN);								//OFF��ť
						LCD_Fill(35,220,95,249,BROWN);									//ON��ť
						LCD_ShowString(58,226,"ON          OFF",1);			//���ط���
				}
				touch_fig = 0;
		}
}







