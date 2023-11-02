#include "GEM_common_header.h"
#include "GEM_can.h"





void CAN_Tx_signal(Cluster_Data_t *Cluster_Data, CAN_TX_Message_t *CAN_TX_Message)
{
	uint8_t a;
    switch (CAN_TX_Message->CAN_Msg_ID)
    {
        case (0x300):
				memcpy(&CAN_TX_Message->m_nData[0],&Cluster_Data->Trip_meter_B, 2); // trip distance
				memcpy(&CAN_TX_Message->m_nData[4],&Cluster_Data->Odometer_Display, 4); // odo value
                break;
        case (0x301):
                CAN_TX_Message->m_nData[0] = Cluster_Data->Vehicle_Speed;
                CAN_TX_Message->m_nData[1] = 00;
                CAN_TX_Message->m_nData[6] = ((CAN_TX_Message->m_nData[6] & 0x0F) | (Cluster_Data->SOC_Bar << 4)); 
                break;
		a=1;
        case (0x304):
                //CAN_TX_Message->m_nData[1] = Cluster_Data->   //RTC value
                break;

        case (0x305):
                //cluster_fault
                CAN_TX_Message->m_nData[0] = ((CAN_TX_Message->m_nData[0] & 0xFC) | (Cluster_Data->cluster_fault & 0x02));
                CAN_TX_Message->m_nData[0] = ((CAN_TX_Message->m_nData[0] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Side_Stand_TT  << 2));
                CAN_TX_Message->m_nData[0] = ((CAN_TX_Message->m_nData[0] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 4));  //Motor temp high
                CAN_TX_Message->m_nData[0] = ((CAN_TX_Message->m_nData[0] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 6));  //MCU Temp high
                CAN_TX_Message->m_nData[1] = ((CAN_TX_Message->m_nData[1] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT ));         //BMS High Temp
                CAN_TX_Message->m_nData[1] = ((CAN_TX_Message->m_nData[1] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Thermal_Runaway_TT << 2 )); //Thermal runaway 
                CAN_TX_Message->m_nData[1] = ((CAN_TX_Message->m_nData[1] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT  << 4 )); //BMS Failure
                CAN_TX_Message->m_nData[1] = ((CAN_TX_Message->m_nData[1] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 6 )); //Battery failure
                CAN_TX_Message->m_nData[2] = ((CAN_TX_Message->m_nData[2] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT )); //MCU failure
                CAN_TX_Message->m_nData[2] = ((CAN_TX_Message->m_nData[2] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 2 )); //Motor failure
                CAN_TX_Message->m_nData[2] = ((CAN_TX_Message->m_nData[2] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 4 )); //VCU failure *
                //CAN_TX_Message->m_nData[2] = ((CAN_TX_Message->m_nData[2] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 2 )); //Telematics failure
                //CAN_TX_Message->m_nData[3] = ((CAN_TX_Message->m_nData[3] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT )); //Limp Home Mode
                CAN_TX_Message->m_nData[3] = ((CAN_TX_Message->m_nData[3] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Service_Alert_TT << 2 )); //Service alert
                CAN_TX_Message->m_nData[3] = ((CAN_TX_Message->m_nData[3] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Service_Alert_TT  << 4 )); //Service alert due to fault
                //CAN_TX_Message->m_nData[3] = ((CAN_TX_Message->m_nData[3] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 6 )); //Speed mode
                CAN_TX_Message->m_nData[4] = ((CAN_TX_Message->m_nData[4] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Battery_Charging_TT ));    //Battery charging status
                //CAN_TX_Message->m_nData[4] = ((CAN_TX_Message->m_nData[4] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Battery_Charging_TT << 2 )); //Aux Battery Charging
                CAN_TX_Message->m_nData[4] = ((CAN_TX_Message->m_nData[4] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Hazard_TT  << 4 )); //Hazard
                CAN_TX_Message->m_nData[4] = ((CAN_TX_Message->m_nData[4] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Headlamp_HighBeam_TT << 6 )); //High Beam
                CAN_TX_Message->m_nData[5] = ((CAN_TX_Message->m_nData[5] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Left_Turn_Indicator_TT ));  //Left turn indicator
                CAN_TX_Message->m_nData[5] = ((CAN_TX_Message->m_nData[5] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Rightt_Turn_Indicator_TT << 2 )); //right turn indicator 
                CAN_TX_Message->m_nData[5] = ((CAN_TX_Message->m_nData[5] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Ready_TT  << 4 )); //ready status
                CAN_TX_Message->m_nData[5] = ((CAN_TX_Message->m_nData[5] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Reverse_TT << 6 )); //reverse status
                CAN_TX_Message->m_nData[6] = ((CAN_TX_Message->m_nData[6] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Throttle_Failure_TT ));         //throttle failure
                CAN_TX_Message->m_nData[6] = ((CAN_TX_Message->m_nData[6] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Battery_TT << 2 )); //battery low
              //CAN_TX_Message->m_nData[6] = ((CAN_TX_Message->m_nData[6] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT  << 4 )); //key fob not near vehicle
              //CAN_TX_Message->m_nData[6] = ((CAN_TX_Message->m_nData[6] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 6 )); //luggage box lamp
                CAN_TX_Message->m_nData[7] = ((CAN_TX_Message->m_nData[7] & 0xFC) | (Cluster_Data->LCD_TellTale_Symbol.bit.Brake_Fail_TT ));         //Brake failure
              //CAN_TX_Message->m_nData[7] = ((CAN_TX_Message->m_nData[7] & 0xF3) | (Cluster_Data->LCD_TellTale_Symbol.bit.Thermal_Runaway_TT << 2 )); //DC-DC convert failure
              //CAN_TX_Message->m_nData[7] = ((CAN_TX_Message->m_nData[7] & 0xCF) | (Cluster_Data->LCD_TellTale_Symbol.bit.buzzer  << 4 )); //Buzzer
              //CAN_TX_Message->m_nData[7] = ((CAN_TX_Message->m_nData[7] & 0x3F) | (Cluster_Data->LCD_TellTale_Symbol.bit.Temperature_TT << 6 )); //reserved
            break;
        case (0x306):        
                // yet to implement related to bluetooth
                break;
                
        case (0x307): 
                // yet to implement related to bluetooth
                break;
        
        case (0x308):
                // yet to implement related to bluetooth
                break;
        case (0x309):
                //memcpy(&CAN_TX_Message->m_nData[0],&Cluster_Data->Trip_meter_A, 4);//trip distance
              //memcpy(&CAN_TX_Message->m_nData[4],&Cluster_Data->Trip_meter_A, 4);//trip time
              //CAN_TX_Message->m_nData[1] = Cluster_Data-> ; //maximum speed
               //    memcpy(&CAN_TX_Message->m_nData[1],&Cluster_Data->Trip_meter_A, 2);//avg speed
              //CAN_TX_Message->m_nData[1] = Cluster_Data-> ; //maximum speed   //reserved
               // memcpy(&CAN_TX_Message->m_nData[1],&Cluster_Data->Trip_meter_A, 4);//trip energy
                break;
        default:
            break;
    }
}


void GEM_CAN_TX(Cluster_Data_t *Cluster_Data)
{
    CAN_TX_Message_t CAN_TX_Message={0};
    uint16_t CAN_IDs_arr[] = {0x300, 0x301, 0x305};
    uint8_t no_of_tx_msg = ((sizeof(CAN_IDs_arr)) / (sizeof(CAN_IDs_arr[0])));
    for(int i=0; i<no_of_tx_msg;i++)
    {
        memset(&CAN_TX_Message,0,sizeof(CAN_TX_Message_t));
        CAN_TX_Message.CAN_Msg_ID = CAN_IDs_arr[i];
        CAN_TX_Message.m_nDlc = 8;
        CAN_TX_Message.m_nExtFlg = 0;
        CAN_TX_Message.m_nRtr = 0;
        CAN_Tx_signal(Cluster_Data,&CAN_TX_Message);

        //GEM_Tx_MsgBuf_Processing_new(0, &CAN_TX_Message);
        GGEM_Tx_MsgBuf_Processing_new(0, &CAN_TX_Message);
    }
    
    

    

}