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
		__HAL_RCC_GPIOB_CLK_ENABLE();			//����GPIOBʱ��
	
		GPIO_Initure.Pin = GPIO_PIN_0|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;		//PA0��PA4��PA5��PA6��PA7
		GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;//�������
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_LOW; //����
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);
	
	  /*Configure GPIO pins : PB0 PB1 PB13 PB14 */
		GPIO_Initure.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_13|GPIO_PIN_14;
		GPIO_Initure.Mode = GPIO_MODE_INPUT;   	//��������
		GPIO_Initure.Pull = GPIO_PULLUP;				//����
		HAL_GPIO_Init(GPIOB, &GPIO_Initure);
	
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);	//PA0
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_RESET);	//PA4��5��6��7��0
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
	static uint8_t cnt = 0;  				//��������
	
	switch(cnt%4){
    case 0:
      {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);			
/*
*				key 7 push down		
*/
        if(!B0_Read())
				{
					delay_ms(5);  						//��ʱ����	
					if(!B0_Read())
					{
						Key_value = Matrixkey7;	//����7
						while(!B0_Read())
						{
							LED2_ON();						//LED2��	
						}
					}
/*
*				key 4 push down
*/
        }
				else if(!B1_Read())
				{
					delay_ms(5);  						//��ʱ����
					if(!B1_Read())
					{
						Key_value = Matrixkey4;	//����4	Rs485_Send(Addr_Matrixkey,Addr_TFT,Matrixkey4,0,"");	//485���͵�TFTģ��
						while(!B1_Read())
						{
							LED2_ON();						//LED2��
						}	
					}				
/*
*				key 1 push down
*/					
        }
				else if(!B13_Read())
				{
					delay_ms(5);  						//��ʱ����				
					if(!B13_Read())
					{
						Key_value = Matrixkey1;	//����1	Rs485_Send(Addr_Matrixkey,Addr_TFT,Matrixkey1,0,"");	//485���͵�TFTģ��
						while(!B13_Read())
						{
							LED2_ON();						//LED2��
						}	
					}	
/*
*				key Enter push down
*/		
        }
				else if(!B14_Read())
				{  
					delay_ms(5);  						//��ʱ����					
					if(!B14_Read())
					{
						Key_value = MatrixkeyEnter;	//����Enter	Rs485_Send(Addr_Matrixkey,Addr_TFT,MatrixkeyEnter,0,"");	//485���͵�TFTģ��
						while(!B14_Read())
						{
							LED2_ON();						//LED2��
						}		
					}
        }
        else
				{
					
				}        
        break;
      }
    case 1:
      {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET);			
