/***********************************************************************************************************************
* File Name    : lcd.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the LCD function.
* Creation Date: 28-08-2023
* Author	   : Praveen A
***********************************************************************************************************************/

#include<stdio.h>
#include "lcd.h"
#include "iodefine.h"
#include "r_cg_macrodriver.h"
#include "GEM_common_header.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"
#include "Calculations.h"


void initLCM(void);
void disp_lattice(void);
void disp_seg(unsigned char *p);
void write_send(uint8_t temp);
void write_com(uint8_t para);
void write_data(uint8_t para);

LCD_DATA_BUFF LCD_BUFF[120];

/***********************************************************************************************************************
* Function Name: delay
* Description  : This function is to add the delay in executing which can be used anywhere when needed.
* Arguments    : value in ms
* Return Value : None
***********************************************************************************************************************/\
void delay(uint8_t ms)				/*delay*/
{
	register int i,j;
	for(i=0;i<ms;i++)
	{
		for(j=0;j<125;j++);
	}
}


void write_send(uint8_t temp)			/*send data in IIC format*/
{
    R_CSI00_Send((uint8_t *)&temp, 1);
}
void write_com(uint8_t para)
{	
	LCD_Disp_SData_Input_Identification_A0 = LOW;
	write_send(para);
    	LCD_Disp_SData_Input_Identification_A0 = HIGH; 
}
void write_data(uint8_t para)
{
	LCD_Disp_SData_Input_Identification_A0 = HIGH;
	write_send(para);
	LCD_Disp_SData_Input_Identification_A0 = LOW;
}

/***********************************************************************************************************************
* Function Name: initLCM
* Description  : This function is to set the initial coditions to lit the LCD which is mentioned in the datasheet.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void initLCM(void)
{	       
	LCD_Disp_Chip_Select = LOW; //CS
	LCD_Disp_Reset = LOW; //RESET
	delay(10);
	LCD_Disp_Reset = HIGH; //RESET
	delay(20);
	write_com(0x5a);//Software Reset
	delay(10);
	write_com(0x66);//(4)number of display MODE set   DISSET
	write_data(0x00);//NORMAL
	write_com(0x6d);//(14)number of display lines set  DISLINSET
	write_data(0x03);//4 duty
	write_com(0x36);//(13)number of display lines set  NLSET
	write_data(0x00);// A ²¨,  N-line=0ff     
	write_com(0xc4);//(5)Common output status Normal
	write_com(0x84);//(10)CANOR (Column Address direction NORmal): Column address direction Normal	      
	write_com(0x27);//(19)power supply control for LCD driver
	write_data(0x01);//external VLCD, internal bias	   PWRCTL
	write_com(0xab);//(15)build t-in oscillation circuit on	  OSCON
	write_com(0x5f);//(17)display frame frequency select     FCLSEL //0x5f
	write_data(0x11);//170hz	  //0x11 
	write_com(0xA2);//(23)lcd BIAS SET(23)		BIASSET
	write_data(0x01);//1/3BIAS  
	write_com(0x25);//(20)Power supply on for LCD drive (20)	 PWRON	      
	write_com(0xaF);//display on	   
}

/***********************************************************************************************************************
* Function Name: disp_lattice
* Description  : This function sets the initial conditions to be done when the lcd is lit.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void disp_lattice(void)
{
	unsigned int j=0;
	LCD_Disp_Chip_Select = LOW; 
	// write_com(0xae);          //display off		
	write_com(0x8a);	         //(7)Display start line set
	write_data(0x00);	         //(7)Parameter,Display start line set
	write_com(0xb1);	         //(8)Page address set
	write_data(0x00);	         //(8)Parameter,Page address set: 4 line
	write_data(0x00);
	write_com(0x13);	         //(9)Column address set
	write_data(0x00);	         //(9)Parameter,Column address set:start address
	write_data(0xEF);	         //(9)Parameter,Column address set:end address
	write_com(0xaf); 
	write_com(0x1d);			 //WRRAM (WRite RAM): Display data RAM write
	for(j=0;j<120;j++)
	{
		write_data(LCD_BUFF[j].byte); 
		//write_data(0xFF); 
	}
	LCD_Disp_Chip_Select = HIGH;		 
}

/***********************************************************************************************************************
* Function Name: disp_seg
* Description  :
* Arguments    : 
* Return Value : None
***********************************************************************************************************************/
void disp_seg(unsigned char *p)
{	
	uint8_t j;
	LCD_Disp_Chip_Select = LOW;
	write_com(0xae); 
	write_com(0x8a);	         //(7)Display start line set
	write_data(0x00);	         //(7)Parameter,Display start line set
	write_com(0xb1);	         //(8)Page address set
	write_data(0x00);	         //(8)Parameter,Page address set: 4 line
	write_com(0x13);	         //(9)Column address set
	write_data(0x00);	         //(9)Parameter,Column address set:start address
	write_data(0xEF);	         //(9)Parameter,Column address set:end address
	write_com(0xaf); 
	write_com(0x1d);			 //WRRAM (WRite RAM): Display data RAM write

	for(j=0;j<120;j++)
	{
		write_data(*p++); 
	}
	LCD_Disp_Chip_Select = HIGH;		
}

void right_indicator_telltile_control(uint8_t status)
{
	right_indicator_telltile(LCD_BUFF,status);
}

void left_indicator_telltile_control(uint8_t status)
{
	left_indicator_telltile(LCD_BUFF,status);
}

