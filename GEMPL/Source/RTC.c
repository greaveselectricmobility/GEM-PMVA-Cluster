#include <stdio.h>
//#include <time.h>
#include <stdint.h>

#include "lcd.h"
#include "GEM_common_header.h"
#include "GEM_can.h"
uint8_t GEM_Tx_Databuf[8];

void GEM_RTC(void)
{
    uint32_t rawtime = 12623189787;
    
    uint16_t seconds = rawtime % 60;
    uint16_t minutes = (rawtime / 60) % 60;
    uint16_t hours = (rawtime / 3600) % 24; 

    // Calculate the uint value representing "HHMM"
    uint16_t hourMinute = (hours * 100) + minutes;
    
    if(hourMinute> 1200)
    {
        gem_RTC(hourMinute - 1200, 1);
    }
    else
    {
        gem_RTC(hourMinute, 0);
    }
    
}

void CAN_Tx_Sample(Cluster_Data_t *Cluster_Data, uint32_t ID)
{
    switch (ID)
    {
        case (0x300):
				memcpy(&GEM_Tx_Databuf[0],&Cluster_Data->Trip_meter_B, 4); // trip distance
				memcpy(&GEM_Tx_Databuf[4],&Cluster_Data->Odometer_Display, 4); // odo value
        
        case (0x301):
                GEM_Tx_Databuf[2] = Cluster_Data->Vehicle_Speed;
                GEM_Tx_Databuf[6] = ((GEM_Tx_Databuf[6] & 0xF0) | (Cluster_Data->SOC_Bar << 4)); 

        case (0x304):
                //GEM_Tx_Databuf[1] = Cluster_Data->   //RTC value

        case (0x305):
                //GEM_Tx_Databuf[0] = ((GEM_Tx_Databuf[0] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Side_Stand_TT ));
                GEM_Tx_Databuf[0] = ((GEM_Tx_Databuf[0] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Side_Stand_TT  << 2)); //side stand
                GEM_Tx_Databuf[0] = ((GEM_Tx_Databuf[0] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 4));  //Motor temp high
                GEM_Tx_Databuf[0] = ((GEM_Tx_Databuf[0] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 6));  //MCU Temp high
                GEM_Tx_Databuf[1] = ((GEM_Tx_Databuf[1] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT ));         //BMS High Temp
                GEM_Tx_Databuf[1] = ((GEM_Tx_Databuf[1] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Thermal_Runaway_TT << 2 )); //Thermal runaway 
                GEM_Tx_Databuf[1] = ((GEM_Tx_Databuf[1] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT  << 4 )); //BMS Failure
                GEM_Tx_Databuf[1] = ((GEM_Tx_Databuf[1] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 6 )); //Battery failure
                GEM_Tx_Databuf[2] = ((GEM_Tx_Databuf[2] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT )); //MCU failure
                GEM_Tx_Databuf[2] = ((GEM_Tx_Databuf[2] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 2 )); //Motor failure
                GEM_Tx_Databuf[2] = ((GEM_Tx_Databuf[2] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 4 )); //VCU failure *
                //GEM_Tx_Databuf[2] = ((GEM_Tx_Databuf[2] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 2 )); //Telematics failure
                //GEM_Tx_Databuf[3] = ((GEM_Tx_Databuf[3] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT )); //Limp Home Mode
                GEM_Tx_Databuf[3] = ((GEM_Tx_Databuf[3] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Service_Alert_TT << 2 )); //Service alert
                GEM_Tx_Databuf[3] = ((GEM_Tx_Databuf[3] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Service_Alert_TT  << 4 )); //Service alert due to fault
                //GEM_Tx_Databuf[3] = ((GEM_Tx_Databuf[3] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 6 )); //Speed mode
                GEM_Tx_Databuf[4] = ((GEM_Tx_Databuf[4] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Battery_Charging_TT ));    //Battery charging status
                //GEM_Tx_Databuf[4] = ((GEM_Tx_Databuf[4] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Battery_Charging_TT << 2 )); //Aux Battery Charging
                GEM_Tx_Databuf[4] = ((GEM_Tx_Databuf[4] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Hazard_TT  << 4 )); //Hazard
                GEM_Tx_Databuf[4] = ((GEM_Tx_Databuf[4] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Headlamp_HighBeam_TT << 6 )); //High Beam
                GEM_Tx_Databuf[5] = ((GEM_Tx_Databuf[5] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Left_Turn_Indicator_TT ));  //Left turn indicator
                GEM_Tx_Databuf[5] = ((GEM_Tx_Databuf[5] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Rightt_Turn_Indicator_TT << 2 )); //right turn indicator 
                GEM_Tx_Databuf[5] = ((GEM_Tx_Databuf[5] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Ready_TT  << 4 )); //ready status
                GEM_Tx_Databuf[5] = ((GEM_Tx_Databuf[5] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Reverse_TT << 6 )); //reverse status
                GEM_Tx_Databuf[6] = ((GEM_Tx_Databuf[6] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Throttle_Failure_TT ));         //throttle failure
                GEM_Tx_Databuf[6] = ((GEM_Tx_Databuf[6] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Battery_TT << 2 )); //battery low
              //GEM_Tx_Databuf[6] = ((GEM_Tx_Databuf[6] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT  << 4 )); //key fob not near vehicle
              //GEM_Tx_Databuf[6] = ((GEM_Tx_Databuf[6] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 6 )); //luggage box lamp
                GEM_Tx_Databuf[7] = ((GEM_Tx_Databuf[7] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Brake_Fail_TT ));         //Brake failure
              //GEM_Tx_Databuf[7] = ((GEM_Tx_Databuf[7] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Thermal_Runaway_TT << 2 )); //DC-DC convert failure
              //GEM_Tx_Databuf[7] = ((GEM_Tx_Databuf[7] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.buzzer  << 4 )); //Buzzer
              //GEM_Tx_Databuf[7] = ((GEM_Tx_Databuf[7] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 6 )); //reserved
        
        case (0x306):        
                // yet to implement related to bluetooth
                
        case (0x307): 
                // yet to implement related to bluetooth
        
        case (0x308):
                // yet to implement related to bluetooth

        case (0x309):
                //memcpy(&GEM_Tx_Databuf[0],&Cluster_Data->Trip_meter_A, 4);//trip distance
              //memcpy(&GEM_Tx_Databuf[4],&Cluster_Data->Trip_meter_A, 4);//trip time
              //GEM_Tx_Databuf[1] = Cluster_Data-> ; //maximum speed
               //    memcpy(&GEM_Tx_Databuf[1],&Cluster_Data->Trip_meter_A, 2);//avg speed
              //GEM_Tx_Databuf[1] = Cluster_Data-> ; //maximum speed   //reserved
               // memcpy(&GEM_Tx_Databuf[1],&Cluster_Data->Trip_meter_A, 4);//trip energy
                



        default:
            break;
    }
}