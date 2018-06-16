#include <string.h>

#include "config.h"

char config_token[TOKEN_MAX_SIZE+1] = {0};

int set_token(char *token)
{
        bzero(config_token, TOKEN_MAX_SIZE+1);
        strncpy(config_token, token, TOKEN_MAX_SIZE-1);
        return 0;
}
