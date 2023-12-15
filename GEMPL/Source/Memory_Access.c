/***********************************************************************************************************************
* File Name    : Memory_Access.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the memory access functions.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
*****************************e <string******************************************************************************************/

#include "r_cg_macrodriver.h"
#include "Calculations.h"
#include <string.h>

extern void eel_fdl_open(void);
extern void eel_fdl_format(void);
extern void eel_fdl_write(uint8_t id);
extern void eel_fdl_read(uint8_t id);
extern void eel_fdl_close(void);
uint8_t TX_buf[5],RX_buf[5];

/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void gem_odo_update(uint32_t nvm_odo)
{
    memcpy(&TX_buf[0],&nvm_odo,sizeof(nvm_odo));	
    eel_fdl_open();
    eel_fdl_format(); 
    eel_fdl_write(3);
    eel_fdl_close();
}

/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Mem_Init(void)
{
    eel_fdl_open();
	eel_fdl_format();       
	eel_fdl_read(3);	
	eel_fdl_close();
}


void GEM_ODO_write_Check(uint32_t odo_disp,uint32_t nvm_odo)
{
    static uint32_t GEM_Prev_Odo = 0;
    if(GEM_Prev_Odo != odo_disp)
    {
        gem_odo_update(nvm_odo);
        GEM_Prev_Odo = odo_disp;
    }
    
}