/*==============================================================================*/
/* DISCLAIMER                                                                   */
/* This software is supplied by Renesas Electronics Corporation and is only     */
/* intended for use with Renesas products. No other uses are authorized. This   */
/* software is owned by Renesas Electronics Corporation and is protected under  */
/* all applicable laws, including copyright laws.                               */
/* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING  */
/* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT      */
/* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE   */
/* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.          */
/* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS       */
/* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE  */
/* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR   */
/* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE  */
/* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.                             */
/* Renesas reserves the right, without notice, to make changes to this software */
/* and to discontinue the availability of this software. By using this software,*/
/* you agree to the additional terms and conditions found by accessing the      */
/* following link:                                                              */
/* http://www.renesas.com/disclaimer                                            */
/*                                                                              */
/* Copyright (C) 2018 Renesas Electronics Corporation. All rights reserved.     */
/*==============================================================================*/

/******************************************************************************
 Include
******************************************************************************/
#include <string.h>
#include "iodefine.h"
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Calculations.h"
/* Standard library (runtime library is used) */


/* Header files for FDL/EEL */
#include "fdl.h"                    /* FDL library header file               */
#include "fdl_types.h"              /* FDL types definition header file      */
#include "fdl_descriptor.h"         /* FDL descriptor header file            */
#include "eel.h"                    /* EEL library header file               */
#include "eel_types.h"              /* EEL types definition header file      */
#include "eel_descriptor.h"         /* EEL descriptor header file            */
#include "eel_user_types.h"         /* EEL user types definition header file */
#include "lcd.h"
/******************************************************************************
 Interrupt function
******************************************************************************/
//#pragma interrupt samIntWdt (vect=INTWDTI)  /* WDT interrupt          */

/******************************************************************************
 Typedef definitions
******************************************************************************/

/******************************************************************************
 Macro definitions
******************************************************************************/
//#define SAM_WDT_RESET() WDTE = 0xAC /* Declare watchdog timer reset function */
//#define SAM_WRITE_SIZE 10           /* Declare write data size */


/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
void eel_fdl_open(void);
void eel_fdl_format(void);
void eel_fdl_write(uint8_t id);
void eel_fdl_read(uint8_t id);

/* Definition of variables */
eel_request_t   dtyEelReq;
eel_u08         dubWriteBuffer[4];
eel_u08         dubReadBuffer[4];
fdl_status_t    fdlStatus = 0; 
eel_u08         err_flag = 0;



extern uint8_t TX_buf[5],RX_buf[5];
//extern float odo_l,Odo_Value;
//extern unsigned short odo_h;
//unsigned short temp_odo_l,temp_odo_h ;
//uint8_t write_buffer = 0x80;
/* End user code. Do not edit comment generated here */


/******************************** LIB OPEN FUNCTION ********************************/

void eel_fdl_open(void)
{
    __EI();
    
    /* Initialize EEL requester */
    dtyEelReq.address_pu08   = 0;
    dtyEelReq.identifier_u08 = 0;
    dtyEelReq.command_enu    = 0;
    dtyEelReq.status_enu     = 0;
    
    /*== EEL / uninitialized =*/
    /***************************************************************************/
    /* FDL initialization processing                                           */
    /***************************************************************************/
    /* Initialize FDL parameters */
    fdlStatus = FDL_Init( &fdl_descriptor_str );
    
    if( fdlStatus == FDL_OK )
    {
        /*== EEL / uninitialized =*/
        /***************************************************************************/
        /* FDL preparation processing                                              */
        /***************************************************************************/
        FDL_Open();
       
        /*== -> EEL / uninitialized -> ( Change EEL state ) ========*/
        /*******************************************************************************/
        /* EEL initialization processing( state : EEL / uninitialized -> EEL / closed )*/
        /*******************************************************************************/
        dtyEelReq.status_enu = EEL_Init();
        
        if( dtyEelReq.status_enu == EEL_OK )
        {
            /*== EEL / closed -> ( Change EEL state ) ===============*/
            /***************************************************************************/
            /* EEL preparation processing ( state : EEL / closed -> EEL / opened )     */
            /***************************************************************************/
            EEL_Open();
	}
    }		
}

