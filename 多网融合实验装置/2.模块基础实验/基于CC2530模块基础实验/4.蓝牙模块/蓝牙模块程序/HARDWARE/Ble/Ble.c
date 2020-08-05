#include "Ble.h"	
#include "delay.h"
#include "Usart.h"

uint8_t BLE_AT_STA = 0;

//==========================================================
//	�������ƣ�	BLE_Init()
//
//	�������ܣ�	������ʼ������
//
//	��ڲ�����	MS   	1:���豸
//				0:���豸
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void BLE_Init(uint8_t MS)
{
    while(!ble_send_cmd(AT,"OK",20));			/*����AT����ģʽ*/

    while(!ble_send_cmd(TXPW,"OK",50));			/*�����ź�ǿ��*/
    
    while(!ble_send_cmd(ADDR,"OK",50));			/*��ѯ������ַ*/
    
    while(!ble_send_cmd(NAME,"OK",50));			/*�޸���������*/
    if(MS)
    {
        while(!ble_send_cmd("AT+ROLE1\r\n","OK",50));	/*��������*/
        while(!ble_send_cmd(CON,"OK",50));		/*���Ӵӻ�MAC��ַ*/
    }
    else
    {
        while(!ble_send_cmd("AT+ROLE0\r\n","OK",50));	/*��������*/
    }
    
    BLE_AT_STA = 1;        /*ATָ�����ɱ�־λ*/
}