void hazard_lamp_control(uint8_t right_bit,uint8_t left_bit)
{
	if((right_bit==HIGH)&&(left_bit==HIGH))
	{
		gem_err_indication(WARNING_ON,1);
	}
	else
	{
		gem_err_indication(WARNING_ON,0);
	}

}
void gem_high(uint8_t high)
{
	highbeam_telltile(LCD_BUFF,high);
	
}
void gem_battery_charg(uint8_t status)
{
	battery_charging_telltale(LCD_BUFF,status);
	
}
void gem_battery_charge_animation(uint8_t status)
{
	battery_chrg_Animation(LCD_BUFF,status);
}

void gem_Reverse(uint8_t reverse)
{
	reverse_telltale(LCD_BUFF,reverse);	
}
void gem_Ready(uint8_t status)
{
	ready_indication(LCD_BUFF,status);
}
void parking_indication(uint8_t status)
{
	parking_led_control(status);
	gem_Ready(status);	
}
void motor_on_indication(uint8_t status)
{	
	if(status)
	{
		gem_set_clear_text_display(MOTOR_ERROR_TXT,SET);
	}
	else
	{
		gem_set_clear_text_display(MOTOR_ERROR_TXT,CLEAR);
	}		
}

void mcu_on_indication(uint8_t status)
{	
	if(status)
	{
		gem_set_clear_text_display(MCU_ERROR_TXT,SET);
	}
	else
	{
		gem_set_clear_text_display(MCU_ERROR_TXT,CLEAR);
	}		
}

/***********************************************************************************************************************
* Function Name: gem_err_indication
* Description  : This function implements the error indication.
* Arguments    : error, status of the error
* Return Value : None
***********************************************************************************************************************/
void gem_err_indication(uint8_t warning,uint8_t status)
{
	
	switch(warning)
	{
		case THERMAL_RUNAWAY_ON:
				thermal_runaway_indication(LCD_BUFF,status);				
				break;	
		case SIDESTAND_ON:
				side_stand_indication(LCD_BUFF,status);
				break;
		case THROTTLE_ON:
				throttle_on_indication(LCD_BUFF,status);				
				break;
		case BATTERY_ON:
				battery_on_indication(LCD_BUFF,status);
				break;
		case TEMP_ON:
				temp_on_indication(LCD_BUFF,status);
				break;
		case MOTOR_ON:
				//motor_on_indication(status);				
				break;
		case  MCU_ON:
				//mcu_on_indication(status);
				break;
		case SERIVCE_ON:
				service_on_indication(LCD_BUFF,status);
				break;
		case BRAKE_ON:
				brake_on_indication(LCD_BUFF,status);
				break;
		case WARNING_ON:
				warning_indication(LCD_BUFF,status);
				break;
		case TOP_BOTTOM_LINE:
				top_bottom_line(LCD_BUFF, status);
				break;
		case CLEAR_ERR_INDICATIONS:
				clear_all_error_indications(LCD_BUFF);
				break;
	}
}

void gem_vehice_modes(uint8_t mode)
{
  vehicle_mode_indication(LCD_BUFF,mode);
}

void gem_Navi_direction(uint8_t direction)
{     
	navigation_direction(LCD_BUFF,direction);
}

void gem_range_bar(uint8_t range_bar,uint8_t range_enable)
{
	range_bar_indication(LCD_BUFF,range_bar,range_enable);	
}

void gem_SOC_bar(uint8_t bar,uint8_t enable)
{	  
	soc_bar_indication(LCD_BUFF,bar,enable);	
}

void gem_trip_meter(int trip_disp)
{
    	//uint32_t trip_disp = get_trip_distance_disp();
	trip_display(LCD_BUFF,trip_disp);	
}

void gem_odo_meter(uint32_t odo_disp)
{
	//uint32_t odo_disp = get_Odo_Value_for_Disp();
	odometer_display(LCD_BUFF,odo_disp);	
}

void gem_Navi_distance(uint8_t kilometer,uint8_t meter)
{
	navigation_distance_display(LCD_BUFF,kilometer,meter);	
}

void gem_RTC(uint16_t rtc , uint8_t am_pm)
{
	rtc_display(LCD_BUFF,rtc, am_pm);
}

void gem_Range(uint8_t range)
{
	range_display(LCD_BUFF,range);
}

void gem_soc(uint8_t soc)
{
	soc_display(LCD_BUFF,soc);	
}

void gem_speed_or_soc_display(uint8_t speed)
{
	speed_or_soc_segments(LCD_BUFF,speed);
}

void gem_disable_msg(void)
{
	disable_segments_run_mode(LCD_BUFF);
}

void gem_disable(void)
{
	disable_segments_charging_mode(LCD_BUFF);    
}	

void Error_indcation_seg(uint8_t error)
{
	error_indiction_text(LCD_BUFF,error);	
}


void gem_set_clear_text_display(uint8_t error, uint8_t status)
{
	set_clear_error_text_display(LCD_BUFF,error,status);
}

void gem_text_display_update(void)
{
	error_indiction_text_display(LCD_BUFF);
}

void gem_Animation_text(char *str)
{
    Animation_text(LCD_BUFF,str);
}

void Set_LCD_Data(uint8_t Value)
{
	uint8_t i;
	//memset(LCD_BUFF,Value,sizeof(LCD_BUFF));
	for(i=0;i<120;i++)
	{
		LCD_BUFF[i].byte = Value;
	}
}


void top_bottom_alert(uint8_t status)
{
	top_bottom_line( LCD_BUFF ,status);
}

void gem_alertname(uint8_t status)
{
    alert_name_tag_warning( LCD_BUFF, status);
}
