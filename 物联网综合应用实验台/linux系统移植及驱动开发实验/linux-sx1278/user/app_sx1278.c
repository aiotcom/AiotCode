/*********************************************************************************************
#####         �Ϻ�Ƕ��ʽ��԰-�������̳�         #####
#####                    www.embedclub.com                        #####
#####             http://embedclub.taobao.com               #####

* File��		key_test.c
* Author:		Hanson
* Desc��	a test for one key scan (with polling method) device driver 
* History:	May 16th 2011
*********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include "string.h"
#include <LORA/LORA.h>
#define msleep(n) usleep(n*1000)
enum{lora_rx=1,lora_tx};
int main(int argc,char *argv[])
{
	unsigned char LoraRecvBuffer[32];
	unsigned char IRQ_RegValue,*cptr;
	int ledstate = 0,mode = lora_rx;
	if(argc < 2){
		printf("error\r\n");
		exit(0);
	}
	cptr = argv[1];
	if(strcmp(cptr,"lora_rx")==0){
		mode = lora_rx;
		printf("mode rx\r\n");
	}
	if(strcmp(cptr,"lora_tx")==0){
		mode = lora_tx;
		printf("mode tx\r\n");
	}	
	LORA_Init();
	memset(LoraRecvBuffer,0,32);
	while(mode == lora_tx)
	{
		msleep(1000);
		Sx1278SendLong("toggle led\r\n",strlen("toggle led\r\n"));
		printf("send toggle led\r\n");
	}
	while (mode == lora_rx) 
	{
		msleep(500);
		IRQ_RegValue = SX1276ReadBuffer( REG_LR_IRQFLAGS );
		if((IRQ_RegValue)&&(IRQ_RegValue != 0XFF)){
		//�� LORA�жϼĴ��� REG_LR_IRQFLAGS���ж��Ƿ����жϷ���
			if(INT_FLG_RX_DONE == SX1278_InteruptHandler(LoraRecvBuffer)){
			//�ǽ����жϣ������յ����ݱ��浽LoraRecvBuffer��				
				printf("LORA RECEIVE==%s\r\n",LoraRecvBuffer);				
				lora_led(ledstate);
				ledstate = 1 - ledstate;
				memset(LoraRecvBuffer,0,32);
			}
		}  		
	}
	/*�ر��豸�ļ����*/
	lora_close();
	return 0;
}
