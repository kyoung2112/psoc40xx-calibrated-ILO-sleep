/*******************************************************************************
* File Name: SW_TX.h
* Version 1.20
*
* Description:
*  This file provides constants and parameter values for the Software Transmit
*  UART Component.
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_SW_TX_UART_SW_TX_H
#define CY_SW_TX_UART_SW_TX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"

#define SW_TX_BAUD_RATE                      (115200u)
#define SW_TX_PIN_STATIC_MODE                (1u)


/***************************************
*        Function Prototypes
***************************************/
#if(SW_TX_PIN_STATIC_MODE == 1u)
    void SW_TX_Start(void) ;
#else
    void SW_TX_StartEx(uint8 port, uint8 pin) ;
#endif /* (SW_TX_PIN_STATIC_MODE == 1u) */

void SW_TX_Stop(void) ;
void SW_TX_PutChar(uint8 txDataByte) ;
void SW_TX_PutString(const char8 string[]) ;
void SW_TX_PutArray(const uint8 array[], uint32 byteCount) ;
void SW_TX_PutHexByte(uint8 txHexByte) ;
void SW_TX_PutHexInt(uint16 txHexInt) ;
void SW_TX_PutCRLF(void) ;

#endif /* CY_SW_TX_UART_SW_TX_H */


/* [] END OF FILE */