/******************************** ERASE FUNCTION ********************************/

void eel_fdl_format(void)
{
	/*== ->  EEL / opened -> ( Change EEL state ) ===============*/
    /***************************************************************************/
    /* EEL execution start processing ( state : EEL / opened -> EEL / started )*/
    /***************************************************************************/
    do {
        /* Set parameter of EEL_CMD_STARTUP command   */
        dtyEelReq.command_enu = EEL_CMD_STARTUP;
        
        /* Execute EEL_CMD_STARTUP command */
        EEL_Execute( &dtyEelReq ); 
        
        /* Wait of command processing end */
        while( dtyEelReq.status_enu == EEL_BUSY )
        {
             EEL_Handler(); /* Check of command end */
        }
            
        /* EEPROM emulation block inconsistency error */
        if( dtyEelReq.status_enu == EEL_ERR_POOL_INCONSISTENT )
        {
            /* Set parameter of EEL_CMD_FORMAT command   */
            dtyEelReq.command_enu = EEL_CMD_FORMAT;
            
            /* Execute EEL_CMD_FORMAT command */
            EEL_Execute( &dtyEelReq );
            
            /* Wait of command processing end */
            while( dtyEelReq.status_enu == EEL_BUSY )
            {
                EEL_Handler();  /* Check of command end */
            }
        }
    /* If EEL_CMD_FORMAT command is successful,       */
    /* re-execute EEL_CMD_STARTUP command.            */
    } while( ( dtyEelReq.command_enu == EEL_CMD_FORMAT ) &&
             ( dtyEelReq.status_enu  == EEL_OK         )  );
    
    /* EEL_CMD_FORMAT command or EEL_CMD_STARTUP command is successful. */
    /* If command is abnormal end,  execute EEL_CMD_SHUTDOWN command.   */
}


/******************************** WRITE FUNCTION ********************************/

void eel_fdl_write(uint8_t id)						//uint32_t *write_buffer,
//void eel_fdl_write(void)
{
    if( dtyEelReq.status_enu == EEL_OK )
    {
        do {
            /**************************/
            /* data write processing  */
            /**************************/
            /* Set of write data */
            dubWriteBuffer[0x00] = TX_buf[0];
            dubWriteBuffer[0x01] = TX_buf[1];
	    dubWriteBuffer[0x02] = TX_buf[2];
            dubWriteBuffer[0x03] = TX_buf[3];
	    //dubWriteBuffer[0x04] = 0x55;
            //dubWriteBuffer[0x05] = 0x66;
	    //dubWriteBuffer[0x06] = 0x77;
            //dubWriteBuffer[0x07] = 0x88;
	    //dubWriteBuffer[0x08] = 0x99;
            //dubWriteBuffer[0x09] = 0xAA;
			
	    //dubWriteBuffer = write_buffer;
            
            /* Set parameter of EEL_CMD_WRITE command */
            dtyEelReq.address_pu08   = dubWriteBuffer;
            dtyEelReq.identifier_u08 = id;
            dtyEelReq.command_enu    = EEL_CMD_WRITE;
            
            /* Execute EEL_CMD_WRITE command */
            EEL_Execute( &dtyEelReq );
            
            /* Wait of command processing end */
            while( dtyEelReq.status_enu == EEL_BUSY )
            {
                /* Check of command end */
                EEL_Handler();
            }
            
             /* Pool full error */
            if (dtyEelReq.status_enu == EEL_ERR_POOL_FULL)
            {
               /* Set parameter of EEL_CMD_REFRESH command */
                dtyEelReq.command_enu    = EEL_CMD_REFRESH;
                
                /* Execute EEL_CMD_REFRESH command */
                EEL_Execute( &dtyEelReq );
                
                /* Wait of command processing end */
                while( dtyEelReq.status_enu == EEL_BUSY )
                {
                    /* Check of command end */
                    EEL_Handler();
                }
            }
        /* If EEL_CMD_REFRESH command is  successful, */
        /* re-execute EEL_CMD_WRITE command..         */
        } while( ( dtyEelReq.command_enu == EEL_CMD_REFRESH ) &&
                 ( dtyEelReq.status_enu  == EEL_OK          )  );
        
        /* EEL_CMD_WRITE command or EEL_CMD_REFRESH command is successful. */
        /* If command is abnormal end, execute EEL_CMD_SHUTDOWN command.   */
    }
}

