#ifndef _AES_CCM_H_
#define _AES_CCM_H_

#include "aes_lib.h"
#include <memory.h>
#include <string.h>

extern void set_iv(uint8_t* iv);

extern cypher_t* aes_cbc_encrypt(uint8_t* key, cypher_t* plain);

extern cypher_t* aes_cbc_decrypt(uint8_t* key, cypher_t* cypehr);

#endif
