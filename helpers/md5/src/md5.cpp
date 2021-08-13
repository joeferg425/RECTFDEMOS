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
#include "get_input.hpp"
#include "md5.hpp"

#define BUFSIZE 1024

int main(int argc, char **argv)
{
    // These vars will contain the hash
    unsigned char buf[16] = {0};
    unsigned char buffer_c[BUFSIZE] = {0};
    int buffer_c_len_i = 0;

    printf("md5\n");
    buffer_c_len_i = get_input(argc, argv, "Enter a string", buffer_c, BUFSIZE);

    md5((uint8_t*)buffer_c, buffer_c_len_i, buf);

    printf("%02X%02X%02X%02X", buf[ 0], buf[ 1], buf[ 2], buf[ 3]);
    printf("%02X%02X%02X%02X", buf[ 4], buf[ 5], buf[ 6], buf[ 7]);
    printf("%02X%02X%02X%02X", buf[ 8], buf[ 9], buf[10], buf[11]);
    printf("%02X%02X%02X%02X", buf[12], buf[13], buf[14], buf[15]);
    puts("");

    return 0;
}