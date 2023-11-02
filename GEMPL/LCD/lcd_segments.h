/***********************************************************************************************************************
* File Name    : lcd_segments.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains declarations for various functions and defines essential macros. It serves as a central repository for function prototypes and macro definitions that are utilized throughout the ldc_segments.c file.
* Creation Date: 28-08-2023
* Author	   : Praveen A
***********************************************************************************************************************/
#ifndef _LCD_S_H_
#define _LCD_S_H_


#include"lcd.h"



unsigned short s_display_db[s_DISPLAY_DB_SIZE] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40,0x00};//7 segement
const unsigned short display_db[DISPLAY_DB_SIZE] = {0x07FF,0x003E,0x1DEF,0x1C7F,0x1F3E,0x1F7B,0x1FFB,0x043F,0x1FFF,0x1F7F,0x1800,0x0000};//speedo meter array
const unsigned long int ABCD_display_db[ABCD_DISPLAY_DB_SIZE] = {0x030CF,0x1A63F,0x000F3,0x1863F,0x030F3,0x030C3,0x020FB,0x030CC,0x18633,0x18663,0x218C0,0x000F0,0x009CC,0x201CC,0x000FF,0x030C7,0x200FF,0x230C7,0x030BB,0x18603,0x000FC,0x048C0,0x246CC,0x24900,0x18900,0x04833,0x0000,0x000FF,0x0000C,0x03077,0x0303F,0x0308C,0x030BB,0x030FB,0x0000F,0x030FF,0x030BF,0x1B600,0x03000,0x3FF00,0x04800,0x03030, 0x10000};//ABCD

#define s_GET_DISP_DATA_BIT(s_idx, s_seg)  (s_display_db[s_idx] & s_seg)? 1 : 0 //7 segement
#define GET_DISP_DATA_BIT(idx, seg)  (display_db[idx] & seg)? 1 : 0 //13 segement
#define ABC_GET_DISP_DATA_BIT(idx, seg)  (ABCD_display_db[idx] & seg)? 1 : 0 //18 segement

#define CHECK_BIT(x, pos) (x & (1UL << pos) )

#define TXT_DISP_DURATION   50

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
void vehicle_mode_indication(LCD_DATA_BUFF *lcd_data, uint8_t mode);
void navigation_direction(LCD_DATA_BUFF *lcd_data, uint8_t direction);
void trip_display(LCD_DATA_BUFF *lcd_data, uint32_t trip_disp);
void soc_bar_indication(LCD_DATA_BUFF *lcd_data, uint8_t bar, uint8_t enable);
void range_bar_indication(LCD_DATA_BUFF *lcd_data, uint8_t bar, uint8_t enable);
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

void top_bottom_alert(uint8_t status);
void gem_alertname(uint8_t status);
void clear_error_bits();
void init_io();














#endif
