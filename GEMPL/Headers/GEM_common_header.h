/***********************************************************************************************************************
* File Name    : GEM_common_header.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains common structures and macros that are utilized across multiple files.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/
#ifndef COMMON_H
#define COMMON_H

//#include <stdint.h>
#include <string.h>

#pragma pack

#include "r_cg_macrodriver.h"
#include "Feature_Config.h"


#define LCD_DATA_ARRAY_Size 120

#define _250KBPS 0x01
#define _500KBPS 0x02

#define CAN_BAUD_RATE _500KBPS


#define CAN_MESSAGE_COUNT 10
#define CAN_TIMEOUT_VALUE 10

#define UC_5V_Control_Output	 	    	P8_bit.no5
//#define UC_3V3_Control_Output	 	    	P8_bit.no4
#define LCD_BackLight_Control_Output 		P8_bit.no4
#define CAN_STB_OUTPUT 			        P3_bit.no7
#define Buzzer_Enable_Output		    	P9_bit.no3
#define BLE_Enable			        P2_bit.no2
#define CAN_TX_Pin				P0_bit.no0
#define CAN_RX_Pin				P0_bit.no1

/* LED OUTPUTS*/

//P1_bit.no3 = 0;//not on
//P1_bit.no4 = 1;//Right LED
//P1_bit.no5 = 0;//not on
//P1_bit.no6 = 0;//not on
//P0_bit.no7 = 0;//not on
//P1_bit.no3 = 1;//Left LED

#define LED_1_Output 			P1_bit.no5
#define LED_2_Output 			P1_bit.no6
//#define LED_3_Output 			P1_bit.no3
#define LED_3_Output 			P7_bit.no5
//#define LED_4_Output 			P1_bit.no4
#define LED_4_Output 			P1_bit.no1
#define LED_5_Output 			P0_bit.no7
//#define LED_5_Output 			P7_bit.no4
#define LED_6_Output 			P1_bit.no3

/* DIGITAL INPUTS*/

#define Digital_Input_1         P9_bit.no2 //BrakeFluid
#define Digital_Input_2         P9_bit.no1
#define Digital_Input_3         P9_bit.no0
#define Digital_Input_4         P8_bit.no7
#define Digital_Input_5         P8_bit.no6
#define Digital_Input_6         P8_bit.no2 //RID
#define Digital_Input_7         P1_bit.no7 //LID
#define Digital_Input_8         P8_bit.no3 //HBM
#define Digital_Input_9         P1_bit.no0
#define Digital_Input_10        P1_bit.no2 //IGN
#define Digital_Input_11

#define SIDE_STAND_INPUT 		P6_bit.no0
// #define Digital_Input_1 		P6_bit.no6
// #define Digital_Input_2 		P1_bit.no0
// #define Digital_Input_3 		P1_bit.no1
// #define Digital_Input_4 		P2_bit.no2
// #define Digital_Input_5 		P1_bit.no7
// #define Digital_Input_6 		P9_bit.no2
// #define Digital_Input_7 		P9_bit.no1
// #define Digital_Input_8 		P9_bit.no0
// #define Digital_Input_9 		P8_bit.no7
// #define Digital_Input_10 		P8_bit.no6
// #define Digital_Input_11 		P8_bit.no5


#define High_Beam_Input Digital_Input_8
#define Left_Turn_Input Digital_Input_7
#define Right_Turn_Input Digital_Input_6
#define Brake_Fluid_Indicator Digital_Input_1
#define Ignition_Input Digital_Input_10
/* ANALOG INPUTS*/
/*
#define Analog_Input_1 
#define Analog_Input_2 
#define Analog_Input_3 
#define Analog_Input_4 
#define Analog_Input_5 
#define Analog_Input_6 

*/

/* LCD PINS */
#define LCD_Disp_Chip_Select				P0_bit.no6
#define LCD_Disp_Reset					P0_bit.no3
#define LCD_Disp_SCL					P0_bit.no4
#define LCD_Disp_SData_Input				P0_bit.no2
#define LCD_Disp_SData_Input_Identification_A0		P0_bit.no5




#define ON 1
#define OFF 0

#define ENABLE 1
#define DISABLE 0


#define HIGH 1
#define LOW 0

#define TRUE 1
#define FALSE 0

#define OUTPUT_HIGH 1
#define OUTPUT_LOW 0

#define TX_BUFFER 5
#define NO_MASK 0
#define MASK_BUFFER_1 1
#define MASK_BUFFER_2 2
#define MASK_BUFFER_3 3
#define MASK_BUFFER_4 4


