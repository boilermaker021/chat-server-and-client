#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>


#include "types.h"


#define PORT 4130

int main() {
  struct sockaddr_in address;
  inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    printf("Socket error: %s\n", strerror(errno));
  }

  int status = connect(socket_fd, (struct sockaddr *)&address, sizeof(address));
  if (status < 0) {
    printf("Connect error: %s\n", strerror(errno));
  }

  message_t *msg = malloc(sizeof(message_t));
  status = recv(socket_fd, msg, sizeof(message_t), 0);
  ntohmsg(msg);

  printf("Sequence: %d\nType: %d\nString: %s\n", msg->sequence, msg->type, msg->contents);

}