/***********************************************************************************************************************
* File Name    : Cluster_Data_Update.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the boundary conditions.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include "r_cg_macrodriver.h"
#include "GEM_common_header.h"
#include "Cluster_Data_Update.h"
#include "GEM_can.h"
#include "Calculations.h"
#include "Digital_Inputs.h"



/***********************************************************************************************************************
* Function Name: SOC_Check
* Description  : This function is to check the boundary conditions of the SOC value.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void SOC_Check(Cluster_Data_t *Cluster_Data)
{
	Cluster_Data->CAN_Value_error.bit.BMS_Value_Error = 0;
	if(Cluster_Data->CAN_Data.SOC > 100)
	{
		Cluster_Data->CAN_Value_error.bit.BMS_Value_Error = 1;
		
	}
}

/***********************************************************************************************************************
* Function Name: Vehicle_Speed_Check
* Description  : This function is to set the maximum speed vehicle can attain under different modes.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
//void Vehicle_Speed_Check(Cluster_Data_t *Cluster_Data)
//{
//	uint16_t rpm_limit;
//	Cluster_Data->CAN_Value_error.bit.MCU_Value_Error = 0;
//	switch (Cluster_Data -> CAN_Data.CAN_RX_Data_Bit.SGNL.Mode_Status_Flag)
//	{
//		case CAN_VEHICLE_MODE_ECO:
//			rpm_limit = 464;
//			break;
//		case CAN_VEHICLE_MODE_PWR:
//			rpm_limit = 575;
//			break;
//		
//		default:
//			rpm_limit = 0;
//			break;
//	}
//	if (Cluster_Data -> CAN_Data.Wheel_RPM > rpm_limit)
//	{
//		Cluster_Data->CAN_Value_error.bit.MCU_Value_Error = 1;
//		//gem_set_clear_text_display(VALUE_ERROR_TXT, ENABLE);
//	}
//	
//}

/***********************************************************************************************************************
* Function Name: Error_Logic
* Description  : This function is to check the error flags for SOC and vehicle speed limits.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void Error_Logic(Cluster_Data_t *Cluster_Data)
{
	SOC_Check(Cluster_Data);
	//Vehicle_Speed_Check(Cluster_Data);
}


/***********************************************************************************************************************
* Function Name: Update_Message_Buffer
* Description  : This function is to update the message buffer with the captured CAN signals and the error flags that has been captured if any.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void Update_Message_Buffer(Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
{
	GEM_CAN_Timeout_increment_counter(gem_timer);
	Get_CAN_Data(&Cluster_Data->CAN_Data);
	Cluster_Data->Vehicle_Speed = GEM_get_Vehicle_Speed();
	Cluster_Data->Odometer_Display = GEM_get_Odo_Value_Disp();
	Cluster_Data->Odometer_Memory = GEM_get_Odo_Value_mtr();
	Cluster_Data->Trip_meter_B = GEM_get_Trip_Odo_B_Value_Disp(); 
	Get_Digital_Input_Data(&Cluster_Data->Digital_Input_Pin);

	Error_Logic(Cluster_Data);
}

/***********************************************************************************************************************
* Function Name: get_GEM_Motor_RPM
* Description  : 
* Arguments    : None
* Return Value : 0xFFFF(constant)
***********************************************************************************************************************/
int16_t get_GEM_Motor_RPM(void)
{
	return 0xFFFF;
}