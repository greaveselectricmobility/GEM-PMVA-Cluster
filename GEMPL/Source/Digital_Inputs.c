/***********************************************************************************************************************
* File Name    : Digital_Inputs.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the digital input pins.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include "GEM_common_header.h"
#include "Digital_Inputs.h"

#include "r_cg_port.h"


Digital_Input_Pin_t Digital_Input_Status;

/***********************************************************************************************************************
* Function Name: High_Beam_Status
* Description  : This function is to check the status of the high beam input that is being given by the user.(digital input)
* Arguments    : None
* Return Value : Boolean value(enable/disable)(0/1)
***********************************************************************************************************************/
uint8_t High_Beam_Status(void)
{
    return High_Beam_Input;
}


/***********************************************************************************************************************
* Function Name: Left_Turn_Ind_Status
* Description  : This function is to check the status of the left turn indicator input that is being given by the user.(digital input)
* Arguments    : None
* Return Value : Boolean value(enable/disable)(0/1)
***********************************************************************************************************************/
uint8_t Left_Turn_Ind_Status(void)
{
    return Left_Turn_Input;
}

/***********************************************************************************************************************
* Function Name: Right_Turn_Ind_Status
* Description  : This function is to check the status of the right turn indicator input that is being given by the user.(digital input)
* Arguments    : None
* Return Value : Boolean value(enable/disable)(0/1)
***********************************************************************************************************************/
uint8_t Right_Turn_Ind_Status(void)
{
    return Right_Turn_Input;
}

/***********************************************************************************************************************
* Function Name: Brake_Fluid_Ind_Status
* Description  : This function is to check the status of the brake fluid that is being captured through CAN signals.
* Arguments    : Cluster_Data
* Return Value : Boolean value(enable/disable)(0/1)
***********************************************************************************************************************/
uint8_t Brake_Fluid_Ind_Status(void)
{
    return Brake_Fluid_Indicator;
}

/***********************************************************************************************************************
* Function Name: Get_Digital_Input_Data
* Description  : This function is to update the values in the structure with the recieved digital inputs.
* Arguments    : *Digital_Input_Pin
* Return Value : None
***********************************************************************************************************************/
void Get_Digital_Input_Data(Digital_Input_Pin_t *Digital_Input_Pin)
{
    Digital_Input_Pin->bit.High_Beam_IP = High_Beam_Input;
    Digital_Input_Pin->bit.Left_Turn_Ind_IP = Left_Turn_Input;
    Digital_Input_Pin->bit.Right_Turn_Ind_IP = Right_Turn_Input;
    Digital_Input_Pin->bit.Brake_Fluid_IP = Brake_Fluid_Indicator;
}