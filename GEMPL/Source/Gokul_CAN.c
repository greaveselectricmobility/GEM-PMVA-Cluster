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


#define CLEAR_IF_FLAG 	0
#define SER_IF_FLAG 	1
#define ENABLE_INTERRUPT 0
#define DISABLE_INTERRUPT 1
#define INT_Priority_High 0
#define INT_Priority_Level_1 1
#define INT_Priority_Level_2 2
#define INT_Priority_Low 3


//----------------------------------------------------------------------------------------------------------------
//#pragma	interrupt GEM_Rx_MsgBuf_Processing(vect=INTC0REC)
//#pragma	interrupt GEM_ISR_CAN_Error(vect=INTC0ERR)
//#pragma interrupt GEM_ISR_CAN_Wakeup(vect=INTC0WUP)
//#pragma	interrupt GEM_INT_Tx(vect=INTC0TRX)

//CAN_RX_Data_t CAN_RX_Data;
//CAN_RX_Timeout_flag_t CAN_RX_Timeout_flag;
//CAN_RX_Timeout_Counter_t CAN_RX_Timeout_Counter;



/***********************************************************************************************************************
* Function Name: CAN_0_Receive_Interrupt
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void GCAN_0_Receive_Interrupt(_Bool IF_Flag, _Bool IF_Mask_Flag, uint8_t Priority)
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
void GCAN_0_Transmit_Interrupt(_Bool IF_Flag, _Bool IF_Mask_Flag, uint8_t Priority)
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
void GCAN_0_Error_Interrupt(_Bool IF_Flag, _Bool IF_Mask_Flag, uint8_t Priority)
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
void GCAN_0_Wakeup_Interrupt(_Bool IF_Flag, _Bool IF_Mask_Flag)
{
	C0WUPIF  = IF_Flag;   //Clear Interrupt flag. 
						  // 0-no intterupt request signal generated
						  // 1 - Interrupt request is generated, interrupt request status
	C0WUPMK = IF_Mask_Flag;  // 0 - Interrupt servicing enabled
							// 1 - Interrupt servicing Disabled	
}

/***********************************************************************************************************************
* Function Name: GEM_CAN_Init
* Description  : 
* Arguments    : Baud_Rate
* Return Value : None
***********************************************************************************************************************/
void GGEM_CAN_Init_new(uint8_t Baud_Rate)
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
	GCAN_0_Receive_Interrupt(CLEAR_IF_FLAG,ENABLE_INTERRUPT,INT_Priority_High);		
	/* ********************    Transmit Interrupt settings ****************************************************** */
	GCAN_0_Transmit_Interrupt(CLEAR_IF_FLAG,ENABLE_INTERRUPT,INT_Priority_Level_1);
	/* ********************    CAN Error Interrupt settings ****************************************************** */
	GCAN_0_Error_Interrupt(CLEAR_IF_FLAG,ENABLE_INTERRUPT,INT_Priority_Low);	
	/* ********************    Wakeup Interrupt settings ****************************************************** */
	GCAN_0_Wakeup_Interrupt(CLEAR_IF_FLAG,DISABLE_INTERRUPT);


	C0CTRL   =  0x817E;   	// clear AL,VALID(no receive valid message),PSMODE1,PSMODE0(no power save mode)
				 	        // clear OPMODE2,OPMODE1 and set OPMODE0(normal mode) 
				 	        // set CCERC(clear C0ERC and C0INFO registers in initialization mode) 
    GGEM_CAN_MsgBuf_Init();
	
    GEM_Rx_MsgBuf_Init(9,0x18FF035A,NO_MASK,IDE_EXT);
		
	GEM_RX_Mask_MsgBuf_Init(0x00000F3A,MASK_BUFFER_1,  IDE_EXT);
	GEM_Rx_MsgBuf_Init(10,0x18FF0F7A,MASK_BUFFER_1,IDE_EXT); //Mask_Value 0x00002f00
	
	GEM_Rx_MsgBuf_Init(11,0x14520902,NO_MASK,IDE_EXT);

	GEM_RX_Mask_MsgBuf_Init(0x04000006,MASK_BUFFER_3,  IDE_EXT);
	GEM_Rx_MsgBuf_Init(12,0x1C530906,MASK_BUFFER_3,IDE_EXT); //Mask_Value 0x04000006

	GEM_Rx_MsgBuf_Init(13,0x3AA,NO_MASK,IDE_STD);

	GEM_RX_Mask_MsgBuf_Init(0x706,MASK_BUFFER_2,  IDE_STD);
	GEM_Rx_MsgBuf_Init(14,0x7A8,MASK_BUFFER_2,IDE_STD); //Mask_Value 0x706
	GEM_Rx_MsgBuf_Init(15,0x150,NO_MASK,IDE_STD);

    Gokul_GEM_Tx_MsgBuf_Init(0);
}
/***********************************************************************************************************************
* Function Name: GEM_CAN_MsgBuf_Init
* Description  : 
* Arguments    : none
* Return Value : None
***********************************************************************************************************************/
//----------------------------------------------------------------------------------------------------------------
void GGEM_CAN_MsgBuf_Init(void)
{
	uint8_t	buffer_number;
    volatile uint16_t  *C0MCTRLm; // uint16_t  *C0MCTRLm = ((uint16_t *)(MsgBuf_address + 0x0e));
    volatile uint8_t *C0MCONFm;

	for (buffer_number = 0 ; buffer_number < 16 ; buffer_number++)		// Init all message buffer
	{
        C0MCTRLm = ((uint16_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x0E));	// Set CAN message buffer[n] register address
        *C0MCTRLm = 0x0006;
        *C0MCTRLm = 0x0001;
        C0MCONFm = ((uint8_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x09));
        //*C0MCONFm &= 0xf8; 
        *C0MCONFm = 0x00;
	}
}

