/*
 ===============================================================================
 Name        : twi_master.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/15
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : Provide the Two wires BUS I/O
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/15	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef TWI_MASTER_H_
#define TWI_MASTER_H_

#include <class/peripheral.h>

#define DEF_TWI_CLK_PIN	29
#define DEF_TWI_DAT_PIN	28

typedef enum {
	TWI_FREQ_100KHZ	= 0x01980000UL,
	TWI_FREQ_250KHZ = 0x04000000UL,
	TWI_FREQ_400KHZ = 0x06680000UL
}TWI_FREQ_T;

const TWI_FREQ_T twi_freqs[] = {TWI_FREQ_100KHZ, TWI_FREQ_250KHZ, TWI_FREQ_400KHZ};

#define TWI_READ_BIT	0

class twiMaster: public CPeripheral {
public:
	/**
	 * @brief twiMaster class constructor.
	 *
	 * @param dat_pin Specify a data pin number.
	 * @param clk_pin Specify a clock pin number.
	 */
	static void init(int dat_pin, int clk_pin, TWI_FREQ_T freq);

	/**
	 * @brief To enable the two wires interface.
	 *
	 * @param freq To enable the twi with the @ref TWM_FREQ_T frequency.
	 *
	 * @return
	 * @retval	true 	If enable successful.
	 * @retval	false	If enable failed.
	 */
	static bool enable();

	/**
	 * @brief To disable the two wires interface.
	 */
	static void disable();

	/**
	 * @brief Function for transferring data over TWI bus.
	 *
	 * If TWI master detects even one NACK from the slave or timeout occurs, STOP condition is issued
	 * and the function returns false.
	 * Bit 0 (@ref TWI_READ_BIT) in the address parameter controls transfer direction;
	 * - If 1, master reads data_length number of bytes from the slave
	 * - If 0, master writes data_length number of bytes to the slave.
	 *
	 * @note Make sure at least data_length number of bytes is allocated in data if TWI_READ_BIT is set.
	 * @note @ref TWI_ISSUE_STOP
	 *
	 * @param address Data transfer direction (LSB) / Slave address (7 MSBs).
	 * @param data Pointer to data.
	 * @param length Number of bytes to transfer.
	 * @param issue_stop_condition If true, STOP condition is issued before exiting function.
	 * If false, STOP condition is not issued before exiting function.
	 * If transfer failed for any reason, STOP condition will be issued in any case.
	 *
	 * @return
	 * @retval true Data transfer succeeded without errors.
	 * @retval false Data transfer failed.
	 */
	static bool transfer(uint8_t address, uint8_t *data, uint8_t length, bool issue_stop_condition);
};

#endif /* TWI_MASTER_H_ */
