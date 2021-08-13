#include <stdio.h>
#include <string.h>
#include "get_input.hpp"
#include "crclike.hpp"

#define BUFSIZE 1024

int main(int argc, char **argv)
{
    unsigned char buffer_c[BUFSIZE] = {0};
    unsigned char buffer_ob_c[BUFSIZE] = {0};
    char c = 0;
    int buffer_c_len_i = 0;
    int buffer_ob_len_i = 0;

    printf("crclike\n");
    buffer_c_len_i = get_input(argc, argv, "Enter a string", buffer_c, BUFSIZE);

    printf("Input : ");
    for (int i = 0; i < buffer_c_len_i; i++)
    {
        printf("%c", buffer_c[i]);
    }
    printf(" (%d bytes)\n", buffer_c_len_i);

    xorit(buffer_c, buffer_c_len_i, buffer_ob_c, &buffer_ob_len_i);
    printf("Output: ");
    for (int i = 0; i < buffer_ob_len_i; i++)
    {
        printf("0x%02X, ", buffer_ob_c[i]);
    }
    printf(" (%d bytes)\n", buffer_ob_len_i);

    un_xorit(buffer_ob_c, buffer_ob_len_i, buffer_c, &buffer_c_len_i);
    printf("Revert: ");
    for (int i = 0; i < buffer_c_len_i; i++)
    {
        printf("%c", buffer_c[i]);
    }
    printf(" (%d bytes)\n", buffer_c_len_i);

    return 0;
}