/******************************** READ FUNCTION ********************************/

void eel_fdl_read(uint8_t id)						//(uint32_t *mem_address, uint32_t *read_buffer, uint8_t bytecount)
//void eel_fdl_read(void)
{
	uint32_t Odo_mem_read;
    if ( dtyEelReq.status_enu == EEL_OK )   
    {
        /************************/
        /* data read processing */
        /************************/
        /* Definition for loop variables*/
        fdl_u16    duh_i;   
        /* Set parameter of EEL_CMD_READ command */
        dtyEelReq.address_pu08   = dubReadBuffer;
        dtyEelReq.identifier_u08 = id; 
        dtyEelReq.command_enu    = EEL_CMD_READ;
        
        /* Execute EEL_CMD_READ command */
        EEL_Execute( &dtyEelReq );
        
        /* Wait of command processing end */
        while( dtyEelReq.status_enu == EEL_BUSY )
        {
            /* Check of command end */
            EEL_Handler();
        }
        
        if (dtyEelReq.status_enu == EEL_OK )
        {
            /* Compare of data of read and data of write. */
            for( duh_i = 0 ; duh_i < sizeof(id) ; duh_i++ )
            {
                if( dubWriteBuffer[ duh_i ] != dubReadBuffer[ duh_i ] )
		//if( dubWriteBuffer != dubReadBuffer)
                {
                    /* error handling */
                    err_flag = 1;
                    break;
                }
            }
        }
            //temp_odo_l=(unsigned short)((dubReadBuffer[1]<<8)|(dubReadBuffer[0]));
            //temp_odo_h =(unsigned short)((dubReadBuffer[3]<<8)|(dubReadBuffer[2]));
	        //Odo_mem_read = (float)(((odo_h)<<16)| (temp_odo_l));
            memcpy(&Odo_mem_read,&dubReadBuffer[0],4);
	        Odo_value_Mem_read(&Odo_mem_read);
            //ign_On_Odo = Odo_Value;

    }

}

void eel_fdl_close(void)
{
    if ( dtyEelReq.status_enu == EEL_OK )   
    {
	/***************************************************************************/
        /* EEL Execution stop processing ( state : EEL / started -> opened )       */
        /***************************************************************************/
        /* Set parameter of EEL_CMD_SHUTDOWN command */
        dtyEelReq.command_enu = EEL_CMD_SHUTDOWN;
        
        /* Execute EEL_CMD_SHUTDOWN */
        EEL_Execute( &dtyEelReq );
        
        /* Wait of command processing end */
        while( dtyEelReq.status_enu == EEL_BUSY )
        {
            /* Check of command end */
            EEL_Handler();
        }
        /*== ->  EEL / opened -> ( Change EEL state ) ===============*/
        /***************************************************************************/
        /* EEL end processing ( state : EEL / opened -> closed )                   */
        /***************************************************************************/
        EEL_Close();
    }
        /*== ->  EEL / closed -> ( Change EEL state )  ===============*/
        /***************************************************************************/
        /* FDL end processing  ( state : EEL / closed -> uninitialized )            */
        /***************************************************************************/
        FDL_Close();
}