/***********************************************************************************************************************
* File Name    : Temperature_symbol.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the temperature symbol and its intervals.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include "GEM_common_header.h"
#include "Temperature_symbol.h"
#include "lcd.h"


/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
uint8_t Temperature_Symbol_blink(int blink_rate_interval, int blink_ctrl,uint32_t gem_timer)
{
    static uint32_t prev_temp_symbol_ms = 0;
    static uint8_t temp_sym_state = ON;
    if (blink_ctrl)
    {
	    if ((gem_timer - prev_temp_symbol_ms) >= blink_rate_interval)
	    {
	        if(!temp_sym_state)
	        {
	            temp_sym_state= ON;
	        }
	        else
	        {
	            temp_sym_state= OFF;
	        }
	        prev_temp_symbol_ms = gem_timer;   
	    }
    }
    else
    {
	    temp_sym_state= OFF;
	    prev_temp_symbol_ms = gem_timer;
    }
    return temp_sym_state;
}

//void Temperature_symbol_check(BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void Temperature_symbol_check(Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
{
    uint8_t Temp_Symbol_State;   // 0: OFF, 1-ON, 2: 1 Sec blink  3: 2 second blink,  
    if ((Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.ERR_THRMLRUNWY_WARNG == 0x01) && (Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.THRMLRUNWY_STS != 0x01))
    {
        Temp_Symbol_State = Temperature_Symbol_blink(20,ENABLE,gem_timer);
        Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT = 1;
        Cluster_Data->CAN_Tx_TT.Thermal_Run_Away = 1;
        Cluster_Data->CAN_Tx_TT.MCU_Temp_High = 0;
        Cluster_Data->CAN_Tx_TT.Motor_Temp_High = 0;
		
        //gem_err_indication(TOP_BOTTOM_LINE,ON);
    }
    else if ((Cluster_Data->CAN_Data.MCU_Temperature >= 105))
    {
        Temperature_Symbol_blink(0,DISABLE,gem_timer);
        Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT = 1;
        Cluster_Data->CAN_Tx_TT.MCU_Temp_High = 2;
        Cluster_Data->CAN_Tx_TT.Motor_Temp_High = 0;
        Cluster_Data->CAN_Tx_TT.Thermal_Run_Away = 0;

	    Temp_Symbol_State = ON;
    }
    else if ((Cluster_Data->CAN_Data.Motor_Temperature >= 180))
    {
        Temperature_Symbol_blink(0,DISABLE,gem_timer);
        Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT = 1;
        Cluster_Data->CAN_Tx_TT.Motor_Temp_High = 2;
        Cluster_Data->CAN_Tx_TT.MCU_Temp_High = 0;
        Cluster_Data->CAN_Tx_TT.Thermal_Run_Away = 0;
	    Temp_Symbol_State = ON;
    }
    else if ((Cluster_Data->CAN_Data.MCU_Temperature > 85) && (Cluster_Data->CAN_Data.MCU_Temperature < 105))
    {
	    Temp_Symbol_State = Temperature_Symbol_blink(10,ENABLE,gem_timer);
        Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT = 1;
        Cluster_Data->CAN_Tx_TT.MCU_Temp_High = 1;
        Cluster_Data->CAN_Tx_TT.Motor_Temp_High = 0;
        Cluster_Data->CAN_Tx_TT.Thermal_Run_Away = 0;
        //gem_err_indication(TOP_BOTTOM_LINE,ON);
    }
    else if ((Cluster_Data->CAN_Data.Motor_Temperature > 160) && (Cluster_Data->CAN_Data.Motor_Temperature < 180))
    {
	    Temp_Symbol_State = Temperature_Symbol_blink(10,ENABLE,gem_timer);
        Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT = 1;
        Cluster_Data->CAN_Tx_TT.Motor_Temp_High = 1;
        Cluster_Data->CAN_Tx_TT.Thermal_Run_Away = 0;
        Cluster_Data->CAN_Tx_TT.MCU_Temp_High = 0;
        //gem_err_indication(TOP_BOTTOM_LINE,ON);
    }
    else
    {
        Temp_Symbol_State = OFF;
        Temperature_Symbol_blink(0,DISABLE,gem_timer);
        Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT = 0;
        //gem_err_indication(TOP_BOTTOM_LINE,OFF);
        Cluster_Data->CAN_Tx_TT.MCU_Temp_High = 0;
        Cluster_Data->CAN_Tx_TT.Motor_Temp_High = 0;
        Cluster_Data->CAN_Tx_TT.Thermal_Run_Away = 0;
    }
    gem_err_indication(TEMP_ON,Temp_Symbol_State);
    //Temperature_Symbol_LCD(Temp_Symbol_State);
}
