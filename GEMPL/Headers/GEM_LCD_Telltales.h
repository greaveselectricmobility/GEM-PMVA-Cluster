/***********************************************************************************************************************
* File Name    : GEM_LCD_Telltales.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains declarations for various functions and defines essential macros. It serves as a central repository for function prototypes and macro definitions that are utilized throughout the GEM_LCD_Telltales.c file.
* Creation Date: 28-08-2023
* Author	   : Thanushree K S
***********************************************************************************************************************/
#ifndef LCD_SYMBOL_H
#define LCD_SYMBOL_H
	

void GEM_Throttle_Telltale (Cluster_Data_t *Cluster_Data);
void GEM_Highbeam_Telltale (Cluster_Data_t *Cluster_Data);
void GEM_LeftTurn_Indicator_Telltale (Cluster_Data_t *Cluster_Data);
void GEM_RightTurn_Indicator_Telltale (Cluster_Data_t *Cluster_Data);
void GEM_Battery_Charging ( Cluster_Data_t *Cluster_Data );
void GEM_Service_Alert ( Cluster_Data_t *Cluster_Data );
void GEM_Reverse_Mode ( Cluster_Data_t *Cluster_Data );
void GEM_Battery_Full ( Cluster_Data_t *Cluster_Data );
void GEM_Battery_Low(Cluster_Data_t *Cluster_Data);
void GEM_MCU_Error(Cluster_Data_t *Cluster_Data);
void GEM_Motor_Error(Cluster_Data_t *Cluster_Data);
void GEM_MCU_Locked_Error(Cluster_Data_t *Cluster_Data);
void GEM_Limp_Home_Mode_Error(Cluster_Data_t *Cluster_Data);
void GEM_Ready_Indication ( Cluster_Data_t *Cluster_Data );
void GEM_Vehicle_Modes(Cluster_Data_t *Cluster_Data);
void GEM_SOC(Cluster_Data_t *Cluster_Data);
void GEM_SOC_Bar_Logic(int soc_percentage)  ;
void GEM_Speed_Display(Cluster_Data_t *Cluster_Data);
void GEM_SOC_Display(Cluster_Data_t *Cluster_Data);
void GEM_Brake_fluid(Cluster_Data_t *Cluster_Data);
void GEM_Top_Bottom_line(Cluster_Data_t *Cluster_Data);
void GEM_Alert_nametag_warning( Cluster_Data_t *Cluster_Data );
void GEM_Charging_Screen_Alert_nametag_warning( Cluster_Data_t *Cluster_Data );
//void GEM_clear_CAN_error_bits(  Cluster_Data_t *Cluster_Data );

#endif