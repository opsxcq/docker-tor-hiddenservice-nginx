#ifndef PRINT_H
#define PRINT_H

#include <openssl/rsa.h>

void base32_onion(char *dst, unsigned char *src);
void print_onion(char *onion);
void print_prkey(RSA *rsa);

#endif
