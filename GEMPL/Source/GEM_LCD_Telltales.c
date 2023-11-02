/***********************************************************************************************************************
* File Name    : GEM_LCD_Telltales.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the telltales function.
* Creation Date: 28-08-2023
* Author	   : Thanushree K S
***********************************************************************************************************************/


#include "GEM_common_header.h"
#include "GEM_LCD_Telltales.h"
#include "Digital_Outputs.h"
#include "lcd.h"

//void GEM_Throttle_Telltale (BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data)

/***********************************************************************************************************************
* Function Name: GEM_Throttle_Telltale
* Description  : This function implements the functionality for the throttle.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Throttle_Telltale (Cluster_Data_t *Cluster_Data)
{
	
	//Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.Throttle_Error=CAN_THROTTLE_ERROR;
    if (Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.Throttle_Error == CAN_THROTTLE_ERROR)
    {
        //Set Telltale ON in LCD_DATA_Function() 
		gem_err_indication(THROTTLE_ON,ON);
        Cluster_Data->LCD_TellTale_Symbol.bit.Throttle_Failure_TT = ON;
		Cluster_Data->CAN_Tx_TT.Throttle_Failure = 1;
    }
    else
    {
        //Set Telltale OFF in LCD_DATA_Function() 
		gem_err_indication(THROTTLE_ON,OFF);
        Cluster_Data->LCD_TellTale_Symbol.bit.Throttle_Failure_TT = OFF;
		Cluster_Data->CAN_Tx_TT.Throttle_Failure = 0;

    }
    
}

/***********************************************************************************************************************
* Function Name: GEM_Highbeam_Telltale
* Description  : This function implements the functionality for the highbeam.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Highbeam_Telltale (Cluster_Data_t *Cluster_Data)
{
	//Cluster_Data->Digital_Input_Pin.bit.High_Beam_IP = CAN_HEADLAMP_HIGHBEAM;
	if( Cluster_Data->Digital_Input_Pin.bit.High_Beam_IP == CAN_HEADLAMP_HIGHBEAM )
	{
		//Set Telltale ON in LCD_DATA_Function()
		Cluster_Data ->LCD_TellTale_Symbol.bit.Headlamp_HighBeam_TT = 1;
		//gem_err_indication()
		gem_high(ON);
		Cluster_Data->CAN_Tx_TT.High_Beam = 1;

	}
	else
	{
		//Set Telltale ON in LCD_DATA_Function()
		Cluster_Data ->LCD_TellTale_Symbol.bit.Headlamp_HighBeam_TT = 0;
		Cluster_Data->CAN_Tx_TT.High_Beam = 0;
		gem_high(OFF);
	}
	
}

/***********************************************************************************************************************
* Function Name: GEM_LeftTurn_Indicator_Telltale
* Description  : This function implements the functionality for the left turn indicator.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_LeftTurn_Indicator_Telltale (Cluster_Data_t *Cluster_Data)
{
	//Cluster_Data->Digital_Input_Pin.bit.Left_Turn_Ind_IP = CAN_LEFT_TURN_INDICATOR;
	if( Cluster_Data->Digital_Input_Pin.bit.Left_Turn_Ind_IP == CAN_LEFT_TURN_INDICATOR )
	{
		//Set Telltale ON in LCD_DATA_Function()
		Cluster_Data ->LCD_TellTale_Symbol.bit.Left_Turn_Indicator_TT = 1;
		Cluster_Data->CAN_Tx_TT.Left_Turn_Indicator = 1;
		left_indicator_telltile_control(ON);
	}
	else
	{
		//Set Telltale ON in LCD_DATA_Function()
		Cluster_Data ->LCD_TellTale_Symbol.bit.Left_Turn_Indicator_TT = 0;
		Cluster_Data->CAN_Tx_TT.Left_Turn_Indicator = 0;
		left_indicator_telltile_control(OFF);
	}
}

/***********************************************************************************************************************
* Function Name: GEM_RightTurn_Indicator_Telltale
* Description  : This function implements the functionality for the right turn indicator.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_RightTurn_Indicator_Telltale (Cluster_Data_t *Cluster_Data)
{
	//Cluster_Data->Digital_Input_Pin.bit.Right_Turn_Ind_IP = CAN_RIGHT_TURN_INDICATOR;
	if( Cluster_Data->Digital_Input_Pin.bit.Right_Turn_Ind_IP == CAN_RIGHT_TURN_INDICATOR )
	{
		//Set Telltale ON in LCD_DATA_Function()
		Cluster_Data ->LCD_TellTale_Symbol.bit.Rightt_Turn_Indicator_TT = 1;
		Cluster_Data->CAN_Tx_TT.Right_Turn_indicator = 1;
		right_indicator_telltile_control(ON);
	}
	else
	{
		//Set Telltale ON in LCD_DATA_Function()
		Cluster_Data ->LCD_TellTale_Symbol.bit.Rightt_Turn_Indicator_TT = 0;
		Cluster_Data->CAN_Tx_TT.Right_Turn_indicator = 0;
		right_indicator_telltile_control(OFF);
	}
	//right_indicator_telltile_control(1);
}

/***********************************************************************************************************************
* Function Name: GEM_Battery_Charging
* Description  : This function implements the functionality for the battery charging.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Battery_Charging ( Cluster_Data_t *Cluster_Data )
{
	//Cluster_Data ->CAN_Data.BMS_STATE == 
	//Cluster_Data ->LCD_TellTale_Symbol.bit.Battery_TT = 1;
	Cluster_Data->CAN_Tx_TT.Main_Battery_charging_status = 1;
	gem_battery_charg(ON);

}

/***********************************************************************************************************************
* Function Name: GEM_Reverse_Mode
* Description  : This function implements the functionality for the reverse mode.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Reverse_Mode ( Cluster_Data_t *Cluster_Data )
{
	//Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.Direction = CAN_REVERSE_MODE;
	if (Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.Direction == CAN_REVERSE_MODE )
	{
		Cluster_Data -> LCD_TellTale_Symbol.bit.Reverse_TT = 1;
		Cluster_Data->CAN_Tx_TT.Reverse_Status = 1;
		gem_Reverse(ON);
	}
	else
	{
		Cluster_Data -> LCD_TellTale_Symbol.bit.Reverse_TT = 0;
		Cluster_Data->CAN_Tx_TT.Reverse_Status = 0;
		gem_Reverse(OFF);
	}

}

/***********************************************************************************************************************
* Function Name: GEM_Battery_Full
* Description  : This function implements the functionality for the battery full condition.
* Arguments    : Cluster_Data->CAN_Data->Batt_FULL
* Return Value : None
***********************************************************************************************************************/
void GEM_Battery_Full ( Cluster_Data_t *Cluster_Data )
{
	//Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.BATT_FULL = CAN_BATTERY_FULL;
	if ( Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.BATT_FULL == CAN_BATTERY_FULL ){
		gem_set_clear_text_display(BATTERY_FULL_TXT, ENABLE);
		//gem_text_display_update();
	}
	else{
		gem_set_clear_text_display(BATTERY_FULL_TXT, DISABLE);
		//gem_text_display_update();
	}
}

