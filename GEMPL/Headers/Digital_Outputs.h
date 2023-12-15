/***********************************************************************************************************************
* File Name    : Digital_Outputs.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains declarations for various functions and defines essential macros. It serves as a central repository for function prototypes and macro definitions that are utilized throughout the Digital_Outputs.c file.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/
#ifndef DIGITAL_OUTPUT_H
#define DIGITAL_OUTPUT_H


void Uc_5V_Control(uint8_t State);
void LCD_BackLight_Control(uint8_t State);
void CAN_STANDBY_Output_Control(uint8_t State);
void CAN_TX(uint8_t State);


void LED_OUTPUT_1(uint8_t State);
void LED_OUTPUT_2(uint8_t State);
void LED_OUTPUT_3(uint8_t State);
void LED_OUTPUT_4(uint8_t State);
void LED_OUTPUT_5(uint8_t State);
void LED_OUTPUT_6(uint8_t State);


#endif