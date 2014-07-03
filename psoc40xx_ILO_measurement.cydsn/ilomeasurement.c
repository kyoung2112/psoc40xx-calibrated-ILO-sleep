/*******************************************************************************
* File Name:      ilomeasurement.c
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
#include "ilomeasurement.h"

/* 
**************************************************************
* This function returns the measured ILO frequency in kHz.
* NOTE: Disables Global Interrupts for an accurate measurement 
***************************************************************
*/
uint16 ILO_Calibration(void)
{
	uint16 WDTBegin, WDTEnd, WDTVal;
	uint32 SysTickBegin, SysTickEnd;
	
	/* Clear systick counter */
	CY_SET_REG32(CYREG_CM0_SYST_CVR, 0);
	
	/* Set systick reload to full 24-bit value */
	CY_SET_REG32(CYREG_CM0_SYST_RVR, 0x0FFFFFF);

	/* Enable systick counter */
	CY_SET_REG32(CYREG_CM0_SYST_CSR,(uint32)5u);
	
	CyGlobalIntDisable;
	WDTBegin = CySysWdtReadCount();
	
	/* Wait for WDT transition to make sure we start on an edge */
	do
	{
		WDTVal = CySysWdtReadCount();
	}
	while(WDTVal  == WDTBegin);
	
	/* Read initial Systick value */
	SysTickBegin = CY_GET_REG32(CYREG_CM0_SYST_CVR); 
	
	/* This is the count at the edge we waited for */
	WDTBegin = WDTVal;
	
	/* Set up our end as ILO_MEAS_CYCLES more ILO cycles */
	WDTEnd = WDTVal + ILO_MEAS_CYCLES;
	
	/* Waitt here for our WDT end count to be reached */
	while (CySysWdtReadCount() != WDTEnd);
	
	/* Read ending Systick value */
	SysTickEnd = CY_GET_REG32(CYREG_CM0_SYST_CVR); 
	
	CyGlobalIntEnable;
	
	/* Check for overflow */
	//regData = CM0->SYST_CSR; ///Countflag
   ///if ( regData & BIT16 ) return DEFAULT_ILO; /// COUNTFLAG is set   
   /// Check that the SYST_CSR COUNTFLAG has not been set. If set it means there is overflow    
   /// If overflow return 32KHz
	
	/* SysTick is a down counter, so SysTickBegin - SysTickEnd is the number of SYSCLK
	*	cycles in ILO_MEAS_CYCLES rising edges of ILO clock. This outputs the ILO freq 
	*	in kHz
	*/
	return (uint16)((CYDEV_BCLK__SYSCLK__KHZ*ILO_MEAS_CYCLES)/(SysTickBegin - SysTickEnd));
	
	
	
	}

/* [] END OF FILE */
