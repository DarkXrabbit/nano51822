/*
===============================================================================
 Name        : main.c
 Author      :
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : CC BY-NC-SA
 Description :
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------

 ===============================================================================
 */

#include <uCXpresso.h>

#ifdef DEBUG
#include <debug.h>
#include <class/serial.h>
#define DBG 	dbg_printf
#define ASSERT	dbg_assert
#else
#define DBG(...)
#define ASSERT(...)
#endif

// TODO: insert other include files here
//#include <class/ble/ble_device_manager.h>
#include <class/ble/ble_device.h>
#include <class/ble/ble_service.h>
#include <class/ble/ble_conn_params.h>
#include <class/ble/ble_service_uart.h>
#include <class/ble/uuid.h>
#include <class/power.h>

#include <stdlib.h>
#include <string.h>
#include <class/thread.h>
#include <class/list.h>
#include <class/pin.h>
#include <class/adc.h>
#include <class/gpio_int.h>
#include <class/sw_pwm.h>

// TODO: insert other definitions and declarations here
#define DEVICE_NAME                          "swiftIO"            /**< Name of device. Will be included in the advertising data. */
#define MANUFACTURER_NAME                    "uCXpresso.NRF"      /**< Manufacturer. Will be passed to Device Information Service. */
#define APP_ADV_INTERVAL                     127                   /**< The advertising interval (in ms). */
#define APP_COMPANY_IDENTIFIER           	 0x0059               /**< Company identifier for Nordic Semi. as per www.bluetooth.org. */

//#define BOARD_LILYPAD
#define BOARD_NANO51822_UDK
#include <config/board.h>

#define AES_STREAM	0

//
// SwiftIO Stream UUID for BLE
//
#include "SwiftIO.h"
const char *swiftIO_base_uuid = "AFEA0000-17D0-42B2-BBD2-14718591D65E";

//
// GPIO Interrupt
//
swiftIO *pSwift;
//class myInt: public gpioINT {
//public:
//	myInt(INT_T number,  uint8_t pin, SENSE_T sense=FALLING, PIN_INPUT_MODE_T mode=INTERNAL_PULL_UP) :
//	gpioINT(number, NULL, pin, sense, mode) {
//	}
//
//	virtual void onEvent() {
//		pSwift->send(OP_INT_TOG, 1, &m_pin);
//	}
//};

void senseTask(CThread *pthread, void *param) {
	CList *interrupts = (CList *) param;

	CPin led(LED_PIN_2);
	led.output(LED_ON);

	gpioSense::enable();
	while(true) {
		gpioSense::wait();
		led.invert();

		LIST_POS pos = interrupts->getHeadPos();
		while( pos != NULL ) {
			gpioSense *irq = (gpioSense *) interrupts->getAt(pos);
			if ( irq->isActived() ) {
				uint8_t pin = irq->pin();
				pSwift->send(OP_INT_TOG, 1, &pin);
			}
			pos = interrupts->getNext(pos);
		}
	}
}

