#include "GEM_common_header.h"
#include "r_cg_timer.h"

#include "r_cg_userdefine.h"
#include "Buzzer.h"
#include "Delay.h"
#include "lcd.h"
#include "Timer.h"

/***********************************************************************************************************************
* Function Name: Buzzer_frequency
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
uint8_t Buzzer_frequency(int blink_rate_interval, int blink_ctrl,uint32_t gem_timer)
{
    static uint32_t prev_buzz_frequency_ms = 0;
    static uint8_t temp_buzz_state = ON;
    if (blink_ctrl)
    {
	    if ((gem_timer - prev_buzz_frequency_ms) >= blink_rate_interval)
	    {
	        if(!temp_buzz_state)
	        {
	            temp_buzz_state= ON;
	        }
	        else
	        {
	            temp_buzz_state= OFF;
	        }
	        prev_buzz_frequency_ms = gem_timer;   
	    }
    }
    else
    {
	    temp_buzz_state= OFF;
	    prev_buzz_frequency_ms = gem_timer;
    }
    return temp_buzz_state;
}
void Duty_Cycle_select(uint8_t dc)
{
    if(dc == 50)
    {
        R_TAU2_Create_50DC();
    }
    else
    {
        R_TAU2_Create_25DC();
    }
}

void Buzzer_ON_OFF(uint8_t value,uint8_t dc)
{
	static uint8_t prev_buzz_state=OFF;
	if (prev_buzz_state != value)
	{
		prev_buzz_state = value;
		if(value == ON)
		{
            Duty_Cycle_select(dc);
			R_TAU2_Channel0_Start();
			GEM_Delay_ms(2);
		}
		else if(value == OFF)
		{
			R_TAU2_Channel0_Stop();
			GEM_Delay_ms(2);
		}
	}
	
}

//void Temperature_symbol_check(BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
/***********************************************************************************************************************
* Function Name: Buzzer_check
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void Buzzer_check(Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
{
	
	//Cluster_Data->CAN_Data.MCU_Temperature = 106;
    uint8_t Buzzer_state;   // 0: OFF, 1-ON, 2: 1 Sec blink  3: 2 second blink,  
    uint8_t Dutycycle=50;
 
	if (Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.THRMLRUNWY_STS == 0x01)
    {

		Buzzer_frequency(0,DISABLE,gem_timer);
	    Buzzer_state = ON;
        Cluster_Data->CAN_Tx_TT.Buzzer = 1;
        //Thermal_Runaway_Symbol_State = ON;
		//buzzer on 	Buzzer_Enable_Output;
    }

    else if ((Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.ERR_THRMLRUNWY_WARNG == 0x01) && (Cluster_Data->CAN_Data.CAN_RX_Data_Bit.SGNL.THRMLRUNWY_STS != 0x01))
    {
        Buzzer_state = Buzzer_frequency(20,ENABLE,gem_timer);
        Cluster_Data->CAN_Tx_TT.Buzzer = 2;
    }
    else if ((Cluster_Data->CAN_Data.MCU_Temperature >= 105))
    {
        Buzzer_frequency(0,DISABLE,gem_timer);
	    Buzzer_state = ON;
        Cluster_Data->CAN_Tx_TT.Buzzer = 1;
    }
    else if ((Cluster_Data->CAN_Data.Motor_Temperature >= 180))
    {
        Buzzer_frequency(0,DISABLE,gem_timer);
	    Buzzer_state = ON;
        Cluster_Data->CAN_Tx_TT.Buzzer = 1;
    }
    else if ((Cluster_Data->CAN_Data.MCU_Temperature > 85) && (Cluster_Data->CAN_Data.MCU_Temperature < 105))
    {
	    Buzzer_state = Buzzer_frequency(10,ENABLE,gem_timer);
        Cluster_Data->CAN_Tx_TT.Buzzer = 2;
    }
    else if ((Cluster_Data->CAN_Data.Motor_Temperature > 160) && (Cluster_Data->CAN_Data.Motor_Temperature < 180))
    {
	    Buzzer_state = Buzzer_frequency(10,ENABLE,gem_timer);
        Cluster_Data->CAN_Tx_TT.Buzzer = 2;
    }
    else if(Cluster_Data->Digital_Input_Pin.bit.Right_Turn_Ind_IP == CAN_RIGHT_TURN_INDICATOR )
    {
	  //Buzzer_state = Buzzer_frequency(5,ENABLE,gem_timer);
	  Buzzer_state = ON; //continuous on
       	   Dutycycle = 25;
        Cluster_Data->CAN_Tx_TT.Buzzer = 1;
    }
    else if(Cluster_Data->Digital_Input_Pin.bit.Left_Turn_Ind_IP == CAN_LEFT_TURN_INDICATOR)
    {
	    //Buzzer_state = Buzzer_frequency(5,ENABLE,gem_timer);
	    Buzzer_state = ON;
       	   Dutycycle = 25;
        Cluster_Data->CAN_Tx_TT.Buzzer = 1;
    }
    /*  using xor for hazard condition 
        if ((Cluster_Data->Digital_Input_Pin.bit.Right_Turn_Ind_IP == CAN_RIGHT_TURN_INDICATOR) ^
        (Cluster_Data->Digital_Input_Pin.bit.Left_Turn_Ind_IP == CAN_LEFT_TURN_INDICATOR))
        {
        Buzzer_state = Buzzer_frequency(5, ENABLE, gem_timer);
        Dutycycle = 25;
        }
    */
    else if (Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.Direction == CAN_REVERSE_MODE )
    {
	    Buzzer_state = Buzzer_frequency(5,ENABLE,gem_timer);
        Cluster_Data->CAN_Tx_TT.Buzzer = 2;
	   //Buzzer_state = ON;
       	   Dutycycle = 25;
    }

    else
    {
        Buzzer_state = OFF;
        Buzzer_frequency(20,DISABLE,gem_timer);
        Cluster_Data->CAN_Tx_TT.Buzzer = 2;
    }
    Buzzer_ON_OFF(Buzzer_state,Dutycycle);
        Cluster_Data->CAN_Tx_TT.Buzzer = 0;
}



/***********************************************************************************************************************
* Function Name: GEM_Buzzer_Module
* Description  : This function implements Buzzer module.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/



