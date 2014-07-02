/*******************************************************************************
* File Name: SW_TX_PVT.h
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

#ifndef CY_SW_TX_UART_SW_TX_PVT_H
#define CY_SW_TX_UART_SW_TX_PVT_H

#include "SW_TX.h"


#if(SW_TX_PIN_STATIC_MODE == 1u)
    #define SW_TX_PIN_NUMBER                 (SW_TX_Tx__0__SHIFT)
    #define SW_TX_PIN_PORT_NUMBER            (SW_TX_Tx__0__PORT)
    #if (CY_PSOC4)
        #define SW_TX_PIN_DR                 (SW_TX_Tx__DR)
    #else
        #define SW_TX_PIN_DR                 (SW_TX_Tx__0__PC)
    #endif /* (CY_PSOC4) */
    
#else
    #if (!CY_PSOC4)
        #define SW_TX_PORT_CNF_BASE          (CYREG_PRT0_PC0)
    #else
        #if (CY_PSOC4A)
            #define SW_TX_PORT_CNF_BASE          ((uint32)CYDEV_PRT0_BASE)
            #define SW_TX_PORT_CNF_SIZE          ((uint32)CYDEV_PRT0_SIZE)
            #define SW_TX_PORT_CNF_MODE_OFFSET   ((uint32)(CYREG_PRT0_PC - CYDEV_PRT0_BASE))
            #define SW_TX_PORT_CNF_DR_OFFSET     ((uint32)(CYDEV_PRT0_BASE - CYREG_PRT0_DR))     
        #else
            #define SW_TX_PORT_CNF_BASE          ((uint32)CYDEV_GPIO_PRT0_BASE)
            #define SW_TX_PORT_CNF_SIZE          ((uint32)CYDEV_GPIO_PRT0_SIZE)
            #define SW_TX_PORT_CNF_MODE_OFFSET   ((uint32)(CYREG_GPIO_PRT0_PC - CYDEV_GPIO_PRT0_BASE))
            #define SW_TX_PORT_CNF_DR_OFFSET     ((uint32)(CYDEV_GPIO_PRT0_BASE - CYREG_GPIO_PRT0_DR))
        #endif /* (CY_PSOC4A) */
    #endif /* (!CY_PSOC4) */
#endif /* (SW_TX_PIN_STATIC_MODE == 1u) */

/* Nibble Offset and Mask */
#define SW_TX_BYTE_UPPER_NIBBLE_SHIFT        (0x04u)
#define SW_TX_U16_UPPER_BYTE_SHIFT           (0x08u)
#define SW_TX_BYTE_LOWER_NIBBLE_MASK         (0x0Fu)
#define SW_TX_U16_LOWER_BYTE_MASK            (0xFFu)

#if (!CY_PSOC4)
    #define SW_TX_MAX_PORT_NUMBER            (15u)
#else
    #define SW_TX_MAX_PORT_NUMBER            (4u)
#endif /* (!CY_PSOC4) */

#define SW_TX_MAX_PIN_NUMBER                 (7u)
#endif /* CY_SW_TX_UART_SW_TX_PVT_H */


/* [] END OF FILE */
