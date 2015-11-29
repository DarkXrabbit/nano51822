/*
 ===============================================================================
 Name        : i2cdev.h
 Author      : uCXpresso
 Version     : v1.0.0
 Date		 : 2014/10/15
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : I2CDev class provide the I2C master interface
 ===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/10/15	v1.0.0	First Edition for nano51822						Jason
 ===============================================================================
 */

#ifndef I2CDEV_H_
#define I2CDEV_H_

#include <class/twi_master.h>

#define I2C_READ_BIT	1

#define DEF_I2C_DAT_PIN	28
#define DEF_I2C_CLK_PIN	29

/**
 * @brief The I2Cdev class provides the i2c interface and compatibility of i2cdevlib/i2cdev class.
 *
 * @class I2Cdev i2cdev.h "class/i2cdev.h"
 *
 * @ingroup Peripherals
 */
class I2Cdev: public twiMaster {
public:
	I2Cdev(int dat_pin=DEF_I2C_DAT_PIN, int clk_pin=DEF_I2C_CLK_PIN, TWI_FREQ_T freq=TWI_FREQ_100KHZ);

	/**
	 * @brief Read a single bit from an 8-bit device register.
	 * @param devAddr	I2C slave device address
	 * @param regAddr	Register regAddr to read from
	 * @param bitNum	Bit position to read (0-7)
	 * @param data		Container for single bit value
	 * @param timeout 	Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return
	 * @retval true 	If read successful.
	 */
	bool readBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data);

	/**
	 * @brief Read a single bit from a 16-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to read from
	 * @param bitNum Bit position to read (0-15)
	 * @param data Container for single bit value
	 * @param timeout Optional read timeout in milliseconds
	 * @return Status of read operation (I2C_OK = success)
	 */
	bool readBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t *data);

	/**
	 * @brief Read multiple bits from an 8-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to read from
	 * @param bitStart First bit position to read (0-7)
	 * @param length Number of bits to read (not more than 8)
	 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
	 * @param timeout Optional read timeout in milliseconds
	 * @return Status of read operation (I2C_OK = success)
	 */
	bool readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);

	/**
	 * @brief Read multiple bits from a 16-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to read from
	 * @param bitStart First bit position to read (0-15)
	 * @param length Number of bits to read (not more than 16)
	 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
	 * @param timeout Optional read timeout in milliseconds
	 * @return Status of read operation (I2C_OK = success)
	 */
	bool readBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data);

	/**
	 * @brief Read single byte from an 8-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to read from
	 * @param data Container for byte value read from device
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Status of read operation (I2C_OK = success)
	 */
	bool readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data);

	/** Read single word from a 16-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to read from
	 * @param data Container for word value read from device
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Status of read operation (I2C_OK = success)
	 */
	bool readWord(uint8_t devAddr, uint8_t regAddr, uint16_t *data);

	/**
	 * @brief Read multiple bytes from an 8-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr First register regAddr to read from
	 * @param length Number of bytes to read
	 * @param data Buffer to store read data in
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Status of read operation (I2C_OK = success)
	 */
	bool readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);

	/**
	 * @brief Read multiple words from a 16-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr First register regAddr to read from
	 * @param length Number of words to read
	 * @param data Buffer to store read data in
	 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
	 * @return Status of read operation (I2C_OK = success)
	 */
	bool readWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t *data);

	/**
	 * @brief write a single bit in an 8-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to write to
	 * @param bitNum Bit position to write (0-7)
	 * @param value New bit value to write
	 * @return Status of read operation (I2C_OK = success)
	 */
	bool writeBit(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint8_t value);

	/**
	 * @brief write a single bit in a 16-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to write to
	 * @param bitNum Bit position to write (0-15)
	 * @param value New bit value to write
	 * @return Status of operation (I2C_OK = success)
	 */
	bool writeBitW(uint8_t devAddr, uint8_t regAddr, uint8_t bitNum, uint16_t data);

	/**
	 * @brief Write multiple bits in an 8-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to write to
	 * @param bitStart First bit position to write (0-7)
	 * @param length Number of bits to write (not more than 8)
	 * @param data Right-aligned value to write
	 * @return Status of operation (I2C_OK = success)
	 */
	bool writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);

	/**
	 * @brief Write multiple bits in a 16-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register regAddr to write to
	 * @param bitStart First bit position to write (0-15)
	 * @param length Number of bits to write (not more than 16)
	 * @param data Right-aligned value to write
	 * @return Status of operation (I2C_OK = success)
	 */
	bool writeBitsW(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t data);

	/**
	 * @brief Write single byte to an 8-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register address to write to
	 * @param data New byte value to write
	 * @return Status of operation (I2C_OK = success)
	 */
	bool writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);

	/**
	 * @brief Write single word to a 16-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr Register address to write to
	 * @param data New word value to write
	 * @return Status of operation (I2C_OK = success)
	 */
	bool writeWord(uint8_t devAddr, uint8_t regAddr, uint16_t data);

	/**
	 * @brief Write multiple bytes to an 8-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr First register address to write to
	 * @param length Number of bytes to write
	 * @param data Buffer to copy new data from
	 * @return Status of operation (I2C_OK = success)
	 */
	bool writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* data);

	/**
	 * @brief Write multiple words to a 16-bit device register.
	 * @param devAddr I2C slave device address
	 * @param regAddr First register address to write to
	 * @param length Number of words to write
	 * @param data Buffer to copy new data from
	 * @return Status of operation (I2C_OK = success)
	 */
	bool writeWords(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint16_t* data);

};

/**\example /peripherals/i2c_scanner/src/main.cpp
 * This is an example of how to use the I2Cdev class.
 * More details about this example.
 */

#endif /* I2CDEV_H_ */
