/***********************************************************************************************************************
* File Name    : my_can.c
* Version      : 
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the CAN configuration.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/


//--------------------------3W--------------------------------------------------------------------------------------
#include "r_cg_macrodriver.h"
#include "my_can.h"
#include "iodefine.h"
#include "GEM_can.h"
//#include "GPIO.h"
#include "CAN_Configure.h"

//#include "Calculation.h"

//----------------------------------------------------------------------------------------------------------------
// #pragma	interrupt MY_Rx_MsgBuf_Processing(vect=INTC0REC)
// #pragma	interrupt MY_ISR_CAN_Error(vect=INTC0ERR)
// #pragma interrupt MY_ISR_CAN_Wakeup(vect=INTC0WUP)
// #pragma	interrupt INT_Tx(vect=INTC0TRX)

//----------------------------------------------------------------------------------------------------------------
uint8_t tx_msg_data[8];
uint8_t Rx_Databuf[8];
uint16_t raw_soc;
 _Bool mcu_flag,bms_flag,can_flag;
 
 /* CAN_variable*/
  uint8_t  FWD_gear;
  uint8_t  NEUTRAL_gear;
  uint8_t PARKING_ind;
 
 uint8_t therml_Runawy;
 uint8_t SOC_Data;
 uint8_t SOC;
 uint8_t mode_3;
 uint8_t throttle_err_3;
 uint8_t mcu_err_3;
 uint8_t Vehicle_rpm_3;
 uint8_t motor_err_3;
 uint8_t bat_fault_3;
 uint8_t charging_status;
 uint8_t Reverse_Mode;
 uint16_t rpm_3;
 uint8_t motor_temp;
 int8_t bat_temp;

 uint8_t batt_full;
 uint8_t batt_low;
 uint8_t BMS_State;
 uint8_t Thermal_Runaway_earl_warn;

