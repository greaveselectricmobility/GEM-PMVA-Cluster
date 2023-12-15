/***********************************************************************************************************************
* File Name    : Thermal_Runaway.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the thermal runaway condition.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include "GEM_common_header.h"
#include "Thermal_Runaway.h"
#include "lcd.h"

//void Thermal_Runaway_symbol_check(BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void Thermal_Runaway_symbol_check(Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
{
    uint8_t Thermal_Runaway_Symbol_State = 0;  // 0: OFF, 1-ON
    if (Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.THRMLRUNWY_STS == 0x01)
    {
        Thermal_Runaway_Symbol_State = ON;
        
    }
    else
    {
        Thermal_Runaway_Symbol_State =OFF;
    }
    gem_err_indication(THERMAL_RUNAWAY_ON,Thermal_Runaway_Symbol_State);
    Cluster_Data->LCD_TellTale_Symbol.bit.Thermal_Runaway_TT = Thermal_Runaway_Symbol_State;
    //Thermal_Runaway_Symbol_LCD(Thermal_Runaway_Symbol_State);
}
