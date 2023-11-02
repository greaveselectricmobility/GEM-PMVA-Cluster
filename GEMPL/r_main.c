/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : Applilet3 for RL78/D1A V2.04.05.02 [08 Nov 2021]
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements main function.
* Creation Date: 19-07-2023
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <string.h>
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */



#include "GEM_common_header.h"
#include "Digital_Outputs.h"
#include "Init.h"
#include "lcd.h"
#include "Animation.h"
#include "Cluster_Data_Update.h"
#include "ChargingScreenLogic.h"
#include "DisChargingScreenLogic.h"
#include "r_cg_userdefine.h"
#include "Timer.h"
#include "Delay.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);
void BMS_State_Check(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
	

	//BYTE_t LCD_Data[LCD_DATA_ARRAY_Size]={0};
	Cluster_Data_t Cluster_Data ={0};
	
    R_MAIN_UserInit();
   	//WDTE =0xAC;
	

    /* Start user code. Do not edit comment generated here */
    // Initailization
	//Set_Cluster_Data(&Cluster_Data,0,sizeof(Cluster_Data));
	
	Init();
	static uint8_t animation_executed = 0;
	

	//if(Ignition_Input)
	
//	GEM_Animation(&Cluster_Data);
	//Set_LCD_Data(0xFF);
	while (1U)
	{
    	if (Ignition_Input == 1)
      	{
            if (animation_executed == 0)
            {
		LED_OUTPUT_4(OUTPUT_HIGH);
                GEM_Animation(&Cluster_Data);
		LED_OUTPUT_4(OUTPUT_LOW);
                animation_executed = 1; // Set the flag to indicate animation executed
            }
	   // while(animation_executed)
	    BMS_State_Check();
        }
	else
	{
		animation_executed = 0;
	}
	}
    
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

// void Set_LCD_Data(BYTE_t *LCD_Data,uint8_t Value, uint8_t length)
// {
// 	memset(LCD_Data,Value,length);
// }
void Set_Cluster_Data(Cluster_Data_t *Cluster_Data,uint8_t Value,uint8_t length)
{
	memset(&Cluster_Data,Value,length);
}
/* End user code. Do not edit comment generated here */

void BMS_State_Check(void)
{
	uint32_t gem_timer=0;
	static uint32_t gem_timer_100ms_prev =0;
	static uint8_t Charging_state_ft = 0;
	static uint8_t DisCharging_state_ft = 0;
	

	Cluster_Data_t Cluster_Data ={0};


	gem_timer = get_GEM_Timer_Value();

		if((gem_timer - gem_timer_100ms_prev) >= 1)
		{
			gem_timer_100ms_prev = gem_timer;
			Update_Message_Buffer(&Cluster_Data,gem_timer);
			if(Cluster_Data.CAN_Data.BMS_STATE == CHARGING_STATE)
			{
				if(Charging_state_ft==0)
				{
					//Set_LCD_Data(LCD_Data,0,sizeof(LCD_Data));
					Set_LCD_Data(0x00);
					Charging_state_ft=1;
					DisCharging_state_ft = 0;
				}
				//Charging_Screen(LCD_Data,&Cluster_Data,gem_timer);
				Charging_Screen(&Cluster_Data,gem_timer);
			}

		else if(Cluster_Data.CAN_Data.BMS_STATE != CHARGING_STATE)
			{
				if(DisCharging_state_ft==0)
				{
					//Set_LCD_Data(LCD_Data,0,sizeof(LCD_Data));
					Set_LCD_Data(0x00);
					DisCharging_state_ft=1;
					Charging_state_ft = 0;
				}
				//DisCharging_Screen(LCD_Data,&Cluster_Data,gem_timer);
				DisCharging_Screen(&Cluster_Data,gem_timer);
			}

			else
			{

			}
			gem_text_display_update();
			disp_lattice();

		}
}