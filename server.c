#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>


#include "types.h"


#define PORT 4130

void *handle_connection(void *param) {
  int sockfd = *((int *)param);
  message_t msg = {.type = MESSAGE, .sequence = 0};
  strcpy(&msg.contents, "This is a test message");

  htonmsg(&msg);
  send(sockfd, &msg, sizeof(message_t), 0);


  close(sockfd);
}

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
  pthread_t *thread_array = malloc(sizeof(pthread_t) * 8);
  unsigned int thread_array_size = 8;
  unsigned int thread_index = 0;
  while (thread_index < thread_array_size) {
    int conn_fd = accept(listen_fd, (struct sockaddr *)&address, &sizeof_address);
    if (conn_fd < 0) {
      printf("Accept error: %s\n", strerror(errno));
    }

    pthread_create(&thread_array[thread_index], NULL, &handle_connection, ((void *)&conn_fd));
    thread_index++;
  }

  close(listen_fd);
}