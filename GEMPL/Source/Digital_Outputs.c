/***********************************************************************************************************************
* File Name    : Digital_Outputs.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : 
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include "GEM_common_header.h"
#include "Digital_Outputs.h"

#include "r_cg_port.h"
/***********************************************************************************************************************
* Function Name: Uc_5V_Control
* Description  : 
* Arguments    : status of the 
* Return Value : None
***********************************************************************************************************************/
void Uc_5V_Control(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			UC_5V_Control_Output = 0;
			break;
		case OUTPUT_HIGH:
			UC_5V_Control_Output = 1;
			break;
		default:
			break;
	}
}

/***********************************************************************************************************************
* Function Name: UC_3V3_Control_Output
* Description  : 
* Arguments    : status of the 
* Return Value : None
***********************************************************************************************************************/
void UC_3V3_Control(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			UC_3V3_Control_Output = 0;
			break;
		case OUTPUT_HIGH:
			UC_3V3_Control_Output = 1;
			break;
		default:
			break;
	}
}

/***********************************************************************************************************************
* Function Name: CAN_STANDBY_Output_Control
* Description  : 
* Arguments    :
* Return Value : None
***********************************************************************************************************************/
void CAN_STANDBY_Output_Control(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			CAN_STB_OUTPUT = 0;
			break;
		case OUTPUT_HIGH:
			CAN_STB_OUTPUT = 1;
			break;
		default:
			break;
	}
}

/***********************************************************************************************************************
* Function Name: LCD_BackLight_Control
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void LCD_BackLight_Control(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			LCD_BackLight_Control_Output = 0;
			break;
		case OUTPUT_HIGH:
			LCD_BackLight_Control_Output = 1;
			break;
		default:
			break;
	}
}

/***********************************************************************************************************************
* Function Name: CAN_TX
* Description  :
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void CAN_TX(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			CAN_TX_Pin = 0;
			break;
		case OUTPUT_HIGH:
			CAN_TX_Pin = 1;
			break;
		default:
			break;
	}
}

/***********************************************************************************************************************
* Function Name: LED_OUTPUT_1
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void LED_OUTPUT_1(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			LED_1_Output = 0;
			break;
		case OUTPUT_HIGH:
			LED_1_Output = 1;
			break;
		default:
			break;
	}	
}

/***********************************************************************************************************************
* Function Name: LED_OUTPUT_2
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void LED_OUTPUT_2(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			LED_2_Output = 0;
			break;
		case OUTPUT_HIGH:
			LED_2_Output = 1;
			break;
		default:
			break;
	}
}

/***********************************************************************************************************************
* Function Name: LED_OUTPUT_3
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void LED_OUTPUT_3(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			LED_3_Output = 0;
			break;
		case OUTPUT_HIGH:
			LED_3_Output = 1;
			break;
		default:
			break;
	}
}

/***********************************************************************************************************************
* Function Name: LED_OUTPUT_4
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void LED_OUTPUT_4(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			LED_4_Output = 0;
			break;
		case OUTPUT_HIGH:
			LED_4_Output = 1;
			break;
		default:
			break;
	}
}

/***********************************************************************************************************************
* Function Name: LED_OUTPUT_5
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void LED_OUTPUT_5(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			LED_5_Output = 0;
			break;
		case OUTPUT_HIGH:
			LED_5_Output = 1;
			break;
		default:
			break;
	}
}

/***********************************************************************************************************************
* Function Name: LED_OUTPUT_6
* Description  : 
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void LED_OUTPUT_6(uint8_t State)
{
	switch (State)
	{
		case OUTPUT_LOW:
			LED_6_Output = 0;
			break;
		case OUTPUT_HIGH:
			LED_6_Output = 1;
			break;
		default:
			break;
	}
}
	