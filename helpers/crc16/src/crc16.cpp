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
#include "get_input.hpp"

// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))

#define BUFSIZE 512
#define CRC_POLYNOMIAL 0x18005

int main(int argc, char **argv)
{
    // will contain the checksum
    unsigned short crc = 0;
    unsigned char buffer_c[BUFSIZE] = {0};
    int buffer_c_len_i = 0;

    printf("crc16\n");
    buffer_c_len_i = get_input(argc, argv, "Enter a string", buffer_c, BUFSIZE);

    crc16((uint8_t*)buffer_c, buffer_c_len_i, &crc, CRC_POLYNOMIAL);

    printf("%04X", crc);
    puts("");

    return 0;
}