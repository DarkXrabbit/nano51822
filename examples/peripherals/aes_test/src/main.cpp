/*
===============================================================================
 Name        : aes_test
 Author      : uCXpresso
 Version     : v1.0.0
 Description : Explain how to exchange a public key.
===============================================================================
 	 	 	 	 	 	 	 	 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/28 v1.0.0	First Edition.									Jason
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
#include <class/power.h>
#include <class/pin.h>
#include <class/aes.h>
// TODO: insert other definitions and declarations here

const uint8_t plaintext[] = "0123456789abcdef0123456789abcdef0123456789abcdef";

const uint8_t private_key[] = {
		0x53, 0x46, 0x70, 0x69,
		0x26, 0x95, 0x79, 0x69,
		0x08, 0x09, 0x0A, 0x0B,
		0x0C, 0x0D, 0x0E, 0x0F
};

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
	// Optional: Enable tickless technology
	//
#ifndef DEBUG
	CPowerSave::tickless(true);
#endif

	//
	// buffer
	//
	uint8_t *ciphertext = new uint8_t[sizeof(plaintext)];
	uint8_t *cleartext = new uint8_t[sizeof(plaintext)];

	//
	// A private key for internal used.
	// use the same key in encrypt and decrypt objects.
	aesCTR encryptCTR(private_key);
	aesCTR decryptCTR(private_key);

	aesCFB encryptCFB(private_key, AES_ENCRYPT);
	aesCFB decryptCFB(private_key, AES_DECRYPT);

	uint32_t i;

	// create new random nonce block (public key)
	// assign the nonce block to decrypt object. it seem to exchange a random public key.
	decryptCTR = encryptCTR.new_nonce();

	// create new randmo IV block (public key)
	decryptCFB = encryptCFB.new_IV();

	//
    // Enter main loop.
	//
    while(1) {
    	//
    	// Debug the AES result
    	//
    	if ( dbg.available() && dbg.read()!=0x1B) {

    		//
    		// AES CTR
    		//
    		DBG("\n\nAES CTR Mode:\n");
    		// encryption
    		DBG("encryption:");
    		encryptCTR.crypt(ciphertext, plaintext, sizeof(plaintext));
    		for (i=0; i<sizeof(plaintext); i++) {
    			DBG("%02X ", ciphertext[i]);	// display the ciphertext contents
    		}

    		// decryption
    		DBG("\ndecryption:");
    		decryptCTR.crypt(cleartext, ciphertext, sizeof(plaintext));
    		for (i=0; i<sizeof(plaintext); i++) {
    			DBG("%02X ", cleartext[i]);		// display the cleartext contents
    		}

    		//
    		// AES CFB
    		//
    		DBG("\n\nAES CFB Mode:\n");
    		// encryption
    		DBG("encryption:");
    		encryptCFB.crypt(ciphertext, plaintext, sizeof(plaintext));
    		for (i=0; i<sizeof(plaintext); i++) {
    			DBG("%02X ", ciphertext[i]);	// display the ciphertext contents
    		}

    		// decryption
    		DBG("\ndecryption:");
    		decryptCFB.crypt(cleartext, ciphertext, sizeof(plaintext));
    		for (i=0; i<sizeof(plaintext); i++) {
    			DBG("%02X ", cleartext[i]);		// display the cleartext contents
    		}
    	}
    	sleep(100);	// give idle time for DFU button check.
    }
}
