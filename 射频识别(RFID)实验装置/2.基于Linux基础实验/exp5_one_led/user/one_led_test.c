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

#define LED_MAGIC 'k'
#define IOCTL_LED_ON _IOW(LED_MAGIC, 1, int)
int main(void)
{
	int i;
	int fd;
	int key_value[1];
	int contrl = 0;
	
	/*��LED�豸�ļ�*/
	fd = open("/dev/one_led", 0);
	if (fd < 0) {
		perror("open device key");
		exit(1);
	}
	for (;;) 
	{
		contrl=1;
		ioctl(fd, IOCTL_LED_ON, &contrl);    // ����
		sleep(1);
		
		contrl = 0;
		ioctl(fd, IOCTL_LED_ON, &contrl);    // Ϩ��
		sleep(1);	
	}
	/*�ر��豸�ļ����*/
	close(fd);
	return 0;
}
