#include "BLE.h"
#include "delay.h"
#include "Usart.h"

uint8_t BLE_AT_STA = 0;

//==========================================================
//	�������ƣ�	BLE_Init()
//
//	�������ܣ�	������ʼ������
//
//	��ڲ�����	MS   	1:���豸
//										0:���豸
//              
//	���ز�����	��
//
//	˵����		
//==========================================================
void BLE_Init(uint8_t MS)
{
	while(!BLE_Send_Cmd(AT,"OK",20));								/*����AT����ģʽ*/

	while(!BLE_Send_Cmd(TXPW,"OK",50));							/*�����ź�ǿ��*/
	
	while(!BLE_Send_Cmd(ADDR,"OK",50));							/*��ѯ������ַ*/
	
	while(!BLE_Send_Cmd(NAME,"OK",50));							/*�޸���������*/
	if(MS)
	{
		while(!BLE_Send_Cmd("AT+ROLE1\r\n","OK",50));	/*��������*/
		while(!BLE_Send_Cmd(CON,"OK",50));						/*���Ӵӻ�MAC��ַ*/
	}
	else
	{
		while(!BLE_Send_Cmd("AT+ROLE0\r\n","OK",50));	/*��������*/
	}
	
	BLE_AT_STA = 1;           											/*ATָ�����ɱ�־λ*/
}




