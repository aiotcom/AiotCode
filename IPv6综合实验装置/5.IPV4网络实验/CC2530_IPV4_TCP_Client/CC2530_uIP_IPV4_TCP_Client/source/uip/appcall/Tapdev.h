#ifndef TAPDEV_H
#define TAPDEV_H
#include "type.h"
void tapdev_init(void);
uint16_t tapdev_read(void);//���ذ��ĳ��ȣ�����uip_len
void tapdev_send(void);

#endif

