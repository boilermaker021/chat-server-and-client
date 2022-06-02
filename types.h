#ifndef TYPES_H
#define TYPES_H


enum type {
  LOGIN,
  LOGOUT,
  MESSAGE
};


typedef struct message {
  enum type type;
  unsigned short sequence;
  char contents[2048];
} message_t;


int checkbyteorder();


#endif