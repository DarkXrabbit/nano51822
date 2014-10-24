/*
 * board pin define
 *
 */

#ifndef BOARD_H_
#define BOARD_H_

#ifdef BOARD_LILYPAD
#define LED_PIN_0		7
#define LED_PIN_1		20
#endif

#ifdef BOARD_PCA10001
#define BUTTON_PIN_0	16
#define BUTTON_PIN_1	17
#define LED_PIN_0		18
#define LED_PIN_1		19
#endif

#endif /* BOARD_H_ */
