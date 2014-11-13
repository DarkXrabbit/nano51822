/*
 ===============================================================================
 Name        : ble_app_uart_remote_control
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : BLE UART remote control for LED
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/14 v1.0.0	First Edition.									LEO
 ===============================================================================
 */

#include <uCXpresso.h>

#ifdef DEBUG
#include <debug.h>
#include <class/serial.h>
#define DBG dbg_printf
#else
#define DBG(...)
#endif

// TODO: insert other include files here
#include <class/ble/ble_device.h>
#include <class/ble/ble_service.h>
#include <class/pin.h>
#include <class/power.h>
#include <class/ble/ble_service_uart.h>
#include <class/ble/ble_conn_params.h>
#include <class/timeout.h>
#include <class/string.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "nanoUART"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"        /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     1000                   /**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	 0x0059                 /**< Company identifier for Apple Inc. as per www.bluetooth.org. */

//#define BOARD_PCA10001
#define BOARD_LILYPAD
#include <config/board.h>

CPin ledLeft(LED_PIN_0);	// for left
CPin ledRight(LED_PIN_1);	// for right

/**
 * Command String Parse:
 *
 * Command Package:
 * $  : start of the command (for synchronize)
 * xxx: command
 * #  : end of the command
 *
 * Example: @right# (right), @left# (left)
 */
class cmdParse {
public:
	//
	// command input
	//
	void input(uint8_t ch) {
		switch (ch) {
		case '$':	// start of command
			m_cmd.clear();
			m_bStart = true;
			break;

		case '#':	// end of command
			m_cmd.makeLower();
			onCommand(m_cmd);
			m_bStart = false;
			break;

		default:
			if (m_bStart) {
				m_cmd += (char) ch;
			}
			break;
		}
	}

	//
	// Events
	//

	virtual void onRight() {
		ledRight = LED_ON;
		ledLeft = LED_OFF;
	}

	virtual void onLeft() {
		ledLeft = LED_ON;
		ledRight = LED_OFF;
	}

	virtual void onUp() {
		// TODO for up
	}

	virtual void onDown() {
		// TODO for down
	}

	virtual void onPlay() {
		// TODO for play
	}

	virtual void onStop() {
		ledRight = LED_OFF;
		ledLeft = LED_OFF;
	}

protected:
	bool m_bStart;
	CString m_cmd;

	/**
	 * On command events (string parse)
	 */
	void onCommand(CString &cmd) {
		if (cmd == "right") {
			onRight();
		} else if (cmd == "left") {
			onLeft();
		} else if (cmd == "up") {
			onUp();
		} else if (cmd == "down") {
			onDown();
		} else if (cmd == "play") {
			onPlay();
		} else if (cmd == "stop") {
			onStop();
		}
	}
};

//
// Main Routine
//
int main(void) {
#ifdef DEBUG
	CSerial ser;		// declare a Serial object
	ser.enable();
	CDebug dbg(ser);	// Debug stream use the UART object
	dbg.start();
#endif

	//
	// SoftDevice
	//
	bleDevice ble;	// use internal 32.768KHz for SoftDevice
	ble.enable();	// enable BLE SoftDevice stack

	// GAP
	ble.m_gap.settings(DEVICE_NAME);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_0dBm);	// set Output power

	//
	// Add BLE UART Service
	//
	bleServiceUART nus(ble);	// declare a BLE "Nordic UART Service" (NUS) object

	//
	// Add "connection parameters update" negotiation. (optional)
	//
	bleConnParams conn(ble);

	//
	// BLE Advertising
	//
	ble.m_advertising.interval(APP_ADV_INTERVAL);	// set advertising interval
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);// add company identifier
	ble.m_advertising.update();						// update advertising data

	// Start advertising
	ble.m_advertising.start();

	//
	// my command parse class
	//
	cmdParse cmd;

	//
	// LED output enable
	//
	ledLeft.output();	// set led0 as an output pin
	ledRight.output();	// set led1 as an output pin
	uint8_t ch= 0;

	//
	// Enable Tickless Technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// Enter main loop.
	//
	while (1) {
		//
		// Uart Service
		//
		if ( ble.isConnected() ) {
			// block in the read() to wati a char.
			// Also, block will save the power when tickless enabled.
			ch = nus.read();
			if ( ch ) {
				cmd.input(ch);
			}

		} else {
			//
			// alternate led when disconnected (idle)
			//
			ch = (ch ? 0 : 1);
			ledRight = (ch ? LED_ON : LED_OFF);
			ledLeft = (ch ? LED_OFF : LED_ON);
			sleep(10);	// blink a short time (10ms)

			ledRight = LED_OFF;
			ledLeft = LED_OFF;
			sleep(990);	// save power with a long time (990ms)
		}
	}
}
