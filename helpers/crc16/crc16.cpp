/*
 * Simple MD5 implementation
 *
 * Compile with: gcc -o md5 -O3 -lm md5.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "crc16.hpp"

// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

#define CRC_POLYNOMIAL 0x18005

int main(int argc, char **argv)
{
    // will contain the checksum
    unsigned short crc = 0;

    if (argc < 2)
    {
        printf("usage: %s 'string'\n", argv[0]);
        return 1;
    }

    char *msg = argv[1];
    size_t len = strlen(msg);

    crc16((uint8_t*)msg, len, &crc, CRC_POLYNOMIAL);

    printf("%04X", crc);
    puts("");

    return 0;
}