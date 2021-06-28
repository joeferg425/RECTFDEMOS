/*
This project combines four 8-bit chars into one 32-bit int. Then multiplies that int by a value to obfuscate it.
*/
#include <stdio.h>
#include <string.h>
#include "get_input.hpp"
#include "char2int_scaled.hpp"

#define BUFSIZE 1024
#define MULTIPLIER 2

int main(int argc, char **argv)
{
    unsigned char buffer_c[BUFSIZE] = {0};
    unsigned int buffer_i[BUFSIZE] = {0};
    int buffer_c_len_i = 0;
    int buffer_i_len_i = 0;

    // get input from user
    printf("char2scaledint\n");
    buffer_c_len_i = get_input(argc, argv, "Enter a string", buffer_c, BUFSIZE);

    // print user input
    printf("Input : ");
    for (int i = 0; i < buffer_c_len_i; i++)
    {
        printf("%c", buffer_c[i]);
    }
    printf(" (%d bytes)\n", buffer_c_len_i);

    char2int_scaled(buffer_c, buffer_c_len_i, buffer_i, &buffer_i_len_i, MULTIPLIER);

    printf("Output: ");
    for (int i = 0; i < buffer_i_len_i; i++)
    {
        printf("0x%08X, ", buffer_i[i]);
    }
    printf(" (%d ints)\n", buffer_i_len_i);

    undo_char2int_scaled(buffer_i, buffer_i_len_i, buffer_c, &buffer_c_len_i, MULTIPLIER);
    printf("Revert: ");
    for (int i = 0; i < buffer_c_len_i; i++)
    {
        printf("%c", buffer_c[i]);
    }
    printf(" (%d bytes)\n", buffer_c_len_i);

    return 0;
}