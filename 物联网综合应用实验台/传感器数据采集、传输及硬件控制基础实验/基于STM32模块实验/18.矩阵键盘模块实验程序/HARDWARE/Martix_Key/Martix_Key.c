#include "Martix_Key.h"	
#include "Rs485.h"
#include "delay.h"

//==========================================================
//	�������ƣ�	KEY_Init
//
//	�������ܣ�	��ʼ������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����			
//==========================================================
void KEY_Init(void)
{
	  GPIO_InitTypeDef GPIO_Initure;

		/* GPIO Ports Clock Enable */
		__HAL_RCC_GPIOA_CLK_ENABLE();			//����GPIOAʱ��

		GPIO_Initure.Pin = WKEY_1_PIN|WKEY_2_PIN|WKEY_3_PIN|WKEY_Right_PIN;		//PA4��PA5��PA6��PA7
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;//�������
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; //����
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);

		GPIO_Initure.Pin = RKEY_Right_PIN|RKEY_Left_PIN|RKEY_Up_PIN|RKEY_Down_PIN;
		GPIO_Initure.Mode = GPIO_MODE_INPUT;   	//��������
		GPIO_Initure.Pull = GPIO_PULLUP;				//����
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);

		WKEY_All_Low();	//PA4��5��6��7��0
}

//==========================================================
//	�������ƣ�	KEY_ConFig
//
//	�������ܣ�	���հ�������
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
uint16_t Key_value;	//��Ű���ֵ

void KEY_ConFig(void)
{
	static uint8_t cnt = 0; //��������

	switch(cnt%4){
    case 0:
      {
        WKEY_All_Hight();	//�����ȫ������
        WKEY_1_Low();			//������һ�飨Enter��1��4��7�����
/*
*				key 7 push down		
*/
        if(!RKEY_Up_Read())
				{
					delay_ms(5);  						//��ʱ����	
					if(!RKEY_Up_Read())
					{
						Key_value = Matrixkey7;	//����7
						while(!RKEY_Up_Read());
					}
/*
*				key 4 push down
*/
        }
				else if(!RKEY_Down_Read())
				{
					delay_ms(5);  						//��ʱ����
					if(!RKEY_Down_Read())
					{
						Key_value = Matrixkey4;	//����4
						while(!RKEY_Down_Read());
					}
/*
*				key 1 push down
*/					
        }
				else if(!RKEY_Left_Read())
				{
					delay_ms(5);  						//��ʱ����				
					if(!RKEY_Left_Read())
					{
						Key_value = Matrixkey1;	//����1
						while(!RKEY_Left_Read());
					}
/*
*				key Enter push down
*/		
        }
				else if(!RKEY_Right_Read())
				{  
					delay_ms(5);  						//��ʱ����
					if(!RKEY_Right_Read())
					{
						Key_value = MatrixkeyEnter;	//����Enter
						while(!RKEY_Right_Read());
					}
        }
        else
				{
					
				}        
        break;
      }
    case 1:
      {
        WKEY_All_Hight();	//�����ȫ������
        WKEY_2_Low();			//�����ڶ��飨0��2��5��8�����
/*
*				key 8 push down
*/	
        if(!RKEY_Up_Read())
				{        
					delay_ms(5);  						//��ʱ����				
					if(!RKEY_Up_Read())
					{
						Key_value = Matrixkey8;	//����8
						while(!RKEY_Up_Read());
					}					
/*
*				key 5 push down
*/		
        }
				else if(!RKEY_Down_Read())
				{
					delay_ms(5);  						//��ʱ����
					if(!RKEY_Down_Read())
					{
						Key_value = Matrixkey5;	//����5
						while(!RKEY_Down_Read());	
					}			
/*
*				key 2 push down
*/		
        }
        else if(!RKEY_Left_Read())
        {
					delay_ms(5);  						//��ʱ����	
					if(!RKEY_Left_Read())
					{
						Key_value = Matrixkey2;	//����2
						while(!RKEY_Left_Read());
					}			
 /*
*				key 0 push down
*/	         
        }
				else if(!RKEY_Right_Read())
				{
					delay_ms(5);  						//��ʱ����			
					if(!RKEY_Right_Read())
					{
						Key_value = Matrixkey0;	//����0
						while(!RKEY_Right_Read());
					}
        }
        else
        {
        }
        break;
      }
    case 2:
      {
        WKEY_All_Hight();	//�����ȫ������
        WKEY_3_Low();			//���������飨Canel��3��6��9�����	
 /*
*				key 9 push down
*/	    
        if(!RKEY_Up_Read())
				{ 
					delay_ms(5);  						//��ʱ����					
					if(!RKEY_Up_Read())
					{
						Key_value = Matrixkey9;	//����9
						while(!RKEY_Up_Read());
					}			
 /*
*				key 6 push down
*/	          
        }
				else if(!RKEY_Down_Read())
				{    
					delay_ms(5);  						//��ʱ����		
					if(!RKEY_Down_Read())
					{
						Key_value = Matrixkey6;	//����6
						while(!RKEY_Down_Read());
					}				
 /*
*				key 3 push down
*/	 	
        }
				else if(!RKEY_Left_Read())
				{
					delay_ms(5);  						//��ʱ����
					if(!RKEY_Left_Read())
					{
						Key_value = Matrixkey3;	//����3
						while(!RKEY_Left_Read());
					}
 /*
*				key Canel push down
*/	           
        }
				else if(!RKEY_Right_Read())
				{
					delay_ms(5);  						//��ʱ����
					if(!RKEY_Right_Read())
					{
						Key_value = MatrixkeyCanel;	//����Canel
						while(!RKEY_Right_Read());
					}
        }
				else
				{
					
        }
        
        break;
      }
    case 3:
      {
        WKEY_All_Hight();	//�����ȫ������
        WKEY_Right_Low();	//������Right�飨Right��Left��Down��UP�����	
 /*
*				key up push down
*/	  
        if(!RKEY_Up_Read())
				{
					delay_ms(5);  						//��ʱ����
					if(!RKEY_Up_Read())
					{
						Key_value = MatrixkeyUP;	//����up
						while(!RKEY_Up_Read());
					}
 /*
*				key down push down
*/	            
        }else if(!RKEY_Down_Read()){
					delay_ms(5);  						//��ʱ����	
					if(!RKEY_Down_Read())
					{
						Key_value = MatrixkeyDown;	//����down
						while(!RKEY_Down_Read());
					}	
 /*
*				key left push down
*/	  
        }
				else if(!RKEY_Left_Read())
				{
					delay_ms(5);  						//��ʱ����	
					if(!RKEY_Left_Read())
					{
						Key_value = MatrixkeyLeft;	//����left
						while(!RKEY_Left_Read());
					} 
 /*
*				key right push down
*/	  					
        }
				else if(!RKEY_Right_Read())
				{
					delay_ms(5);  						//��ʱ����				
					if(!RKEY_Right_Read())
					{
						Key_value = MatrixkeyRight;	//����right
						while(!RKEY_Right_Read());				
					}					
        }
				else
				{
					
        }
        break;
      }
    }
	
    cnt++;   			//�����ۼ�
}

    





