#include "aes_cbc.h"

static uint8_t IV[16] = {0};

static cypher_t* block_padding(cypher_t* origin);

cypher_t* block_padding(cypher_t* origin)
{
	cypher_t* ret;
	if (origin->len_data == 0){
		ret = (cypher_t*)malloc(sizeof(uint8_t) + 16);
		ret->len_data = 16;
		memset(ret->data, 0, ret->len_data);
	}
	else if (origin->len_data %16 != 0){
		uint8_t blocks = origin->len_data / 16 + 1;
		ret = (cypher_t*)malloc(sizeof(uint8_t) + blocks * 16);
		ret->len_data = blocks * 16;
		memset(ret->data, 0, ret->len_data);
		memcpy(ret->data, origin->data, origin->len_data);
	}
	else if (origin->len_data % 16 == 0){
		ret = (cypher_t*)malloc(sizeof(uint8_t) + origin->len_data);
		ret->len_data = origin->len_data;
		memset(ret->data, 0, ret->len_data);
		memcpy(ret->data, origin->data, origin->len_data);
	}
	return ret;
}

void set_iv(uint8_t* iv)
{
	memcpy(IV, iv, 16);
}


cypher_t* aes_cbc_encrypt(uint8_t* key, cypher_t* data_in)
{
	//pad last block with 0
	cypher_t* data_in_padding = block_padding(data_in);
	cypher_t* cypher_out = (cypher_t*)malloc(sizeof(uint8_t) + data_in->len_data);
	cypher_out->len_data = data_in_padding->len_data;
	
	uint8_t iv[16] = {0};
	memcpy(iv, IV, 16);
	uint8_t temp_out[16] = {0};
	for (uint8_t index = 0; index < data_in_padding->len_data/16 ; ++index){
		array_xor(16, temp_out, data_in_padding->data + (index * 16), iv);		//明文与iv异或
		_aes128_encryption(key, cypher_out->data + index * 16, temp_out);		//进行块加密得到密文，同时密文是下次加密的iv
		memcpy(iv, cypher_out->data + index * 16, 16);							//本次的密文是下次加密的iv
	}
	free(data_in_padding);
	return cypher_out;
}

cypher_t* aes_cbc_decrypt(uint8_t* key, cypher_t* data_in)
{
	cypher_t* cypher_padding = block_padding(data_in);
	cypher_t* plain = (cypher_t*)malloc(data_in->len_data);
	plain->len_data = cypher_padding->len_data;
	uint8_t iv[16] = {0};
	memcpy(iv, IV, 16);
	uint8_t temp_out[16] = {0};
	for (uint8_t index = 0; index < cypher_padding->len_data/16 ; ++index){
		_aes128_decryption(key, temp_out, cypher_padding->data + (index*16));	//密文块解密
		array_xor(16, plain->data + (index*16), temp_out, iv);					//与iv异或得到明文
		memcpy(iv, cypher_padding->data + (index*16), 16);						//设置下次解密用到的iv
	}
	free(cypher_padding);
	return plain;
}

