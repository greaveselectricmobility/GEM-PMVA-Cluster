#ifndef READ_PARAMETERS_H
#define READ_PARAMETERS_H


#define DEVICE_NAME         0x0100
#define DEVICE_VARIANT  0x0101
#define DEVICE_PLANT_NAME   0x0102
#define DEVICE_MANUFACTURING_DATE   0x0103
#define DEVICE_EOL_FLAG     0x0104
#define BOOT_SOFTWARE_VERSION   0x0105
#define APPLICATION_SOFTWARE_VERSION    0x0106
#define CONFIGURATION_VERSION   0x0107
#define HARDWARE_VERSION    0x0108
#define BOOT_SOFTWARE_FLASH_DATE    0x0109
#define SOFTWARE_FLASHING_DATE  0x010A
#define CONFIGURATION_FLASHING_DATE     0x010B
#define VEHICLE_NAME    0x010C
#define VEHICLE_VARIANT     0x010D
#define VEHICLE_PLANT_NAME  0x010E
#define VEHICLE_MANUFACTURING_DATE  0x010F
#define VIN_NUMBER  0x0110
#define VEHICLE_REGISTRATION_NUMBER     0x0111
#define VEHICLE_EOL_FLAG    0x0112
#define VEHICLE_MAIN_BATTERY_VOLTAGE    0x0113
#define INSTRUMENT_CLUSTER_INPUT_VOLTAGE    0x0114
#define IGNITION_STATUS     0x0115
#define IGNITION_ON_TIME_BEFORE_SENDING_READDTC     0x0116
#define BLUETOOTH_MAC_ID    0x0117
#define RTC_TIME    0x0118
#define WHEEL_RADIUS    0x0119
#define GEAR_RATIO  0x011A
#define VEHICLE_SPEED_TOLERANCE_PERCENTAGE  0x011B
#define VEHICLE_SPEED   0x011C
#define ODOMETER_VALUE  0x011D
#define TRIP_DISTANCE_A     0x011E
#define TRIP_TIME_A     0x011F
#define MAX_SPEED_A     0x0120
#define AVG_SPEED_A     0x0121
#define TRIP_ENERGY_A   0x0122
#define TRIP_DISTANCE_B     0x0123
#define TRIP_TIME_B     0x0124
#define MAX_SPEED_B     0x0125
#define AVG_SPEED_B     0x0126
#define TRIP_ENERGY_B   0x0127
#define TOTAL_VEHICLE_HOURS     0x0128
#define MOTOR_SPEED_GAUGE_BAR_DIAL  0x0129
#define STATE_OF_CHARGE_PERCENTAGE  0x012A
#define STATE_OF_CHARGE_GAUGE_BAR_DIAL  0x012B
#define DISTANCE_TO_EMPTY_KM    0x012C
#define DISTANCE_TO_EMPTY_BAR_GAUGE_DIAL    0x012D
#define TIME_TO_FULL_CHARGE     0x012E
#define CHARGING_PERCENTAGE     0x012F
#define CHARGING_PERCENTAGE_GAUGE_BAR_DIAL  0x0130
#define LAST_CHARGING_TIME  0x0131
#define EFFICIENCY_PERCENTAGE   0x0132
#define EFFICIENCY_GAUGE_BAR_DIAL   0x0133
#define BATTERY_TEMPERATURE     0x0134
#define MCU_TEMPERATURE     0x0135
#define MOTOR_TEMPERATURE   0x0136
#define NAVIGATION_DESTINATION_DISTANCE     0x0137
#define TURN_DISTANCE   0x0138
#define HIGH_BEAM_INDICATION    0x0139
#define LEFT_TURN_INDICATION    0x013A
#define RIGHT_TURN_INDICATION   0x013B
#define HAZARD_INDICATION_HAZARD_SYMBOL     0x013C
#define MAIN_BATTERY_CHARGING   0x013D
#define SIDE_STAND_INDICATION   0x013E
#define HIGH_TEMPERATURE_INDICATION_MCU_MOTOR_CHARGER   0x013F
#define THERMAL_RUN_AWAY_INDICATION     0x0140
#define LIMP_HOME_MODE  0x0141
#define REVERSE_MODE    0x0142
#define READY_INDICATION    0x0143
#define SPEED_MODE_MODE_1   0x0144
#define SPEED_MODE_MODE_2   0x0145
#define SPEED_MODE_MODE_3   0x0146
#define SPEED_MODE_MODE_4   0x0147
#define SERVICE_DUE_ALERT   0x0148
#define SERVICE_ALERT_DUE_TO_FAULT  0x0149
#define THROTTLE_FAILURE_INDICATION     0x014A
#define BLUETOOTH_INDICATION    0x014B
#define WI_FI_INDICATION    0x014C
#define NAVIGATION_INDICATION   0x014D
#define DIRECTION_INDICATION_DISPLAY    0x014E
#define INTERIOR_COMPARTMENT_LAMP   0x014F
#define TELEPHONE_CALL_ALERT_INDICATION     0x0150
#define INBOX_MESSAGE_ALERT_INDICATION  0x0151
#define MOBILE_CHARGE_ALERT     0x0152
#define MISSED_CALL_ALERT   0x0153
#define KEYFOB_BATERY_LOW_INDICATION    0x0154
#define KEY_FOB_NOT_NEAR_VEHICLE_INDICATION     0x0155
#define BRAKE_FAILURE_INDICATION    0x0156
#define ALPHANUMERIC_DISPLAY    0x0157
#define EEPROM_SIZE_OF_FREE_MEMORY  0x0158
#define EEPROM_MEMORY_CHECK_CORRUPTED_NOT_CORRUPTED    0x0159
#define FLASH_MEMORY_FREE_SIZE  0x015A
#define FLASH_MEMORY_CHECK_CORRUPTED_NOT_CORRUPTED     0x015B
#define DEVICE_SERIAL_NUMBER    0x015C
#define BASE_FIRMWARE_VERSION_WHEN_BOOT_VERSION_IS_PART_OF_FIRMWARE_VERSION     0x015D
#define LED_1_INDICATION 0x015E
#define LED_2_INDICATION 0x015F
#define LED_3_INDICATION 0x0160
#define LED_4_INDICATION 0x0161
#define LED_5_INDICATION 0x0162
#define LED_6_INDICATION 0x0163


void read_parameter_ID(uint8_t ID);

#endif