/***********************************************************************************************************************
* Function Name: GEM_Tx_MsgBuf_Init
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
//----------------------------------------------------------------------------------------------------------------
void Gokul_GEM_Tx_MsgBuf_Init(uint8_t buffer_number)
{
	uint8_t data_cnt;
    
    volatile uint8_t     *C0MDBxm   = ((uint8_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x00));
    volatile uint8_t     *C0MDLCm   = ((uint8_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x08));
    volatile uint8_t     *C0MCONFm  = ((uint8_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x09));
    volatile uint16_t    *C0MIDLm   = ((uint16_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x0A));
    volatile uint16_t    *C0MIDHm   = ((uint16_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x0C));
    volatile uint16_t    *C0MCTRLm  = ((uint16_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x0E));

    *C0MCONFm = 0x01;
    *C0MIDLm = 0x0000;
    *C0MIDHm = 0x0000;
    *C0MDLCm = 0x00;

    for(data_cnt = 0 ; data_cnt < 8 ; data_cnt++)			
	{
        C0MDBxm = C0MDBxm + data_cnt;
		*C0MDBxm = 0x00;
	}
	#if 1
	*C0MCTRLm = 0x001e;  // C0MCTRLm
								// clear MOW,IE,DN,TRQ bit
								// MOV=0,The message buffer is not overwritten by a newly received data frame.
								// IE=0,Normal message transmission completion interrupt disabled
								// DN=0,A data frame or remote frame is not stored in the message buffer.
								// TRQ=0,No message frame transmitting request that is pending or being transmitted
	#endif

	#if 0							
	*C0MCTRLm = 0x0816;  // clear MOW,DN,TRQ bit
								// set IE=1,Normal message transmission completion interrupt enabled
	#endif
	
	*C0MCTRLm = 0x0100; 	// // Set RDY bit,The CAN module can write to the message buffer
}

void GGEM_TX_Msg_Abort(uint8_t buffer_number)
{
    volatile uint16_t    *C0MCTRLm  = ((uint16_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x0E));
    uint8_t	tx_buffer_number;

    *C0MCTRLm = 0x0002;
    while((C0CTRL & 0x0100) != 0)
    {
        NOP();
    }

    tx_buffer_number = C0LOPT;
    if (tx_buffer_number == buffer_number)
    {
        NOP();
    }

}

void GGEM_Tx_MsgBuf_Processing_new(uint8_t buffer_number, CAN_TX_Message_t *CAN_TX_Message)
{
    uint8_t data_cnt;
    
    volatile uint8_t     *C0MDBxm   = ((uint8_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x00));
    volatile uint8_t     *C0MDLCm   = ((uint8_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x08));
    volatile uint8_t     *C0MCONFm  = ((uint8_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x09));
    volatile uint16_t    *C0MIDLm   = ((uint16_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x0A));
    volatile uint16_t    *C0MIDHm   = ((uint16_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x0C));
    volatile uint16_t    *C0MCTRLm  = ((uint16_t *)((MSGBUF_BASE_ADD + (0x10 * buffer_number)) + 0x0E));

    while (( (*C0MCTRLm) & 0x0002) != 0)
	{
		NOP();
		GGEM_TX_Msg_Abort(buffer_number);
	}

    *C0MCTRLm = 0x0001;
    if(((*C0MCTRLm) & 0x0001) == 0)
	{
		if(CAN_TX_Message->m_nDlc <= 8)
		{
			if ((CAN_TX_Message->m_nExtFlg == 1) && (CAN_TX_Message->CAN_Msg_ID > 0x7FF))
			{
				*C0MIDLm = (uint32_t) CAN_TX_Message->CAN_Msg_ID;   			
				*C0MIDHm = (uint32_t)((CAN_TX_Message->CAN_Msg_ID >> 16) | 0x8000); 	//C0MIDHm
			}
			else
			{
				*C0MIDLm = 0x0000;   			//standard frame,C0MIDLm=0x0000;
				*C0MIDHm = ((CAN_TX_Message->CAN_Msg_ID << 2) & 0x1FFC); 	//C0MIDHm
			}
			*C0MDLCm = CAN_TX_Message->m_nDlc;
			//*C0MCONFm = ((*C0MCONFm) | (CAN_TX_Message->m_nRtr << 6));
			//*C0MCONFm = 0x40;
			for(data_cnt = 0 ; ((data_cnt < CAN_TX_Message->m_nDlc) && (data_cnt<8)) ; data_cnt++)
			{
				*C0MDBxm = CAN_TX_Message->m_nData[data_cnt];
				//*C0MDBxm = data_cnt+1;
				C0MDBxm = C0MDBxm + 1;
			}
            		//*C0MDBxm = CAN_TX_Message->m_nData[3];
		}
		*C0MCTRLm = 0x0100;
		*C0MCTRLm = 0x0200;
	}
    /*while (( (*C0MCTRLm) & 0x0002) == 0)
	{
		NOP();
	}*/
}