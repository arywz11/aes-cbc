#include "aes_cbc.h"

int main()
{
	uint8_t key[16] = {
		0x01, 0x02, 0x03, 0x04, 0x0a, 0x0b, 0x0c, 0x0d, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff
	};
	uint8_t iv[16] = {
		0xa, 0xb, 0xc, 0xd, 0x1, 0x2, 0x3, 0x3, 0xa, 0xa, 0xa, 0xa, 0xf, 0xf, 0xf, 0xf
	};
	uint8_t* text = "hello aes_cbc encryption!";
	
	printf("密钥：");
	for (int i = 0; i < 16; ++i){
		if (i%4 == 0 && i != 0)
			printf(" ");
		if (i % 16 == 0 && i != 0)
			printf("\n");
		printf("%02x ", key[i]);
	}
	printf("\n");
	printf("明文：%s\n\n", text);

	set_iv(iv);
	//--------------------------aes cbc encrypt--------------------------------------
	cypher_t* plain = (cypher_t*)malloc(sizeof(uint8_t) + strlen(text));
	plain->len_data = strlen(text);
	memcpy(plain->data, text, plain->len_data);
	cypher_t* cypher = aes_cbc_encrypt(key, plain);
	puts("密文:");
	for (int i = 0; i < cypher->len_data; ++i){
		if (i%4 == 0 && i != 0)
			printf(" ");
		if (i % 16 == 0 && i != 0)
			printf("\n");
		printf("%02x ", cypher->data[i]);
		
	}
	printf("\n\n");
	free(plain);
	//--------------------------aes cbc decrypt--------------------------------------
	cypher_t* decrypted_plain = aes_cbc_decrypt(key, cypher);
	puts("解密之后:");
	for (int i = 0; i < decrypted_plain->len_data; ++i){
		if (i%4 == 0 && i != 0)
			printf(" ");
		if (i % 16 == 0 && i != 0)
			printf("\n");
		printf("%02x ", decrypted_plain->data[i]);
	}
	printf("\n\n");
	printf("解密之后的明文字符串输出:\n%s", decrypted_plain);
	printf("\n\n");
	free(decrypted_plain);
	return 0;
}
