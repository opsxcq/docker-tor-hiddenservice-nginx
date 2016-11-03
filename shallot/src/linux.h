#ifndef LINUX_H
#define LINUX_H

#include "config.h"

#if defined(LINUX_PORT) || defined(OSX) || defined(GENERIC)

#include <stdint.h>

#if defined(OSX) || defined(GENERIC)
  #include <arpa/inet.h>
#else
  #include <endian.h>
  #include <netinet/in.h>
#endif

#ifndef htobe64
	#if BYTE_ORDER == BIG_ENDIAN
		#warning Compiling for a BIG_ENDIAN system.
		#define htobe64(x) (x)
		#define htobe16(x) (x)

	#elif BYTE_ORDER == LITTLE_ENDIAN
		#warning Compiling for a LITTLE_ENDIAN system.
		#define htobe64(x) (((uint64_t)htonl(x) << 32) | htonl(x >> 32))
		#define htobe16(x) htons(x)

	#else
		#error Sell your PDP.
	#endif
#endif

#ifdef LINUX_PORT
uint8_t parse_cpuinfo(char *buf, uint16_t avail, uint16_t *used);
#endif

#endif // defined(LINUX_PORT) || defined(OSX) || defined(GENERIC)

#endif
