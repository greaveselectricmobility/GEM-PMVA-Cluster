/***********************************************************************************************************************
* File Name    : GEM_Can.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the CAN.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

//----------------------------------------------------------------------------------------------------------------
#include "r_cg_macrodriver.h"
#include "GEM_common_header.h"
#include "GEM_can.h"
#include "my_can.h"
#include "iodefine.h"
#include "Digital_Outputs.h"
#include "RTC.h"

//----------------------------------------------------------------------------------------------------------------
#pragma	interrupt GEM_Rx_MsgBuf_Processing(vect=INTC0REC)
//#pragma	interrupt GEM_ISR_CAN_Error(vect=INTC0ERR)
//#pragma interrupt GEM_ISR_CAN_Wakeup(vect=INTC0WUP)
//#pragma	interrupt GEM_INT_Tx(vect=INTC0TRX)

//----------------------------------------------------------------------------------------------------------------
//uint8_t GEM_Tx_Databuf[8];
uint8_t GEM_Rx_Databuf[8];
_Bool OK_flag;

CAN_RX_Data_t CAN_RX_Data;
CAN_RX_Timeout_flag_t CAN_RX_Timeout_flag;
CAN_RX_Timeout_Counter_t CAN_RX_Timeout_Counter;

#define CLEAR_IF_FLAG 	0
#define SER_IF_FLAG 	1
#define ENABLE_INTERRUPT 0
#define DISABLE_INTERRUPT 1
#define INT_Priority_High 0
#define INT_Priority_Level_1 1
#define INT_Priority_Level_2 2
#define INT_Priority_Low 3

/***********************************************************************************************************************
* Function Name: CAN_0_Receive_Interrupt
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void CAN_0_Receive_Interrupt(_Bool IF_Flag, _Bool IF_Mask_Flag, uint8_t Priority)
{
	C0RECIF  = IF_Flag;   //Clear Interrupt flag. 
						  // 0-no intterupt request signal generated
						  // 1 - Interrupt request is generated, interrupt request status
	C0RECMK = IF_Mask_Flag;  // 0 - Interrupt servicing enabled
							// 1 - Interrupt servicing Disabled	

	switch (Priority)
	{
		case 0:    //Specify level 0 (high priority level)
			C0RECPR0 = 0;
			C0RECPR1 = 0;
			break;
		case 1:    //Specify level 1 (priority level)
			C0RECPR0 = 1;
			C0RECPR1 = 0;
			break;
		case 2:    //Specify level 2 (priority level)
			C0RECPR0 = 0;
			C0RECPR1 = 1;
			break;
		case 3:    //Specify level 3 (priority level)
			C0RECPR0 = 1;
			C0RECPR1 = 1;
			break;
		default:   // low priority
			C0RECPR0 = 1;
			C0RECPR1 = 1;
			break;
	}
}

/***********************************************************************************************************************
* Function Name: CAN_0_Transmit_Interrupt
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void CAN_0_Transmit_Interrupt(_Bool IF_Flag, _Bool IF_Mask_Flag, uint8_t Priority)
{
	C0TRXIF  = IF_Flag;   //Clear Interrupt flag. 
						  // 0-no intterupt request signal generated
						  // 1 - Interrupt request is generated, interrupt request status
	C0TRXMK = IF_Mask_Flag;  // 0 - Interrupt servicing enabled
							// 1 - Interrupt servicing Disabled	

	switch (Priority)
	{
		case 0:    //Specify level 0 (high priority level)
			C0TRXPR0 = 0;
			C0TRXPR1 = 0;
			break;
		case 1:    //Specify level 1 (priority level)
			C0TRXPR0 = 1;
			C0TRXPR1 = 0;
			break;
		case 2:    //Specify level 2 (priority level)
			C0TRXPR0 = 0;
			C0TRXPR1 = 1;
			break;
		case 3:    //Specify level 3 (priority level)
			C0TRXPR0 = 1;
			C0TRXPR1 = 1;
			break;
		default:   // low priority
			C0TRXPR0 = 1;
			C0TRXPR1 = 1;
			break;
	}
}

/***********************************************************************************************************************
* Function Name: CAN_0_Error_Interrupt
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void CAN_0_Error_Interrupt(_Bool IF_Flag, _Bool IF_Mask_Flag, uint8_t Priority)
{
	C0ERRIF  = IF_Flag;   //Clear Interrupt flag. 
						  // 0-no intterupt request signal generated
						  // 1 - Interrupt request is generated, interrupt request status
	C0ERRMK = IF_Mask_Flag;  // 0 - Interrupt servicing enabled
							// 1 - Interrupt servicing Disabled	

	switch (Priority)
	{
		case 0:    //Specify level 0 (high priority level)
			C0ERRPR0 = 0;
			C0ERRPR1 = 0;
			break;
		case 1:    //Specify level 1 (priority level)
			C0ERRPR0 = 1;
			C0ERRPR1 = 0;
			break;
		case 2:    //Specify level 2 (priority level)
			C0ERRPR0 = 0;
			C0ERRPR1 = 1;
			break;
		case 3:    //Specify level 3 (priority level)
			C0ERRPR0 = 1;
			C0ERRPR1 = 1;
			break;
		default:   // low priority
			C0ERRPR0 = 1;
			C0ERRPR1 = 1;
			break;
	}
}

/***********************************************************************************************************************
* Function Name: CAN_0_Wakeup_Interrupt
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void CAN_0_Wakeup_Interrupt(_Bool IF_Flag, _Bool IF_Mask_Flag)
{
	C0WUPIF  = IF_Flag;   //Clear Interrupt flag. 
						  // 0-no intterupt request signal generated
						  // 1 - Interrupt request is generated, interrupt request status
	C0WUPMK = IF_Mask_Flag;  // 0 - Interrupt servicing enabled
							// 1 - Interrupt servicing Disabled	
}
/*--------------------------------CAN INIT-------------------------------*/

