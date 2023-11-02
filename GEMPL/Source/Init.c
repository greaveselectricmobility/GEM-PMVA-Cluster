/***********************************************************************************************************************
* File Name    : init.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the init function.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include "Init.h"
#include "GEM_common_header.h"
#include "Digital_Outputs.h"
#include "Digital_Inputs.h"
#include "r_cg_serial.h"
//#include "r_cg_adc.h"
#include "r_cg_timer.h"
#include "lcd.h"
#include "my_can.h"
#include "GEM_can.h"
#include "Calculations.h"


/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void Init(void)
{
	
	Uc_5V_Control(OUTPUT_LOW);
	UC_3V3_Control(OUTPUT_HIGH);
	LCD_BackLight_Control(OUTPUT_LOW);
	CAN_TX(OUTPUT_HIGH);
	//CAN_RX(OUTPUT_LOW);
	
//	LED_OUTPUT_1(OUTPUT_LOW);
//	LED_OUTPUT_2(OUTPUT_LOW);
//	LED_OUTPUT_3(OUTPUT_LOW);
//	LED_OUTPUT_4(OUTPUT_LOW);
//	LED_OUTPUT_5(OUTPUT_LOW);
//	LED_OUTPUT_6(OUTPUT_LOW);
//	LED_OUTPUT_1(OUTPUT_HIGH);
//	LED_OUTPUT_2(OUTPUT_HIGH);
//	LED_OUTPUT_3(OUTPUT_HIGH);
//	LED_OUTPUT_4(OUTPUT_HIGH);
//	LED_OUTPUT_5(OUTPUT_HIGH);
//	LED_OUTPUT_6(OUTPUT_HIGH);
	//gem_odo_update((uint32_t)100000);
	GEM_Mem_Init();
	GEM_Trip_Odo_B_Reset();
	R_TAU0_Channel0_Start();
	//GEM_CAN_Init_new(CAN_BAUD_RATE);
	GGEM_CAN_Init_new(CAN_BAUD_RATE);
	CAN_STANDBY_Output_Control(OUTPUT_LOW);

	Set_LCD_Data(0x00);
	R_CSI00_Start();
	initLCM();
	R_UARTF0_Start();
	disp_lattice();
}

