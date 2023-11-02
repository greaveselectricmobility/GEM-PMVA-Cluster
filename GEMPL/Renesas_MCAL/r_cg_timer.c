/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012, 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_timer.c
* Version      : Applilet3 for RL78/D1A V2.04.05.02 [08 Nov 2021]
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements device driver for TAU module.
* Creation Date: 30-08-2023
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"
#include "Timer.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_TAU0_Create
* Description  : This function initializes the TAU0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Create(void)
{
    TAU0EN = 1U;        /* supply input clock */
    TPS0 = _0000_TAU_CKM0_FCLK_0 | _0060_TAU_CKM1_FCLK_6 | _0000_TAU_CKM2_FCLK_0 | _0000_TAU_CKM3_FCLK_0;
    /* Stop all channels */
    TT0 = _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON |
          _0008_TAU_CH3_STOP_TRG_ON | _0010_TAU_CH4_STOP_TRG_ON | _0020_TAU_CH5_STOP_TRG_ON |
          _0040_TAU_CH6_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;        /* disable INTTM00 interrupt */
    TMIF00 = 0U;        /* clear INTTM00 interrupt flag */
    /* Set INTTM00 low priority */
    TMPR100 = 1U;
    TMPR000 = 1U;
    /* Channel 0 used as interval timer */
    TMR00 = _4000_TAU_CLOCK_SELECT_CKM1 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_MODE_INTERVAL_TIMER |
            _0001_TAU_START_INT_USED;
    TDR00 = _C34F_TAU_TDR00_VALUE;
    TOM0 &= ~_0001_TAU_CH0_OUTPUT_COMBIN;
    TOL0 &= ~_0001_TAU_CH0_OUTPUT_LEVEL_L;
    TOE0 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;
    /* Set noise filter sampling clock divisor and channels selected*/
    TNFSMP0 = _00_TAU0_NOISE_DIVISOR;
    TNFCS0 = _00_TAU0_NOISE_CHANNEL_SELECT;
}

/***********************************************************************************************************************
* Function Name: R_TAU0_Channel0_Start
* Description  : This function starts TAU0 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel0_Start(void)
{
    TMIF00 = 0U;        /* clear INTTM00 interrupt flag */
    TMMK00 = 0U;        /* enable INTTM00 interrupt */
    TS0 |= _0001_TAU_CH0_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_TAU0_Channel0_Stop
* Description  : This function stops TAU0 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU0_Channel0_Stop(void)
{
    TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
    TMMK00 = 1U;        /* disable INTTM00 interrupt */
    TMIF00 = 0U;        /* clear INTTM00 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_TAU2_Create
* Description  : This function initializes the TAU2 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU2_Create_50DC(void)
{
    TAU2EN = 1U;        /* supply input clock */
    TPS2 = _0000_TAU_CKM0_FCLK_0 | _0000_TAU_CKM1_FCLK_0 | _0000_TAU_CKM2_FCLK_0 | _0000_TAU_CKM3_FCLK_0;
    /* Stop all channels */
    TT2 = _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON |
          _0008_TAU_CH3_STOP_TRG_ON | _0010_TAU_CH4_STOP_TRG_ON | _0020_TAU_CH5_STOP_TRG_ON |
          _0040_TAU_CH6_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK20 = 1U;        /* disable INTTM20 interrupt */
    TMIF20 = 0U;        /* clear INTTM20 interrupt flag */
    /* Channel 0 is used as master channel for PWM output function */
    TMR20 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0800_TAU_COMBINATION_MASTER |
            _0000_TAU_TRIGGER_SOFTWARE | _0001_TAU_MODE_PWM_MASTER;
    TDR20 = _3E7F_TAU_TDR20_VALUE;
    TOM2 &= ~_0001_TAU_CH0_OUTPUT_COMBIN;
    TOL2 &= ~_0001_TAU_CH0_OUTPUT_LEVEL_L;
    TOE2 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;
    /* Channel 7 is used as slave channel for PWM output function */
    TMR27 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE |
            _0400_TAU_TRIGGER_MASTER_INT | _0009_TAU_MODE_PWM_SLAVE;
    TDR27 = _1F40_TAU_TDR27_VALUE;
    TOM2 |= _0080_TAU_CH7_OUTPUT_COMBIN;
    TOL2 &= ~_0080_TAU_CH7_OUTPUT_LEVEL_L;
    TO2 &= ~_0080_TAU_CH7_OUTPUT_VALUE_1;
    TOE2 |= _0080_TAU_CH7_OUTPUT_ENABLE;
    /* Set noise filter sampling clock divisor and channels selected*/
    TNFSMP2 = _00_TAU2_NOISE_DIVISOR;
    TNFCS2 = _00_TAU2_NOISE_CHANNEL_SELECT;
    /* Set TO27 pin */
    TOS21 &= 0x3FU;  
    P9 &= 0xF7U;
    PM9 &= 0xF7U;
}

