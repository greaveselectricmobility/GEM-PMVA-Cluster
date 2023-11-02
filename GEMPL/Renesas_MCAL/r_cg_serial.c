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
* File Name    : r_cg_serial.c
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
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t  * gp_csi00_rx_address;        /* csi00 receive buffer address */
volatile uint16_t   g_csi00_rx_length;          /* csi00 receive data length */
volatile uint16_t   g_csi00_rx_count;           /* csi00 receive data count */
volatile uint8_t  * gp_csi00_tx_address;        /* csi00 send buffer address */
volatile uint16_t   g_csi00_tx_length;          /* csi00 send data length */
volatile uint16_t   g_csi00_tx_count;           /* csi00 send data count */
volatile uint8_t    g_iic11_master_status_flag; /* iic11 start flag for send address check by master mode */
volatile uint8_t  * gp_iic11_tx_address;        /* iic11 send data pointer by master mode */
volatile uint16_t   g_iic11_tx_count;           /* iic11 send data size by master mode */
volatile uint8_t  * gp_iic11_rx_address;        /* iic11 receive data pointer by master mode */
volatile uint16_t   g_iic11_rx_count;           /* iic11 receive data size by master mode */
volatile uint16_t   g_iic11_rx_length;          /* iic11 receive data length by master mode */


volatile uint8_t  * gp_uartf0_tx_address;       /* uartf0 transmit data address */
volatile uint8_t  * gp_uartf0_tx_bf_address;    /* uartf0 transmit buffer address in buffer mode */
volatile uint16_t   g_uartf0_quotient;          /* uartf0 transmit buffer data count */
volatile uint16_t   g_uartf0_remainder;         /* uartf0 transmit buffer data remainer */
volatile uint16_t   g_uartf0_tx_cnt;            /* uartf0 transmit data number */
volatile uint8_t  * gp_uartf0_rx_address;       /* uartf0 receive data address */
volatile uint16_t   g_uartf0_rx_cnt;            /* uartf0 receive data number */
volatile uint16_t   g_uartf0_rx_len;            /* uartf0 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_SAU0_Create
* Description  : This function initializes SAU0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Create(void)
{
    SAU0EN = 1U;    /* supply SAU0 clock */
    NOP();
    NOP();
    NOP();
    NOP();
    SPS0 = _0000_SAU_CK00_FCLK_0 | _0000_SAU_CK01_FCLK_0;
    
    R_CSI00_Create();
}

/***********************************************************************************************************************
* Function Name: R_CSI00_Create
* Description  : This function initializes CSI00.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSI00_Create(void)
{
    ST0 |= _0001_SAU_CH0_STOP_TRG_ON;     /* disable CSI00 */
    CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
    /* Set INTCSI00 low priority */
    CSIPR100 = 1U;
    CSIPR000 = 1U;
    SIR00 = _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR00 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS |
            _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_CSI | _0001_SAU_BUFFER_EMPTY;
    SCR00 = _8000_SAU_TRANSMISSION | _3000_SAU_TIMING_4 | _0000_SAU_MSB | _0007_SAU_LENGTH_8;
    SDR00 = _0400_CSI00_DIVISOR;
    SO0 &= ~_0100_SAU_CH0_CLOCK_OUTPUT_1; /* output CSI00 clock value 0 */
    SO0 &= ~_0001_SAU_CH0_DATA_OUTPUT_1;  /* output CSI00 data value 0 */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;  /* enable CSI00 output */
    /* use P04, P03, P02 as SCK00, SI00, SO00 */
    STSEL0 |= _04_CSI00_PIN_SELECTION_2;
    /* Set SO00 pin */
    P0 |= 0x04U;
    PM0 &= 0xFBU;
    /* Set SCK00 pin */
    P0 |= 0x10U;
    PM0 &= 0xEFU;
}

/***********************************************************************************************************************
* Function Name: R_CSI00_Start
* Description  : This function starts CSI00.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSI00_Start(void)
{
    SO0 &= ~_0100_SAU_CH0_CLOCK_OUTPUT_1;  /* output CSI00 clock value 0 */
    SO0 &= ~_0001_SAU_CH0_DATA_OUTPUT_1;   /* output CSI00 data value 0 */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;   /* enable CSI00 output */
    SS0 |= _0001_SAU_CH0_START_TRG_ON;     /* enable CSI00 */
    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
    CSIMK00 = 0U;    /* enable INTCSI00 */
}

