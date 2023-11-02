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
* File Name    : r_cg_serial_user.c
* Version      : Applilet3 for RL78/D1A V2.04.05.02 [08 Nov 2021]
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements device driver for Serial module.
* Creation Date: 07-10-2023
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt r_csi00_interrupt(vect=INTCSI00)
#pragma interrupt r_iic11_interrupt(vect=INTIIC11)
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t  * gp_csi00_rx_address;        /* csi00 receive buffer address */
extern volatile uint16_t   g_csi00_rx_length;          /* csi00 receive data length */
extern volatile uint16_t   g_csi00_rx_count;           /* csi00 receive data count */
extern volatile uint8_t  * gp_csi00_tx_address;        /* csi00 send buffer address */
extern volatile uint16_t   g_csi00_tx_length;          /* csi00 send data length */
extern volatile uint16_t   g_csi00_tx_count;           /* csi00 send data count */
extern volatile uint8_t    g_iic11_master_status_flag; /* iic11 start flag for send address check by master mode */
extern volatile uint8_t  * gp_iic11_tx_address;        /* iic11 send data pointer by master mode */
extern volatile uint16_t   g_iic11_tx_count;           /* iic11 send data size by master mode */
extern volatile uint8_t  * gp_iic11_rx_address;        /* iic11 receive data pointer by master mode */
extern volatile uint16_t   g_iic11_rx_count;           /* iic11 receive data size by master mode */
extern volatile uint16_t   g_iic11_rx_length;          /* iic11 receive data length by master mode */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_csi00_interrupt
* Description  : This function is INTCSI00 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_csi00_interrupt(void)
{
    if (g_csi00_tx_count > 0U) 
    {
        SDR00L = *gp_csi00_tx_address;
        gp_csi00_tx_address++;
        g_csi00_tx_count--;
    }
    else 
    {
        SMR00 &= ~_0001_SAU_BUFFER_EMPTY;

        if ((SSR00 & _0040_SAU_UNDER_EXECUTE) == 0U)
        {
            r_csi00_callback_sendend();    /* complete send */
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_csi00_callback_sendend
* Description  : This function is a callback function of CSI00.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_csi00_callback_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_iic11_interrupt
* Description  : This function is INTIIC11 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void __near r_iic11_interrupt(void)
{
    volatile uint16_t w_count;

    /* Set delay to start next transmission. The delay time depend on slave device.
       Here set 20us as default base on current clock */
    for (w_count = 0U; w_count <= IIC11_WAITTIME_2; w_count++)
    {
        NOP();
    }

    if (((SSR11 & _0002_SAU_PARITY_ERROR) == 0x0002U) && (g_iic11_tx_count != 0U))
    {
        SIR11 |= _0002_SAU_SIRMN_PECTMN; //clear ACK error detection flag
        R_IIC11_StopCondition();
        r_iic11_callback_master_error(MD_NACK);
    }
    else if(((SSR11 & _0001_SAU_OVERRUN_ERROR) == 0x0001U) && (g_iic11_tx_count != 0U))
    {
        SIR11 |= _0001_SAU_SIRMN_OVCTMN; //clear overrun error detection flag
        R_IIC11_StopCondition();
        r_iic11_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic11_master_status_flag & _01_SAU_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic11_tx_count > 0U)
            {
                SDR11L = *gp_iic11_tx_address;
                gp_iic11_tx_address++;
                g_iic11_tx_count--;
            }
            else
            {
                /* IIC master transmission finishes and a callback function can be called here. */
                r_iic11_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic11_master_status_flag & _04_SAU_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                ST1 |= _0002_SAU_CH1_STOP_TRG_ON;
                SCR11 &= ~_C000_SAU_RECEPTION_TRANSMISSION;
                SCR11 |= _4000_SAU_RECEPTION;                
                SS1 |= _0002_SAU_CH1_START_TRG_ON;
                g_iic11_master_status_flag |= _04_SAU_IIC_SENDED_ADDRESS_FLAG;
                
                if(g_iic11_rx_length == 1U)
                {
                    SOE1 &= ~_0002_SAU_CH1_OUTPUT_ENABLE;    /* disable IIC11 out */
                }
                
                SDR11L = 0xFFU;
            }
            else
            {
                if (g_iic11_rx_count < g_iic11_rx_length)
                {
                    *gp_iic11_rx_address = SDR11L;
                    gp_iic11_rx_address++;
                    g_iic11_rx_count++;
                    
                    if (g_iic11_rx_count == (g_iic11_rx_length - 1U))
                    {
                        SOE1 &= ~_0002_SAU_CH1_OUTPUT_ENABLE;    /* disable IIC11 out */
                        SDR11L = 0xFFU;
                    }
                    
                    if (g_iic11_rx_count == g_iic11_rx_length)
                    {
                        /* IIC master reception finishes and a callback function can be called here. */
                        r_iic11_callback_master_receiveend();
                    }
                    else
                    {
                        SDR11L = 0xFFU;
                    }
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_iic11_callback_master_error
* Description  : This function callback function open for users operation when IIC11 master error.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_iic11_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_iic11_callback_master_receiveend
* Description  : This function callback function open for users operation when IIC11 master receive finish.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_iic11_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_iic11_callback_master_sendend
* Description  : This function callback function open for users operation when IIC11 master transmit finish.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_iic11_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
