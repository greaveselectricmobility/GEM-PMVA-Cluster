/***********************************************************************************************************************
* File Name    : lcd.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains declarations for various functions and defines essential macros. It serves as a central repository for function prototypes and macro definitions that are utilized throughout the lcd.c file.
* Creation Date: 28-08-2023
* Author	   : Praveen A
***********************************************************************************************************************/
#ifndef _LCD_H_
#define _LCD_H_

#include<stdio.h>
#include "iodefine.h"
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_serial.h"

typedef union{
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
}LCD_DATA_BUFF;

extern LCD_DATA_BUFF LCD_BUFF[120];

#define THERMAL_RUNAWAY_ERR 1
#define BAT_ERR             2
#define BATTERY_LOW         3
#define MOTOR_ERR           4
#define MCU_ERR             5
#define THROTTLE_ERR        6
#define BATTERY_FULL        7
#define RESET_SEG           50

#define MCU_ERROR_TXT 			0
#define MOTOR_ERROR_TXT 		1
#define LIMP_MODE_HOME_TXT 		2
#define MCU_LOCKED_TXT 			3
#define BATTERY_FULL_TXT 		4
#define BATTERY_LOW_TXT 		5
//#define MCU_VALUE_ERROR_TXT		6

#define CLEAR_TXT 				6
#define MAX_TXT_DISP_COUNT 	6


typedef union ERROR_BITS_t{
	uint8_t BYTE;
	struct{
		uint8_t BIT_MCU_ERROR 		:1;
		uint8_t BIT_MOTOR_ERROR 	:1;
		uint8_t BIT_LIMP_MODE_HOME 	:1;
		uint8_t BIT_MCU_LOCKED 		:1;
		uint8_t BIT_BATTERY_FULL 	:1;
		uint8_t BIT_BATTERY_LOW 	:1;
		//uint8_t BIT_MCU_VALUE_ERROR :1;
		uint8_t BIT_VALUE_ERROR 	:1;

	}BIT;
}ERROR_BITS_t;



#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8
#define J 9
#define K 10
#define L 11
#define M 12
#define N 13
#define O 14
#define P 15
#define Q 16
#define R 17
#define S 18
#define T 19
#define U 20
#define V 21
#define W 22
#define X 23
#define Y 24
#define Z 25

#define TXT_A 0
#define TXT_B 1
#define TXT_C 2
#define TXT_D 3
#define TXT_E 4
#define TXT_F 5
#define TXT_G 6
#define TXT_H 7
#define TXT_I 8
#define TXT_J 9
#define TXT_K 10
#define TXT_L 11
#define TXT_M 12
#define TXT_N 13
#define TXT_O 14
#define TXT_P 15
#define TXT_Q 16
#define TXT_R 17
#define TXT_S 18
#define TXT_T 19
#define TXT_U 20
#define TXT_V 21
#define TXT_W 22
#define TXT_X 23
#define TXT_Y 24
#define TXT_Z 25
#define BLANK 26
#define NUM_0 27
#define NUM_1 28
#define NUM_2 29
#define NUM_3 30
#define NUM_4 31
#define NUM_5 32
#define NUM_6 33
#define NUM_7 34
#define NUM_8 35
#define NUM_9 36
#define NUM_PLUS 37
#define NUM_MINUS 38
#define NUM_MULTIPLY 39
#define NUM_DIVIDE 40
#define NUM_EQUAL 41
#define NUM_DOT 42

#define TXT_POS_1 	1
#define TXT_POS_2 	2
#define TXT_POS_3	3
#define TXT_POS_4	4
#define TXT_POS_5	5
#define TXT_POS_6	6
#define TXT_POS_7	7
#define TXT_POS_8	8
#define TXT_POS_9	9
#define TXT_POS_10	10
#define TXT_POS_11	11
#define TXT_POS_12	12
#define TXT_POS_13	13
#define TXT_POS_14	14
#define TXT_POS_15	15
#define TXT_POS_16	16
#define TXT_POS_17	17
#define TXT_POS_18	18
#define TXT_POS_19	19
#define TXT_POS_20	20
#define TXT_POS_21	21
#define TXT_POS_22	22

#define MAX_TXT_POS	22




#define SIDESTAND_ON        1
#define THROTTLE_ON         2
#define BATTERY_ON          3
#define TEMP_ON             4
#define MOTOR_ON            5
#define MCU_ON              6
#define SERIVCE_ON          7
#define BRAKE_ON            8
#define WARNING_ON          9
#define THERMAL_RUNAWAY_ON  10
#define TOP_BOTTOM_LINE     11
#define CLEAR_ERR_INDICATIONS  50