/***********************************************************************************************************************
* Function Name: R_CSI00_Stop
* Description  : This function stops CSI00.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_CSI00_Stop(void)
{
    CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
    ST0 |= _0001_SAU_CH0_STOP_TRG_ON;        /* disable CSI00 */
    SOE0 &= ~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable CSI00 output */
    CSIIF00 = 0U;    /* clear INTCSI00 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_CSI00_Send
* Description  : This function sends CSI00 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_CSI00_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_csi00_tx_count = tx_num;       /* send data count */
        gp_csi00_tx_address = tx_buf;    /* send buffer pointer */
        SMR00 |= _0001_SAU_BUFFER_EMPTY;
        CSIMK00 = 1U;    /* disable INTCSI00 interrupt */
        SDR00L = *gp_csi00_tx_address;     /* started by writing data to SDR[7:0] */
        gp_csi00_tx_address++;
        g_csi00_tx_count--;
        CSIMK00 = 0U;    /* enable INTCSI00 interrupt */
    }
    
    return (status);
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Create
* Description  : This function initializes SAU1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Create(void)
{
    SAU1EN = 1U;    /* supply SAU1 clock */
    NOP();
    NOP();
    NOP();
    NOP();
    SPS1 = _0001_SAU_CK00_FCLK_1 | _0000_SAU_CK01_FCLK_0;
    
    R_IIC11_Create();
}

/***********************************************************************************************************************
* Function Name: R_IIC11_Create
* Description  : This function initializes IIC11.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IIC11_Create(void)
{
    ST1 |= _0002_SAU_CH1_STOP_TRG_ON;    /* disable IIC11 */
    IICMK11 = 1U;    /* disable INTIIC11 interrupt */
    IICIF11 = 0U;    /* clear INTIIC11 interrupt flag */
    /* Set INTIIC11 low priority */
    IICPR111 = 1U;
    IICPR011 = 1U;
    SIR11 = _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* error flag clear */
    SMR11 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS |
            _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_EDGE_FALL | _0004_SAU_IIC | _0000_SAU_TRANSFER_END;
    SCR11 = _0000_SAU_TIMING_1 | _0000_SAU_MSB | _0010_SAU_STOP_1 | _0007_SAU_LENGTH_8;
    SDR11 = _9E00_IIC11_DIVISOR;
    SO1 |= _0200_SAU_CH1_CLOCK_OUTPUT_1 | _0002_SAU_CH1_DATA_OUTPUT_1;
    /* use P30, P31 as SCL11, SDA11 */
    STSEL1 |= _40_IIC11_PIN_SELECTION_2;
    /* Set SCL11, SDA11 pin */
    P3 |= 0x03U;
    PM3 &= 0xFCU;
}

/***********************************************************************************************************************
* Function Name: R_IIC11_Master_Send
* Description  : This function starts transferring data for IIC11 in master mode.
* Arguments    : adr -
*                    set address for select slave
*                tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : None
***********************************************************************************************************************/
void R_IIC11_Master_Send(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num)
{    
    g_iic11_master_status_flag = _00_SAU_IIC_MASTER_FLAG_CLEAR;    /* clear IIC11 master status flag */
    adr &= 0xFEU;    /* send mode */
    g_iic11_master_status_flag = _01_SAU_IIC_SEND_FLAG;    /* set master status flag */
    SCR11 &= ~_C000_SAU_RECEPTION_TRANSMISSION;
    SCR11 |= _8000_SAU_TRANSMISSION;
    /* Set paramater */
    g_iic11_tx_count = tx_num;
    gp_iic11_tx_address = tx_buf; 

    /* Start condition */
    R_IIC11_StartCondition();
    IICIF11 = 0U;    /* clear INTIIC11 interrupt flag */
    IICMK11 = 0U;    /* enable INTIIC11 */
    SDR11L = adr;
}

