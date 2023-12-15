#include <stdio.h>
#include <stdint.h>


#include "Read_Parameters.h"



void read_parameter_ID(uint8_t ID)
{

  switch (ID)
  {
    case DEVICE_NAME    :
                                
                                break;
    
    case DEVICE_VARIANT :
                                
                                break;
    
    case DEVICE_PLANT_NAME  :
                                
                                break;
    
    case DEVICE_MANUFACTURING_DATE  :
                                
                                break;
    
    case DEVICE_EOL_FLAG    :
                                
                                break;
    
    case BOOT_SOFTWARE_VERSION  :
                                
                                break;
    
    case APPLICATION_SOFTWARE_VERSION   :
                                
                                break;
    
    case CONFIGURATION_VERSION  :
                                
                                break;
    
    case HARDWARE_VERSION   :
                                
                                break;
    
    case BOOT_SOFTWARE_FLASH_DATE   :
                                
                                break;
    
    case SOFTWARE_FLASHING_DATE :
                                
                                break;
    
    case CONFIGURATION_FLASHING_DATE    :
                                
                                break;
    
    case VEHICLE_NAME   :
                                
                                break;
    
    case VEHICLE_VARIANT    :
                                
                                break;
    
    case VEHICLE_PLANT_NAME :
                                
                                break;
    
    case VEHICLE_MANUFACTURING_DATE :
                                
                                break;
    
    case VIN_NUMBER :
                                
                                break;
    
    case VEHICLE_REGISTRATION_NUMBER    :
                                
                                break;
    
    case VEHICLE_EOL_FLAG   :
                                
                                break;
    
    case VEHICLE_MAIN_BATTERY_VOLTAGE   :
                                
                                break;
    
    case INSTRUMENT_CLUSTER_INPUT_VOLTAGE   :
                                
                                break;
    
    case IGNITION_STATUS    :
                                
                                break;
    
    case IGNITION_ON_TIME_BEFORE_SENDING_READDTC    :
                                
                                break;
    
    case BLUETOOTH_MAC_ID   :
                                
                                break;
    
    case RTC_TIME   :
                                
                                break;
    
    case WHEEL_RADIUS   :
                                
                                break;
    
    case GEAR_RATIO :
                                
                                break;
    
    case VEHICLE_SPEED_TOLERANCE_PERCENTAGE :
                                
                                break;
    
    case VEHICLE_SPEED  :
                                
                                break;
    
    case ODOMETER_VALUE :
                                
                                break;
    
    case TRIP_DISTANCE_A    :
                                
                                break;
    
    case TRIP_TIME_A    :
                                
                                break;
    
    case MAX_SPEED_A    :
                                
                                break;
    
    case AVG_SPEED_A    :
                                
                                break;
    
    case TRIP_ENERGY_A  :
                                
                                break;
    
    case TRIP_DISTANCE_B    :
                                
                                break;
    
    case TRIP_TIME_B    :
                                
                                break;
    
    case MAX_SPEED_B    :
                                
                                break;
    
    case AVG_SPEED_B    :
                                
                                break;
    
    case TRIP_ENERGY_B  :
                                
                                break;
    
    case TOTAL_VEHICLE_HOURS    :
                                
                                break;
    
    case MOTOR_SPEED_GAUGE_BAR_DIAL :
                                
                                break;
    
    case STATE_OF_CHARGE_PERCENTAGE :
                                
                                break;
    
    case STATE_OF_CHARGE_GAUGE_BAR_DIAL :
                                
                                break;
    
    case DISTANCE_TO_EMPTY_KM   :
                                
                                break;
    
    case DISTANCE_TO_EMPTY_BAR_GAUGE_DIAL   :
                                
                                break;
    
    case TIME_TO_FULL_CHARGE    :
                                
                                break;
    
    case CHARGING_PERCENTAGE    :
                                
                                break;
    
    case CHARGING_PERCENTAGE_GAUGE_BAR_DIAL :
                                
                                break;
    
    case LAST_CHARGING_TIME :
                                
                                break;
    
    case EFFICIENCY_PERCENTAGE  :
                                
                                break;
    
    case EFFICIENCY_GAUGE_BAR_DIAL  :
                                
                                break;
    
    case BATTERY_TEMPERATURE    :
                                
                                break;
    
    case MCU_TEMPERATURE    :
                                
                                break;
    
    case MOTOR_TEMPERATURE  :
                                
                                break;
    
    case NAVIGATION_DESTINATION_DISTANCE    :
                                
                                break;
    
    case TURN_DISTANCE  :
                                
                                break;
    
    case HIGH_BEAM_INDICATION   :
                                
                                break;
    
    case LEFT_TURN_INDICATION   :
                                
                                break;
    
    case RIGHT_TURN_INDICATION  :
                                
                                break;
    
    case HAZARD_INDICATION_HAZARD_SYMBOL    :
                                
                                break;
    
    case MAIN_BATTERY_CHARGING  :
                                
                                break;
    
    case SIDE_STAND_INDICATION  :
                                
                                break;
    
    case HIGH_TEMPERATURE_INDICATION_MCU_MOTOR_CHARGER  :
                                
                                break;
    
    case THERMAL_RUN_AWAY_INDICATION    :
                                
                                break;
    
    case LIMP_HOME_MODE :
                                
                                break;
    
    case REVERSE_MODE   :
                                
                                break;
    
    case READY_INDICATION   :
                                
                                break;
    
    case SPEED_MODE_MODE_1  :
                                
                                break;
    
    case SPEED_MODE_MODE_2  :
                                
                                break;
    
    case SPEED_MODE_MODE_3  :
                                
                                break;
    
    case SPEED_MODE_MODE_4  :
                                
                                break;
    
    case SERVICE_DUE_ALERT  :
                                
                                break;
    
    case SERVICE_ALERT_DUE_TO_FAULT :
                                
                                break;
    
    case THROTTLE_FAILURE_INDICATION    :
                                
                                break;
    
    case BLUETOOTH_INDICATION   :
                                
                                break;
    
    case WI_FI_INDICATION   :
                                
                                break;
    
    case NAVIGATION_INDICATION  :
                                
                                break;
    
    case DIRECTION_INDICATION_DISPLAY   :
                                
                                break;
    
    case INTERIOR_COMPARTMENT_LAMP  :
                                
                                break;
    
    case TELEPHONE_CALL_ALERT_INDICATION    :
                                
                                break;
    
    case INBOX_MESSAGE_ALERT_INDICATION :
                                
                                break;
    
    case MOBILE_CHARGE_ALERT    :
                                
                                break;
    
    case MISSED_CALL_ALERT  :
                                
                                break;
    
    case KEYFOB_BATERY_LOW_INDICATION   :
                                
                                break;
    
    case KEY_FOB_NOT_NEAR_VEHICLE_INDICATION    :
                                
                                break;
    
    case BRAKE_FAILURE_INDICATION   :
                                
                                break;
    
    case ALPHANUMERIC_DISPLAY   :
                                
                                break;
    
    case EEPROM_SIZE_OF_FREE_MEMORY :
                                
                                break;
    
    case EEPROM_MEMORY_CHECK_CORRUPTED_NOT_CORRUPTED    :
                                
                                break;
    
    case FLASH_MEMORY_FREE_SIZE :
                                
                                break;
    
    case FLASH_MEMORY_CHECK_CORRUPTED_NOT_CORRUPTED :
                                
                                break;
    
    case DEVICE_SERIAL_NUMBER   :
                                
                                break;
    
    case BASE_FIRMWARE_VERSION_WHEN_BOOT_VERSION_IS_PART_OF_FIRMWARE_VERSION    :
                                
                                break;

    case LED_1_INDICATION : 

                                break;

    case LED_2_INDICATION : 

                                break;

    case LED_3_INDICATION : 

                                break;

    case LED_4_INDICATION : 

                                break;

    case LED_5_INDICATION : 

                                break;

    case LED_6_INDICATION : 

                                break;


    default :

                break;
}


}