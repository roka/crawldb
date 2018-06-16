#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdio.h>

#ifdef DEBUG
        #define debug_print(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__);
#else
        #define debug_print(fmt, ...) 
#endif

#define TOKEN_MAX_SIZE 255

extern char config_token[TOKEN_MAX_SIZE+1];
int set_token(char *token);

#endif