/***********************************************************************************************************************
* Function Name: R_IIC11_Master_Receive
* Description  : This function starts receiving data for IIC11 in master mode.
* Arguments    : adr -
*                    set address for select slave
*                rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : None
***********************************************************************************************************************/
void R_IIC11_Master_Receive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num)
{
    g_iic11_master_status_flag = _00_SAU_IIC_MASTER_FLAG_CLEAR;    /* clear master status flag */
    adr |= 0x01U;    /* receive mode */
    g_iic11_master_status_flag = _02_SAU_IIC_RECEIVE_FLAG;   /* set master status flag */
    SCR11 &= ~_C000_SAU_RECEPTION_TRANSMISSION;
    SCR11 |= _8000_SAU_TRANSMISSION;
    /* Set parameter */
    g_iic11_rx_length = rx_num;
    g_iic11_rx_count = 0U;
    gp_iic11_rx_address = rx_buf;
    /* Start condition */
    R_IIC11_StartCondition();
    IICIF11 = 0U;    /* clear INTIIC11 interrupt flag */
    IICMK11 = 0U;    /* enable INTIIC11 */
    SDR11L = adr;
}

/***********************************************************************************************************************
* Function Name: R_IIC11_Stop
* Description  : This function stops the IIC11 operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IIC11_Stop(void)
{
    /* Stop transfer */
    IICMK11 = 1U;    /* disable INTIIC11 */
    ST1 |= _0002_SAU_CH1_STOP_TRG_ON;    /* disable IIC11 */
    IICIF11 = 0U;    /* clear INTIIC11 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_IIC11_StartCondition
* Description  : This function starts IIC11 condition.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IIC11_StartCondition(void)
{
    uint8_t w_count;
    SO1 &= ~_0002_SAU_CH1_DATA_OUTPUT_1;    /* clear IIC11 SDA */
    
    /* Set delay to secure a hold time after SDA output low. The delay time depend on slave device.
       Here set 5us as default base on current clock */
    for (w_count = 0U; w_count <= IIC11_WAITTIME; w_count++)
    {
        NOP();
    }
    
    SOE1 |= _0002_SAU_CH1_OUTPUT_ENABLE;    /* enable IIC11 out */
    SO1 &= ~_0200_SAU_CH1_CLOCK_OUTPUT_1;   /* clear IIC11 SCL */
    SS1 |= _0002_SAU_CH1_START_TRG_ON;      /* enable IIC11 */

    /* Set delay to secure a hold time after SCL output low. The delay time depend on slave device.
       Here set 5us as default base on current clock */
    for (w_count = 0U; w_count <= IIC11_WAITTIME; w_count++)
    {
        NOP();
    }
}

/***********************************************************************************************************************
* Function Name: R_IIC11_StopCondition
* Description  : This function stops IIC11 condition.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IIC11_StopCondition(void)
{
    uint8_t w_count;
    ST1 |= _0002_SAU_CH1_STOP_TRG_ON;       /* disable IIC11 */
    SOE1 &= ~_0002_SAU_CH1_OUTPUT_ENABLE;   /* disable IIC11 out */
    SO1 &= ~_0002_SAU_CH1_DATA_OUTPUT_1;    /* clear IIC11 SDA */

    /* Set delay to secure a hold time after SDA output low. The delay time depend on slave device.
       Here set 5us as default base on current clock */
    for (w_count = 0U; w_count <= IIC11_WAITTIME; w_count++)
    {
        NOP();
    }

    SO1 |= _0200_SAU_CH1_CLOCK_OUTPUT_1;    /* set IIC11 SCL */
    
    /* Set delay to secure a hold time after SCL output high. The delay time depend on slave device.
       Here set 5us as default base on current clock */
    for (w_count = 0U; w_count <= IIC11_WAITTIME; w_count++)
    {
        NOP();
    }
    
    SO1 |= _0002_SAU_CH1_DATA_OUTPUT_1;     /* set IIC11 SDA */

    /* Set delay to secure a hold time after SDA output high. The delay time depend on slave device.
       Here set 5us as default base on current clock */
    for (w_count = 0U; w_count <= IIC11_WAITTIME; w_count++)
    {
        NOP();
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_UARTF0_Create
* Description  : This function initializes the UARTF0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
/***********************************************************************************************************************
* Function Name: R_UARTF0_Create
* Description  : This function initializes the UARTF0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UARTF0_Create(void)
{
    LIN0EN = 1U;
    UF0CTL0 &= (uint8_t)(~_40_UARTF_TRANSMISSION_ENABLE & ~_20_UARTF_RECEPTION_ENABLE);    /* disable UARTF0 operation */
    LTMK0 = 1U;  /* disable INTLT interrupt */
    LTIF0 = 0U;  /* clear INTLT interrupt flag */
    LRMK0 = 1U;  /* disable INTLR interrupt */
    LRIF0 = 0U;  /* clear INTLR interrupt flag */
    LSMK0 = 1U;  /* disable INTLS interrupt */
    LSIF0 = 0U;  /* clear INTLS interrupt flag */
    /* Set INTLT low priority */
    LTPR10 = 1U;
    LTPR00 = 1U;
    /* Set INTLR high priority */
    LRPR10 = 0U;
    LRPR00 = 0U;
    /* Set INTLS low priority */
    LSPR10 = 1U;
    LSPR00 = 1U;
    UF0CTL1 = _0000_UARTF_BASECLK_1 | _0683_UARTF0_K_VALUE;
    UF0OPT0 = _14_UARTF_UFNOPT0_INITIALVALUE | _00_UARTF_TRAN_DATALEVEL_NORMAL | _00_UARTF_REC_DATALEVEL_NORMAL;
    UF0OPT1 = _00_UARTF_EXPANSIONBIT_UNUSE | _00_UARTF_NORMAL_MODE;
    UF0OPT2 = _00_UARTF_LT_INT_GENTIME_0 | _02_UARTF_DATA_NOISE_FILTER_UNUSED;
    UF0CTL0 = _10_UARTF_TRANSFDIR_LSB | _00_UARTF_PARITY_NONE | _02_UARTF_DATALENGTH_8BIT | _00_UARTF_STOPLENGTH_1BIT;
    STSEL0 |= _00_UARTF_PIN_P71_P70;
    /* Set LTXD0 pin */
    P7 |= 0x02;
    PM7 &= 0xFDU;
    /* Set LRXD0 pin */
    PM7 |= 0x01U;
}