//----------------------------------------------------------------------------------------------------------------
void Grg_CAN_Init(void)
{
	SCAN0 = 1;			// 1-CAN pins on P00(TX) & P01(RX)
	
    PM3_bit.no7 = 0;		// CAN standby
	P3_bit.no7  = 1;
	P3_bit.no7  = 0;
	
	P0_bit.no0  = 1;
	PM0_bit.no0 = 0;		// CAN TX
	
	P0_bit.no1  = 1;
	PM0_bit.no1 = 1;		//CAN RX //IRK 
	
	PCKSEL = 0x10;
	C0GMCS  = 0x03;         	// CAN module clock select, fCANMOD = fCAN/4--> 32MHz/4-->8MHz
	C0GMCTRL= 0x0100;       	// set GOM=1; enable CAN module operation
	C0BRP	= 0x01;			// fTQ=fCANMOD/1-->8MHz/1-->4MHz-->500kbps
	C0BTR	= 0x0104;      		// Baud-rate: 500kbps
					// SYNC Jump width --> 1TQ
					// Time segment 2 --> 2TQ
					// Time segment 1 --> 5TQ
	C0IE = 0x3f00;
	
 /* ********************    Receiver Interrupt settings ****************************************************** */		
	C0RECIF  = 0;			// clear receive interrupt flag
	C0RECMK  = 0;			// Enable Receive interrupt
	C0RECPR0 = 0;
        C0RECPR1 = 0;  /* The intrrupt priority level is set to High priority */
	
 /* ********************    Transmit Interrupt settings ****************************************************** */
        C0TRXIF  = 0;  /* Interrupt request flag is cleared at initial */ 
        C0TRXMK  = 0;   // enabe transmit interupt
        C0TRXPR0 = 0;
        C0TRXPR0 = 0;  /* The intrrupt priority level is set to High priority */

/* ********************    CAN Error Interrupt settings ****************************************************** */
        C0ERRIF  = 0;	// clear error interrupt flag
	C0ERRMK  = 0;	// enable error interrupt
	C0ERRPR0 = 0; /* Error Interrupt priority set to High priority */
        C0ERRPR1 = 0;
	
/* ********************    Wakeup Interrupt settings ****************************************************** */
	C0WUPIF = 0;			// clear wakeup interrupt flag
	C0WUPMK = 0;			// enable wakeup interrupt 


	C0CTRL   =  0x817E;   	// clear AL,VALID(no receive valid message),PSMODE1,PSMODE0(no power save mode)
				 	        // clear OPMODE2,OPMODE1 and set OPMODE0(normal mode) 
				 	        // set CCERC(clear C0ERC and C0INFO registers in initialization mode) 
    MY_CAN_MsgBuf_Init();
    //MY_Rx_MsgBuf_Init(1,0x18FF015A); //BMS fault Battery fault   0x18FF1D5A
   // MY_Rx_MsgBuf_Init(2,0x18FF025A); //Battery soc
   // MY_Rx_MsgBuf_Init(3,0x18FF035A); //new_BMS State
   // MY_Rx_MsgBuf_Init(4,0x14520902); //Vechicle Speed
    
    //MY_Rx_MsgBuf_Init(5,0x18FF1D5A); //thermal runaway
    //MY_Rx_MsgBuf_Init(6,0x18530902); //drive mode//MCU Error//Motor Error//Throttle failure/motor_temp
   // MY_Rx_MsgBuf_Init(7,0x18FF045A); //bat_temp
   // MY_Rx_MsgBuf_Init(8,0x2AA);      //soc 
   
    MY_Rx_MsgBuf_Init(0,0x18FF015A); //BAT_ERR,BAT_FUL CHRG
    MY_Rx_MsgBuf_Init(8,0x1AA);      //BAT_ERR,BAT_FUL CHRG
    MY_Rx_MsgBuf_Init(1,0x18FF025A); //BAT_soc
    MY_Rx_MsgBuf_Init(9,0x2AA);      //BAT_soc
    MY_Rx_MsgBuf_Init(2,0x18FF035A); //BMS state
    MY_Rx_MsgBuf_Init(10,0x3AA);      //BMS state
    MY_Rx_MsgBuf_Init(3,0x18FF0D5A); //thermal runaway_early warn (>60)
    MY_Rx_MsgBuf_Init(11,0x4AC);      //thermal runaway_early warn (>60)
    MY_Rx_MsgBuf_Init(4,0x18FF0060); //thermal runaway
    MY_Rx_MsgBuf_Init(12,0x150);      //thermal runaway
    MY_Rx_MsgBuf_Init(5,0x14520902); //Vechicle Speed
    MY_Rx_MsgBuf_Init(6,0x18530902); //drive mode//MCU Error//Motor Error//Throttle failure/motor_temp
    //MY_Rx_MsgBuf_Init(7,0x18FF045A); //bat_temp
    //MY_Rx_MsgBuf_Init(13,0x4AA);      //bat_temp
    MY_Rx_MsgBuf_Init(14,0x18530904); 
    MY_Rx_MsgBuf_Init(15,0x1C530902); 
    MY_Rx_MsgBuf_Init(7,0x7DF);
    MY_Tx_MsgBuf_Init(13,0x7DA,8);
	
   //clear_CAN_data();
}
void MY_CAN_MsgBuf_Init(void)
{
	uint8_t	buffer_number;
	int32_t	MsgBuf_address;

	for (buffer_number = 0 ; buffer_number < 16 ; buffer_number++)		// Init all message buffer
	 {
		
		MsgBuf_address = (MSGBUF_BASE_ADD + (0x10 * buffer_number));	// Set CAN message buffer[n] register address
		
		*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0006;		// Clear TRQ, DN bit
				
		*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0001;		// Clear RDY bit
		
		*((uint8_t *)(MsgBuf_address + 0x09)) &= 0xf8;		// Clear MA0 bit
	 }
}
void MY_Tx_MsgBuf_Init(uint8_t buffer_number,unsigned int tx_msg_ID,uint8_t tx_msg_DLC)
{
	uint32_t	MsgBuf_address;
	uint8_t data_cnt;
	
	MsgBuf_address = (MSGBUF_BASE_ADD + (0x10 * buffer_number));		// Set CAN message buffer[n] register address

	*((uint8_t *)(MsgBuf_address + 0x09)) = 0x01;      		// Set C0MCONFm register, Transmit message buffer, MA0=1,msg buffer used

if (tx_msg_ID > 0x7FFF)
{
	*((uint16_t *)(MsgBuf_address + 0x0a)) = (uint16_t)(tx_msg_ID);   		// standard frame,C0MIDLm=0x0000;
	*((uint16_t *)(MsgBuf_address + 0x0c)) = (uint32_t)((tx_msg_ID >>16) | 0x8000); 	// C0MIDHm
}
else
{
	*((uint16_t *)(MsgBuf_address + 0x0a)) = 0x0000;   		// standard frame,C0MIDLm=0x0000;
	*((uint16_t *)(MsgBuf_address + 0x0c)) = ((tx_msg_ID << 2) & 0x1fff); 	// C0MIDHm
}

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
void MY_Rx_MsgBuf_Init(uint8_t buffer_number,int32_t rx_mask_ID)
{
		unsigned long	MsgBuf_address;

	
	MsgBuf_address = (MSGBUF_BASE_ADD + (0x10 * buffer_number));		// Set CAN message buffer[n] register address

	// Set C0MCONFm register 
	*((unsigned char *)(MsgBuf_address + 0x09)) = 0x09;     // Receive message buffer(no mask), MA0=1,msg buffer used
	if (rx_mask_ID > 0x7FFF)
	{
		*((unsigned short *)(MsgBuf_address + 0x0a)) = (unsigned int) rx_mask_ID;   			//standard frame,C0MIDLm=0x0000;
		*((unsigned short *)(MsgBuf_address + 0x0c)) = (unsigned long)((rx_mask_ID >> 16) | 0x8000); 	//C0MIDHm
	}
	else
	{
		*((unsigned short *)(MsgBuf_address + 0x0a)) = 0x0000;   			//standard frame,C1MIDLm=0x0000;
		*((unsigned short *)(MsgBuf_address + 0x0c)) = ((rx_mask_ID << 2) & 0x1fff); 	//C1MIDHm
	}
	
	
	*((unsigned short *)(MsgBuf_address + 0x0e)) = 0x0916;  // Set C0MCTRLm register 
								// clear MOW,DN,TRQ bit
								// MOV=0,The message buffer is not overwritten by a newly received data frame.
								// set IE=1,Valid message reception completion interrupt enabled.
								// DN=0,A data frame or remote frame is not stored in the message buffer.
								// TRQ=0,No message frame transmitting request that is pending or being transmitted
	
	//*((unsigned short *)(MsgBuf_address + 0x0e)) = 0x001F;  // Set RDY bit,The CAN module can write to the message buffer
	*((unsigned short *)(MsgBuf_address + 0x0e)) = 0x0100;  // Set RDY bit,The CAN module can write to the message buffer

}
void MY_Tx_MsgBuf_Processing(uint8_t buffer_number,uint8_t tx_msg_DLC,uint8_t* tx_msg_data)
{
	int32_t	MsgBuf_address;
	uint16_t  C0MCTRLm;
	uint8_t data_cnt;
	
	MsgBuf_address = (MSGBUF_BASE_ADD + (0x10 * buffer_number));	// Set CAN message buffer[n] register address

	C0MCTRLm = *((uint8_t *)(MsgBuf_address + 0x0e));		// Check TRQ bit
	//while((C0MCTRLm & 0x0002) != 0)
	//{
	//	NOP();//return;
	//}

	
	*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0001;    	// Clear RDY bit ,The message buffer can be written by software.
	
	C0MCTRLm = *((uint8_t *)(MsgBuf_address + 0x0e));

	
	if((C0MCTRLm & 0x0001) == 0)					// Set C0MDATAxm register
	{
		
		
		for(data_cnt = 0 ; data_cnt < tx_msg_DLC ; data_cnt++)
		{
			*((uint8_t *)(MsgBuf_address + (0x01 * data_cnt))) = tx_msg_data[data_cnt];    //clear each byte data=0x00
		}
		
		//*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0800;	// Set EI bit-pratik
		*((uint16_t *)(MsgBuf_address + 0x0e)) =  0x0100;	// Set RDY bit
		
		*((uint16_t *)(MsgBuf_address + 0x0e)) = 0x0200;	// Set TRQ bit
	}
	
	//while((C0MCTRLm & 0x0002) == 0x0002)
	//{
	//	NOP();
	//	NOP();
	//}
	//return;
}
//----------------------------------------------------------------------------------------------------------------
static void __near MY_Rx_MsgBuf_Processing(void)
{
	
  //Grg_CAN_RX_Process();
  GEM_CAN_RX_DATA_Processing();
}
void Grg_CAN_RX_Process(void)
{
	unsigned long	MsgBuf_address,check;
	unsigned char	rx_msg_DLC;
	unsigned char	rx_data_cnt;
	unsigned short 	rx_msg_ID_L,rx_msg_ID_H;
	unsigned long	rx_msg_ID ;
	unsigned char   rx_buffer_number;
	uint8_t i;
	C0INTS = 0x0002;
	
	rx_buffer_number = C0LIPT;						// Get receive message buffer number
	for(i =0;i<9;i++)
	{
		Rx_Databuf[i]=0;
	}
	
	MsgBuf_address = (MSGBUF_BASE_ADD + (0x10 * rx_buffer_number));		// Set CAN message buffer[n] register address
	
	while(((*((unsigned short *)(MsgBuf_address + 0x0e))) & 0x2004) != 0) 	//check DN and MUC bit
	{
		can_flag=1;
		
		*((unsigned short *)(MsgBuf_address + 0x0e)) = 0x0004;		// Clear DN bit
		
		rx_msg_DLC = *((unsigned char *)(MsgBuf_address + 0x08));	// Get receive message data length
		check=(((*((unsigned short *)(MsgBuf_address + 0x0C))))&(0x8000));
	
                if((0x8000)!=(check)) //std_id
                  {
	                rx_msg_ID = (*((unsigned short *)(MsgBuf_address + 0x0C)))>>2;	// Get receive message ID
                  }
              else   //ext_id
                  {	  
		            rx_msg_ID_L = (*((unsigned short *)(MsgBuf_address + 0x0A)));	// Get receive message ID
		            rx_msg_ID_H = ((*((unsigned short *)(MsgBuf_address + 0x0C))) & (0x1fff));     //standard frame,just need C0MIDHm,C0MIDLm=0x0000
		            rx_msg_ID   = (unsigned long)((((rx_msg_ID_H)|(0xffff0000))<<16) | (rx_msg_ID_L));
                  }
		  for(rx_data_cnt = 0 ;((rx_data_cnt < rx_msg_DLC) && (rx_data_cnt < 8)) ; rx_data_cnt++)
		{
			Rx_Databuf[rx_data_cnt] = *((uint8_t *)(MsgBuf_address + (0x01 * rx_data_cnt)));	// Get receive data
		}
		

		switch(rx_msg_ID)
		{
			case (0x18FF015A):	//BMA & BATTERY ERROR
			   
				 
			     bat_fault_3 =  ((0x02)&(Rx_Databuf[1]));
			     //charging_status =  ((0x08)&(Rx_Databuf[1]));
			     batt_full = ((0x04)&(Rx_Databuf[0]));
			     batt_low = ((0x10)&(Rx_Databuf[0]));
			     bms_flag=0;
			     __nop();
			     break;
			case (0x1AA):	//BMA & BATTERY ERROR
			 
				 
			     bat_fault_3 =  ((0x02)&(Rx_Databuf[1]));
			     //charging_status =  ((0x08)&(Rx_Databuf[1]));
			     batt_full = ((0x04)&(Rx_Databuf[0]));
			     batt_low = ((0x10)&(Rx_Databuf[0]));
			     bms_flag=0;
			     __nop();
			     break;
			case (0x18FF025A):		//Battery Soc
			      //Rx_Databuf[0] = *((uint8_t *)(MsgBuf_address + (0x01 * 0))); 
			      SOC_Data =  (uint8_t)(Rx_Databuf[0]);
			      bms_flag=0;
			      __nop();
			       break;
			case (0x2AA):		//Battery Soc
			      //Rx_Databuf[0] = *((uint8_t *)(MsgBuf_address + (0x01 * 0))); 
			      SOC_Data =  (uint8_t)(Rx_Databuf[0]);
			      bms_flag=0;
			      __nop();
			       break;
			case (0x18FF035A):	
			      //Rx_Databuf[0] = *((uint8_t *)(MsgBuf_address + (0x01 * 0))); 
			      BMS_State =  (uint8_t)(Rx_Databuf[7]);
			      bms_flag=0;
			      __nop();
			       break;
			case (0x3AA):		//Battery Soc
			      //Rx_Databuf[0] = *((uint8_t *)(MsgBuf_address + (0x01 * 0))); 
			      BMS_State =  (uint8_t)(Rx_Databuf[7]);
			      bms_flag=0;
			      __nop();
			       break;
			case (0x18FF045A):	//bat_temp
			    //Rx_Databuf[5] = *((uint8_t *)(MsgBuf_address + (0x01 * 5))); 
			    bat_temp =  (signed char)(Rx_Databuf[5]);
			    bms_flag=0;
			    __nop();
			    break;  
			case (0x4AA):	//bat_temp
			    //Rx_Databuf[5] = *((uint8_t *)(MsgBuf_address + (0x01 * 5))); 
			    bat_temp =  (signed char)(Rx_Databuf[5]);
			    bms_flag=0;
			    __nop();
			    break;
			case (0x18FF0D5A):	//Thermal Runaway early warning
			     //Rx_Databuf[0] = *((uint8_t *)(MsgBuf_address + (0x01 * 0)));
				 
			     Thermal_Runaway_earl_warn =  ((0x80)&(Rx_Databuf[6]));
			     bms_flag=0;
			     __nop();
			     break;
			case (0x4AC):	//Thermal Runaway eary warning
			     //Rx_Databuf[0] = *((uint8_t *)(MsgBuf_address + (0x01 * 0)));
				 
			     Thermal_Runaway_earl_warn =  ((0x80)&(Rx_Databuf[6]));
			     bms_flag=0;
			     __nop();
			     break;
			case (0x18FF0060):	//Thermal Runaway
			     //Rx_Databuf[0] = *((uint8_t *)(MsgBuf_address + (0x01 * 0)));
				 
			     therml_Runawy =  ((0x03)&(Rx_Databuf[0]));
			     bms_flag=0;
			     __nop();
			     break;
			case (0x150):	//Thermal Runaway
			     //Rx_Databuf[0] = *((uint8_t *)(MsgBuf_address + (0x01 * 0)));
				 
			     therml_Runawy =  ((0x03)&(Rx_Databuf[0]));
			     bms_flag=0;
			     __nop();
			     break;
			case (0x14520902):	//Vehicle Speed
			     //Rx_Databuf[0] = *((uint8_t *)(MsgBuf_address + (0x01 * 0)));
			     //Rx_Databuf[1] = *((uint8_t *)(MsgBuf_address + (0x01 * 1)));
				 
			     rpm_3 = ((Rx_Databuf[1]<<8)|(Rx_Databuf[0]));
			     mcu_flag=0;
			     __nop();
			     break;
			case (0x18530902):	//drive mode//motor error//MCU error
			     //Rx_Databuf[1] = *((uint8_t *)(MsgBuf_address + (0x01 * 1)));
			     //Rx_Databuf[2] = *((uint8_t *)(MsgBuf_address + (0x01 * 2)));
			     //Rx_Databuf[3] = *((uint8_t *)(MsgBuf_address + (0x01 * 3))); 
			     
			     motor_temp     = (uint8_t)(Rx_Databuf[3]);
			     mode_3         = (uint8_t)((0x03)&(Rx_Databuf[1]));
			     Reverse_Mode   = (uint8_t)((0x08)&(Rx_Databuf[1]));
			     throttle_err_3 = (uint8_t) ((0x20)&(Rx_Databuf[2]));
			     mcu_err_3      = (uint8_t) ((0x40)&(Rx_Databuf[2]));
			     motor_err_3    = (uint8_t) ((0x80)&(Rx_Databuf[2]));
			     
			     FWD_gear     = ((0x02)&Rx_Databuf[4]);
			     NEUTRAL_gear = ((0x04)&Rx_Databuf[4]);
			     PARKING_ind  = ((0x04)&Rx_Databuf[1]);
			  
			     mcu_flag=0;
			     __nop();
			     break;
		}	
	}
}

uint16_t get_RPM(void)
{
	return rpm_3;
}
uint8_t get_SOC(void)
{
	return SOC_Data;
}
/***********************************************************************************************************************
* Function Name:  
* Description  :   
* Arguments    : None
* Return Value : None 
***********************************************************************************************************************/  
void MY_CAN_SleepMode_Setting(void)
{
	C0CTRL = 0x0810;   			// set PSMODE0=1,PSMODE1=0, setting CAN sleep mode
	while((C0CTRL&0x0008) == 0); 		// check PSMODE0=1
} 
/***********************************************************************************************************************
* Function Name:  
* Description  :   
* Arguments    : None
* Return Value : None 
***********************************************************************************************************************/ 
void MY_CAN_StopMode_Setting(void)
{
	MY_CAN_SleepMode_Setting();
	C0CTRL = 0x1800;   			// set PSMODE0=1,PSMODE1=1, setting CAN stop mode
	while((C0CTRL&0x0010) == 0); 		// check PSMODE1=1
} 
/***********************************************************************************************************************
* Function Name:  
* Description  :   
* Arguments    : None
* Return Value : None 
***********************************************************************************************************************/ 
void MY_CAN_StopMode_Release(void)
{
	C0CTRL = 0x0810;   			// clear PSMODE1=0, release stop mode to sleep mode
} 
/***********************************************************************************************************************
* Function Name:  
* Description  :   
* Arguments    : None
* Return Value : None 
***********************************************************************************************************************/ 
void MY_CAN_SleepMode_Release(void)
{
	C0CTRL = 0x0008;    			// clear PSMODE0=0,release sleep mode by software
	
	#if 0
	//Sleep mode can also be released by a falling edge at the CAN reception pin---wakeup signal
	C0INTS = 0x0020;    			// clear CINTS5(Wakeup interrupt)
	#endif
} 
/***********************************************************************************************************************
* Function Name:  
* Description  :   
* Arguments    : None
* Return Value : None 
***********************************************************************************************************************/ 
static void __near MY_ISR_CAN_Wakeup(void)
{
	C0INTS = 0x0020;    			// clear CINTS5(Wakeup interrupt)
} 
/***********************************************************************************************************************
* Function Name:  
* Description  :   
* Arguments    : None
* Return Value : None 
***********************************************************************************************************************/ 
static void __near MY_ISR_CAN_Error(void)
{
	C0INTS = 0x001C;
       // Grg_CAN_Init();
}
static void __near INT_Tx(void)
{
	NOP();
}

void Grg_CAN_err_Recovery(void)
{
	if((C0INTS) == (0x001C))
	{
	 Grg_CAN_Init();
	}
}

void clear_CAN_data(void)
{
  //Thermal_runaway =0;
  SOC_Data=0;
  SOC=0;
  mode_3=0;
  throttle_err_3=0;
  mcu_err_3=0;
  Vehicle_rpm_3=0;
  motor_err_3=0;
  bat_fault_3=0;
  charging_status=0;
  Reverse_Mode=0;
  rpm_3=0;
  motor_temp=0;
  bat_temp=0;

}
//----------------------------------------------------------------------------------------------------------------
