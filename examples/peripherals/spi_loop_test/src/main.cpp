/*
===============================================================================
 Name        : SPI Loop Test
 Author      : uCXpresso
 Version     : v1.0.0
 Copyright   : www.ucxpresso.net
 License	 : MIT
 Description : A SPI loop test example
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/16 v1.0.0	First Edition.									Jason
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
#include <class/pin.h>
#include <class/spi_master.h>
#include <class/timeout.h>

// TODO: insert other definitions and declarations here
#define TX_RX_MSG_LENGTH	16
static uint8_t m_tx_data_spi[TX_RX_MSG_LENGTH]; /**< SPI master TX buffer. */
static uint8_t m_rx_data_spi[TX_RX_MSG_LENGTH]; /**< SPI master RX buffer. */


/**@brief The function initializes TX buffer to values to be sent and clears RX buffer.
 *
 * @note Function initializes TX buffer to values from 0 to (len - 1).
 *       and clears RX buffer (fill by 0).
 *
 * @param[out] p_tx_data    A pointer to a buffer TX.
 * @param[out] p_rx_data    A pointer to a buffer RX.
 * @param[in] len           A length of the data buffers.
 */
static void init_buf(uint8_t * const p_tx_buf,
                     uint8_t * const p_rx_buf,
                     const uint16_t len)
{
    uint16_t i;
    for (i = 0; i < len; i++)
    {
        p_tx_buf[i] = i;
        p_rx_buf[i] = 0;
    }
}

/**@brief Function for checking if buffers are equal.
 *
 * @note Function compares each element of p_tx_buf with p_rx_buf.
 *
 * @param[in] p_tx_data     A pointer to a buffer TX.
 * @param[in] p_rx_data     A pointer to a buffer RX.
 * @param[in] len           A length of the data buffers.
 *
 * @retval true     Buffers are equal.
 * @retval false    Buffers are different.
 */
static bool check_buf_equal(const uint8_t * const p_tx_buf,
                            const uint8_t * const p_rx_buf,
                            const uint16_t len)
{
    uint16_t i;
    for (i = 0; i < len; i++)
    {
        if (p_tx_buf[i] != p_rx_buf[i])
        {
            return false;
        }
    }
    return true;
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
	// Your setup code here
	//
	CPin led0(18);	// Declare led0 on P0.18
	CPin led1(19);
	led0.output();
	led1.output();

	spiMaster spi;	// default pins: mosi=21, miso=22, ssl=23, sck=24
	spi.enable();

	CTimeout tm;
	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Your loop code here
    	//

    	init_buf(m_tx_data_spi, m_rx_data_spi, TX_RX_MSG_LENGTH);

    	if ( spi.transfer(m_tx_data_spi, m_rx_data_spi, TX_RX_MSG_LENGTH)==NRF_SUCCESS ) {
    		if ( check_buf_equal(m_tx_data_spi, m_rx_data_spi, TX_RX_MSG_LENGTH) ) {
    			led1 = LED_ON;
    		} else {
    			led1 = LED_OFF;
    		}
    	} else led1 = LED_OFF;

    	//
    	// blink led
    	//
    	if ( tm.isExpired(500) ) {
    		tm.reset();
    		led0.invert();
    	}
    }
}