typedef union BYTE_t{
	unsigned char byte;
	struct{

		unsigned char bit_0 :1;
		unsigned char bit_1 :1;
		unsigned char bit_2 :1;
		unsigned char bit_3 :1;
		unsigned char bit_4 :1;
		unsigned char bit_5 :1;
		unsigned char bit_6 :1;
		unsigned char bit_7 :1;
	}bit;
}BYTE_t;

typedef union Digital_Input_Pin_t{
	uint16_t byte16;
	struct{

		uint16_t Left_Turn_Ind_IP :1;
		uint16_t Right_Turn_Ind_IP :1;
		uint16_t High_Beam_IP :1;
		uint16_t Brake_Fluid_IP :1;
        uint16_t bit_4 :1;
        uint16_t bit_5 :1;
        uint16_t bit_6 :1;
        uint16_t bit_7 :1;
        uint16_t bit_8 :1;
        uint16_t bit_9 :1;
        uint16_t bit_10 :1;
        uint16_t bit_11 :1;
        uint16_t bit_12 :1;
        uint16_t bit_13 :1;
        uint16_t bit_14 :1;
        uint16_t bit_15 :1;

	}bit;
}Digital_Input_Pin_t;

typedef union CAN_RX_Timeout_flag_t{
    uint32_t Timeout_Value;
    struct {
        uint32_t MSG_0x18FF015A_1AA                   :1;
        uint32_t MSG_0x18FF025A_2AA                   :1;
        uint32_t MSG_0x18FF035A_3AA                   :1;
        uint32_t MSG_0x18FF0D5A_4AC                   :1;
        uint32_t MSG_0x18FF0060_150                   :1;
        uint32_t MSG_0x14520902                       :1;
        uint32_t MSG_0x18530902                       :1;
        uint32_t MSG_0x18530904                       :1;
        uint32_t MSG_0x1C530902                       :1;
        uint32_t MSG_7DF                              :1;
    }Timeout_Flag;
}CAN_RX_Timeout_flag_t;


typedef union CAN_RX_Timeout_Counter_t
{
    uint8_t counter[CAN_MESSAGE_COUNT]; // No. of counter variables below
    struct{
        uint8_t MSG_0x18FF015A_1AA;
        uint8_t MSG_0x18FF025A_2AA;
        uint8_t MSG_0x18FF035A_3AA;
        uint8_t MSG_0x18FF0D5A_4AC;
        uint8_t MSG_0x18FF0060_150;
        uint8_t MSG_0x14520902;    
        uint8_t MSG_0x18530902;    
        uint8_t MSG_0x18530904;    
        uint8_t MSG_0x1C530902;    
        uint8_t MSG_7DF;           
    }count;
}CAN_RX_Timeout_Counter_t;

typedef union CAN_RX_Data_Bit_t{
	uint32_t byte32;
	struct{
        uint32_t BMS_ERR_DET                        :1;
        uint32_t BATT_FULL                          :1;
        uint32_t BATT_LOW                           :1;
        uint32_t BMS_WAR_DET                        :1;
        uint32_t ERR_OV                             :1;
        uint32_t ERR_UV1                            :1;
        uint32_t ERR_UV2                            :1;
        uint32_t ERR_THRMLRUNWY_TEMP                :1;
        uint32_t ERR_THRMLRUNWY_GAS                 :1;
        uint32_t ERR_THRMLRUNWY_WARNG               :1;
        uint32_t THRMLRUNWY_STS                     :2;
        uint32_t THRMLRUNWY_SRC                     :2;
        uint32_t Mode_Status_Flag                   :1;
        uint32_t Park_Indication                    :1;
        uint32_t Direction                          :1;
        uint32_t Overcurrent_Error                  :1;
        uint32_t Overload_Error                     :1;
        uint32_t Controller_Lock                    :1;
        uint32_t MCU_Charging_Status                :1;
        uint32_t Regenerative_Braking               :1;
        uint32_t Throttle_Error                     :1;
        uint32_t Controller_Error                   :1;
        uint32_t Motor_Error                        :1;
        uint32_t Immobilize_Sts                     :1;
        uint32_t Limp_Home_Mode                     :1;
        
    }SGNL;
}CAN_RX_Data_Bit_t;

typedef struct CAN_RX_Data_t{
    uint8_t SOC;
    uint8_t BMS_STATE;
    uint8_t MAX_CT;
    uint8_t MIN_CT;
    uint16_t Wheel_RPM;
    uint16_t Wheel_Revolution;
    uint8_t Throttle_Percentage;
    int8_t MCU_Temperature;
    int16_t Motor_Temperature;
    uint8_t MCU_Fault_Codes;
    CAN_RX_Data_Bit_t CAN_RX_Data_Bit;
    uint8_t CAN_Req[8];
    uint8_t CAN_Resp[8];
}CAN_RX_Data_t;

