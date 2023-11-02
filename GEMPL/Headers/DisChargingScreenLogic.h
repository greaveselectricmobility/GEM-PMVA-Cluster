/***********************************************************************************************************************
* File Name    : DischargingScreenLogic.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains declarations for various functions and defines essential macros. It serves as a central repository for function prototypes and macro definitions that are utilized throughout the DischargingScreenLogic.c file.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/
#ifndef DISCHARGING_H
#define DISCHARGING_H


//void DisCharging_Screen(BYTE_t *LCD_Data,Cluster_Data_t *Cluster_Data,uint32_t gem_timer);
void DisCharging_Screen(Cluster_Data_t *Cluster_Data,uint32_t gem_timer);

#endif