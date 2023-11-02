/***********************************************************************************************************************
* File Name    : ChargingScreenLogic.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the logic for all the telltales that should be illuminated and unillumated when the vehicle is in the Charging state.
* Creation Date: 28-08-2023
* Author	   : Thanushree K S
***********************************************************************************************************************/

#include "GEM_common_header.h"
#include "ChargingScreenLogic.h"
#include "GEM_LCD_Telltales.h"
#include "lcd.h"
#include "Battery_Symbol.h"
#include "Temperature_symbol.h"
#include "Thermal_Runaway.h"
#include "Buzzer.h"
//void Charging_Screen(BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
/***********************************************************************************************************************
* Function Name: Charging_Screen
* Description  : This function is to determine which are the telltales should be in lit state when the vehicle is charging.
* Arguments    : Cluster_Data, gem_timer
* Return Value : None
***********************************************************************************************************************/
void Charging_Screen(Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
{
	gem_battery_charg(ON);
	GEM_SOC_Display(Cluster_Data);
	GEM_Battery_Low(Cluster_Data);
	GEM_Battery_Full ( Cluster_Data );
	Battery_symbol_Red_check(Cluster_Data,gem_timer);
	Temperature_symbol_check(Cluster_Data,gem_timer);
    Thermal_Runaway_symbol_check(Cluster_Data,gem_timer);
	GEM_Alert_nametag_warning( Cluster_Data );
	GEM_Top_Bottom_line(Cluster_Data);
	Buzzer_check(Cluster_Data,gem_timer);

	//GEM_Top_Bottom_line(Cluster_Data);
}