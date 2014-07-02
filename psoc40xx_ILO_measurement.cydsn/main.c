/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

int main()
{
	CyGlobalIntEnable; 
	SW_TX_Start();	
	
	
	
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

   
    for(;;)
    {
		/* Print Charaters on PC UART Terminal */
		SW_TX_PutCRLF();	
		SW_TX_PutCRLF();
		SW_TX_PutString("CYPRESS SEMICONDUCTOR");
		SW_TX_PutCRLF();
		SW_TX_PutCRLF();
		SW_TX_PutString("PSoC 4000 - Starter Design: Low Power CapSense");
		SW_TX_PutCRLF();
		SW_TX_PutCRLF();
		SW_TX_PutString("  X    Y");
		SW_TX_PutCRLF();	
    }
}

/* [] END OF FILE */
