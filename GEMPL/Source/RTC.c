#include <stdio.h>
//#include <time.h>
//#include <stdint.h>

#include "lcd.h"
#include "GEM_common_header.h"


void GEM_RTC(void)
{
    uint32_t rawtime = 1262318978;
    
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

