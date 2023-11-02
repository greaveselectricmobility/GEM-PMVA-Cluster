#include "GEM_common_header.h"
#include "Analog_Voltage.h"
#include "r_cg_adc.h"
#include "r_cg_userdefine.h"

void GEM_Analog(void)
{
    uint16_t adc_value=0;
    uint16_t temp=0;
    R_ADC_Set_OperationOn();
    R_ADC_Start();
    while(get_GEM_ADC_read_complete() != 1);
    R_ADC_Get_Result(&adc_value);
    temp = adc_value;
}