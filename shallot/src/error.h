#ifndef ERROR_H
#define ERROR_H

#include "config.h"

#include <stdint.h>

// error codes
#define X_WRONG_NUMARGS 0x01
#define X_REGEX_COMPILE 0x02
#define X_REGEX_INVALID 0x03
#define X_SGNL_INT_TERM 0x04
#define X_YOURE_UNLUCKY 0x05
#define X_KEY_GEN_FAILS 0x06
#define X_THREAD_CREATE 0x07
#define X_BIGNUM_FAILED 0x08
#define X_INVALID_THRDS 0x09
#define X_EXCLUSIVE_OPT 0x0A
#define X_INVALID_E_LIM 0x0B
#define X_NEED_FILE_OUT 0x0C
#define X_FILE_OPEN_ERR 0x0D
#define X_DAEMON_FAILED 0x0E
#define X_OUT_OF_MEMORY 0x11
#define X_MAXTIME_REACH 0x12


#ifdef BSD
  // BSD specific defines
  #define X_SYSCTL_FAILED 0x0F
#elif defined(LINUX_PORT)
  // Linux specific defines
  #define X_BAD_FILE_DESC 0x0F
  #define X_ABNORMAL_READ 0x10
#endif

void usage(void);
void pattern(void);
void error(int32_t code);

#endif

