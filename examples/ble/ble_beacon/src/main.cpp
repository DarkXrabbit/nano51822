/*
===============================================================================
 Name        : iBeacon Demo
 Author      : uCXpresso
 Version     : v1.0.1
 Copyright	 : www.ucxpresso.net
 License   	 : MIT
 Description : beacon test
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/8/2	v1.0.0	First Edition for nano51822						Leo
 2014/10/26 v1.0.1	Add power save solution.						Jason
 ===============================================================================
 */

#include <stdlib.h>
#include <string.h>
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
#include <class/ble/ble_service_dfu.h>
#include <class/pin.h>
#include <class/timeout.h>
#include <class/power.h>

// TODO: insert other definitions and declarations here
#define APP_BEACON_INFO_LENGTH           0x17                              /**< Total length of information advertised by the Beacon. */
#define APP_ADV_DATA_LENGTH              0x15                              /**< Length of manufacturer specific data in the advertisement. */
#define APP_DEVICE_TYPE                  0x02                              /**< 0x02 refers to Beacon. */
#define APP_MEASURED_RSSI                ((uint8_t)-66)                    /**< The Beacon's measured RSSI at 1 meter distance in dBm. */
#define APP_COMPANY_IDENTIFIER           0x0059                            /**< Company identifier for Nordic Semi. as per www.bluetooth.org. */
#define APP_BEACON_UUID                  0x01, 0x12, 0x23, 0x34, \
                                         0x45, 0x56, 0x67, 0x78, \
                                         0x89, 0x9a, 0xab, 0xbc, \
                                         0xcd, 0xde, 0xef, 0xf0            /**< Proprietary UUID for Beacon. */

#define USE_UICR_FOR_MAJ_MIN_VALUES	 0

#if USE_UICR_FOR_MAJ_MIN_VALUES
#define UICR_ADDRESS                     0x10001080                        /**< Address of the UICR register used by this example. The major and minor versions to be encoded into the advertising data will be picked up from this location. */

    // If USE_UICR_FOR_MAJ_MIN_VALUES is defined, the major and minor values will be read from the
    // UICR instead of using the default values. The major and minor values obtained from the UICR
    // are encoded into advertising data in big endian order (MSB First).
    // To set the UICR used by this example to a desired value, write to the address 0x10001080
    // using the nrfjprog tool. The command to be used is as follows.
    // nrfjprog --snr <Segger-chip-Serial-Number> --memwr 0x10001080 --val <your major/minor value>
    // For example, for a major value and minor value of 0xabcd and 0x0102 respectively, the
    // the following command should be used.
    // nrfjprog --snr <Segger-chip-Serial-Number> --memwr 0x10001080 --val 0xabcd0102
#define major_value  		(((*(uint32_t *)UICR_ADDRESS) & 0xFFFF0000) >> 16)
#define minor_value 		((*(uint32_t *)UICR_ADDRESS) & 0x0000FFFF)
#define APP_MAJOR_VALUE 	MSB_FIRST(major_value)	/**< Major value used to identify Beacons. */
#define APP_MINOR_VALUE 	MSB_FIRST(minor_value)	/**< Minor value used to identify Beacons. */
#else
#define APP_MAJOR_VALUE		MSB_FIRST(0x0102)		/**< Major value used to identify Beacons. */
#define APP_MINOR_VALUE     MSB_FIRST(0x0304)		/**< Minor value used to identify Beacons. */
#endif

static const uint8_t m_beacon_info[APP_BEACON_INFO_LENGTH] =               /**< Information advertised by the Beacon. */
{
    APP_DEVICE_TYPE,     // Manufacturer specific information. Specifies the device type in this
                         // implementation.
    APP_ADV_DATA_LENGTH, // Manufacturer specific information. Specifies the length of the
                         // manufacturer specific data in this implementation.
    APP_BEACON_UUID,     // 128 bit UUID value.
    APP_MAJOR_VALUE,     // Major arbitrary value that can be used to distinguish between Beacons.
    APP_MINOR_VALUE,     // Minor arbitrary value that can be used to distinguish between Beacons.
    APP_MEASURED_RSSI,   // Manufacturer specific information. The Beacon's measured TX power in
                         // this implementation.
};

//
// Board LED define
//
//#define BOARD_PCA10001
#define BOARD_LILYPAD
#include <config/board.h>

static const uint8_t flags = BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED;

int main(void)
{
//
// for Save Power, it have to build with "Release Build" and disable the Debug feature.
//
#ifdef DEBUG
	CSerial ser;
	ser.enable();
	CDebug dbg(ser);
	dbg.start();
#endif

	//
	// SoftDevice Driver
	//
	bleDevice ble;
	ble.enable();										// enable BLE stack

	// GAP
	ble.m_gap.settings("nano51822");					// set ble device name
	ble.m_gap.tx_power(BLE_TX_0dBm);					// set TX radio power

	//
	// Add BLE DFU Service
	//
	bleServiceDFU dfu(ble);

	//
	// Advertisement
	//
	ble.m_advertising.interval(20);						// set advertising interval = 25ms
	ble.m_advertising.name_type(BLE_ADVDATA_NO_NAME);	// set beacon name type (No Name)
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);
	ble.m_advertising.manuf_specific_data(m_beacon_info, APP_BEACON_INFO_LENGTH); // set beacon data
	ble.m_advertising.flags(&flags, sizeof(flags));		// set flags
	ble.m_advertising.update();							// update advertising data

	// enable DFU service if need.
	dfu.enable();

	//
	// blink LED
	//
	CPin led(LED_PIN_0);
	led.output();

	//
	// Enable Tickless Technology
	//
	CPowerSave::tickless(true);

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Control the on/off interval of Advertisement for save power.
    	//
		led = LED_ON;
		ble.m_advertising.start();	// turn on the advertisement
		sleep(50);					// turn on with a short time
		led = LED_OFF;
		ble.m_advertising.stop();	// turn off the advertisement for save power.
    	sleep(950);				// sleep with a long time
    }
}
