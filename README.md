uCXpresso.NRF
===============================
A RTOS C/C++ Framework for nRF51 (Bluetooth Low Energy)

###Web Site: http://www.ucxpresso.net
###Getting Started: https://rawgit.com/ucxpresso/nano51822/master/documents/getting_started_with_ucxpresso.nrf.pdf
###Class Manual : http://www.embeda.com.tw/manual/nrf/html/index.html
###Approval Sheet: https://rawgit.com/ucxpresso/nano51822/master/documents/nano51822_approval_sheet.pdf
###License: http://www.embeda.com.tw/ucxpresso/?article=ucxpresso-nrf-license

v1.0.1 rc2 15th November 2014
--------------------------------
###Details: 
    1. Remote gpioINT class.
    2. Add gpioSense class to provide 30 interrupt.
    3. Add task_handle in CThread constructor. (optional)


v1.0.1 rc1 13th November 2014
--------------------------------
###Details: 
	1. Add type() member in bleAdvertising class to support the nRF-Beacon app.
	2. Set bleDeviceManager became to optional in application, to save the heap memory.
	3. Update the all beacon examples.

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
