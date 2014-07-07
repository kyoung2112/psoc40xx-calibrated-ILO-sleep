## PSoC 40xx ILO Measurement with Sleep ##
   
Copyright (2014), Cypress Semiconductor Corporation.
   
Device Used:       CY8C4014LQI-422 
Software Used:     PSoC Creator 3.0 SP1
Compiler Used:     ARM GCC 4.7.3 
Related Hardware:  CY8CKIT-040 

Theory of Operation:
Measures ILO against internal main oscillator by using Systick (clocked from CPU clock) and the watchdog timer (clocked from the ILO). The demo project calls the routine and prints out the return value (ILO freq in kHz) in hex. It also sets up a WDT interrupt to wake the processor from deep sleep on a fixed interval. The interval uses the measured ILO frequency to set its accuracy. Probing R30 on the KIT-040 will allow oscilloscope/frequency counter measurement of the resulting accuracy.

TODO: 
Need to implement robust error checking (WDT underflow, range checking, etc.).

