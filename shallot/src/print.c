// printing functions for shallot

#include "config.h"

#include "print.h"
#include "defines.h"
#include "globals.h"
#include "error.h"

#include <stdio.h>
#include <string.h>
#include <openssl/pem.h>

// endian crap for htobe16() [only needed
// for base32_onion which should be moved] {
#include <stdint.h> // OpenBSD needs this included before sys/endian.h

#if defined(LINUX_PORT) || defined(OSX) || defined(GENERIC)
  #include "linux.h"
#else
  #include <sys/param.h> // OpenBSD needs this early on too
  #include <sys/endian.h>
#endif
// }

// TODO: Move to math.c?
void base32_onion(char *dst, unsigned char *src) { // base32-encode hash
  uint8_t byte = 0,   // dst location
          offset = 0; // bit offset
  for(; byte < BASE32_ONIONLEN; offset += 5) {
    if(offset > 7) {
      offset -= 8;
      src++;
    }
    dst[byte++] = BASE32_ALPHABET[(htobe16(*(uint16_t*)src) >> (11-offset))
                                  & (uint16_t)0x001F];
  }
  dst[byte] = '\0';
}

void print_onion(char *onion) { // pretty-print hash
  uint8_t i;
  char *s;
  #ifdef GENERIC
  s = malloc(PRINT_ONION_MAX);
  snprintf(s, PRINT_ONION_MAX, PRINT_ONION_STR, loop, onion);
  #else
  if (asprintf(&s, PRINT_ONION_STR, loop, onion) == -1)
		error(X_OUT_OF_MEMORY);
  #endif
  for(i=0; i<strlen(s); i++)
    printf("-"); // TODO: use fputc()?
  printf("\n%s\n", s);
  for(i=0; i<strlen(s); i++)
    printf("-"); // TODO: use fputc()?
  printf("\n");
  free(s);
}

void print_prkey(RSA *rsa) { // print PEM formatted RSA key
  BUF_MEM *buf;
  BIO *b = BIO_new(BIO_s_mem());
  PEM_write_bio_RSAPrivateKey(b, rsa, NULL, NULL, 0, NULL, NULL);
  BIO_get_mem_ptr(b, &buf);
  (void)BIO_set_close(b, BIO_NOCLOSE);
  BIO_free(b);
  char *dst = malloc(buf->length+1);
  strncpy(dst, buf->data, buf->length);
  dst[buf->length] = '\0';
  printf("%s", dst);
  BUF_MEM_free(buf);
}

