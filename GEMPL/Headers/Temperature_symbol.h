/***********************************************************************************************************************
* File Name    : Temperature_symbol.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains declarations for various functions and defines essential macros. It serves as a central repository for function prototypes and macro definitions that are utilized throughout the Temperature_symbol.c file.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/
#ifndef TEMPERATURE_SYMBOL_H
#define TEMPERATURE_SYMBOL_H

//void Temperature_symbol_check(BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data,uint32_t gem_timer);
void Temperature_symbol_check(Cluster_Data_t *Cluster_Data,uint32_t gem_timer);

#endif