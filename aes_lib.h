#ifndef _AES_LIB_H
#define _AES_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/*
 * Advanced Encryption Standard
 * @author Dani Huertas
 * @email huertas.dani@gmail.com
 *
 * Based on the document FIPS PUB 197
 */

typedef struct _cypher_t{
	uint8_t len_data;
	uint8_t data[0];
}cypher_t;

extern void array_xor(int len, unsigned char*des, unsigned char*a1, unsigned char* a2);

extern int _aes128_encryption(unsigned char* key, unsigned char* ciphertext, unsigned char* plaintext);

extern int _aes128_decryption(unsigned char* key, unsigned char* plain_text, unsigned char* cypher);

#endif // _AES_LIB_H
