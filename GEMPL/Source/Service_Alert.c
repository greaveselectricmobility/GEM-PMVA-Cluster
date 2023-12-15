/***********************************************************************************************************************
* File Name    : Service_Alert.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the Service alert functionality.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
***********************************************************************************************************************/

#include "GEM_common_header.h"
#include <string.h>
#include "Service_Alert.h"
#include "lcd.h"
#include "my_can.h"



/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
uint8_t Service_alert_blink(int blink_rate_interval, int blink_ctrl,uint32_t gem_timer)
{
    
    static uint32_t prev_ser_alrt_symbol_ms = 0;
    static uint8_t temp_ser_alrt_sym_state = ON;
    if (blink_ctrl)
    {
	    if ((gem_timer - prev_ser_alrt_symbol_ms) >= blink_rate_interval)
	    {
	        if(!temp_ser_alrt_sym_state)
	        {
	            temp_ser_alrt_sym_state= ON;
	        }
	        else
	        {
	            temp_ser_alrt_sym_state= OFF;
	        }
	        prev_ser_alrt_symbol_ms = gem_timer;   
	    }
    }
    else
    {
	    temp_ser_alrt_sym_state= OFF;
	    prev_ser_alrt_symbol_ms = gem_timer;
    }
    return temp_ser_alrt_sym_state;
}

/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void Service_alert(Cluster_Data_t *Cluster_Data,uint32_t gem_timer)
{
    static uint8_t Service_alert_Symbol_State=0;  //0 - OFF, 1 - Blink, 2 - ON.
    uint32_t s_km_mod_1000 = 0xFFFFFFFF;
    uint32_t s_km_mod_5000 = 0xFFFFFFFF;
    uint8_t ser_sts_flag=0;
    static uint8_t ser_sts=0;

    uint32_t Service_km = (Cluster_Data->Odometer_Display) / 10;
    if (Service_km > 1500)
    {
        s_km_mod_5000 = Service_km % 5000;
    }
    else if ((Service_km >= 500) && (Service_km <= 1500))
    {
        s_km_mod_1000 = Service_km % 1000;
    }
    

    if(ser_sts != 1)
    {
        if (((s_km_mod_1000 >= 950) && (s_km_mod_1000 < 1000)) || ((s_km_mod_5000 >= 4950) && (s_km_mod_5000 < 5000)))
        {
           Service_alert_Symbol_State = Service_alert_blink(10,ENABLE,gem_timer);
            Cluster_Data->LCD_TellTale_Symbol.bit.Service_Alert_TT = 1;
            ser_sts_flag = 1;

        }
        else if (((s_km_mod_1000 < 50)) || ((s_km_mod_5000 < 50)))
        {
            
            Service_alert_blink(0,DISABLE,gem_timer);
            Service_alert_Symbol_State = ON;
            Cluster_Data->LCD_TellTale_Symbol.bit.Service_Alert_TT = 1;
            ser_sts_flag=1;
            
        }
        else
        {
            Service_alert_Symbol_State = OFF;
            Service_alert_blink(0,DISABLE,gem_timer);
            Cluster_Data->LCD_TellTale_Symbol.bit.Service_Alert_TT = 0;
            ser_sts_flag=0;
        }
    }
    if((Cluster_Data->CAN_Data.CAN_Req[1] == 0x2E) && (Cluster_Data->CAN_Data.CAN_Req[3] == 0x01))
    {
	    ser_sts=1;
        if(Cluster_Data->CAN_Data.CAN_Req[4] == 0x00)
        {
            Service_alert_Symbol_State=OFF;
        }
        else if(Cluster_Data->CAN_Data.CAN_Req[4] == 0x01)
        {
            Service_alert_Symbol_State=ON;
        }
        Cluster_Data->CAN_Data.CAN_Resp[0] = 0x03;
        Cluster_Data->CAN_Data.CAN_Resp[1] = 0x6E;
        Cluster_Data->CAN_Data.CAN_Resp[2] = 0x00;
        Cluster_Data->CAN_Data.CAN_Resp[3] = 0x01;
        Cluster_Data->CAN_Data.CAN_Resp[4] = 0xFF;
        Cluster_Data->CAN_Data.CAN_Resp[5] = 0xFF;
        Cluster_Data->CAN_Data.CAN_Resp[6] = 0xFF;
        Cluster_Data->CAN_Data.CAN_Resp[7] = 0xFF;
        MY_Tx_MsgBuf_Processing(13,8,&Cluster_Data->CAN_Data.CAN_Resp[0]);
        memset(&Cluster_Data->CAN_Data.CAN_Resp[0],0,8);
        memset(&Cluster_Data->CAN_Data.CAN_Req[0],0,8);
    }
    if((Cluster_Data->CAN_Data.CAN_Req[1] == 0x22) && (Cluster_Data->CAN_Data.CAN_Req[3] == 0x01))
    {
        Cluster_Data->CAN_Data.CAN_Resp[0] = 0x04;
        Cluster_Data->CAN_Data.CAN_Resp[1] = 0x62;
        Cluster_Data->CAN_Data.CAN_Resp[2] = 0x00;
        Cluster_Data->CAN_Data.CAN_Resp[3] = 0x01;
        Cluster_Data->CAN_Data.CAN_Resp[4] = ser_sts_flag;
        Cluster_Data->CAN_Data.CAN_Resp[5] = 0xFF;
        Cluster_Data->CAN_Data.CAN_Resp[6] = 0xFF;
        Cluster_Data->CAN_Data.CAN_Resp[7] = 0xFF;
        MY_Tx_MsgBuf_Processing(13,8,&Cluster_Data->CAN_Data.CAN_Resp[0]);
        memset(&Cluster_Data->CAN_Data.CAN_Resp[0],0,8);
        memset(&Cluster_Data->CAN_Data.CAN_Req[0],0,8);
    }
    gem_err_indication(SERIVCE_ON,Service_alert_Symbol_State);
}