#define RIGHT_INDICATOR_BIT     P8_bit.no2  
#define LEFT_INDICATOR_BIT      P1_bit.no7
#define HIGH_BEAM_BIT 			P8_bit.no3

#define LED_BRAKE_FLUID_BIT 	P9_bit.no2
#define BRAKE_FLUID_LED		 	P7_bit.no5
#define LED_PARKING_BIT 		P9_bit.no1
#define PARKING_LED 			P1_bit.no1

#define LCD_IF_A0 				P0_bit.no5
#define LCD_IF_CS 				P0_bit.no6
#define LCD_IF_RESET			P0_bit.no3

#define HIGH      1
#define LOW       0

#define LEFT_ON      1
#define LEFT_OFF     2
#define RIGHT_ON     3
#define RIGHT_OFF    4


#define ECO  1
#define CITY 2
#define PWR  3
#define ECO_PWR  4


#define bar0  0
#define bar1  1
#define bar2  2
#define bar3  3
#define bar4  4
#define bar5  5
#define bar6  6
#define bar7  7
#define bar8  8
#define bar9  9
#define bar10 10

#define  range0  0
#define  range1  1
#define  range2  2
#define  range3  3
#define  range4  4
#define  range5  5
#define  range6  6
#define  range7  7
#define  range8  8
#define  range9  9
#define  range10 10

#define DIRECTION_1 1
#define DIRECTION_2 2
#define DIRECTION_3 3
#define DIRECTION_4 4
#define DIRECTION_5 5
#define DIRECTION_6 6
#define DIRECTION_7 7


#define ON  1
#define OFF 0

#define SET  1
#define CLEAR 0



void Error_indcation_seg(uint8_t fault);
void initLCM(void);
void disp_lattice(void);
void disp_seg(unsigned char *p);
void write_send(uint8_t temp);
void write_com(uint8_t para);
void write_data(uint8_t para);
void delay(uint8_t ms);
void Set_LCD_Data(uint8_t Value);

void gem_disable(void);
void gem_disable_msg(void);
void gem_speed_or_soc_display(uint8_t spd);
void gem_soc(uint8_t pre);
void gem_Range(uint8_t rang);
void gem_RTC(uint16_t rtc, uint8_t am_pm);
void gem_Navi_distance(uint8_t Km,uint8_t m);
void gem_trip_meter(int trip_disp);
void gem_odo_meter(uint32_t odo_disp);
void gem_SOC_bar(uint8_t bar,uint8_t en);
void gem_range_bar(uint8_t r_bar,uint8_t r_en);
void gem_Navi_direction(uint8_t way);
void gem_vehice_modes(uint8_t mode);
void gem_err_indication(uint8_t warng,uint8_t stat);
void gem_Ready(uint8_t rdy);
void gem_Reverse(uint8_t reverse);
void gem_battery_charg(uint8_t chrg_status);
void gem_battery_charge_animation(uint8_t status);
void gem_high(uint8_t high);
void gem_LEFT_RIGHT(uint8_t inc);
void top_bottom_alert(uint8_t status);
void gem_alertname(uint8_t status);



#define DISPLAY_DB_SIZE 12 // 13 segement
#define s_DISPLAY_DB_SIZE 12 // 7segement
#define ABCD_DISPLAY_DB_SIZE 43 // 18 segement

/*13 segement*/
#define SEGMENT_A 0x0001
#define SEGMENT_B 0x0002
#define SEGMENT_C 0x0004
#define SEGMENT_D 0x0008
#define SEGMENT_E 0x0010
#define SEGMENT_F 0x0020
#define SEGMENT_G 0x0040
#define SEGMENT_H 0x0080
#define SEGMENT_I 0x0100
#define SEGMENT_J 0x0200
#define SEGMENT_K 0x0400
#define SEGMENT_L 0x0800
#define SEGMENT_M 0x1000
/*7 segement*/
#define s_SEGMENT_A 0x01
#define s_SEGMENT_B 0x02
#define s_SEGMENT_C 0x04
#define s_SEGMENT_D 0x08
#define s_SEGMENT_E 0x10
#define s_SEGMENT_F 0x20
#define s_SEGMENT_G 0x40
         //32 16 8 4 2 1
