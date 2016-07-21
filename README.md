uCXpresso.NRF
===============================
A RTOS C/C++ Framework for nRF51 (Bluetooth Low Energy)

###Web Site: http://www.ucxpresso.net
###Getting Started: http://www.embeda.com.tw/manual/nrf/getting_started_with_ucxpresso.nrf.pdf
###Class Manual : http://www.embeda.com.tw/manual/nrf/html/index.html
###Approval Sheet: https://rawgit.com/ucxpresso/nano51822/master/documents/nano51822_approval_sheet.pdf
###License: http://www.embeda.com.tw/ucxpresso/?article=ucxpresso-nrf-license
###Online Shop: 
	Japan & Internation: https://international.switch-science.com/catalog/2158
	UK: http://vurt.blue/products/lilypad-for-nano51822?variant=1095070781


v1.1.2 rc1 20th July 2016
--------------------------------
###Details: 
	1. Add nanopb to support the Google Science Journal project.
	2. Updates the BLE stack to support the customer UUID in advertisement.


v1.0.7 released 6th July 2015
--------------------------------
###Details: 
	1. Add nano51822-UDK board pin defined.
	2. Add fast external interrupts service. (gpioINT class)

v1.0.6 released 20th April 2015
--------------------------------
###Details: 
	1. Add the SStream class to provide the AES 128 secure stream.
	2. Update bleAdvertising class.
	3. Add the ARM CMSIS DSP Library.
	4. Kernel update to v8.2.0
	5. Fixed the tickless problem when the TIMER (timer, pwm...) is enabled.

v1.0.5 released 20th January 2015
--------------------------------
###Details: 
	1. Support nano51822-AC RAM 32KB version. (for Licensed Only)
	2. Add isActive member function in bleAdvertising class.
	3. Fixed Channel 3 of PWM no output problem.

v1.0.4 released 30th December 2014
--------------------------------
###Details: 
	1. New ASSERT scheme for debug.
	2. Add osTimer class.

v1.0.3 released 16th December 2014
--------------------------------
###Details: 
	1. Fixed "Connect Directed" mode for bond connection. (BT 4.1 spec.)
	2. Fixed "Connection Parameters Update" negotiation bug.

v1.0.2 released 1th December 2014
--------------------------------
###Features: 
	1. Add AES 128 bits CTR and CFB mode encryption/decrytion services class.
	2. Support bond connection.
	3. Add bleServiceHID & bleServiceKB classes.
	4. Add CButton class.

v1.0.1 released 20th November 2014
--------------------------------
###Features: 
	1. Implement for bond connection. (see example ble_app_proximity).
	2. Add gpioSense class to provide 30 edge interrupts.
	3. Add task_handle in CThread constructor. (optional)
	4. Negotiate the "Connection Parameters Update" in main loop.
	5. Speed up the BLE efficiency.
	6. Add advertising mode options.
	7. Enter to system power off mode when Advertising timeout.

v1.0.0-released 12th November 2014
--------------------------------
###Features: 
	1. SoftDevice 7.1 ready.
	2. Enhanced BLE C++ framework.
	3. High performance BLE UART service ready. (Use Nordic UART over BLE profile).
	4. Flexible service objects.
	5. Multi-Tasking RTOS ready. (v8.1.2)
	6. Tickless Technology ready. (activity @ avg.: 26uA / min.: 6uA)
	7. Rich Peripherals I/O class library.
	8. DFU button support on P0.0 (Active Low, bootloader @ 0x3C000)
