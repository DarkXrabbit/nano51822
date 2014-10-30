nano51822
===============================
uCXpresso.NRF RTOS C/C++ Framework for Bluetooth Low Energy

###Getting Started: https://cdn.rawgit.com/ucxpresso/nano51822/master/documents/getting_started_with_ucxpresso.nrf.pdf
###Class Manual : https://cdn.rawgit.com/ucxpresso/nano51822/master/documents/doxygen/html/index.html
###Approval Sheet: https://rawgit.com/ucxpresso/nano51822/master/documents/nano51822_approval_sheet.pdf

v1.0.0 rc3 28th October 2014
--------------------------------
###Features: 
	1. Add Tickless Technology for low power feaure. (Min. 5uA)
	2. Updated bleServiceUART TX/RX char. UUID.

v1.0.0 rc2 25th October 2014
--------------------------------
###Features: 
 	1. Provide two TIMER (TIMER_1 and TIMER_2)
 	2. Add hwPWM class to provide six PWM (Hardware PWM)
 	3. Add CPowerSave class to provide the "system_off" feature.
 	4. Remove RTC class.
 	5. Add bleDevice::Init() in the setup.cpp of project.
 	6. Kernel updated for low power feature.

v1.0.0 rc1 21th October 2014
--------------------------------
###Features: 
	1. RTOS update to v8.1.2.
	2. Free LPCXpresso IDE supported. (for OS/X, Linux and Windows)
	3. NRF framework preparing ...
