/*******************************************************************************
* Project Name:      psoc40xx_ILO_measurement
* Device Used:       CY8C4014LQI-422 
* Software Used:     PSoC Creator 3.0 SP1
* Compiler Used:     ARM GCC 4.7.3 
* Related Hardware:  CY8CKIT-040 
********************************************************************************
* Theory of Operation:
*	Measures ILO against internal main oscillator by using Systick (clocked from CPU clock)
*	and the watchdog timer (clocked from the ILO). The demo project calls the routine
*	and prints out the return value (ILO freq in kHz) in hex. It also sets up a WDT interrupt
*	to wake the processor from deep sleep on a fixed interval. The interval uses the
*	measured ILO frequency to set its accuracy. Probing R30 on the KIT-040 will allow
*	oscilloscope/frequency counter measurement of the resulting accuracy.
*
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
#include <project.h>
#include "ilomeasurement.h"

#define 	TRUE	1u
#define 	FALSE	0u

/* This is the period we want from the WDT interrupt in ms */
#define WDT_PERIOD_MS		500u

#define DISABLE_WDT_RESET	TRUE	/* TRUE to disable watchdog timer reset */

uint32 ILODelayCycles;	/* ILO cycles for a given delay */

/* Prototype watchdog ISR */
CY_ISR(WDT_ISR);

int main()
{
	
	uint8 ILOFreqkHz;			/* ILO frequency in kHz */
	CyGlobalIntEnable; 
	SW_TX_Start();	
	
	/* Print Charaters on PC UART Terminal */
	SW_TX_PutCRLF();	
	SW_TX_PutString("PSoC Rocks!");
	SW_TX_PutCRLF();
	SW_TX_PutString("ILO Measurement:  0x");
	
	ILOFreqkHz = (uint8)ILO_Calibration();	/* Note, this function disables global interrupts for a while */
	SW_TX_PutHexByte(ILOFreqkHz);
	SW_TX_PutCRLF();
	
	/* Now let's set up our WDT interrupt so that we can wake up on an accurate interval. */
	#if DISABLE_WDT_RESET
	/* Disable watchdog reset */
	CySysWdtDisable();	
	#endif
	
	ILODelayCycles = WDT_PERIOD_MS * ILOFreqkHz;
	
	/* Update the match register for generating a periodic WDT ISR.
    Note: In order to do a periodic ISR using WDT, Match value needs to be
    updated every WDT ISR with the desired time value added on top of the
    existing match value */
    CySysWdtWriteMatch(ILODelayCycles);
      
    /* Enable the WDT interrupt in SRSS INTR mask register */
    CySysWdtUnmaskInterrupt();
  
    /* Map the WatchDog_ISR vector to the WDT_ISR */
    isr_WDT_StartEx(WDT_ISR);      	

    for(;;)
    {
		
		LED_Write(1^LED_Read());
		CySysPmDeepSleep();
		
		
    }
}

CY_ISR(WDT_ISR)
{
	/* Clear WDT interrupt */ 
	CySysWdtClearInterrupt(); 
 
 	/* Write WDT_MATCH with current match value + desired match value */ 
 	CySysWdtWriteMatch((uint16)CySysWdtReadMatch()+ILODelayCycles); 
}



/* [] END OF FILE */