/*
*				key 8 push down
*/	
        if(!B0_Read())
				{        
					delay_ms(5);  						//��ʱ����				
					if(!B0_Read())
					{
						Key_value = Matrixkey8;	//����8	Rs485_Send(Addr_Matrixkey,Addr_TFT,Matrixkey8,0,"");	//485���͵�TFTģ��
						while(!B0_Read())
						{
							LED2_ON();					//LED2��
						}	
					}					
/*
*				key 5 push down
*/		
        }
				else if(!B1_Read())
				{
					delay_ms(5);  						//��ʱ����
					if(!B1_Read())
					{
						Key_value = Matrixkey5;	//����5	Rs485_Send(Addr_Matrixkey,Addr_TFT,Matrixkey5,0,"");	//485���͵�TFTģ��
						while(!B1_Read())
						{
							LED2_ON();						//LED2��
						}		
					}			
/*
*				key 2 push down
*/		
        }
        else if(!B13_Read())
        {
					delay_ms(5);  						//��ʱ����	
					if(!B13_Read())
					{
						Key_value = Matrixkey2;	//����2	Rs485_Send(Addr_Matrixkey,Addr_TFT,Matrixkey2,0,"");	//485���͵�TFTģ��
						while(!B13_Read())
						{
							LED2_ON();						//LED2��
						}	
					}			
 /*
*				key 0 push down
*/	         
        }
				else if(!B14_Read())
				{
					delay_ms(5);  						//��ʱ����			
					if(!B14_Read())
					{
						Key_value = Matrixkey0;	//����0	Rs485_Send(Addr_Matrixkey,Addr_TFT,Matrixkey0,0,"");	//485���͵�TFTģ��
						while(!B14_Read())
						{
							LED2_ON();						//LED2��
						}	
					}
        }
        else
        {
        }
        break;
      }
    case 2:
      {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_RESET);			
 /*
*				key 9 push down
*/	    
        if(!B0_Read())
				{ 
					delay_ms(5);  						//��ʱ����					
					if(!B0_Read())
					{
						Key_value = Matrixkey9;	//����9	Rs485_Send(Addr_Matrixkey,Addr_TFT,Matrixkey9,0,"");	//485���͵�TFTģ��
						while(!B0_Read())
						{
							LED2_ON();						//LED2��
						}	
					}			
 /*
*				key 6 push down
*/	          
        }
				else if(!B1_Read())
				{    
					delay_ms(5);  						//��ʱ����		
					if(!B1_Read())
					{
						Key_value = Matrixkey6;	//����6	Rs485_Send(Addr_Matrixkey,Addr_TFT,Matrixkey6,0,"");	//485���͵�TFTģ��
						while(!B1_Read())
						{
							LED2_ON();						//LED2��	
						}	
					}				
 /*
*				key 3 push down
*/	 	
        }
				else if(!B13_Read())
				{
					delay_ms(5);  						//��ʱ����
					if(!B13_Read())
					{
						Key_value = Matrixkey3;	//����3	Rs485_Send(Addr_Matrixkey,Addr_TFT,Matrixkey3,0,"");	//485���͵�TFTģ��
						while(!B13_Read())
						{
							LED2_ON();						//LED2��
						}	
					}
 /*
*				key Canel push down
*/	           
        }
				else if(!B14_Read())
				{
					delay_ms(5);  						//��ʱ����
					if(!B14_Read())
					{
						Key_value = MatrixkeyCanel;	//����Canel	Rs485_Send(Addr_Matrixkey,Addr_TFT,MatrixkeyCanel,0,"");	//485���͵�TFTģ��
						while(!B14_Read())
						{
							LED2_ON();						//LED2��	
						}	
					}
        }
				else
				{
					
        }
        
        break;
      }
    case 3:
      {
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
 /*
*				key up push down
*/	  
        if(!B0_Read())
				{
					delay_ms(5);  						//��ʱ����
					if(!B0_Read())
					{
						Key_value = MatrixkeyUP;	//����up //Rs485_Send(Addr_Matrixkey,Addr_TFT,MatrixkeyUP,0,"");	//485���͵�TFTģ��
						while(!B0_Read())
						{
							LED2_ON();						//LED2��
						}	
					}
 /*
*				key down push down
*/	            
        }else if(!B1_Read()){
					delay_ms(5);  						//��ʱ����	
					if(!B1_Read())
					{
						Key_value = MatrixkeyDown;	//����down //Rs485_Send(Addr_Matrixkey,Addr_TFT,MatrixkeyDown,0,"");	//485���͵�TFTģ��
						while(!B1_Read())
						{
							LED2_ON();						//LED2��		
						}	
					}	
 /*
*				key left push down
*/	  
        }
				else if(!B13_Read())
				{
					delay_ms(5);  						//��ʱ����	
					if(!B13_Read())
					{
						Key_value = MatrixkeyLeft;	//����left //Rs485_Send(Addr_Matrixkey,Addr_TFT,MatrixkeyLeft,0,"");	//485���͵�TFTģ��
						while(!B13_Read())
						{
							LED2_ON();						//LED2��
						}	
					} 
 /*
*				key right push down
*/	  					
        }
				else if(!B14_Read())
				{
					delay_ms(5);  						//��ʱ����				
					if(!B14_Read())
					{
						Key_value = MatrixkeyRight;	//����right //Rs485_Send(Addr_Matrixkey,Addr_TFT,MatrixkeyRight,0,"");	//485���͵�TFTģ��
						while(!B14_Read())
						{
							LED2_ON();						//LED2��
						}						
					}					
        }
				else
				{
					
        }
        break;
      }
    }
	
		if(B0_Read() && B1_Read() && B13_Read() && B14_Read())
		{
			LED2_OFF();	//LED2��
		}
    cnt++;   			//�����ۼ�
}

    

