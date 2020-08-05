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
#include <nfc/nfc.h>
#include <nfc/PN532.h>
#define msleep(n) usleep(n*1000)
unsigned int  NFC_CardID2;
unsigned char Secret_Key2[6] = {0xff,0xff,0xff,0xff,0xff,0xff};//��Կ����
int main(void)
{
	int i;
	unsigned char LoraRecvBuffer[32];
	unsigned char IRQ_RegValue;
	int key_value=0;
	int temp,humi;
	int contrl = 0;

	nfc_init();
    SAMConfig();							//��ʼ��оƬ����
    msleep(500);						//��ʱ�ȴ�	
	for (;;) 
	{
		msleep(1000);
        NFC_CardID2 = readPassiveTargetID(0x00);//0x00 s50�� 106kbps Ѱ��

        if(NFC_CardID2)
        {		 
			printf("nfc:get id\r\n");
			printf("==%02x\r\n",NFC_CardID2);
            if(authenticateBlock(1,NFC_CardID2,0x05,KEY_A,Secret_Key2))			//��֤��ԿA
            {
				
            }
        }		
	}
	/*�ر��豸�ļ����*/
	nfc_close();
	return 0;
}
