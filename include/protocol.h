#ifndef __PROTOCOL_H_
#define __PROTOCOL_H_

#define URL_MAX_LEN 2048

#define PROTO_PUT     0x65 // char[URL_MAX_LEN] url
#define PROTO_GET     0x66 // uint64_t n
#define PROTO_GET_PTR 0x67
#define PROTO_SET_PTR 0x68 // uint64_t ptr
#define PROTO_SET_VISITED 0x69 // char[URL_MAX_LEN]

#define ERR_CMD 0x01

#define ERR_GET_URL_OVERFLOW -1

#include <stdint.h>

typedef struct {
        char cmd;
        uint64_t arg;
        char *payload;
} db_pkg;


int put(db_pkg *p, uint64_t payload_len);
int get(db_pkg *p, uint64_t payload_len);

#endif
