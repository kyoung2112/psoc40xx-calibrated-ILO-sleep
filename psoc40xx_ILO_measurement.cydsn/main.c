/*******************************************************************************
* Project Name:      NXT_ID
* Version:           1.0
* Device Used:       CY8C44245AXI-483
* Software Used:     PSoC Creator 3.0 SP1
* Compiler Used:     ARM GCC 4.7.3 
* Related Hardware:  CY8CKIT-042 
********************************************************************************
* Theory of Operation:
*	Measures ILO against internal main oscillator by using Systick (clocked from CPU clock)
*	and the watchdog timer (clocked from the ILO). Based on code found at XAV-409. 
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

uint16 ILO_Calibration(void);

int main()
{
	uint32 wdValue;
	uint32 systValue;
	uint16 outword;
	CyGlobalIntEnable; 
	SW_TX_Start();	
	
	/* Print Charaters on PC UART Terminal */
	SW_TX_PutCRLF();	
	SW_TX_PutCRLF();
	SW_TX_PutString("CYPRESS SEMICONDUCTOR");
	SW_TX_PutCRLF();
	SW_TX_PutCRLF();
	SW_TX_PutString("PSoC 4000 - ILO Measurement");
	SW_TX_PutCRLF();
	SW_TX_PutCRLF();
	
	#if 0
	/* Clear systick counter */
	CY_SET_REG32(CYREG_CM0_SYST_CVR, 0);
	
	/* Set systick reload */
	CY_SET_REG32(CYREG_CM0_SYST_RVR, 0x0000FFFF);

	
	/* Enable systick counter */
	CY_SET_REG32(CYREG_CM0_SYST_CSR,(uint32)5u);
	#endif
	
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	//(void)SysTick_Config(0xFFFF);
   
	SW_TX_PutHexInt((uint16)ILO_Calibration());
	SW_TX_PutCRLF();
		
    for(;;)
    {
//		wdValue = CySysWdtReadCount();
//		SW_TX_PutString("WDT :");
//		SW_TX_PutHexInt((uint16)wdValue);
//		SW_TX_PutString("  SYST:");
//		systValue = CY_GET_REG32(CYREG_CM0_SYST_CVR);
//		SW_TX_PutHexInt((uint16)systValue);
//		SW_TX_PutCRLF();

		
		
    }
}

/* Return the number of CPU clocks in a given number of ILO clocks. Uses the cortex systick
counter */
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
	
	WDTBegin = CySysWdtReadCount();
	
	/* Wait for WDT transition */
	do
	{
		WDTVal = CySysWdtReadCount();
	}
	while(WDTVal  != WDTBegin);
	
	/* Read initial Systick value */
	SysTickBegin = CY_GET_REG32(CYREG_CM0_SYST_CVR); 
	
	WDTBegin = WDTVal;
	
	/* Looking for 2 ILO counts */
	WDTEnd = WDTVal + 2u;
	
	while (CySysWdtReadCount() != WDTEnd);
	
	/* Read ending Systick value */
	SysTickEnd = CY_GET_REG32(CYREG_CM0_SYST_CVR); 
	
	return (uint16)(SysTickBegin - SysTickEnd);
	
	/* Check for overflow */
	//regData = CM0->SYST_CSR; ///Countflag
   ///if ( regData & BIT16 ) return DEFAULT_ILO; /// COUNTFLAG is set   
   /// Check that the SYST_CSR COUNTFLAG has not been set. If set it means there is overflow    
   /// If overflow return 32KHz
	
	}

/* [] END OF FILE */