/***********************************************************************************************************************
* Function Name: GEM_CAN_Init
* Description  : 
* Arguments    : Baud_Rate
* Return Value : None
***********************************************************************************************************************/
void GEM_CAN_Init(uint8_t Baud_Rate)
{
	SCAN0 = 1;				// 1-CAN pins on P00(TX) & P01(RX)
	
	PCKSEL = 0x10;
	
      /* if you configure internal oscilator 32MHZ */
	C0GMCS  = 0x03;         	// CAN module clock select, fCANMOD = fCAN/1--> 16MHz/1-->16MHz
	
	/* if you configure internal oscilator 16MHZ */
	//C0GMCS  = 0x01;         	// CAN module clock select, fCANMOD = fCAN/1--> 16MHz/1-->16MHz
	
	C0GMCTRL= 0x0100;       	// set GOM=1; enable CAN module operation
	
	
	switch (Baud_Rate)
	{
	case _500KBPS:
		C0BRP	= 0x01;		
		C0BTR	= 0x0104; 
		break;
	case _250KBPS:
		C0BRP	= 0x03;
		C0BTR	= 0x0104;
	
	default:
		break;
	}
	
	C0IE = 0x3f00;
	
	// C0RECIF = 0;			// clear receive interrupt flag
	// C0RECMK = 0;			// Enable Receive interrupt

	CAN_0_Receive_Interrupt(CLEAR_IF_FLAG,ENABLE_INTERRUPT,INT_Priority_High);
	CAN_0_Transmit_Interrupt(CLEAR_IF_FLAG,DISABLE_INTERRUPT,INT_Priority_Level_1);
	CAN_0_Error_Interrupt(CLEAR_IF_FLAG,DISABLE_INTERRUPT,INT_Priority_Low);
	CAN_0_Wakeup_Interrupt(CLEAR_IF_FLAG,DISABLE_INTERRUPT);
	// C0WUPIF = 0;			// clear wakeup interrupt flag
	// C0WUPMK = 1;			// Disable wakeup interrupt
	// C0ERRIF = 0;			// clear error interrupt flag
	// C0ERRMK = 1;			// Disable error interrupt
	// C0TRXMK = 1;   			// Disable transmit interupt
	
	C0CTRL   =  0x817E;   		// clear AL,VALID(no receive valid message),PSMODE1,PSMODE0(no power save mode)
				 	// clear OPMODE2,OPMODE1 and set OPMODE0(normal mode) 
				 	// set CCERC(clear C0ERC and C0INFO registers in initialization mode) 
	//C0CTRL = 0x0502;		// set self-test mode
}


