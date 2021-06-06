// originally from https://gist.github.com/creationix/4710780

/*
 * Simple MD5 implementation
 *
 * Compile with: gcc -o md5 -O3 -lm md5.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "md5.hpp"

// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))



int main(int argc, char **argv)
{
    // These vars will contain the hash
    unsigned char buf[16] = {0};

    if (argc < 2)
    {
        printf("usage: %s 'string'\n", argv[0]);
        return 1;
    }

    char *msg = argv[1];
    size_t len = strlen(msg);

    md5((uint8_t*)msg, len, buf);

    printf("%02X%02X%02X%02X", buf[ 0], buf[ 1], buf[ 2], buf[ 3]);
    printf("%02X%02X%02X%02X", buf[ 4], buf[ 5], buf[ 6], buf[ 7]);
    printf("%02X%02X%02X%02X", buf[ 8], buf[ 9], buf[10], buf[11]);
    printf("%02X%02X%02X%02X", buf[12], buf[13], buf[14], buf[15]);
    puts("");

    return 0;
}