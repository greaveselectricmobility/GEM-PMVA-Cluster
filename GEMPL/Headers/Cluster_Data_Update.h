/***********************************************************************************************************************
* File Name    : Cluster_Data_Update.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains declarations for various functions and defines essential macros. It serves as a central repository for function prototypes and macro definitions that are utilized throughout the Cluster_Data_Update.c file.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#ifndef UPDATE_H
#define UPDATE_H

#include "GEM_common_header.h"

void Update_Message_Buffer(Cluster_Data_t *Cluster_Data,uint32_t gem_timer);
int16_t get_GEM_Motor_RPM(void);

#endif