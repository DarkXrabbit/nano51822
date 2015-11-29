/*
 ===============================================================================
 Name        : aes_ecb
 Author      : Jason
 Version     : v1.0.1
 Date		 : 2014/11/30
 Copyright   : Copyright (C) www.embeda.com.tw
 Description : AES ECB encryption
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/28	v1.0.0	First Edition for CTR mode.		 				Jason
 2014/11/30 v1.0.1	Add CFB mode.									Jason
 ===============================================================================
 */

#ifndef CLASS_AES_H_
#define CLASS_AES_H_

#include <string.h>
#include <class/object.h>

#define AES_BLOCK_SIZE	16

/**
 * @brief AES mode selection
 * @ingroup Enumerations
 */
enum AES_MODE_T {
	AES_DECRYPT,	///< AES decryption
	AES_ENCRYPT		///< AES encryption
};

/**
 * @brief 128-bit AES ECB encryption base class.
 * @class AES128 aes.h	"class/aes.h"
 * @ingroup Peripherals
 */
class AES128: public CObject {
public:
	AES128(uint8_t const *key);

	/**
	 * @brief Encrypts a block according to the specified parameters.
	 * @param[in] cleartext Pointer to the cleartext contents.
	 *
	 * @retval ::NRF_SUCCESS
	 */
	uint32_t encrypt(uint8_t *cleartext);

	/**
	 * @brief Pointer to the ciphertext contents after encryption.
	 */
	uint8_t* ciphertext();

	/**
	 * @brief Pointer to the cleartext contents.
	 */
	uint8_t* cleartext();

	/**
	 * @brief Pointer to the key of AES.
	 */
	uint8_t* key();

	inline bool isValid() {
		return (m_handle!=NULL ? true : false);
	}

	//
	///@cond
	//
	~AES128();
protected:
	xHandle	 	m_handle;
	///@endcond
};

/**
 * @brief AES 128 counter mode encryption/decryption service class.
 * @class aesCTR aes.h	"class/aes.h"
 * @ingroup Peripherals
 */
class aesCTR: public AES128 {
public:
	/**
	 * @brief aesECB constructor
	 * @param[in] key A 128 bits (16 bytes) private KEY.
	 */
	aesCTR(uint8_t const *key);

	/**
	 * @brief Encrypt/Decrypt data by AES CTR mode.
	 *
	 * @param output Result of encryption/decryption.
	 * @param input  Source data to be encrypted/decrypted.
	 * @param length The size of the data.
	 *
	 * @return NRF_SUCCESS if the crypt operation completed.
	 */
	virtual uint32_t crypt(uint8_t *output, uint8_t const *input, uint16_t length);

	/**
	 * @brief Generate a new nonce block.
	 * @return Pointer to the m_nonce.
	 */
	uint8_t* new_nonce();

	/**
	 * @brief Pointer to the m_nonce.
	 */
	inline uint8_t* get_nonce() {
		return cleartext();
	}

	/**
	 * @brief Assign a nonce block, and reset session
	 */
	inline void set_nonce(uint8_t *p_nonce) {
		memcpy(get_nonce(), p_nonce, AES_BLOCK_SIZE);
		m_offset = 0;
	}

	/**
	 * @brief Shorthand operator to assign the nonce block of CTR.
	 */
	inline void operator = (uint8_t *p_nonce) {
		set_nonce(p_nonce);
	}

	//
	///@cond PRIVATE
	//
protected:
	uint8_t		m_offset;
	///@endcond
};


/**
 * @brief AES 128 CFB mode encryption/decryption service class.
 * @class aesCFB aes.h	"class/aes.h"
 * @ingroup Peripherals
 */
class aesCFB : public AES128 {
public:
	/**
	 * @brief Constructs the aesCFB object.
	 * @param[in] key  A 128 bits (16 bytes) private KEY.
	 * @param[in] mode Specifies the CFB mode to @ref AES_MODE_T.
	 */
	aesCFB(uint8_t const *key, AES_MODE_T mode);

	/**
	 * @brief Encrypt/Decrypt data by AES CFB mode.
	 *
	 * @param output Result of encryption/decryption.
	 * @param input  Source data to be encrypted/decrypted.
	 * @param length The size of the data.
	 *
	 * @return NRF_SUCCESS if the crypt operation completed.
	 */
	virtual uint32_t crypt(uint8_t *output, uint8_t const *input, uint16_t length);

	/**
	 * @brief Creates a random "Initialization Vector" of CFB.
	 */
	uint8_t* new_IV();

	/**
	 * @brief Retrieve the current "Initialization Vector" of CFB.
	 */
	inline uint8_t* get_IV() {
		return cleartext();
	}

	/**
	 * @brief Assign the "Initialization Vector" of CFB, and reset session.
	 */
	inline void set_IV(uint8_t *p_IV) {
		memcpy(get_IV(), p_IV, AES_BLOCK_SIZE);
		m_offset = 0;
	}

	/**
	 * @brief Shorthand operator to assign the IV of CFB.
	 */
	inline void operator = (uint8_t *p_IV) {
		set_IV(p_IV);
	}

protected:
	uint8_t 	m_offset;
	AES_MODE_T 	m_mode;
	///@endcond
};

/**\example /peripherals/aes_test/src/main.cpp
 * This is an example of how to use the AES 128 encryption/decryption services.
 * More details about this example.
 */

#endif /* CLASS_AES_H_ */
