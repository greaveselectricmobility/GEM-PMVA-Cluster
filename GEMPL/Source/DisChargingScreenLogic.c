/***********************************************************************************************************************
* File Name    : DischargingScreenLogic.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the Discharging screeen logic.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include "GEM_common_header.h"
#include "DisChargingScreenLogic.h"
#include "lcd.h"
#include "Battery_Symbol.h"
#include "Temperature_symbol.h"
#include "Thermal_Runaway.h"
#include "Service_Alert.h"
#include "GEM_LCD_Telltales.h"
#include "Buzzer.h"
#include "RTC.h"
#include "Calculations.h"

//void LCD_Telltales(BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data,uint32_t gem_timer)

/***********************************************************************************************************************
* Function Name: LCD_Telltales
* Description  : This function updates the LCD telltales when the vehicle in is discharging state.
* Arguments    : Cluster_Data, gem_timer
* Return Value : None
***********************************************************************************************************************/
void LCD_Telltales(Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
{
	
	//Cluster_Data->CAN_Data.MCU_Temperature = 86;
	gem_battery_charg(OFF);
    //Battery_symbol_Red_check(LCD_Data,Cluster_Data,gem_timer);
    //Temperature_symbol_check(LCD_Data,Cluster_Data,gem_timer);
    //Thermal_Runaway_symbol_check(LCD_Data,Cluster_Data,gem_timer);
    //GEM_Throttle_Telltale(LCD_Data,Cluster_Data);
    //GEM_Ready_Telltale(LCD_Data,Cluster_Data);
    //GEM_Highbeam_Telltale(LCD_Data,Cluster_Data);
    //GEM_LeftTurn_Indicator_Telltale(LCD_Data,Cluster_Data);
    //GEM_RightTurn_Indicator_Telltale(LCD_Data,Cluster_Data);
    
    //gem_err_indication(CLEAR_ERR_INDICATIONS,OFF);
    Battery_symbol_Red_check(Cluster_Data,gem_timer);
    Temperature_symbol_check(Cluster_Data,gem_timer);
    Thermal_Runaway_symbol_check(Cluster_Data,gem_timer);
    Service_alert( Cluster_Data, gem_timer);
    GEM_Throttle_Telltale(Cluster_Data);
    GEM_Highbeam_Telltale(Cluster_Data);
    GEM_LeftTurn_Indicator_Telltale(Cluster_Data);
    GEM_RightTurn_Indicator_Telltale(Cluster_Data);
    //GEM_Service_Alert ( Cluster_Data );
    GEM_Reverse_Mode ( Cluster_Data );
    GEM_Battery_Full ( Cluster_Data );
    GEM_Ready_Indication ( Cluster_Data );
    GEM_Battery_Low(Cluster_Data);
    GEM_MCU_Error(Cluster_Data);
    GEM_Motor_Error(Cluster_Data);
    GEM_MCU_Locked_Error(Cluster_Data);
    GEM_Limp_Home_Mode_Error(Cluster_Data);
    GEM_Vehicle_Modes(Cluster_Data);
    GEM_SOC(Cluster_Data);
    GEM_Speed_Display(Cluster_Data);
    Buzzer_check(Cluster_Data,gem_timer);
    GEM_Brake_fluid(Cluster_Data);
    GEM_Top_Bottom_line(Cluster_Data);
    GEM_Alert_nametag_warning( Cluster_Data );
    GEM_RTC();
   
}


//void DisCharging_Screen(BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data,uint32_t gem_timer)

/***********************************************************************************************************************
* Function Name: DisCharging_Screen
* Description  : This function is to manage the update frequency of the LCD.
* Arguments    : Cluster_Data, gem_timer
* Return Value : None
***********************************************************************************************************************/
void DisCharging_Screen(Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
{
    static uint32_t gem_timer_1sec_prev =0;
    //100ms function calls
    //vehicle_speed_calc()
    //Vehicle_Speed_Error_Logic()
    
    LCD_Telltales(Cluster_Data,gem_timer);
    
    if((gem_timer - gem_timer_1sec_prev) >= 10)
    {
        gem_timer_1sec_prev = gem_timer;
        GEM_ODO_write_Check(GEM_get_Odo_Value_Disp(),GEM_get_Odo_Value_mtr());
        //Odometer_Calc()
        //Odometer_Write_to_memory
        //LCD_Telltales(LCD_Data,Cluster_Data,gem_timer);
	//LCD_Telltales(Cluster_Data,gem_timer);
        //LED_Telltales()
        //Error_Logic(Cluster_Data,gem_timer);
    }
}