void GEM_CAN_Init_new(uint8_t Baud_Rate)
{
	SCAN0 = 1;			// 1-CAN pins on P00(TX) & P01(RX)
	
	PCKSEL = 0x10;
	C0GMCS  = 0x03;         	// CAN module clock select, fCANMOD = fCAN/4--> 32MHz/4-->8MHz
	C0GMCTRL= 0x0100;       	// set GOM=1; enable CAN module operation
	switch (Baud_Rate)
	{
	case _500KBPS:
		C0BRP	= 0x01;		
		C0BTR	= 0x0104; 
		break;
	case _250KBPS:
		C0BRP	= 0x03;
		C0BTR	= 0x0104;
	
	default:
		break;
	}
	C0IE = 0x3f00;
	
 	/* ********************    Receiver Interrupt settings ****************************************************** */
	CAN_0_Receive_Interrupt(CLEAR_IF_FLAG,ENABLE_INTERRUPT,INT_Priority_High);		
	/* ********************    Transmit Interrupt settings ****************************************************** */
	CAN_0_Transmit_Interrupt(CLEAR_IF_FLAG,DISABLE_INTERRUPT,INT_Priority_Level_1);
	/* ********************    CAN Error Interrupt settings ****************************************************** */
	CAN_0_Error_Interrupt(CLEAR_IF_FLAG,DISABLE_INTERRUPT,INT_Priority_Low);	
	/* ********************    Wakeup Interrupt settings ****************************************************** */
	CAN_0_Wakeup_Interrupt(CLEAR_IF_FLAG,DISABLE_INTERRUPT);


	C0CTRL   =  0x817E;   	// clear AL,VALID(no receive valid message),PSMODE1,PSMODE0(no power save mode)
				 	        // clear OPMODE2,OPMODE1 and set OPMODE0(normal mode) 
				 	        // set CCERC(clear C0ERC and C0INFO registers in initialization mode) 
    GEM_CAN_MsgBuf_Init();
   

    //MY_Rx_MsgBuf_Init(8,0x1AA);      //BAT_ERR,BAT_FUL CHRG
	GEM_Rx_MsgBuf_Init(0,0x18FF035A,NO_MASK,IDE_EXT);
	
	
	GEM_RX_Mask_MsgBuf_Init(0x00000F3A,MASK_BUFFER_1,  IDE_EXT);
	GEM_Rx_MsgBuf_Init(1,0x18FF0F7A,MASK_BUFFER_1,IDE_EXT); //Mask_Value 0x00002f00
	
	GEM_Rx_MsgBuf_Init(2,0x14520902,NO_MASK,IDE_EXT);

	GEM_RX_Mask_MsgBuf_Init(0x04000006,MASK_BUFFER_3,  IDE_EXT);
	GEM_Rx_MsgBuf_Init(3,0x1C530906,MASK_BUFFER_3,IDE_EXT); //Mask_Value 0x04000006

	GEM_Rx_MsgBuf_Init(4,0x3AA,NO_MASK,IDE_STD);

	GEM_RX_Mask_MsgBuf_Init(0x706,MASK_BUFFER_2,  IDE_STD);
	GEM_Rx_MsgBuf_Init(5,0x7A8,MASK_BUFFER_2,IDE_STD); //Mask_Value 0x706
	GEM_Rx_MsgBuf_Init(6,0x150,NO_MASK,IDE_STD);



    //MY_Rx_MsgBuf_Init(10,0x3AA);      //BMS state
    //MY_Rx_MsgBuf_Init(11,0x4AC);      //thermal runaway_early warn (>60)
    //MY_Rx_MsgBuf_Init(12,0x150);      //thermal runaway
    //MY_Rx_MsgBuf_Init(5,0x14520902); //Vechicle Speed
						 
    //MY_Rx_MsgBuf_Init(6, 0x18530902); //drive mode//MCU Error//Motor Error//Throttle failure/motor_temp
    //MY_Rx_MsgBuf_Init(14,0x18530904); 
    //MY_Rx_MsgBuf_Init(15,0x1C530902); 
    MY_Rx_MsgBuf_Init(7,0x7DF);
    MY_Tx_MsgBuf_Init(13,0x7DA,8);
	
   //clear_CAN_data();
}
/***********************************************************************************************************************
* Function Name: GEM_CAN_MsgBuf_Init
* Description  : 
* Arguments    : none
* Return Value : None
***********************************************************************************************************************/
//----------------------------------------------------------------------------------------------------------------
void GEM_CAN_MsgBuf_Init(void)
{
	uint8_t	buffer_number;
	uint32_t	MsgBuf_address;

	for (buffer_number = 0 ; buffer_number < 16 ; buffer_number++)		// Init all message buffer
	{
		
		MsgBuf_address = (MSGBUF_BASE_ADD + (0x10 * buffer_number));	// Set CAN message buffer[n] register address
		
		*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0006;		// Clear TRQ, DN bit
				
		*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0001;		// Clear RDY bit
		
		*((uint8_t *)(MsgBuf_address + 0x09)) &= 0xf8;		// Clear MA0 bit
	}
}

