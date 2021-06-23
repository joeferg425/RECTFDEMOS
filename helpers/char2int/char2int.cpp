/*
This obfuscation project simply converts ascii to hexadecimal values and combines 4 8-chars into one 32-bit int.
*/
#include <stdio.h>
#include <string.h>
#include "get_input.hpp"
#include "char2int.hpp"

#define BUFSIZE 1024

int main(int argc, char** argv)
{
    unsigned char buffer_c[BUFSIZE] = {0};
    unsigned int buffer_i[BUFSIZE] = {0};
    char c = 0;
    int buffer_c_len_i = 0;
    int buffer_i_len_i = 0;

    printf("char2int\n");
    buffer_i_len_i = get_input(argc, argv, "Enter a string", buffer_c, BUFSIZE);

    printf("Input : ");
    for (int i = 0; i < buffer_c_len_i; i++)
    {
        printf("%c", buffer_c[i]);
    }
    printf(" (%d bytes)\n", buffer_c_len_i);

    char2int(buffer_c, buffer_c_len_i, buffer_i, &buffer_i_len_i);
    printf("Output: ");
    for (int i = 0; i < buffer_i_len_i; i++)
    {
        printf("0x%08X, ", buffer_i[i]);
    }
    printf(" (%d ints)\n", buffer_i_len_i);

    int2char(buffer_i, buffer_i_len_i, buffer_c, &buffer_c_len_i);
    printf("Revert: ");
    for (int i = 0; i < buffer_c_len_i; i++)
    {
        printf("%c", buffer_c[i]);
    }
    printf(" (%d bytes)\n", buffer_c_len_i);

    return 0;
}