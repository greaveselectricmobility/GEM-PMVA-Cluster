/***********************************************************************************************************************
* File Name    : my_can.h
* Version      : 
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the CAN configuration.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

/*****************3W****************/
#ifndef my_can_H_
#define my_can_H_

#define	MSGBUF_BASE_ADD	((unsigned long)(0x0F0600))

void CAN_Pin_configure(void);
void Grg_CAN_Init(void);
void MY_CAN_MsgBuf_Init(void);
void MY_Rx_MsgBuf_Init(uint8_t buffer_number,int32_t rx_mask_ID);
void MY_Tx_MsgBuf_Init(unsigned char ,unsigned int ,unsigned char );
void MY_Tx_MsgBuf_Processing(unsigned char ,unsigned char  ,unsigned char* );
void Grg_CAN_RX_Process(void);
void MY_CAN_StopMode_Release(void);
void MY_CAN_SleepMode_Release(void);
void MY_CAN_StopMode_Setting(void);
void MY_CAN_SleepMode_Setting(void);
uint16_t get_RPM(void);
void clear_CAN_data(void);
void Grg_CAN_err_Recovery(void);

static void __near MY_ISR_CAN_Error(void);
static void __near MY_ISR_CAN_Wakeup(void);
static void __near MY_Rx_MsgBuf_Processing(void);
static void __near INT_Tx(void);

#endif /* my_can_H_ */

