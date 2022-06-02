#include <stdlib.h>
#include <endian.h>
#include <byteswap.h>

#include "types.h"


#define ntohs(message) htonmsg(message); //same function;

void htonmsg(message_t *message) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  message->type = bswap_32(message->type);
  message->sequence = bswap_16(message->sequence);
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
  return; //already in network order
#endif
}
