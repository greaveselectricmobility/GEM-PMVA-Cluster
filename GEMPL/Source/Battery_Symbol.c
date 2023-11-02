/***********************************************************************************************************************
* File Name    : Battery_Symbol.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the Battery symbol blink and its interval.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include "GEM_common_header.h"
#include "Battery_Symbol.h"
#include "lcd.h"
/***********************************************************************************************************************
* Function Name: BMS_Symbol_blink
* Description  : This function implements the blinking rate of battery symbol under various conditions .
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
uint8_t BMS_Symbol_blink(int blink_rate_interval, int blink_ctrl,uint32_t gem_timer)
{
    static uint32_t prev_bms_symbol_ms = 0;
    static uint8_t bms_sym_state = ON;
    if (blink_ctrl)
    {
	    if ((gem_timer - prev_bms_symbol_ms) >= blink_rate_interval)
	    {
	        if(!bms_sym_state)
	        {
	            bms_sym_state= ON;
	        }
	        else
	        {
	            bms_sym_state= OFF;
	        }
	        prev_bms_symbol_ms = gem_timer;   
	    }
    }
    else
    {
	    bms_sym_state= OFF;
	    prev_bms_symbol_ms = gem_timer;
    }
    return bms_sym_state;
}

//void Battery_symbol_Red_check(BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
/***********************************************************************************************************************
* Function Name: Battery_symbol_Red_check
* Description  : This function implements the functionality for the battery telltale for various conditions.
* Arguments    : Cluster_Data, gem_timer
* Return Value : None
***********************************************************************************************************************/
void Battery_symbol_Red_check(Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
{    
    uint8_t BMS_Symbol_State = OFF;  // 0: OFF, 1-ON, 2: 1 Sec blink for BMS Value error. 3: 2 second blink,
    if ((Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.ERR_THRMLRUNWY_WARNG == 0x01) && (Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.THRMLRUNWY_STS != 0x01))
    {
        BMS_Symbol_State = BMS_Symbol_blink(20,ENABLE,gem_timer);
        Cluster_Data->LCD_TellTale_Symbol.bit.Battery_TT = 1;
		Cluster_Data->CAN_Tx_TT.BMS_High_Temp = 1;
        
    }
    else if (Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.BMS_ERR_DET == 0x01)
    {
       	BMS_Symbol_blink(0,DISABLE,gem_timer);
        BMS_Symbol_State = ON;
        Cluster_Data->LCD_TellTale_Symbol.bit.Battery_TT = 1;
		Cluster_Data->CAN_Tx_TT.BMS_Failure = 2;
    }
    else if (Cluster_Data->CAN_Value_error.bit.BMS_Value_Error == 0x01)
    {
        BMS_Symbol_State = BMS_Symbol_blink(10,ENABLE,gem_timer);
        Cluster_Data->LCD_TellTale_Symbol.bit.Battery_TT = 1;
		Cluster_Data->CAN_Tx_TT.BMS_Failure = 1;
    }
    else
    {
        BMS_Symbol_State =OFF;
        BMS_Symbol_blink(0,DISABLE,gem_timer);
        Cluster_Data->LCD_TellTale_Symbol.bit.Battery_TT = 0;
		Cluster_Data->CAN_Tx_TT.BMS_Failure = 0;
    }
    gem_err_indication(BATTERY_ON,BMS_Symbol_State);
    //BMS_Symbol_LCD(BMS_Symbol_State);
}