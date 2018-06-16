#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "config.h"

#ifndef TEST

int main(int argc, char *argv[])
{
        char c;

        while ((c = getopt (argc, argv, "t:")) != -1) {
                switch(c) {
                case 't':
                        set_token(optarg);
                        debug_print("token=%s\n", config_token);
                        break;
                }
        }
}

#endif
