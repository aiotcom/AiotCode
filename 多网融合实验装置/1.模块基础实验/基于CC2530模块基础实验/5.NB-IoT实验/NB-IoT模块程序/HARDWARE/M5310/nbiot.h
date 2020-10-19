#ifndef ONENET_NBIOT_H_
#define ONENET_NBIOT_H_

#include <ioCC2530.h>
#include "stdbool.h"
#include "delay.h"

#ifdef __cplusplus
extern "C" {
#endif

//obj ��ID ��Դ(res)��IDҪ����IPSO��׼��������ο�������վ��
//http://www.openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html#x_label
#define OBJ_SENSOR_Temp_ID  3303
#define INST_ID_Temp    		0
#define RES_ID_SENSOR   		5700		//Sensor Value

#define OBJ_SENSOR_Humi_ID  3304
#define INST_ID_Humi    		0

#define OBJ_SENSOR_illum_ID 3301
#define INST_ID_illum   		0

#define OBJ_LED_ID      		3311
#define INST_ID_LED     		0
#define RES_ID_LED      		5850

/**
 * value type
**/
#define NBIOT_UNKNOWN       0x0
#define NBIOT_BOOLEAN       0x5
#define NBIOT_INTEGER       0x3
#define NBIOT_FLOAT         0x4
#define NBIOT_STRING        0x1
#define NBIOT_BINARY        0x2
/**
 * value flag
**/
#define NBIOT_READABLE      0x1
#define NBIOT_WRITABLE      0x2
#define NBIOT_EXECUTABLE    0x4
#define NBIOT_UPDATED       0x8

#define NBIOT_ERR_OK        0

/**
* resource uri flag
**/
#define NBIOT_SET_OBJID     0x1
#define NBIOT_SET_INSTID    0x2
#define NBIOT_SET_RESID     0x4

/**
 * value����
**/
typedef struct _nbiot_uri_t
{
    uint16_t objid;
    uint16_t instid;
    uint16_t resid;
    uint8_t  flag;
} nbiot_uri_t;

extern nbiot_uri_t temp_uri;
extern nbiot_uri_t humi_uri;
extern nbiot_uri_t illum_uri;
extern nbiot_uri_t led_uri;

extern uint8_t AppStart;
extern uint8_t light_control;
extern uint8_t msgcode;
extern uint8_t MemCpyEndComma(uint8_t *pdst,uint8_t *psrc,uint8_t maxlen);
extern uint16_t PreTempValue,PreHumiValue,PreIllumValue,u16Temp;

extern char coap_uri[]; //
extern char *serv_addr;
//****************************IMEI��         ;IMSI��         Ӧ�봴����Ӧ�õ�IMEI�룬IMSI��һ��
//const char endpoint_name[] = "865820031095552;460042437101012"; 
extern const char endpoint_name[];

/**
 * ���� Object ������
**/
extern void Subscription_esources(void);

/**
 * device����
**/
typedef struct _nbiot_device_t nbiot_device_t;

/**
 * ����OneNET�����豸ʵ��
 * @param dev �豸ʵ��
**/
void nbiot_device_destroy( nbiot_device_t *dev );

/**
 * ����OneNET����
 * @param dev        �豸ʵ��
 *        server_uri �������ӵ�ַ������coap://127.0.0.1:5683��
 *        timeout    ��ʱʱ�����룩
 * @return �ɹ�����NBIOT_ERR_OK
**/
int nbiot_device_connect( nbiot_device_t *dev,
                          int             timeout );

/**
* �ر���OneNET���������
* @param dev �豸ʵ��
**/
void nbiot_device_close( nbiot_device_t *dev,
                         int             timeout );

/**
 * �����豸�������շ����߼�����
 * @param dev     �豸ʵ��
 *        timeout ��ʱʱ�����룩
 * @return �ɹ�����NBIOT_ERR_OK
**/
int nbiot_device_step( nbiot_device_t *dev,
                       int             timeout );

/**
 * �豸��Դɾ����ֻ�޸�״̬��δ֪ͨserver��
 * @param dev  �豸ʵ��
 *        uri  ��Դ��ַ��Ϣ
 * @return �ɹ�����NBIOT_ERR_OK
**/
int nbiot_resource_del( nbiot_device_t *dev,
                        uint16_t        objid,
                        uint16_t        instid,
                        uint16_t        resid );

/**
 * ����ͬ���豸��Ϣ����Դ�ı�ȣ�
 * @param dev     �豸ʵ��
**/
void nbiot_device_sync( nbiot_device_t *dev );

int nbiot_send_buffer(const nbiot_uri_t * uri,
	                     uint8_t *buffer,
                       size_t        buffer_len,
											 uint16_t       ackid,
                       bool          updated );
												
int nbiot_recv_buffer( uint8_t           *buffer,
                       size_t             buffer_len );

extern  void handle_request( nbiot_device_t    *dev,
                            uint16_t           code,
                            uint8_t           *buffer,
                            size_t             buffer_len,
                            size_t             max_buffer_len );

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* ONENET_NBIOT_H_ */
