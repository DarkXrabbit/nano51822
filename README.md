uCXpresso.NRF
===============================
A RTOS C/C++ Framework for nRF51 (Bluetooth Low Energy)

###Web Site: http://www.ucxpresso.net
###Getting Started: https://rawgit.com/ucxpresso/nano51822/master/documents/getting_started_with_ucxpresso.nrf.pdf
###Class Manual : http://www.embeda.com.tw/manual/nrf/html/index.html
###Approval Sheet: https://rawgit.com/ucxpresso/nano51822/master/documents/nano51822_approval_sheet.pdf
###License: http://www.embeda.com.tw/ucxpresso/?article=ucxpresso-nrf-license

v1.0.2 rc3 30th November 2014
--------------------------------
###Details: 
	1. Add AES 128 bits CTR and CFB mode encryption/decrytion services class.
	2. Fixed "connect directed mode".
	3. Add bleServiceHID & bleServiceKB classes.
	4. Add CButton class.
	5. Add descriptions in CString class.
	6. Add find() member in String class to handle a command list.
	7. Add app_beacon_v2 example project to explain how to make an "AT Command" application.  
	8. Add default "connection parameters" in bleConnParams constructor.

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
