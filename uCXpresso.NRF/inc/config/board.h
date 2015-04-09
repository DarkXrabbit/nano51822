/*
 * board pin define
 *
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <class/ble/ble_device.h>

#ifdef BOARD_LILYPAD
#define BUTTON_PIN_0	0		// DFU Button
#define LED_PIN_0		7
#define LED_PIN_1		20
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

#ifdef BOARD_NANO51822_UDK
#define BUTTON_PIN_0	0
#define BUTTON_PIN_1	30
#define LED_PIN_0		18
#define LED_PIN_1		19
#define LED_PIN_2		20
#define LED_PIN_3		21
#endif

#endif /* BOARD_H_ */
