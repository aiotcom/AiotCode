

#ifndef ONENET_UTILS_H_
#define ONENET_UTILS_H_

#include <ioCC2530.h>
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * �ַ�������
 * @param ָ���ַ������ڴ�
 * @return �����ַ�������
**/
int nbiot_strlen( const char *str );

/**
 * �����ַ���
 * @param dest ָ��Ŀ���ַ������ڴ�
 *        src  ָ��Դ�ַ������ڴ�
 *        size �����ַ�������-1��ʾȫ����
 * @return ���ؿ����ַ�����
**/
int nbiot_strncpy( char       *dest,
                   const char *src,
                   int         size );
/**
 * �ַ����Ƚ�
 * @param str1 ָ���ַ���1���ڴ�
 *        str2 ָ���ַ���2���ڴ�
 *        size �Ƚ��ַ�������-1��ʾȫ�Ƚ�
 * @return str1 < str2 ���ظ�ֵ
 *         str1 = str2 ����0
 *         str1 > str2 ������ֵ
**/
int nbiot_strncmp( const char *str1,
                   const char *str2,
                   int         size );

/**
 * �����µ��ַ���
 * @param str  ָ��Դ�ַ������ڴ�
 *        size �ַ������ȣ�-1��ʾ�����ַ���
 * @return �������ַ������ڴ�ָ��
**/
char* nbiot_strdup( const char *str,
                    int         size );

/**
 * ��������ַ�����λ��
 * @param str  ָ��Դ�ַ������ڴ�
 *        size Դ�ַ�������,-1��ʾ�����ַ���
 *        ch   ָ���ַ�
 * @return ���ҳɹ��������ַ���ָ�룬���򷵻�NULL
**/
const char* nbiot_strrchr( const char *str,
                           int         size,
                           char        ch );

/**
 * �ַ���ת��������
 * @param str Դ�ַ���
 *        len ת���ַ�������-1��ʾ�����ַ���
 * @return ��������
**/
int nbiot_atoi( const char *str,
                int         size );

/**
 * ����ת�����ַ���
 * @param val ����
 *        str ָ��Ŀ���ַ����ڴ�
 *        len �ַ����ڴ��С��-1��ʾ�㹻�ڴ��С
 * @return ����ת���ַ�����
**/
int nbiot_itoa( int   val,
                char *str,
                int   size );

/**
 * �����ڴ��
 * @param dst  ָ��Ŀ���ڴ��
 *        src  ָ��Դ�ڴ��
 *        size �������ֽ���
 * @return ����Ŀ���ڴ��ָ��
**/
void* nbiot_memmove( void       *dst,
                     const void *src,
                     size_t      size );

/**
 * �ڴ��Ƚ�
 * @param mem1 ָ���ڴ��1
 *        mem2 ָ���ڴ��2
 *        size �Ƚ����ֽ���
 * @return mem1 > mem2 ��������
 *         mem1 = mem2 ����0
 *         mem1 < mem2 ���ظ���
**/
int nbiot_memcmp( const void *mem1,
                  const void *mem2,
                  size_t      size );
/**
 * �ڴ��������0
 * @param mem  ָ��Ŀ���ڴ��
 *        size �ڴ������ֽ���
**/
void nbiot_memzero( void  *mem,
                    size_t size );

/**
 * ���������
 * @return �����������
**/
int nbiot_rand( void );

#ifdef NBIOT_DEBUG
/**
 * ���ָ���ַ��Ƿ���space
 * @param ch ָ���ַ�
 * @return ��space���ط�0ֵ�����򷵻�0ֵ
**/
int nbiot_isspace( int ch );

/**
* ���ָ���ַ��Ƿ�ɴ�ӡ
* @param ch ָ���ַ�
* @return �ɴ�ӡ���ط�0ֵ�����򷵻�0ֵ
**/
int nbiot_isprint( int ch );

/**
 * ��ʽ���������
 * @param format ��ʽ���ַ���
**/
void nbiot_printf( const char *format, ... );

/**
 * ��ʽ����ӡ�ڴ����Ϣ
 * @param buf ָ���ڴ��
 *        len �ڴ���С
**/
void nbiot_buffer_printf( const void *buf,
                          size_t      len );
#endif

#ifdef __cplusplus
} /* extern "C" { */
#endif

#endif /* ONENET_UTILS_H_ */


