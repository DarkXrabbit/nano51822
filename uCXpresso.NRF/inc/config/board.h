/*
 * board pin assignment
 *
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <class/ble/ble_device.h>

#ifdef BOARD_NANO51822_UDK
#define BUTTON_PIN_0	0
#define BUTTON_PIN_1	30
#define LED_PIN_0		18
#define LED_PIN_1		19
#define LED_PIN_2		20
#define LED_PIN_3		21

// Board's Text No. to GPIO Pin No.
#define LED1			LED_PIN_0
#define LED2			LED_PIN_1
#define LED3			LED_PIN_2
#define LED4			LED_PIN_3
#define BTN1			BUTTON_PIN_0
#define	BTN2			BUTTON_PIN_1
#define P12				7
#define P13				12
#define P14				13
#define P15				14
#define P16				15
#define P17				16
#define P18				17
#define P19				22
#define P20				23
#define P24				24
#define P25				25
#define P30				30
#define SCL				28
#define SDA				29
#endif

#ifdef BOARD_LILYPAD
#define BUTTON_PIN_0	0		// DFU Button
#define LED_PIN_0		7
#define LED_PIN_1		20
#define LED1			LED_PIN_0
#define LED2			LED_PIN_1
#endif

#ifdef BOARD_PCA10001
#define BUTTON_PIN_0	16
#define BUTTON_PIN_1	17
#define LED_PIN_0		18
#define LED_PIN_1		19
#define LED_PIN_2		20
#define LED_PIN_3		21
#define LED_PIN_4		22
#endif

#endif /* BOARD_H_ */
