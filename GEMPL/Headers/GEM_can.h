/***********************************************************************************************************************
* File Name    : GEM_can.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains declarations for various functions and defines essential macros. It serves as a central repository for function prototypes and macro definitions that are utilized throughout the GEM_can.c file.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#ifndef GEM_can_H_
#define GEM_can_H_
//----------------------------------------------------------------------------------------------------------------

#include "GEM_common_header.h"

#define CRxD_Port_PM 	PM0.1
#define CRxD_Port	P0.1
#define CTxD_Port_PM 	PM0.0
#define CTxD_Port	P0.0

#define CAN_S		P3.7
#define	CAN_S_PM	PM3.7

#define	MSGBUF_BASE_ADD	((uint32_t)(0x0F0600))
#define	MASKBUF_BASE_ADD	((uint32_t)(0x0F05D0))

#define TX_ID0	0x0012
#define TX_ID1	0x0001
#define TX_ID2 	0x0002
#define TX_ID3	0x0003
#define TX_ID4	0x0004
#define TX_ID5 	0x0005
#define TX_ID6	0x0006
#define TX_ID7	0x0007
#define TX_ID8 	0x0008
#define TX_ID9	0x0009
#define TX_ID10	0x0010
#define TX_ID11 0x0011
#define TX_ID12	0x0012
#define TX_ID13	0x0013
#define TX_ID14 0x0014
#define TX_ID15	0x0015

#define RX_ID15	0x0101

#define MSG_LEN 8
#define IDE_EXT 1
#define IDE_STD 0
//----------------------------------------------------------------------------------------------------------------

void GEM_CAN_MsgBuf_Init(void);
void GEM_CAN_Init_new(uint8_t Baud_Rate);
void GEM_CAN_Init(uint8_t Baud_Rate);
void MY_Tx_MsgBuf_Processing(uint8_t ,uint8_t  ,uint8_t* );
//void GEM_Rx_MsgBuf_Init(uint8_t  ,unsigned int, uint8_t Mask_Buffer);
void GEM_Rx_MsgBuf_Init(uint8_t buffer_number,uint32_t rx_mask_ID, uint8_t Mask_Buffer, uint8_t extid);
void GEM_RX_Mask_MsgBuf_Init(uint32_t rx_mask_ID, uint8_t Mask_Buffer, uint8_t extid);
//void GEM_Rx_MsgBuf_Init(uint8_t ,unsigned int );
void GEM_Tx_MsgBuf_Init(uint8_t buffer_number,uint32_t tx_msg_ID,uint8_t tx_msg_DLC);
// addded by pratik
void GEM_CAN_StopMode_Release(void);
static void __near GEM_ISR_CAN_Error(void);
static void __near GEM_ISR_CAN_Wakeup(void);
void GEM_CAN_SleepMode_Release(void);
void GEM_CAN_StopMode_Release(void);
void GEM_CAN_StopMode_Setting(void);
void  GEM_CAN_SleepMode_Setting(void);
static void __near GEM_Rx_MsgBuf_Processing(void);
static void __near GEM_INT_Tx(void);


//
void GEM_CAN_RX_DATA_Processing(void);
void Get_CAN_Data(CAN_RX_Data_t *Data);
int16_t get_GEM_Wheel_RPM(void);

void GEM_CAN_Timeout_increment_counter(uint32_t gem_timer);
//----------------------------------------------------------------------------------------------------------------

#endif /* my_can_H_ */