//
// Main Routine
//
int main(void) {
#ifdef DEBUG
	CSerial ser;		// declare a UART object
	ser.enable();
	CDebug dbg(ser);	// Debug stream use the UART object
	dbg.start();
#endif
	//
	// SoftDevice
	//
	bleDevice ble;
	ble.enable();	// enable BLE SoftDevice task

	// Device Manager for bond device. (Optional, for bond link device only)
//	bleDeviceManager man(ble);

	// GAP
	ble.m_gap.settings(DEVICE_NAME, 7.5, 10);	// set Device Name on GAP
	ble.m_gap.tx_power(BLE_TX_0dBm);

	//
	// TODO: Add BLE Service
	//
	bleServiceUART stream1(ble);				// stream1 for BLE UART

	CUUID base(swiftIO_base_uuid);
	bleServiceUART stream2(ble, &base.uuid);	// stream2 for SwiftIO

	//
	// Optional: Add "Connection Parameters Update" negotiation.
	//
	bleConnParams conn(ble);

	//
	// BLE Advertising
	//
	ble.m_advertising.interval(APP_ADV_INTERVAL);					// set advertising interval
	ble.m_advertising.commpany_identifier(APP_COMPANY_IDENTIFIER);	// add company identifier

	// Optional: add standard profile uuid in advertisement.
	ble.m_advertising.add_uuid_to_complete_list(stream2);

	// Optional: add appearance to indicate who you are in advertisement.
	ble.m_advertising.update();										// update advertisement data

	// Start advertising
	ble.m_advertising.start();

	//
	// Optional: Enable tickless technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// Your Application setup code here
	//
	CPin led(LED_PIN_3);
	led.output();

	// Declare SwiftIO
	swiftIO swift(stream2);
	swiftIO_packet_t *packet_in;
	pSwift = &swift;

	// Analog
	CAdc::init();
	CAdc::enable();

	// PWM
	swPWM pwm(TIMER_1);
	pwm.period(0.02);	// 20ms
	pwm.enable();

	// Interrupt Task
	CList 	m_interrupts;
	CThread thread(senseTask, &m_interrupts);
	thread.start("irq", 96, PRI_HARDWARE);

	CTimeout tm;

	//
    // Enter main loop.
	//
    while(1) {

		if ( swift.isConnected() ) {
			if ( (packet_in = swift.read()) != NULL ) {
				switch(packet_in->opcode) {
				case OP_DO_SET:{
					// data[0] : pin number
					// data[1] : pin value  0=LOW, 1=HIGH
					uint8_t pin = packet_in->data[0];
					CPin DO(pin);
					DO.output((PIN_LEVEL_T) packet_in->data[1]);
					}break;

				case OP_DI_GET:{
					// data[0] : pin number
					// data[1] : pin Input Mode
					uint8_t pin = packet_in->data[0];
					CPin DI(pin);
					DI.input((PIN_INPUT_MODE_T) packet_in->data[1]);
					// reply
					uint8_t data[2];
					data[0] = pin;
					data[1] = DI.read();
					swift.send(OP_DI_GET, sizeof(data), data);
					}break;

				case OP_AD_REF: {
					CAdc::disable();
					CAdc::reference((AREF_T)packet_in->data[0]);
					CAdc::source((ADC_SOURCE_T)packet_in->data[1]);
					CAdc::enable();
					}break;

				case OP_AD_GET: {
					uint8_t pin = packet_in->data[0];
					uint8_t data[3];
					uint16_t value = 0;
					data[0] = pin;
					if ( pin > 0 && pin <= 6 ) {
						if ( CAdc::read(analog_pin[pin], value) ) {
							memcpy(data+1, &value, sizeof(value));
						}
					} else {
						if ( CAdc::read(value) ) {
							memcpy(data+1, &value, sizeof(value));
						}
					}
					swift.send(OP_AD_GET, sizeof(data), data);
					}break;

				case OP_PWM_SET: {	// set PWM period (ms)
					float second;
					memcpy(&second, packet_in->data, sizeof(second));
					pwm.period(second);
					}break;

				case OP_PWM_OUT: {
					uint8_t pin = packet_in->data[0];
					float second;
					memcpy(&second, packet_in->data+1, sizeof(second));
					pwm.pulsewidth(pin, second);
					}break;

				case OP_INT_SET: {
					uint8_t pin = packet_in->data[0];
					uint8_t sense = packet_in->data[1];
					uint8_t mode = packet_in->data[2];
					gpioSense *irq = new gpioSense(pin, (SENSE_T)sense, (PIN_INPUT_MODE_T)mode);
					irq->enable();
					m_interrupts.addHead(irq);
					}break;

				case OP_INT_DEL: {
					uint8_t pin = packet_in->data[0];
					for (uint8_t index=0; index<m_interrupts.count(); index++) {
						gpioSense *irq = (gpioSense *) m_interrupts.getAt(index);
						if ( irq != NULL && irq->pin() == pin ) {
							m_interrupts.removeAt(index);
							delete irq;
							break;	// exit for-loop
						}
					}
					}break;

				}
				// free packet_in & data
				delete packet_in->data;
				delete packet_in;
			}
		}

		if ( tm.isExpired(500) ) {
			tm.reset();
			led.invert();
		}
    	//
    	// Negotiate the "connection parameters update" in main-loop
    	//
    	conn.negotiate();
    }
}