// #define SEGMENT_A 0x000001  //1seg
// #define SEGMENT_B 0x000002
// #define SEGMENT_C 0x000004
// #define SEGMENT_D 0x000008
// #define SEGMENT_E 0x000010
// #define SEGMENT_F 0x000020
// #define SEGMENT_G 0x000040
// #define SEGMENT_H 0x000080
// #define SEGMENT_I 0x000100
// #define SEGMENT_J 0x000200
// #define SEGMENT_K 0x000400
// #define SEGMENT_L 0x000800
// #define SEGMENT_M 0x001000
#define SEGMENT_N 0x002000
#define SEGMENT_O 0x004000
#define SEGMENT_P 0x008000
#define SEGMENT_Q 0x010000
#define SEGMENT_R 0x020000  //18seg

/*
segment 18   
2 1 8 4 2 1 8 4 2 1 8 4 2 1 8 4 2 1 
R Q P O N M L K J I H G F E D C B A   index  Data
0 0 0 0 1 1 0 0 0 0 1 1 0 0 1 1 1 1     A    0x030CF
0 1 1 0 1 0 0 1 1 0 0 0 1 1 1 1 1 1     B    0x1A63F
0 0 0 0 0 0 0 0 0 0 1 1 1 1 0 0 1 1     C    0x000F3
0 1 1 0 0 0 0 1 1 0 0 0 1 1 1 1 1 1     D    0x1863F
0 0 0 0 1 1 0 0 0 0 1 1 1 1 0 0 1 1     E    0x030F3
0 0 0 0 1 1 0 0 0 0 1 1 0 0 0 0 1 1     F    0x030C3
0 0 0 0 1 0 0 0 0 0 1 1 1 1 1 0 1 1     G    0x020FB
0 0 0 0 1 1 0 0 0 0 1 1 0 0 1 1 0 0     H    0x030CC
0 1 1 0 0 0 0 1 1 0 0 0 1 1 0 0 1 1     I    0x18633
0 1 1 0 0 0 0 1 1 0 0 1 1 0 0 0 1 1     J    0x18663
1 0 0 0 0 1 1 0 0 0 1 1 0 0 0 0 0 0     K    0x218C0
0 0 0 0 0 0 0 0 0 0 1 1 1 1 0 0 0 0     L    0x000F0
0 0 0 0 0 0 1 0 0 1 1 1 0 0 1 1 0 0     M    0x009CC
1 0 0 0 0 0 0 0 0 1 1 1 0 0 1 1 0 0     N    0x201CC
0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1     O    0x000FF
0 0 0 0 1 1 0 0 0 0 1 1 0 0 0 1 1 1     P    0x030C7
1 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1     Q    0x200FF
1 0 0 0 1 1 0 0 0 0 1 1 0 0 0 1 1 1     R    0x230C7
0 0 0 0 1 1 0 0 0 0 1 0 1 1 1 0 1 1     S    0x030BB
0 1 1 0 0 0 0 1 1 0 0 0 0 0 0 0 1 1     T    0x18603
0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 0 0     U    0x000FC
0 0 0 1 0 0 1 0 0 0 1 1 0 0 0 0 0 0     V    0x048C0
1 0 0 1 0 0 0 1 1 0 1 1 0 0 1 1 0 0     W    0x246CC
1 0 0 1 0 0 1 0 0 1 0 0 0 0 0 0 0 0     X    0x24900
0 1 1 0 0 0 1 0 0 1 0 0 0 0 0 0 0 0     Y    0x18900
0 0 0 1 0 0 1 0 0 0 0 0 1 1 0 0 1 1     Z    0x04833
*/
/*
13 segement
1 8 4 2 1 8 4 2 1 8 4 2 1
M L K J I H G F E D C B A  index  data
0 0 1 1 1 1 1 1 1 1 1 1 1    0    0x07FF
0 0 0 0 0 0 0 1 1 1 1 1 0    1    0x003E
1 1 1 0 1 1 1 1 0 1 1 1 1    2    0x1DEF
1 1 1 0 0 0 1 1 1 1 1 1 1    3    0x1C7F
1 1 1 1 1 0 0 1 1 1 1 1 0    4    0x1F3E
1 1 1 1 1 0 1 1 1 1 0 1 1    5    0x1F7B//
1 1 1 1 1 1 1 1 1 1 0 1 1    6    0x1FFB//
0 0 1 0 0 0 0 1 1 1 1 1 1    7    0x043F
1 1 1 1 1 1 1 1 1 1 1 1 1    8    0x1FFF
1 1 1 1 1 0 1 1 1 1 1 1 1    9    0x1F7F//
1 1 0 0 0 0 0 0 0 0 0 0 0    -    0x1800
0 0 0 0 0 0 0 0 0 0 0 0 0  empty  0x0000
7 segement
 4 2 1 8 4 2 1
 G F E D C B A  index  data
 0 1 1 1 1 1 1   0     0x3F
 0 0 0 0 1 1 0   1     0x06
 1 0 1 1 0 1 1   2     0x5B
 1 0 0 1 1 1 1   3     0x4F
 1 1 0 0 1 1 0   4     0x66
 1 1 0 1 1 0 1   5     0x6D
 1 1 1 1 1 0 1   6     0x7D
 0 0 0 0 1 1 1   7     0x07
 1 1 1 1 1 1 1   8     0x7F
 1 1 0 1 1 1 1   9     0x6F
 1 0 0 0 0 0 0   -     0x40
 0 0 0 0 0 0 0  empty  0x00
*/