/***********************************************************************************************************************
* Function Name: GEM_Ready_Indication
* Description  : This function implements the functionality for the ready symbol.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Ready_Indication ( Cluster_Data_t *Cluster_Data )
{
	
	gem_Ready(~ (Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.Park_Indication));
	Cluster_Data->CAN_Tx_TT.Ready_status = 1;
	
	//gem_set_clear_text_display(BATTERY_FULL_TXT, ENABLE);
	//gem_text_display_update();
	
}

/***********************************************************************************************************************
* Function Name: GEM_Battery_Low
* Description  : This function implements the functionality for the battery low condition.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Battery_Low(Cluster_Data_t *Cluster_Data)
{
	//Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.BATT_LOW = CAN_BATTERY_LOW;
	if ( Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.BATT_LOW == CAN_BATTERY_LOW){
		gem_set_clear_text_display(BATTERY_LOW_TXT, ENABLE);
		
	}
	else{
		gem_set_clear_text_display(BATTERY_LOW_TXT, DISABLE);
		
	}
}

/***********************************************************************************************************************
* Function Name: GEM_MCU_Error
* Description  : This function implements the functionality for the MCU error.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_MCU_Error(Cluster_Data_t *Cluster_Data)
{
	//Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Controller_Error = CAN_MCU_ERROR;
	if( Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Controller_Error == CAN_MCU_ERROR){
		gem_set_clear_text_display(MCU_ERROR_TXT, ENABLE);
		Cluster_Data->CAN_Tx_TT.MCU_Failure = 1;
		Cluster_Data->CAN_Tx_TT.Motor_Failure = 0;

	}
	else{
		gem_set_clear_text_display(MCU_ERROR_TXT, DISABLE);
		Cluster_Data->CAN_Tx_TT.MCU_Failure = 0;
		Cluster_Data->CAN_Tx_TT.Motor_Failure = 0;
	}
	//if(Cluster_Data->CAN_Value_error.bit.MCU_Value_Error == CAN_MCU_ERROR){
	//	gem_set_clear_text_display(MCU_VALUE_ERROR_TXT, ENABLE);
	//}
	//else{
	//	gem_set_clear_text_display(MCU_VALUE_ERROR_TXT, DISABLE);
	//}
}

/***********************************************************************************************************************
* Function Name: GEM_Motor_Error
* Description  : This function implements the functionality for the Motor error.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Motor_Error(Cluster_Data_t *Cluster_Data)
{
	//Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Motor_Error = CAN_MOTOR_ERROR;
	if( Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Motor_Error == CAN_MOTOR_ERROR){
		gem_set_clear_text_display(MOTOR_ERROR_TXT, ENABLE);
		Cluster_Data->CAN_Tx_TT.Motor_Failure = 1;
		Cluster_Data->CAN_Tx_TT.MCU_Failure = 0;
	}
	else{
		gem_set_clear_text_display(MOTOR_ERROR_TXT, DISABLE);
		Cluster_Data->CAN_Tx_TT.Motor_Failure = 0;
		Cluster_Data->CAN_Tx_TT.MCU_Failure = 0;

	}
}

/***********************************************************************************************************************
* Function Name: GEM_MCU_Locked_Error
* Description  : This function implements the functionality for the MCU locked state.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_MCU_Locked_Error(Cluster_Data_t *Cluster_Data)
{
	//Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Immobilize_Sts = CAN_MCU_LOCKED_ERROR;
	if( Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Immobilize_Sts == CAN_MCU_LOCKED_ERROR){
		gem_set_clear_text_display(MCU_LOCKED_TXT, ENABLE);
		
	}
	else{
		gem_set_clear_text_display(MCU_LOCKED_TXT, DISABLE);
	}
}

/***********************************************************************************************************************
* Function Name: GEM_Limp_Home_Mode_Error
* Description  : This function implements the functionality for the limp home mode.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Limp_Home_Mode_Error(Cluster_Data_t *Cluster_Data)
{
	//Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Limp_Home_Mode = CAN_LIMP_HOME_MODE_ERROR;
	if( Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Limp_Home_Mode == CAN_LIMP_HOME_MODE_ERROR){
		gem_set_clear_text_display(LIMP_MODE_HOME_TXT, ENABLE);
		Cluster_Data->CAN_Tx_TT.Limp_home_Mode = 2;

	}
	else{
		gem_set_clear_text_display(LIMP_MODE_HOME_TXT, DISABLE);
		Cluster_Data->CAN_Tx_TT.Limp_home_Mode = 0;

	}
}

/***********************************************************************************************************************
* Function Name: GEM_Vehicle_Modes
* Description  : This function implements the functionality for the vehicle modes.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Vehicle_Modes(Cluster_Data_t *Cluster_Data)
{
	//Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.Mode_Status_Flag = CAN_VEHICLE_MODE_CITY;
	//if (Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.Mode_Status_Flag == CAN_VEHICLE_MODE_CITY)
	//{
	//	gem_vehice_modes(CITY);
	//}
	if (Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.Mode_Status_Flag == CAN_VEHICLE_MODE_ECO )
	{
		gem_vehice_modes(ECO);
	    Cluster_Data->CAN_Tx_TT.Speed_Mode = 0;
	}
	else if(Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.Mode_Status_Flag == CAN_VEHICLE_MODE_PWR )
	{
		gem_vehice_modes(PWR);
	    Cluster_Data->CAN_Tx_TT.Speed_Mode = 1;

	}
	else{
		gem_vehice_modes(0);
	    Cluster_Data->CAN_Tx_TT.Speed_Mode = 0;
	}
}

/***********************************************************************************************************************
* Function Name: GEM_SOC_Display
* Description  : This function implements SOC percentage display function for charging screen.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_SOC_Display(Cluster_Data_t *Cluster_Data)
{
	if ((Cluster_Data->CAN_Data.SOC <= 100) && (Cluster_Data->CAN_Data.SOC > 0))
	{
		gem_speed_or_soc_display(Cluster_Data-> CAN_Data.SOC);
	}
	else if(Cluster_Data->CAN_Data.SOC > 100)
	{
		gem_speed_or_soc_display(100);
	}
	else
	{
		gem_speed_or_soc_display(0);
	}
	
	//gem_speed_or_soc_display(Cluster_Data-> CAN_Data.SOC);
}

void GEM_Speed_Display(Cluster_Data_t *Cluster_Data)
{
	gem_speed_or_soc_display(Cluster_Data->Vehicle_Speed);
	//gem_speed_or_soc_display(100);
	gem_odo_meter(Cluster_Data->Odometer_Display);
	gem_trip_meter(Cluster_Data->Trip_meter_B);
}

/***********************************************************************************************************************
* Function Name: GEM_SOC_Bar_Logic
* Description  : This function implements SOC Bar Calculation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
uint8_t GEM_SOC_Bar_Logic(int soc_percentage) 
{
    int bar;
    if ((soc_percentage==100) || (soc_percentage<=5) || ((soc_percentage%10) ==0))
    {
        if((soc_percentage%10) ==0)
        {
           	bar =soc_percentage/10;
        }
        else if((soc_percentage<=5))
        {
            bar=0;
        }
        else if(soc_percentage==100)
        {
            bar=10;
        }
    }
    else
    {
        bar=soc_percentage/10;
        bar+=1;
    }
    gem_SOC_bar(bar, ENABLE);
	return bar;
}

/***********************************************************************************************************************
* Function Name: GEM_SOC
* Description  : This function implements SOC Bar implementation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_SOC(Cluster_Data_t *Cluster_Data)
{
	//Cluster_Data-> CAN_Data.SOC = 50;
	gem_soc(Cluster_Data-> CAN_Data.SOC);
	if ((Cluster_Data->CAN_Data.SOC <= 100))
	{
		//gem_soc(Cluster_Data-> CAN_Data.SOC);
		Cluster_Data->SOC_Bar = GEM_SOC_Bar_Logic(Cluster_Data-> CAN_Data.SOC);
	}
	else
	{
		
		gem_SOC_bar(0,DISABLE);
		Cluster_Data->SOC_Bar = 0;
	}

}


void GEM_Brake_fluid(Cluster_Data_t *Cluster_Data)
{
	if(Brake_Fluid_Indicator == 1)
	{
		LED_OUTPUT_3(ON);
		Cluster_Data->CAN_Tx_TT.Brake_Failure_alert = 1;

	}
	else{
		LED_OUTPUT_3(OFF);
		Cluster_Data->CAN_Tx_TT.Brake_Failure_alert = 0;

	}

}

void GEM_Top_Bottom_line(Cluster_Data_t *Cluster_Data)
{
	if((Cluster_Data->LCD_TellTale_Symbol.bit.Service_Alert_TT) || (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT) || 
		(Cluster_Data->LCD_TellTale_Symbol.bit.Battery_TT) || (Cluster_Data->LCD_TellTale_Symbol.bit.Throttle_Failure_TT) ||
		(Cluster_Data->LCD_TellTale_Symbol.bit.Thermal_Runaway_TT) ||(Cluster_Data->LCD_TellTale_Symbol.bit.Reverse_TT))
		{
			gem_err_indication(TOP_BOTTOM_LINE,ON);
		}
		else
		{
			gem_err_indication(TOP_BOTTOM_LINE,OFF);
		}
}

void GEM_Alert_nametag_warning( Cluster_Data_t *Cluster_Data )
{
	if(		Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.BATT_FULL == 1 
	 	|| 	Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.BATT_LOW == 1
	 	||  Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Controller_Error == 1
	 	||  Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Motor_Error == 1
	 	|| 	Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Immobilize_Sts == 1
	 	|| 	Cluster_Data-> CAN_Data.CAN_RX_Data_Bit.SGNL.Limp_Home_Mode == 1 
		//|| 	Cluster_Data-> CAN_Value_error.bit.MCU_Value_Error == 1
	)
	 {
		gem_alertname(ON);
	 }
	 else
	 {
		gem_alertname(OFF);
	 }
}