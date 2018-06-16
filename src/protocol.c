#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>
#include <inttypes.h>

#include "protocol.h"

int parse_data(db_pkg *p, uint64_t payload_len)
{
        switch(p->cmd) {
        case PROTO_GET:
                return get(p, payload_len);
                break;
        case PROTO_PUT:
                return put(p, payload_len);
                break;
        case PROTO_GET_PTR:
                break;
        case PROTO_SET_PTR:
                break;
        case PROTO_SET_VISITED:
                break;
        default:
                return ERR_CMD;
                break;
        }

        return 0;
}

/*
 * Puts n amount of URLs into the database.
 *
 * +--------------------------------------+
 * | Byte | Type     | Content            |
 * | 0    | char     | command            |
 * | 1-9  | uint64_t | number URLs to put |
 * | 10>  | char*    | data               |
 * +--------------------------------------+
 *
 */
int put(db_pkg *p, uint64_t payload_len)
{
        printf("get\n");
        uint64_t links_read = 0;
        uint64_t i, url_len = 0;

        char *url = (char*) malloc(URL_MAX_LEN + 1);
        bzero(url, URL_MAX_LEN + 1);

        char cur_byte = 0, prev_byte = 0;

        printf("%" PRIu64 "\n", p->arg);

        for(i = 0; i < payload_len; i++) {
                cur_byte = p->payload[i];

                if (cur_byte == 0 && prev_byte == 0) {
                        return p->arg - links_read;
                } else if (cur_byte == 0 && prev_byte != 0) {
                        url[url_len] = cur_byte;
                        printf("%s\n", url);
                        free(url);
                        url = (char*) malloc(URL_MAX_LEN + 1);
                        bzero(url, URL_MAX_LEN + 1);

                        url_len = 0;
                        links_read++;
                } else {
                        url[url_len] = cur_byte;
                        url_len++;
                }

                if (cur_byte != 0 && url_len >= URL_MAX_LEN + 1) {
                        return ERR_GET_URL_OVERFLOW;
                }

                prev_byte = cur_byte;
        }

        return p->arg - links_read;
}

/*
 * Get n amount of not visited URLs
 *
 * +--------------------------------------+
 * | Byte | Type     | Content            |
 * | 0    | char     | command            |
 * | 1-9  | uint64_t | number URLs to get |
 * +--------------------------------------+
 *
 */
int get(db_pkg *p, uint64_t payload_len)
{
        return 0;
}

int get_ptr(char *data)
{
        return 0;
}

int set_ptr(char *data)
{
        return 0;
}

int set_visited(char *data)
{
        return 0;
}