void initLCM(void);









void speed_or_soc_segments(LCD_DATA_BUFF *lcd_data, uint8_t value);
void disable_segments_run_mode(LCD_DATA_BUFF *lcd_data);
void disable_segments_charging_mode(LCD_DATA_BUFF *lcd_data);
void reverse_telltale(LCD_DATA_BUFF *lcd_data, uint8_t reverse);
void battery_charging_telltale(LCD_DATA_BUFF *lcd_data, uint8_t status);
void battery_chrg_Animation(LCD_DATA_BUFF *lcd_data, uint8_t status);
void right_indicator_telltile(LCD_DATA_BUFF *lcd_data, uint8_t status);
void left_indicator_telltile(LCD_DATA_BUFF *lcd_data, uint8_t status);
void ready_indication(LCD_DATA_BUFF *lcd_data, uint8_t status);
void parking_led_control(uint8_t status);
void break_fluid_led_control(uint8_t status);
void hazard_lamp_control(uint8_t right_bit,uint8_t left_bit);
void thermal_runaway_indication(LCD_DATA_BUFF *lcd_data, uint8_t status);
void side_stand_indication(LCD_DATA_BUFF *lcd_data, uint8_t status);	
void throttle_on_indication(LCD_DATA_BUFF *lcd_data, uint8_t status);
void battery_on_indication(LCD_DATA_BUFF *lcd_data, uint8_t status);
void temp_on_indication(LCD_DATA_BUFF *lcd_data, uint8_t status);
void service_on_indication(LCD_DATA_BUFF *lcd_data, uint8_t status);
void brake_on_indication(LCD_DATA_BUFF *lcd_data, uint8_t status);
void warning_indication(LCD_DATA_BUFF *lcd_data, uint8_t status);
void top_bottom_line(LCD_DATA_BUFF *lcd_data, uint8_t status);
void alert_name_tag_warning(LCD_DATA_BUFF *lcd_data, uint8_t status);
void clear_all_error_indications(LCD_DATA_BUFF *lcd_data);
void error_indiction_text(LCD_DATA_BUFF *lcd_data, uint8_t error);

void right_indicator_telltile_control(uint8_t status);
void left_indicator_telltile_control(uint8_t status);
void vehicle_mode_indication(LCD_DATA_BUFF *lcd_data, uint8_t mode);
void navigation_direction(LCD_DATA_BUFF *lcd_data, uint8_t direction);
void trip_display(LCD_DATA_BUFF *lcd_data, uint32_t trip_disp);
void soc_bar_indication(LCD_DATA_BUFF *lcd_data, uint8_t bar, uint8_t enable);
void range_bar_indication(LCD_DATA_BUFF *lcd_data, uint8_t bar, uint8_t enable);
void init_io(void);
void soc_display(LCD_DATA_BUFF *lcd_data, uint8_t soc);
void range_display(LCD_DATA_BUFF *lcd_data, uint8_t range);
void rtc_display(LCD_DATA_BUFF *lcd_data, uint16_t rtc, uint8_t am_pm);
void trip_display(LCD_DATA_BUFF *lcd_data, uint32_t trip_disp);
void odometer_display(LCD_DATA_BUFF *lcd_data, uint32_t odo_disp);
void navigation_distance_display(LCD_DATA_BUFF *lcd_data, uint8_t kilometer, uint8_t meter);
void highbeam_telltile(LCD_DATA_BUFF *lcd_data, uint8_t highbeam);
void set_clear_error_text_display(LCD_DATA_BUFF *lcd_data, uint8_t error, uint8_t status);
void error_indiction_text_display(LCD_DATA_BUFF *lcd_data);
void gem_set_clear_text_display(uint8_t error, uint8_t status);
void gem_text_display_update(void);
void gem_Animation_text(char *str);
void Animation_text(LCD_DATA_BUFF *lcd_data, char *str);



#endif