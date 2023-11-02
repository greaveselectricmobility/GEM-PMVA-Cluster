/***********************************************************************************************************************
* File Name    : Calculations.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains declarations for various functions and defines essential macros. It serves as a central repository for function prototypes and macro definitions that are utilized throughout the Calculations.c file.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#ifndef CALC_H
#define CALC_H

void Vehicle_Speed_Calculations(void);

//uint16_t GEM_Vehicle_Speed_Calc(uint16_t v_Motor_RPM);
void GEM_Vehicle_Speed_Calc(uint16_t v_Motor_RPM);
uint8_t GEM_get_Vehicle_Speed(void);
uint32_t GEM_get_Odo_Value_mtr(void);
uint32_t GEM_get_Odo_Value_Disp(void);
uint32_t GEM_get_Trip_Odo_B_Value_Disp(void);
void GEM_Trip_Odo_B_Reset(void);

void GEM_Mem_Init(void);
void gem_odo_update(uint32_t nvm_odo);
void Odo_value_Mem_read(uint32_t *Odo_mem_read);
void GEM_ODO_write_Check(uint32_t odo_disp,uint32_t nvm_odo);
void i2c_test(void);

void Calculate_Dummy_Odo_value(void);
#endif