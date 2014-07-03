/*******************************************************************************
* File Name:      ilomeasurement.h
* Version:           1.0
* Device Used:       CY8C4014LQI-422 
* Software Used:     PSoC Creator 3.0 SP1
* Compiler Used:     ARM GCC 4.7.3 
* Related Hardware:  CY8CKIT-040 
*********************************************************************************
* Copyright (2014), Cypress Semiconductor Corporation.
********************************************************************************
* This software, including source code, documentation and related materials
* ("Software") is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and 
* foreign), United States copyright laws and international treaty provisions. 
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the 
* Cypress source code and derivative works for the sole purpose of creating 
* custom software in support of licensee product, such licensee product to be
* used only in conjunction with Cypress's integrated circuit as specified in the
* applicable agreement. Any reproduction, modification, translation, compilation,
* or representation of this Software except as specified above is prohibited 
* without the express written permission of Cypress.
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes to the Software without notice. 
* Cypress does not assume any liability arising out of the application or use
* of Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use as critical components in any products 
* where a malfunction or failure may reasonably be expected to result in 
* significant injury or death ("High Risk Product"). By including Cypress's 
* product in a High Risk Product, the manufacturer of such system or application
* assumes all risk of such use and in doing so indemnifies Cypress against all
* liability. Use of this Software may be limited by and subject to the applicable
* Cypress software license agreement.
*/

#include "project.h"

/* How many ILO cycles to use in measurement */
#define ILO_MEAS_CYCLES	2u

/* Prototype */
uint16 ILO_Calibration(void);


/* [] END OF FILE */