/***********************************************************************************************************************
* Function Name: GEM_Tx_MsgBuf_Init
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
//----------------------------------------------------------------------------------------------------------------
void GEM_Tx_MsgBuf_Init(uint8_t buffer_number,uint32_t tx_msg_ID,uint8_t tx_msg_DLC)
{
	uint32_t	MsgBuf_address;
	uint8_t data_cnt;
	
	MsgBuf_address = (MSGBUF_BASE_ADD + (0x10 * buffer_number));		// Set CAN message buffer[n] register address

	*((uint8_t *)(MsgBuf_address + 0x09)) = 0x01;      		// Set C0MCONFm register, Transmit message buffer, MA0=1,msg buffer used

	*((uint16_t *)(MsgBuf_address + 0x0a)) = 0x0000;   		// standard frame,C0MIDLm=0x0000;
	*((uint16_t *)(MsgBuf_address + 0x0c)) = ((tx_msg_ID << 2) & 0x1fff); 	// C0MIDHm

	*((uint8_t *)(MsgBuf_address + 0x08)) = tx_msg_DLC;     		// set C0MDLCm -data length

	for(data_cnt = 0 ; data_cnt < tx_msg_DLC ; data_cnt++)			
	{
		*((uint8_t *)(MsgBuf_address + (0x01 * data_cnt))) = 0x00;    // clear each byte data=0x00
	}
	

	#if 1
	*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x001e;  // C0MCTRLm
								// clear MOW,IE,DN,TRQ bit
								// MOV=0,The message buffer is not overwritten by a newly received data frame.
								// IE=0,Normal message transmission completion interrupt disabled
								// DN=0,A data frame or remote frame is not stored in the message buffer.
								// TRQ=0,No message frame transmitting request that is pending or being transmitted
	#endif

	#if 0							
	*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0816;  // clear MOW,DN,TRQ bit
								// set IE=1,Normal message transmission completion interrupt enabled
	#endif
	
	*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0100; 	// // Set RDY bit,The CAN module can write to the message buffer

}

/***********************************************************************************************************************
* Function Name: GEM_Rx_MsgBuf_Init
* Description  :
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
//----------------------------------------------------------------------------------------------------------------
void GEM_Rx_MsgBuf_Init(uint8_t buffer_number,uint32_t rx_mask_ID, uint8_t Mask_Buffer, uint8_t extid)
{
	uint32_t	MsgBuf_address;

	
	MsgBuf_address = (MSGBUF_BASE_ADD + (0x10 * buffer_number));		// Set CAN message buffer[n] register address

	switch (Mask_Buffer)
	{
		case TX_BUFFER:
						*((uint8_t *)(MsgBuf_address + 0x09)) = 0x01;   // Transmit buffer
						break;
		case NO_MASK:
						*((uint8_t *)(MsgBuf_address + 0x09)) = 0x09;   // Receive message buffer(no mask), MA0=1,msg buffer used
						break;
	
		case MASK_BUFFER_1:
						*((uint8_t *)(MsgBuf_address + 0x09)) = 0x11;    	// Receive message buffer(mask 1), MA0=1,msg buffer used
						break;
		case MASK_BUFFER_2:
						*((uint8_t *)(MsgBuf_address + 0x09)) = 0x19;   // Receive message buffer(mask 2), MA0=1,msg buffer used
						break;
		case MASK_BUFFER_3:
						*((uint8_t *)(MsgBuf_address + 0x09)) = 0x21;   // Receive message buffer(mask 3), MA0=1,msg buffer used
						break;
		case MASK_BUFFER_4:
						*((uint8_t *)(MsgBuf_address + 0x09)) = 0x29;   // Receive message buffer(mask 4), MA0=1,msg buffer used
						break;
	
	default:
		break;
	}

	// Set C0MCONFm register 
	//*((uint8_t *)(MsgBuf_address + 0x09)) = 0x09;   // Receive message buffer(no mask), MA0=1,msg buffer used
	//*((uint8_t *)(MsgBuf_address + 0x09)) = 0x89;	// OWS=1, receive buffer will overwrite if DN=1
	//*((uint8_t *)(MsgBuf_address + 0x09)) = 0x11;    	// Receive message buffer(mask 1), MA0=1,msg buffer used
	//*((uint8_t *)(MsgBuf_address + 0x09)) = 0x19;   // Receive message buffer(mask 2), MA0=1,msg buffer used
	//*((uint8_t *)(MsgBuf_address + 0x09)) = 0x21;   // Receive message buffer(mask 3), MA0=1,msg buffer used
	//*((uint8_t *)(MsgBuf_address + 0x09)) = 0x29;   // Receive message buffer(mask 4), MA0=1,msg buffer used
	if ((extid == 1) && (rx_mask_ID > 0x7FF))
	{
		
		*((uint16_t *)(MsgBuf_address + 0x0a)) = (uint32_t) rx_mask_ID;   			
		*((uint16_t *)(MsgBuf_address + 0x0c)) = (uint32_t)((rx_mask_ID >> 16) | 0x8000); 	//C0MIDHm
	}
	else
	{
		
		*((uint16_t *)(MsgBuf_address + 0x0a)) = 0x0000;   			//standard frame,C0MIDLm=0x0000;
		*((uint16_t *)(MsgBuf_address + 0x0c)) = ((rx_mask_ID << 2) & 0x1FFC); 	//C0MIDHm
	}
	

	
	*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0916;  // Set C0MCTRLm register 
								// clear MOW,DN,TRQ bit
								// MOV=0,The message buffer is not overwritten by a newly received data frame.
								// set IE=1,Valid message reception completion interrupt enabled.
								// DN=0,A data frame or remote frame is not stored in the message buffer.
								// TRQ=0,No message frame transmitting request that is pending or being transmitted
	
	*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0100;  // Set RDY bit,The CAN module can write to the message buffer

}


/***********************************************************************************************************************
* Function Name: GEM_RX_Mask_MsgBuf_Init
* Description  :
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void GEM_RX_Mask_MsgBuf_Init(uint32_t rx_mask_ID, uint8_t Mask_Buffer, uint8_t extid)
{
	uint32_t MaskBuf_address;
	MaskBuf_address = MASKBUF_BASE_ADD;
	switch (Mask_Buffer)
	{
		case NO_MASK:
						
						break;

		case MASK_BUFFER_1:
						if (extid)
						{
							*((uint16_t *)(MaskBuf_address + 0x00)) = (uint16_t) rx_mask_ID;   			
							*((uint16_t *)(MaskBuf_address + 0x02)) = (uint32_t)((rx_mask_ID >> 16)); 	//C0MIDHm
						}
						else
						{
							*((uint16_t *)(MaskBuf_address + 0x00)) = 0x0000;   			//standard frame,C0MIDLm=0x0000;
							*((uint16_t *)(MaskBuf_address + 0x02)) = ((rx_mask_ID << 2) & 0x1FFC); 	//C0MIDHm
						}
						break;
		case MASK_BUFFER_2:
						if (extid)
						{
							*((uint16_t *)(MaskBuf_address + 0x04)) = (uint16_t) rx_mask_ID;   			
							*((uint16_t *)(MaskBuf_address + 0x06)) = (uint32_t)((rx_mask_ID >> 16)); 	//C0MIDHm
						}
						else
						{
							*((uint16_t *)(MaskBuf_address + 0x04)) = 0x0000;   			//standard frame,C0MIDLm=0x0000;
							*((uint16_t *)(MaskBuf_address + 0x06)) = ((rx_mask_ID << 2) & 0x1FFC); 	//C0MIDHm
						}
						break;
		case MASK_BUFFER_3:
						if (extid)
						{
							*((uint16_t *)(MaskBuf_address + 0x08)) = (uint16_t) rx_mask_ID;   			
							*((uint16_t *)(MaskBuf_address + 0x0A)) = (uint32_t)((rx_mask_ID >> 16)); 	//C0MIDHm
						}
						else
						{
							*((uint16_t *)(MaskBuf_address + 0x08)) = 0x0000;   			//standard frame,C0MIDLm=0x0000;
							*((uint16_t *)(MaskBuf_address + 0x0A)) = ((rx_mask_ID << 2) & 0x1FFC); 	//C0MIDHm
						}
						break;
		case MASK_BUFFER_4:
						if (extid)
						{
							*((uint16_t *)(MaskBuf_address + 0x0C)) = (uint16_t) rx_mask_ID;   			
							*((uint16_t *)(MaskBuf_address + 0x0E)) = (uint32_t)((rx_mask_ID >> 16)); 	//C0MIDHm
						}
						else
						{
							*((uint16_t *)(MaskBuf_address + 0x0C)) = 0x0000;   			//standard frame,C0MIDLm=0x0000;
							*((uint16_t *)(MaskBuf_address + 0x0E)) = ((rx_mask_ID << 2) & 0x1FFC); 	//C0MIDHm
						}
						break;
	}
}

//----------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************
* Function Name: GEM_Tx_MsgBuf_Processing
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void GEM_Tx_MsgBuf_Processing(uint8_t buffer_number,uint8_t tx_msg_DLC,uint8_t* tx_msg_data)
{
	uint32_t	MsgBuf_address;
	uint16_t  C0MCTRLm;
	
	MsgBuf_address = (MSGBUF_BASE_ADD + (0x10 * buffer_number));	// Set CAN message buffer[n] register address

	C0MCTRLm = *((uint8_t *)(MsgBuf_address + 0x0e));		// Check TRQ bit
	while((C0MCTRLm & 0x0002) != 0)
	{
		NOP();//return;
	}

	
	*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0001;    	// Clear RDY bit ,The message buffer can be written by software.
	
	C0MCTRLm = *((uint8_t *)(MsgBuf_address + 0x0e));

	
	if((C0MCTRLm & 0x0001) == 0)					// Set C0MDATAxm register
	{
		uint8_t data_cnt;
		
		for(data_cnt = 0 ; data_cnt < tx_msg_DLC ; data_cnt++)
		{
			*((uint8_t *)(MsgBuf_address + (0x01 * data_cnt))) = tx_msg_data[data_cnt];    //clear each byte data=0x00
		}
		
		//*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0800;	// Set EI bit-pratik
		*((uint16_t *)(MsgBuf_address + 0x0e)) =  0x0100;	// Set RDY bit
		
		*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0200;	// Set TRQ bit
	}
	
	//C0MCTRLm = *((uint8_t *)(MsgBuf_address + 0x0e)); 
	while((C0MCTRLm & 0x0002) == 0x0002)
	{
		NOP();
		NOP();
	}
	return;
}

//----------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************
* Function Name: GEM_CAN_RX_DATA_Processing
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void GEM_CAN_RX_DATA_Processing(void)
{
	uint32_t	MsgBuf_address;
	uint8_t	rx_msg_DLC,rx_data_cnt,rx_buffer_number;
	uint32_t 	rx_msg_ID,rx_msg_ID_L,rx_msg_ID_H;
	uint16_t extid;
	
	C0INTS = 0x0002;
	
	rx_buffer_number = C0LIPT;						// Get receive message buffer number
	
	MsgBuf_address = (MSGBUF_BASE_ADD + (0x10 * rx_buffer_number));		// Set CAN message buffer[n] register address
	
	while(((*((uint16_t *)(MsgBuf_address + 0x0e))) & 0x2004) != 0) 	//check DN and MUC bit
	{
		
		*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0004;		// Clear DN bit
		
		rx_msg_DLC = *((uint8_t *)(MsgBuf_address + 0x08));	// Get receive message data length
		extid = (((*((uint16_t *)(MsgBuf_address + 0x0C))))&(0x8000));
		if (extid == 0x8000)  //EXT ID
		{
			rx_msg_ID_L = (*((uint16_t *)(MsgBuf_address + 0x0A)));	// Get receive message ID
			rx_msg_ID_H = ((*((uint16_t *)(MsgBuf_address + 0x0C))) & (0x1fff));     //standard frame,just need C0MIDHm,C0MIDLm=0x0000
			rx_msg_ID   = (uint32_t)((((rx_msg_ID_H)|(0xffff0000))<<16) | (rx_msg_ID_L));
		}
		else //STD ID
		{
			
			rx_msg_ID = (*((uint16_t *)(MsgBuf_address + 0x0C)))>>2;	
		}

		//rx_msg_ID = *((uint16_t *)(MsgBuf_address + 0x0C));	// Get receive message ID
		
		//rx_msg_ID = ((*((uint16_t *)(MsgBuf_address + 0x0C)))>>2) & (0x07ff);     //standard frame,just need C0MIDHm,C0MIDLm=0x0000
		for(rx_data_cnt = 0 ;((rx_data_cnt < rx_msg_DLC) && (rx_data_cnt < 8)) ; rx_data_cnt++)
		{
			GEM_Rx_Databuf[rx_data_cnt] = *((uint8_t *)(MsgBuf_address + (0x01 * rx_data_cnt)));	// Get receive data
		}
		
		switch(rx_msg_ID)
		{
			case (0x18FF015A): 
			case (0x1AA):    	
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.BMS_ERR_DET = ((GEM_Rx_Databuf[1] & 0x02) >> 1);
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.BATT_LOW = ((GEM_Rx_Databuf[0] & 0x10) >> 4);
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.BATT_FULL = ((GEM_Rx_Databuf[0] & 0x08) >> 3);
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.BMS_WAR_DET = ((GEM_Rx_Databuf[1] & 0x40) >> 6);
				CAN_RX_Timeout_flag.Timeout_Flag.MSG_0x18FF015A_1AA = 1;
				CAN_RX_Timeout_Counter.count.MSG_0x18FF015A_1AA = 0;
				__nop();
				break;
			case (0x18FF025A):
			case (0x2AA): 
				CAN_RX_Data.SOC = GEM_Rx_Databuf[0];
				CAN_RX_Timeout_flag.Timeout_Flag.MSG_0x18FF025A_2AA = 1;
				CAN_RX_Timeout_Counter.count.MSG_0x18FF025A_2AA = 0;
				__nop();
				break;
			case (0x18FF035A):
			case (0x3AA): 
				CAN_RX_Data.BMS_STATE = GEM_Rx_Databuf[7];
				CAN_RX_Timeout_flag.Timeout_Flag.MSG_0x18FF035A_3AA = 1;
				CAN_RX_Timeout_Counter.count.MSG_0x18FF035A_3AA = 0;
				
				__nop();
				break;
			case (0x18FF045A):
			case (0x4AA): 
				//CAN_RX_Data.MIN_CT = GEM_Rx_Databuf[4];
				//CAN_RX_Data.MAX_CT = GEM_Rx_Databuf[5];
				__nop();
				break;
			case (0x18FF0D5A):
			case (0x4AC): 
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_OV = (GEM_Rx_Databuf[0] & 0x01);
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_UV1 = ((GEM_Rx_Databuf[0] & 0x02) >> 1);
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_UV2 = ((GEM_Rx_Databuf[1] & 0x04) >> 2);
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_THRMLRUNWY_TEMP = ((GEM_Rx_Databuf[6] & 0x10) >> 4);
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_THRMLRUNWY_GAS = ((GEM_Rx_Databuf[6] & 0x20) >> 5);
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_THRMLRUNWY_WARNG = ((GEM_Rx_Databuf[6] & 0x80) >> 7);
				CAN_RX_Timeout_flag.Timeout_Flag.MSG_0x18FF0D5A_4AC = 1;
				CAN_RX_Timeout_Counter.count.MSG_0x18FF0D5A_4AC = 0;
				__nop();
				break;
			case (0x18FF0060):
			case (0x150):
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.THRMLRUNWY_STS = ((GEM_Rx_Databuf[0] & 0x03));
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.THRMLRUNWY_SRC = ((GEM_Rx_Databuf[1] & 0x03));
				CAN_RX_Timeout_flag.Timeout_Flag.MSG_0x18FF0060_150 = 1;
				CAN_RX_Timeout_Counter.count.MSG_0x18FF0060_150 = 0;
				__nop();
				break;
			case (0x14520902):
				CAN_RX_Data.Wheel_RPM = (uint16_t) ((GEM_Rx_Databuf[1]<<8)|(GEM_Rx_Databuf[0]));
				CAN_RX_Data.Wheel_RPM =  ((GEM_Rx_Databuf[1]<<8)|(GEM_Rx_Databuf[0]));
				//CAN_RX_Data.Wheel_Revolution = (uint16_t) ((GEM_Rx_Databuf[3]<<8)|(GEM_Rx_Databuf[2]));
				//CAN_RX_Data.Wheel_Revolution = ((GEM_Rx_Databuf[3]<<8)|(GEM_Rx_Databuf[2]));
				CAN_RX_Timeout_flag.Timeout_Flag.MSG_0x14520902 = 1;
				CAN_RX_Timeout_Counter.count.MSG_0x14520902 = 0;
				__nop();
				break;
			case (0x18530902):
				//CAN_RX_Data.Throttle_Percentage = GEM_Rx_Databuf[0];
				CAN_RX_Data.MCU_Temperature = GEM_Rx_Databuf[3];
				CAN_RX_Data.Motor_Temperature = (uint16_t) ((GEM_Rx_Databuf[5]<<8)|(GEM_Rx_Databuf[4]));
				//CAN_RX_Data.MCU_Fault_Codes = GEM_Rx_Databuf[6];
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Mode_Status_Flag = ((GEM_Rx_Databuf[1] & 0x01));
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Park_Indication = ((GEM_Rx_Databuf[1] & 0x04) >> 2);
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Direction = ((GEM_Rx_Databuf[1] & 0x08) >> 3);
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Overcurrent_Error = ((GEM_Rx_Databuf[1] & 0x10) >> 4);
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Overload_Error = ((GEM_Rx_Databuf[1] & 0x20) >> 5);
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Controller_Lock = ((GEM_Rx_Databuf[1] & 0x80) >> 7);
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.MCU_Charging_Status = ((GEM_Rx_Databuf[2] & 0x04) >> 2);
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Regenerative_Braking = ((GEM_Rx_Databuf[2] & 0x08) >> 3);
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Throttle_Error = ((GEM_Rx_Databuf[2] & 0x20) >> 5);
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Controller_Error = ((GEM_Rx_Databuf[2] & 0x40) >> 6);
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Motor_Error = ((GEM_Rx_Databuf[2] & 0x80) >> 7);
				CAN_RX_Timeout_flag.Timeout_Flag.MSG_0x18530902 = 1;
				CAN_RX_Timeout_Counter.count.MSG_0x18530902 = 0;
				__nop();
				break;
			
			case (0x18530904):
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Immobilize_Sts = ((GEM_Rx_Databuf[0] & 0x04) >> 2);
				CAN_RX_Timeout_flag.Timeout_Flag.MSG_0x18530904 = 1;
				CAN_RX_Timeout_Counter.count.MSG_0x18530904 = 0;
				__nop();
				break;
			case (0x1C530902):
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Limp_Home_Mode = ((GEM_Rx_Databuf[7] & 0x01));
				CAN_RX_Timeout_flag.Timeout_Flag.MSG_0x1C530902 = 1;
				CAN_RX_Timeout_Counter.count.MSG_0x1C530902 = 0;
				__nop();
				break;
			case (0x7DF):
				CAN_RX_Data.CAN_Req[0] = GEM_Rx_Databuf[0];
				CAN_RX_Data.CAN_Req[1] = GEM_Rx_Databuf[1];
				CAN_RX_Data.CAN_Req[2] = GEM_Rx_Databuf[2];
				CAN_RX_Data.CAN_Req[3] = GEM_Rx_Databuf[3];
				CAN_RX_Data.CAN_Req[4] = GEM_Rx_Databuf[4];
				CAN_RX_Data.CAN_Req[5] = GEM_Rx_Databuf[5];
				CAN_RX_Data.CAN_Req[6] = GEM_Rx_Databuf[6];
				CAN_RX_Data.CAN_Req[7] = GEM_Rx_Databuf[7];
				CAN_RX_Timeout_flag.Timeout_Flag.MSG_7DF = 1;
				CAN_RX_Timeout_Counter.count.MSG_7DF = 0;
				__nop();
				break;
			default:
				break;
		}
//		
		OK_flag = 1;
			
	}
}

//static void __near MY_Rx_MsgBuf_Processing(void)
/***********************************************************************************************************************
* Function Name: GEM_Rx_MsgBuf_Processing
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near GEM_Rx_MsgBuf_Processing(void)
{
	GEM_CAN_RX_DATA_Processing();
}
//----------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************
* Function Name: GEM_CAN_SleepMode_Setting
* Description  :
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void GEM_CAN_SleepMode_Setting()
{
	C0CTRL = 0x0810;   			// set PSMODE0=1,PSMODE1=0, setting CAN sleep mode
	while((C0CTRL&0x0008) == 0); 		// check PSMODE0=1
}
//----------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************
* Function Name: GEM_CAN_StopMode_Setting
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void GEM_CAN_StopMode_Setting()
{
	GEM_CAN_SleepMode_Setting();
	C0CTRL = 0x1800;   			// set PSMODE0=1,PSMODE1=1, setting CAN stop mode
	while((C0CTRL&0x0010) == 0); 		// check PSMODE1=1
}
//----------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************
* Function Name: GEM_CAN_StopMode_Release
* Description  :
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void GEM_CAN_StopMode_Release()
{
	C0CTRL = 0x0810;   			// clear PSMODE1=0, release stop mode to sleep mode
}
//----------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************
* Function Name: GEM_CAN_SleepMode_Release
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void GEM_CAN_SleepMode_Release()
{
	C0CTRL = 0x0008;    			// clear PSMODE0=0,release sleep mode by software
	
	#if 0
	//Sleep mode can also be released by a falling edge at the CAN reception pin---wakeup signal
	C0INTS = 0x0020;    			// clear CINTS5(Wakeup interrupt)
	#endif
}
//----------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************
* Function Name: GEM_ISR_CAN_Wakeup
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near GEM_ISR_CAN_Wakeup()
{
	C0INTS = 0x0020;    			// clear CINTS5(Wakeup interrupt)
}
//----------------------------------------------------------------------------------------------------------------
/***********************************************************************************************************************
* Function Name: GEM_ISR_CAN_Error
* Description  :
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near GEM_ISR_CAN_Error()
{
	C0INTS = 0x001C;
}

/***********************************************************************************************************************
* Function Name: GEM_INT_Tx
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near GEM_INT_Tx(void)
{
	NOP();
}


/***********************************************************************************************************************
* Function Name: Get_CAN_Data
* Description  : 
* Arguments    : CAN_RX_Data_t
* Return Value : None
***********************************************************************************************************************/
void Get_CAN_Data(CAN_RX_Data_t *Data)
{
	memcpy(Data,&CAN_RX_Data,sizeof(CAN_RX_Data_t));
	memset(&CAN_RX_Data.CAN_Req[0],0,8);
	memset(&CAN_RX_Data.CAN_Resp[0],0,8);
}

