/***********************************************************************************************************************
* File Name    : Animation.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the Animation.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include "GEM_common_header.h"
#include "r_cg_userdefine.h"
#include "Animation.h"
#include "GEM_LCD_Telltales.h"
#include "Digital_Outputs.h"
#include "Buzzer.h"
#include "lcd.h"
#include "Timer.h"

//void GEM_Animation(BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data)
/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function is for self checking purpose, to check whether all the telltales and other modules are working fine or not,
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Animation(Cluster_Data_t *Cluster_Data)
{
    uint32_t gem_ani_timer=0;
    uint32_t gem_ani_timer_prev =0;
    uint8_t count=0;
    uint8_t count1=0;

    char sym1[] = "0000000000000000000000";
    char sym2[] = "XXXXXXXXXXXXXXXXXXXXXX";
    char sym3[] = "++++++++++++++++++++++";
    char Version_Number[] = "     SW VER 02.00      ";

    gem_vehice_modes(ECO_PWR);
    //gem_vehice_modes(PWR);
    gem_err_indication(SERIVCE_ON,ON);
    gem_err_indication(TEMP_ON,ON);
    gem_err_indication(BATTERY_ON,ON);
    gem_err_indication(THROTTLE_ON,ON);
    gem_err_indication(THERMAL_RUNAWAY_ON,ON);
    gem_Reverse(ON);
    gem_Ready(ON);
    gem_battery_charg(OFF);
    gem_battery_charge_animation(ON);
    gem_high(ON);
    left_indicator_telltile_control(ON);
    right_indicator_telltile_control(ON);
    LED_OUTPUT_3(OUTPUT_HIGH);
    top_bottom_alert(ON);
    gem_alertname(ON);
    Buzzer_ON_OFF(ON, 25);
    //LED_OUTPUT_4(OUTPUT_HIGH);
    while(count <= 22)
    {
        gem_ani_timer = get_GEM_Timer_Value();
        if(((gem_ani_timer - gem_ani_timer_prev) >= 2))
        {
            gem_ani_timer_prev = gem_ani_timer;
            if (count == 1)
            {
                Buzzer_ON_OFF(OFF, 25);
            }
                if (count <= 20)
                {
                if (count <=10 )
                {
                    gem_speed_or_soc_display(count);
                    gem_soc(count);
                    GEM_SOC_Bar_Logic(count);
                }
                else
                {
                    gem_speed_or_soc_display((count-10) * 10);
                    gem_soc((count-10) * 10);
                    GEM_SOC_Bar_Logic((count-10) * 10);
                }
                if ((count1 == 2) && (count !=20))
                {
                    gem_odo_meter(((count)/2) * 1111111);
	                gem_trip_meter(((count)/2) * 1111);
                    count1 = 0;
                }
                }
                if (count <= 2)
                {
                    gem_Animation_text(sym1);
                }
                else if(count <= 4)
                {
                    gem_Animation_text(sym2);
                }
                else if(count <= 6)
                {
                    gem_Animation_text(sym3);
                }
                else
                {
			    gem_Animation_text(Version_Number);
                }
                count +=1;
                count1++;
                disp_lattice();
            }
        }
     //Set_LCD_Data(0);   
	LED_OUTPUT_3(OUTPUT_HIGH);
    //LED_OUTPUT_4(OUTPUT_HIGH);
	
}