/***********************************************************************************************************************
* File Name    : Calculations.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file includes all the basic math functions.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include <stdlib.h>
#include "r_cg_macrodriver.h"
#include "Calculations.h"
#include "Cluster_Data_Update.h"
#include "GEM_can.h"




#define SPEED_TOLERANCE (1.05)  //5% higher value
#define WHEEL_RADIUS (0.2285f)   // Unit: meter
#define PI ((22/7))
#define WHEEL_CIRCUMFERENCE ((2) * (PI) * (WHEEL_RADIUS))
#define WHEEL_SPEED_CONSTANT ((((WHEEL_CIRCUMFERENCE) * (60))/(1000)) * (((100) + (SPEED_TOLERANCE)) / (100)))
#define KMPH_to_mps ((1000)/(3600))
#define VEHICLE_SPEED_CONSTANT ((WHEEL_RADIUS)*(2.0f)*(3.14f)*(60.0f) * (1.05f))
float GEM_Vehicle_Speed;
uint32_t GEM_Odo_Value;
//float GEM_Odo_Value = 4000000;
uint32_t GEM_Odo_Value_mem;
uint32_t GEM_Trip_Odo_A , GEM_Trip_Odo_B;   // A- user reset, B-ign ON reset.
uint32_t GEM_TRIP_Start_Odo_A, GEM_IGN_ON_Odo_Read_B;





/***********************************************************************************************************************
* Function Name: GEM_get_Vehicle_Speed
* Description  : This function is to get the vehicle speed.
* Arguments    : None
* Return Value : Vehicle Speed
***********************************************************************************************************************/
uint8_t GEM_get_Vehicle_Speed(void)
{
	return (uint8_t)GEM_Vehicle_Speed;
}



/***********************************************************************************************************************
* Function Name: Calculate_Odo_value
* Description  : This function is to calculate the odometer value w.r.t speed and to reset the odometer value to zero once it reaches the maximum speed.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void Calculate_Odo_value(void)
{
	float meter = 0;
	static float meter_f = 0;
	if(GEM_Vehicle_Speed > 0)
	{
		//meter = GEM_Vehicle_Speed * KMPH_to_mps * 10;  // 1.6m is converted to 16.... 125m as 1250..... 0.1km
		meter = (GEM_Vehicle_Speed* 1000) / 3600;  // 1.6m is converted to 16.... 125m as 1250..... 0.1km
		meter_f = meter_f + meter;
		
		GEM_Odo_Value = (uint32_t)(GEM_Odo_Value + (uint8_t)meter_f);
		meter_f = meter_f - (uint8_t)meter_f;
		
		if (GEM_Odo_Value >= 1000000000)  
		{
			GEM_Odo_Value = 0;
		}
		
	}
	
}
/***********************************************************************************************************************
* Function Name: GEM_get_Odo_Value_mtr
* Description  : This function is to get the odometer value.
* Arguments    : None
* Return Value : Odometer value
***********************************************************************************************************************/
uint32_t GEM_get_Odo_Value_mtr(void)
{
	return (GEM_Odo_Value);
}

/***********************************************************************************************************************
* Function Name: GEM_get_Odo_Value_Disp
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
uint32_t GEM_get_Odo_Value_Disp(void)
{
	return ((uint32_t)(GEM_Odo_Value/100));
}

/***********************************************************************************************************************
* Function Name: Calculate_Trip_distance_A
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void Calculate_Trip_distance_A(void)
{
	GEM_Trip_Odo_A = GEM_get_Odo_Value_mtr() - GEM_TRIP_Start_Odo_A;
}

/***********************************************************************************************************************
* Function Name: Calculate_Trip_distance_B
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void Calculate_Trip_distance_B(void)
{
	GEM_Trip_Odo_B = GEM_get_Odo_Value_mtr() - GEM_IGN_ON_Odo_Read_B;
}

/***********************************************************************************************************************
* Function Name: GEM_get_Trip_Odo_A_Value_Disp
* Description  : 
* Arguments    : None
* Return Value : 
***********************************************************************************************************************/
uint32_t GEM_get_Trip_Odo_A_Value_Disp(void)
{
	return (GEM_Trip_Odo_A/100);
}

/***********************************************************************************************************************
* Function Name: GEM_get_Trip_Odo_B_Value_Disp
* Description  : 
* Arguments    : None
* Return Value : 
***********************************************************************************************************************/
uint32_t GEM_get_Trip_Odo_B_Value_Disp(void)
{
	return (GEM_Trip_Odo_B/100);
}

/***********************************************************************************************************************
* Function Name: GEM_Trip_Odo_A_Reset
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void GEM_Trip_Odo_A_Reset(void)
{
	// To be cleared in memory
}

/***********************************************************************************************************************
* Function Name: GEM_Trip_Odo_B_Reset
* Description  :  
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void GEM_Trip_Odo_B_Reset(void)
{
	GEM_Trip_Odo_B = 0;
	GEM_IGN_ON_Odo_Read_B = GEM_get_Odo_Value_mtr();
}


/***********************************************************************************************************************
* Function Name: GEM_Vehicle_Speed_Calc
* Description  : This function is to calculate the vehicle speed with respect to Wheel RPM.
* Arguments    : Vehicle's motor RPM
* Return Value : None
***********************************************************************************************************************/
void GEM_Vehicle_Speed_Calc(uint16_t g_Motor_RPM)
{
	static uint32_t t_time=0;
	
	GEM_Vehicle_Speed = (((float)g_Motor_RPM*VEHICLE_SPEED_CONSTANT) / 1000);
	if (GEM_Vehicle_Speed > 99)
	{
		GEM_Vehicle_Speed = 99;
	}
	
	++t_time;
	if(t_time % 10 == 0)
	{
		//Calculate_Dummy_Odo_value();
		Calculate_Odo_value();
		Calculate_Trip_distance_B();
	}
}

/***********************************************************************************************************************
* Function Name: Calculations
* Description  : This function is to calculate the odometer value and trip distance by the wheel rpm.
* Arguments    : none
* Return Value : None
***********************************************************************************************************************/
void Vehicle_Speed_Calculations(void)
{
	
	int16_t wrpm = abs(get_GEM_Wheel_RPM());
	//wrpm = 600;
	if(wrpm > 0)
	{
		GEM_Vehicle_Speed_Calc(wrpm);
	}
	else
	{
		GEM_Vehicle_Speed = 0;
	}
	
}

/***********************************************************************************************************************
* Function Name: Odo_value_Mem_read
* Description  : This function is to read the odometer value from the memory using the address pointer.
* Arguments    : *Odo_mem_read
* Return Value : None
***********************************************************************************************************************/
void Odo_value_Mem_read(uint32_t *Odo_mem_read)
{
	GEM_Odo_Value = *Odo_mem_read;
}

uint32_t GEM_Odo_Value1;

void Calculate_Dummy_Odo_value(void)
{
	float meter = 0;
	if(GEM_Vehicle_Speed > 0)
	{
		//meter = GEM_Vehicle_Speed * KMPH_to_mps * 10;  // 1.6m is converted to 16.... 125m as 1250..... 0.1km
		meter = ((float)GEM_get_Vehicle_Speed()* 1000) / 3600;  // 1.6m is converted to 16.... 125m as 1250..... 0.1km
		
		GEM_Odo_Value = (uint32_t)(GEM_Odo_Value + ((uint8_t)meter));
		if (GEM_Odo_Value >= 1000000000)  
		{
			GEM_Odo_Value = 0;
		}
					
	}				
	
}