/***********************************************************************************************************************
* Function Name: R_UARTF0_Start
* Description  : This function starts the UARTF0 operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UARTF0_Start(void)
{
    LTIF0 = 0U;  /* clear INTLT interrupt flag */
    LTMK0 = 0U;  /* enable INTLT interrupt */
    LRIF0 = 0U;  /* clear INTLR interrupt flag */
    LRMK0 = 0U;  /* enable INTLR interrupt */
    LSIF0 = 0U;  /* clear INTLS interrupt flag */
    LSMK0 = 0U;  /* enable INTLS interrupt */
    UF0CTL0 |= _40_UARTF_TRANSMISSION_ENABLE | _20_UARTF_RECEPTION_ENABLE; /* enable UARTF0 operation */
}

/***********************************************************************************************************************
* Function Name: R_UARTF0_Stop
* Description  : This function stops the UARTF0 operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_UARTF0_Stop(void)
{
    UF0CTL0 &= (uint8_t)(~_40_UARTF_TRANSMISSION_ENABLE & ~_20_UARTF_RECEPTION_ENABLE);  /* disable UARTF0 operation */
    LTMK0 = 1U;  /* disable INTLT interrupt */
    LTIF0 = 0U;  /* clear INTLT interrupt flag */
    LRMK0 = 1U;  /* disable INTLR interrupt */
    LRIF0 = 0U;  /* clear INTLR interrupt flag */
    LSMK0 = 1U;  /* disable INTLS interrupt */
    LSIF0 = 0U;  /* clear INTLS interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_UARTF0_Receive
* Description  : This function receives UARTF0 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_UARTF0_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        if ((UF0STR & 0x0040U) == 0U)
        {
            g_uartf0_rx_cnt = 0U;
            g_uartf0_rx_len = rx_num;
            gp_uartf0_rx_address = rx_buf;
        }
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_UARTF0_Send
* Description  : This function sends UARTF0 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK, MD_ARGERROR or MD_DATAEXISTS
***********************************************************************************************************************/
MD_STATUS R_UARTF0_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uartf0_tx_address = tx_buf;
        g_uartf0_tx_cnt = tx_num;
        
        if ((UF0STR & 0x0080U) == 0U)
        {
            LTMK0 = 1U;  /* disable INTLT interrupt */
            UF0TXB = *gp_uartf0_tx_address;
            gp_uartf0_tx_address++;
            g_uartf0_tx_cnt--;
            LTMK0 = 0U;  /* enable INTLT interrupt */
        }
        else
        {
            status = MD_DATAEXISTS;
        }
    }

    return (status);
}
