// Linux-specific stuff for shallot

#include "linux.h"

#ifdef LINUX_PORT

#include "defines.h"
#include <string.h>

// Linux-specific stuff (damn this is ugly code.  blame Linus.)
uint8_t parse_cpuinfo(char *buf, uint16_t avail, uint16_t *used) {
  uint16_t x = 0;
  char procsfound = 0;
  static uint8_t skip = 0;

  if(!skip) {
    if(memcmp(&CPUINFO_PROC_STR, buf, CPUINFO_PROC_STR_LEN) == 0)
      procsfound++;
  }

  while((buf[x] != 0) && (x < avail)) {
    if(x) {
      if(buf[x - 1] == '\n') {
        break;
      }
    }
    x++;
  }

  *used = x;

  if(!x)
    return 0; // prevent the next if statement from causing a buffer overflow

  if((x == avail) && (buf[x - 1] != '\n'))
    skip = 1;
  else
    skip = 0;

  return procsfound;
}

#endif

