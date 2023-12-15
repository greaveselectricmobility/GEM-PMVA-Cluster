#include "GEM_common_header.h"
#include "Delay.h"
#include "r_cg_userdefine.h"
#include "r_cg_it.h"

uint16_t GEM_delay_int=0;

/* End user code. Do not edit comment generated here */

void set_GEM_delay_int(void)

{

    GEM_delay_int=1;

}

uint16_t get_GEM_delay_int(void)

{

    return GEM_delay_int;

}

void Reset_GEM_delay_int(void)

{

    GEM_delay_int=0;

}

void GEM_Delay_ms(uint16_t ms)
{
	uint16_t loop_1ms;
	for (loop_1ms = 0; loop_1ms < ms; loop_1ms++)
    	{
	        Reset_GEM_delay_int();
	        R_IT_Start();
	        while(get_GEM_delay_int() !=1);
	        R_IT_Stop();
    	}
}
