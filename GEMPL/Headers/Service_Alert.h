/***********************************************************************************************************************
* File Name    : Service_Alert.h
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This header file contains declarations for various functions and defines essential macros. It serves as a central repository for function prototypes and macro definitions that are utilized throughout the Service_Alert.c file.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/
#ifndef _SERVICE_ALERT_H_
#define _SERVICE_ALERT_H_


#define service_symbol_blink_interval 10
#define TRUE 1
#define FALSE 0


uint8_t Service_alert_blink(int blink_rate_interval, int blink_ctrl,uint32_t gem_timer);
void Service_alert(Cluster_Data_t *Cluster_Data,uint32_t gem_timer);



#endif

