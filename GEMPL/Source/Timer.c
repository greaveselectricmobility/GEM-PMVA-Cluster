#include "GEM_common_header.h"
#include "Timer.h"
#include "Calculations.h"

uint32_t GEM_Timer_Value=0;



uint32_t get_GEM_Timer_Value(void)
{
	return GEM_Timer_Value;
}

void GEM_Timer_Value_Increment(void)
{
    GEM_Timer_Value = GEM_Timer_Value+1;
	Vehicle_Speed_Calculations();
}