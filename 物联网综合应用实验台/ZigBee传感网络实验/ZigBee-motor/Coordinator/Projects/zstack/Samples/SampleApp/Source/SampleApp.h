/**************************************************************************************************
  Filename:       SampleApp.h
  Revised:        $Date: 2007-10-27 17:22:23 -0700 (Sat, 27 Oct 2007) $
  Revision:       $Revision: 15795 $

  Description:    This file contains the Sample Application definitions.


  Copyright 2007 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED 揂S IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, 
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com. 
**************************************************************************************************/

#ifndef SAMPLEAPP_H
#define SAMPLEAPP_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */
#include "ZComDef.h"
#include "AF.h"
#include "led_mode.h"
/*********************************************************************
 * CONSTANTS
 */

// These constants are only for example and should be changed to the
// device's needs
#define SAMPLEAPP_ENDPOINT           20

#define BIND_REQUEST_CMD_ID          0X0040
#define BIND_RSP_CMD_ID              0X0041
  
#define SAMPLEAPP_PROFID             0x0F08
#define SAMPLEAPP_DEVICEID           0x0001
#define SAMPLEAPP_DEVICE_VERSION     0
#define SAMPLEAPP_FLAGS              0

#define LIGHT_INTENSITY_CLUSTERID      0x0001 
#define FAN_CONTROL_CLUSTERID          0x0002
#define LOCK_CONTROL_CLUSTERID         0x0008 
#define TEMP_HUMI_CLUSTERID            0x0010
#define SIREN_CONTROL_CLUSTERID        0x0020  
#define MOTOR_CONTROL_CLUSTERID        0x0080  
#define PIR_CONTROL_CLUSTERID          0x00100  
 
#define BIND_TIME_MSG_EVT        0x0001   
#define READ_KEY_EVT             0x0002
#define GET_KEY_EVT              0x0004
  
#define FAN_ON                   1
#define FAN_OFF                  0

/*		设备地址		*/
#define			Addr_Light						0x1001		//光照传感器地址
#define			Addr_WS							0x1101		//温湿度传感器地址
#define			Addr_Motor						0x1201		//直流电机地址
#define			Addr_Lock						0x1301		//电磁锁地址
#define			Addr_Siren						0x1401		//警报器地址
#define			Addr_Fan						0x1501		//风扇地址
#define			Addr_LED						0x1601		//风扇地址
#define			Addr_NULL						0xFFFF		//空地址-无对象地址时数据传入该地址

/*		命令码		*/
#define			Get_Light_Data					0x1000		//获取光照传感器数据
#define			Light_Data						0x1001		//光照传感器数据

#define			Get_WS_Data						0x1100		//获取温湿度传感器数据
#define			WS_Data							0x1101		//温湿度传感器数据

#define			Motor_OFF						0x1200		//关闭直流电机
#define			Motor_ON						0x1201		//打开直流电机

#define			Lock_OFF						0x1300		//关闭电磁锁
#define			Lock_ON							0x1301		//打开电磁锁

#define			Siren_OFF						0x1400		//关闭警报器
#define			Siren_ON						0x1401		//打开警报器

#define			Fan_OFF							0x1500		//关闭风扇
#define			Fan_ON							0x1501		//打开风扇  
#define         LED_Control                     0x1600
/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*
 * Task Initialization for the Generic Application
 */
extern void SampleApp_Init( uint8 task_id );
extern void Coor_SendFanControlCmd(uint8 cmd);
extern UINT16 SampleApp_ProcessEvent( uint8 task_id, uint16 events );


extern afAddrType_t Boardcast_DstAddr;
extern endPointDesc_t Coordinator_epDesc;
extern endPointDesc_t EndDevice_epDesc;
extern uint8 SampleApp_TransID;
extern uint8 KeyValue;
extern uint8 SampleApp_TaskID;
extern uint8 Hal_TaskID;
/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* SAMPLEAPP_H */