typedef union LED_Telltale_Symbol_t{
	unsigned char byte;
	struct{

		unsigned char LED_1 :1;
		unsigned char LED_2 :1;
		unsigned char LED_3 :1;
		unsigned char LED_4 :1;
		unsigned char LED_5 :1;
		unsigned char LED_6 :1;
		unsigned char bit_6 :1;
		unsigned char bit_7 :1;
	}bit;
}LED_Telltale_Symbol_t;

typedef union LCD_Telltale_Symbol_t{
    uint16_t byte16;
    struct{
        uint16_t Service_Alert_TT               :1;
        uint16_t Temperature_TT                 :1;
        uint16_t Battery_TT                     :1;
        uint16_t Throttle_Failure_TT            :1;
        uint16_t Thermal_Runaway_TT             :1;
        uint16_t Side_Stand_TT                  :1;
        uint16_t Reverse_TT                     :1;
        uint16_t Hazard_TT                      :1;
        uint16_t Brake_Fail_TT                  :1;
        uint16_t Bluetooth_TT                   :1;
        uint16_t Left_Turn_Indicator_TT         :1;
        uint16_t Battery_Charging_TT            :1;
        uint16_t Headlamp_HighBeam_TT           :1;
        uint16_t Rightt_Turn_Indicator_TT       :1;
        uint16_t Ready_TT                       :1;
        uint16_t bit_15                         :1;
    }bit;
}LCD_Telltale_Symbol_t;


typedef union CAN_Value_error_t{
	unsigned char Error;
	struct{

		unsigned char BMS_Value_Error :1;
		//unsigned char MCU_Value_Error :1;
		unsigned char Cluster_Calc_Value_Error :1;
        unsigned char Value_Error :1;
	}bit;
}CAN_Value_error_t;

typedef struct Cluster_Data_t{
    uint8_t Vehicle_Speed;
    //uint16_t Motor_Speed;
    uint32_t Odometer_Display;
    uint32_t Odometer_Memory;
    uint16_t Trip_meter_A;
    uint16_t Trip_meter_B;
    //uint8_t SOC_Percentage;
    uint8_t SOC_Bar;
    //uint8_t BMS_State;
    //uint8_t Thermal_Early_Warning;
    //uint8_t Thermal_Runaway;
    //uint8_t BMS_Error;
    //uint8_t Parking_Indication;
    //uint8_t Throttle_Error;
    //uint16_t Motor_Temperature;
    //uint8_t Controller_Temperature;
    //uint8_t Vehicle_Mode_Status;
    //uint8_t Reverse_Status;
    //uint8_t Ready_Status;
    CAN_RX_Data_t CAN_Data;
    CAN_Value_error_t CAN_Value_error;
    Digital_Input_Pin_t Digital_Input_Pin; 
    LCD_Telltale_Symbol_t LCD_TellTale_Symbol;
    LED_Telltale_Symbol_t LED_Telltale_Symbol;
}   Cluster_Data_t;


/*CAN SIGNAL STATE*/
#define DISCHARGING_STATE 0x00
#define CHARGERDET 0x01
#define CHARGING_STATE 0x04

#define CAN_THROTTLE_ERROR 0x01
#define CAN_READY_STATE 0x01
#define CAN_HEADLAMP_HIGHBEAM 0x01
#define CAN_RIGHT_TURN_INDICATOR 0x01
#define CAN_LEFT_TURN_INDICATOR 0x01
#define CAN_BATTERY_CHARGE 0x01
#define CAN_SERVICE ALERT 0x01
#define CAN_REVERSE_MODE 0x01
#define CAN_READY 0x01
#define CAN_BRAKE_FLUID 0x01

#define CAN_VEHICLE_MODE_ECO 0x00
#define CAN_VEHICLE_MODE_CITY 0x01
#define CAN_VEHICLE_MODE_PWR 0x01


#define CAN_BATTERY_FULL 0x01
#define CAN_BATTERY_LOW 0x01
#define CAN_MCU_ERROR 0x01
#define CAN_MOTOR_ERROR 0x01
#define CAN_MCU_LOCKED_ERROR 0x01
#define CAN_LIMP_HOME_MODE_ERROR 0x01
//void Set_LCD_Data(BYTE_t *LCD_Data,uint8_t Value,uint8_t length);
void Set_Cluster_Data(Cluster_Data_t *Cluster_Data,uint8_t Value,uint8_t length);
#endif