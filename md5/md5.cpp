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
uint32_t h0, h1, h2, h3;

    if (argc < 2)
    {
        printf("usage: %s 'string'\n", argv[0]);
        return 1;
    }

    char *msg = argv[1];
    size_t len = strlen(msg);

    md5((uint8_t*)msg, len, &h0, &h1, &h2, &h3);
    // }

    //var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
    uint8_t *p;

    // display result

    p=(uint8_t *)&h0;
    printf("%2.2X%2.2X%2.2X%2.2X", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h1;
    printf("%2.2X%2.2X%2.2X%2.2X", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h2;
    printf("%2.2X%2.2X%2.2X%2.2X", p[0], p[1], p[2], p[3]);

    p=(uint8_t *)&h3;
    printf("%2.2X%2.2X%2.2X%2.2X", p[0], p[1], p[2], p[3]);
    puts("");

    return 0;
}