void R_TAU2_Create_25DC(void)
{
    TAU2EN = 1U;        /* supply input clock */
    TPS2 = _0000_TAU_CKM0_FCLK_0 | _0000_TAU_CKM1_FCLK_0 | _0000_TAU_CKM2_FCLK_0 | _0000_TAU_CKM3_FCLK_0;
    /* Stop all channels */
    TT2 = _0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON |
          _0008_TAU_CH3_STOP_TRG_ON | _0010_TAU_CH4_STOP_TRG_ON | _0020_TAU_CH5_STOP_TRG_ON |
          _0040_TAU_CH6_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK20 = 1U;        /* disable INTTM20 interrupt */
    TMIF20 = 0U;        /* clear INTTM20 interrupt flag */
    /* Channel 0 is used as master channel for PWM output function */
    TMR20 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0800_TAU_COMBINATION_MASTER |
            _0000_TAU_TRIGGER_SOFTWARE | _0001_TAU_MODE_PWM_MASTER;
    TDR20 = _3E7F_TAU_TDR20_VALUE;
    TOM2 &= ~_0001_TAU_CH0_OUTPUT_COMBIN;
    TOL2 &= ~_0001_TAU_CH0_OUTPUT_LEVEL_L;
    TOE2 &= ~_0001_TAU_CH0_OUTPUT_ENABLE;
    /* Channel 7 is used as slave channel for PWM output function */
    TMR27 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE |
            _0400_TAU_TRIGGER_MASTER_INT | _0009_TAU_MODE_PWM_SLAVE;
    TDR27 = _1F40_TAU_TDR27_VALUE;
    TOM2 |= _0080_TAU_CH7_OUTPUT_COMBIN;
    TOL2 &= ~_0080_TAU_CH7_OUTPUT_LEVEL_L;
    TO2 &= ~_0080_TAU_CH7_OUTPUT_VALUE_1;
    TOE2 |= _0080_TAU_CH7_OUTPUT_ENABLE;
    /* Set noise filter sampling clock divisor and channels selected*/
    TNFSMP2 = _00_TAU2_NOISE_DIVISOR;
    TNFCS2 = _00_TAU2_NOISE_CHANNEL_SELECT;
    /* Set TO27 pin */
    TOS21 &= 0x3FU;  
    P9 &= 0xF7U;
    PM9 &= 0xF7U;
}

/***********************************************************************************************************************
* Function Name: R_TAU2_Channel0_Start
* Description  : This function starts TAU2 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU2_Channel0_Start(void)
{
    TOE2 |= _0080_TAU_CH7_OUTPUT_ENABLE;
    TS2 |= _0001_TAU_CH0_START_TRG_ON | _0080_TAU_CH7_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_TAU2_Channel0_Stop
* Description  : This function stops TAU2 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_TAU2_Channel0_Stop(void)
{
    TT2 |= _0001_TAU_CH0_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON;
    TOE2 &= ~_0080_TAU_CH7_OUTPUT_ENABLE;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
