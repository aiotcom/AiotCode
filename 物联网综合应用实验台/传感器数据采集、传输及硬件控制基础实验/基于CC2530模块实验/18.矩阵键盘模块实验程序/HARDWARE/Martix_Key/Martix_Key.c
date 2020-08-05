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
    P1SEL &= ~0xF0;     //����P1.4��P1.5��P1.6��P1.7Ϊ��ͨIO��  
    P1DIR |= 0xF0;      //P1.4��P1.5��P1.6��P1.7����Ϊ���
    
    P0SEL &= ~0x0D;     //����P0.0��P0.2��P0.3Ϊ��ͨIO��  
    P0DIR &= ~0x0D;     //��������P0.0��P0.2��P0.3���ϣ���P0.0��P0.2��P0.3Ϊ����ģʽ 
    P0INP &= ~0x0D;     //��P0.0��P0.2��P0.3��������
    
    P1SEL &= ~0x04;     //����P1.2Ϊ��ͨIO��  
    P1DIR &= ~0x04;     //��������P1.2���ϣ���P1.2Ϊ����ģʽ 
    P1INP &= ~0x04;     //��P1.2��������
    
    WKEY_All_Low();	//��ʼ��ȫ����0
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
uint16_t Key_value;	  //��Ű���ֵ

void KEY_ConFig(void)
{
  static uint8_t cnt = 0; //��������
	
  switch(cnt%4)
  {
    case 0:
      {
        WKEY_All_Hight(); //�����ȫ������
        delay_ms(2);
        WKEY_1_Low();	  //������һ�飨Enter��1��4��7�����
        delay_ms(2);
/*
*	key 7 push down		
*/
        if(!RKEY_Up_Read())
        {
          delay_ms(5);            //��ʱ����	
        if(!RKEY_Up_Read())
        {
          Key_value = Matrixkey7; //����7
          while(!RKEY_Up_Read());
        }
/*
*	key 4 push down
*/
        }
        else if(!RKEY_Down_Read())
        {
          delay_ms(5);  	  //��ʱ����
          if(!RKEY_Down_Read())
          {
            Key_value = Matrixkey4;	//����4
            while(!RKEY_Down_Read());
          }				
/*
*	key 1 push down
*/					
        }
        else if(!RKEY_Left_Read())
        {
          delay_ms(5);  		//��ʱ����				
          if(!RKEY_Left_Read())
          {
            Key_value = Matrixkey1;	//����1
            while(!RKEY_Left_Read());
          }	
/*
*	key Enter push down
*/		
        }
          else if(!RKEY_Right_Read())
          {  
            delay_ms(5);  		//��ʱ����					
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
        WKEY_All_Hight();   //�����ȫ������
        delay_ms(2);
        WKEY_2_Low();	    //�����ڶ��飨0��2��5��8�����
        delay_ms(2);
/*
*	key 8 push down
*/	
        if(!RKEY_Up_Read())
        {        
          delay_ms(5);  		//��ʱ����				
          if(!RKEY_Up_Read())
          {
            Key_value = Matrixkey8;	//����8
            while(!RKEY_Up_Read());
          }					
/*
*	key 5 push down
*/		
        }
        else if(!RKEY_Down_Read())
        {
          delay_ms(5);  		//��ʱ����
          if(!RKEY_Down_Read())
          {
            Key_value = Matrixkey5;	//����5
            while(!RKEY_Down_Read());	
          }			
/*
*	key 2 push down
*/		
        }
        else if(!RKEY_Left_Read())
        {
          delay_ms(5);  		//��ʱ����	
          if(!RKEY_Left_Read())
          {
            Key_value = Matrixkey2;	//����2
            while(!RKEY_Left_Read());
          }			
 /*
*	key 0 push down
*/	         
        }
        else if(!RKEY_Right_Read())
        {
          delay_ms(5);  		//��ʱ����			
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
        WKEY_All_Hight();   //�����ȫ������
        delay_ms(2);
        WKEY_3_Low();	    //���������飨Canel��3��6��9�����	
        delay_ms(2);
 /*
*	key 9 push down
*/	    
        if(!RKEY_Up_Read())
        { 
          delay_ms(5);  	        //��ʱ����					
          if(!RKEY_Up_Read())
          {
              Key_value = Matrixkey9;	//����9
              while(!RKEY_Up_Read());
          }			
 /*
*	key 6 push down
*/	          
        }
        else if(!RKEY_Down_Read())
        {    
          delay_ms(5);  		//��ʱ����		
          if(!RKEY_Down_Read())
          {
            Key_value = Matrixkey6;	//����6
            while(!RKEY_Down_Read());
          }				
 /*
*	key 3 push down
*/	 	
        }
        else if(!RKEY_Left_Read())
        {
          delay_ms(5);  		//��ʱ����
          if(!RKEY_Left_Read())
          {
            Key_value = Matrixkey3;	//����3
            while(!RKEY_Left_Read());
          }
 /*
*	key Canel push down
*/	           
        }
        else if(!RKEY_Right_Read())
        {
          delay_ms(5);  		//��ʱ����
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
        delay_ms(2);
        WKEY_Right_Low();	//������Right�飨Right��Left��Down��UP�����	
        delay_ms(2);
 /*
*	key up push down
*/	  
        if(!RKEY_Up_Read())
        {
          delay_ms(5);  		//��ʱ����
          if(!RKEY_Up_Read())
          {
            Key_value = MatrixkeyUP;	//����up
            while(!RKEY_Up_Read());
          }
 /*
*	key down push down
*/	            
        }else if(!RKEY_Down_Read()){
        delay_ms(5);  			//��ʱ����	
        if(!RKEY_Down_Read())
        {
          Key_value = MatrixkeyDown;	//����down
          while(!RKEY_Down_Read());
        }	
 /*
*	key left push down
*/	  
        }
        else if(!RKEY_Left_Read())
        {
          delay_ms(5);  		//��ʱ����	
          if(!RKEY_Left_Read())
          {
            Key_value = MatrixkeyLeft;	//����left
            while(!RKEY_Left_Read());
          } 
 /*
*	key right push down
*/	  					
        }
        else if(!RKEY_Right_Read())
        {
          delay_ms(5);  		//��ʱ����				
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
	
    cnt++;   //�����ۼ�
}
    





