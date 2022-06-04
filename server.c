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
  int sizeof_address = sizeof(address);
  address.sin_port = htons(PORT);
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;

  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);

  int status = bind(listen_fd, (struct sockaddr *)&address, sizeof(address));
  if (status < 0) {
    printf("Bind error: %s\n", strerror(errno));
  }

  status = listen(listen_fd, 4);
  if (status < 0) {
    printf("Listen error: %s\n", strerror(errno));
  }

  int conn_fd = accept(listen_fd, (struct sockaddr *)&address, &sizeof_address);
  if (conn_fd < 0) {
    printf("Accept error: %s\n", strerror(errno));
  }

  message_t msg;
  msg.sequence = 1;
  msg.type = MESSAGE;
  strcpy(msg.contents, "This is a test"); //buffer overflow fix later

  htonmsg(&msg);
  send(conn_fd, &msg, sizeof(msg), 0);

}