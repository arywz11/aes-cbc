## aes-cbc模式加密——密码分组链接模式（Cipher Block Chaining (CBC)）
aes-cbc模式加密和解密代码

##编译和运行
make
./app.out




输出：
>
密钥：01 02 03 04  0a 0b 0c 0d  00 00 00 00  ff ff ff ff 
明文：hello aes_cbc encryption!
>
密文:
76 ae bb ed  d2 c3 a6 16  00 4a 4b 3b  33 67 96 07
85 7c 70 c5  0b 7e f2 b6  75 ff fc 67  f4 99 c0 8a 
>
解密之后:
68 65 6c 6c  6f 20 61 65  73 5f 63 62  63 20 65 6e  
63 72 79 70  74 69 6f 6e  21 00 00 00  00 00 00 00 
>
解密之后的明文字符串输出:
 hello aes_cbc encryption!


注：aes加密解密函数来源于互联网