/***********************************************************************************************************************
* Function Name: get_GEM_Wheel_RPM
* Description  : 
* Arguments    : None
* Return Value : wheel rpm
***********************************************************************************************************************/
int16_t get_GEM_Wheel_RPM(void)
{
	return CAN_RX_Data.Wheel_RPM;
}
//----------------------------------------------------------------------------------------------------------------



void GEM_CAN_Timeout(uint8_t msg_no)
{
	uint32_t msg_id[CAN_MESSAGE_COUNT] = {0x18FF015A,0x18FF025A,0x18FF035A,0x18FF0D5A,0x18FF0060,0x14520902,0x18530902,0x18530904,0x1C530902,0x7DF};
	uint32_t id = msg_id[msg_no];
	switch(id)
	{
			case (0x18FF015A): 
			case (0x1AA):    	
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.BMS_ERR_DET 			= 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.BATT_LOW 				= 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.BATT_FULL 				= 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.BMS_WAR_DET 			= 0;
				break;
			case (0x18FF025A):
			case (0x2AA): 
				CAN_RX_Data.SOC = 0;
				break;
			case (0x18FF035A):
			case (0x3AA): 
				CAN_RX_Data.BMS_STATE = 0;
				break;
			case (0x18FF0D5A):
			case (0x4AC): 
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_OV = 0;
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_UV1 = 0;
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_UV2 = 0;
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_THRMLRUNWY_TEMP = 0;
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_THRMLRUNWY_GAS = 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.ERR_THRMLRUNWY_WARNG = 0;
				break;
			case (0x18FF0060):
			case (0x150):
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.THRMLRUNWY_STS = 0;
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.THRMLRUNWY_SRC = 0;
				break;
			case (0x14520902):
				CAN_RX_Data.Wheel_RPM = 0;
				//CAN_RX_Data.Wheel_Revolution = 0;
				break;
			case (0x18530902):
				//CAN_RX_Data.Throttle_Percentage = 0;
				CAN_RX_Data.MCU_Temperature = 0;
				CAN_RX_Data.Motor_Temperature = 0;
				//CAN_RX_Data.MCU_Fault_Codes = 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Mode_Status_Flag = 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Park_Indication = 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Direction = 0;
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Overcurrent_Error = 0;
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Overload_Error = 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Controller_Lock = 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.MCU_Charging_Status = 0;
				//CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Regenerative_Braking = 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Throttle_Error = 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Controller_Error = 0;
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Motor_Error = 0;
				break;
			
			case (0x18530904):
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Immobilize_Sts = 0;
				break;
			case (0x1C530902):
				CAN_RX_Data.CAN_RX_Data_Bit.SGNL.Limp_Home_Mode = 0;
				break;
			case (0x7DF):
				CAN_RX_Data.CAN_Req[0] = 0;
				CAN_RX_Data.CAN_Req[1] = 0;
				CAN_RX_Data.CAN_Req[2] = 0;
				CAN_RX_Data.CAN_Req[3] = 0;
				CAN_RX_Data.CAN_Req[4] = 0;
				CAN_RX_Data.CAN_Req[5] = 0;
				CAN_RX_Data.CAN_Req[6] = 0;
				CAN_RX_Data.CAN_Req[7] = 0;
				break;
			default:
				break;
	}
}

void GEM_CAN_Timeout_increment_counter(uint32_t gem_timer)
{
	static uint32_t can_gen_timeout_timer_prev = 0;
	uint8_t i = 0;
	if ((gem_timer - can_gen_timeout_timer_prev) >= CAN_TIMEOUT_VALUE)
	{
		can_gen_timeout_timer_prev = gem_timer;
		for(i=0;i<CAN_MESSAGE_COUNT;i++)
		{
			CAN_RX_Timeout_Counter.counter[i] +=1;
			if(CAN_RX_Timeout_Counter.counter[i] >= 5)
			{
				GEM_CAN_Timeout(i);
			}
		}
	}
}