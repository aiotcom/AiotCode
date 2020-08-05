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
#define msleep(n) usleep(n*1000)
const int arg_0 = 0,arg_1 = 1;
#define RELAY_MAGIC 'k'
#define IOCTRL_CMD_RELAY_1 _IOW(RELAY_MAGIC, 1, int)
#define IOCTRL_CMD_RELAY_2 _IOW(RELAY_MAGIC, 2, int)

int relay_fd;
int main(void)
{
	unsigned char buf[2];
	/*�򿪼����豸�ļ�*/
	relay_fd = open("/dev/relay", O_RDWR);
	if (relay_fd < 0) {
		perror("**/dev/relay\r\n");
		exit(1);
	}
	
	for (;;) 
	{
		msleep(1000);
		ioctl(relay_fd, IOCTRL_CMD_RELAY_1, &arg_0);
		printf("relay1 off\r\n");
		msleep(1000);
		ioctl(relay_fd, IOCTRL_CMD_RELAY_1, &arg_1);
		printf("relay1 on\r\n");
		msleep(1000);
		ioctl(relay_fd, IOCTRL_CMD_RELAY_2, &arg_0);
		printf("relay2 off\r\n");
		msleep(1000);
		ioctl(relay_fd, IOCTRL_CMD_RELAY_2, &arg_1);	
		printf("relay2 on\r\n");
	}
	/*�ر��豸�ļ����*/
	close(relay_fd);
	return 0;
}
