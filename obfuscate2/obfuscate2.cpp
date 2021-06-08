#include <stdio.h>
#include <string.h>
#include "obfuscate2.hpp"

#define BUFSIZE 1024

int main(int argc, char** argv)
{
    unsigned char buffer_c[BUFSIZE] = {0};
    unsigned int buffer_i[BUFSIZE] = {0};
    char c = 0;
    int buffer_c_len_i = 0;
    int buffer_i_len_i = 0;
    if (argc < 2)
    {
        printf("Obfuscate2\n");
        printf("Enter a string >> ");
        for (buffer_c_len_i = 0; buffer_c_len_i < BUFSIZE, (c = getchar()) != EOF; buffer_c_len_i++)
        {
            if (c == '\n')
            {
                break;
            }
            buffer_c[buffer_c_len_i] = (unsigned char)c;
        }
        buffer_c[buffer_c_len_i] = 0;
        buffer_c_len_i++;
    }
    else
    {
        strcpy((char*)buffer_c, argv[1]);
        buffer_c_len_i = strlen(argv[1]);
    }

    printf("Input : ");
    for (int i = 0; i < buffer_c_len_i; i++)
    {
        printf("%c", buffer_c[i]);
    }
    printf(" (%d bytes)\n", buffer_c_len_i);

    obfuscate2(buffer_c, buffer_c_len_i, buffer_i, &buffer_i_len_i);
    printf("Output: ");
    for (int i = 0; i < buffer_i_len_i; i++)
    {
        printf("0x%08X, ", buffer_i[i]);
    }
    printf(" (%d ints)\n", buffer_i_len_i);

    deobfuscate2(buffer_i, buffer_i_len_i, buffer_c, &buffer_c_len_i);
    printf("Revert: ");
    for (int i = 0; i < buffer_c_len_i; i++)
    {
        printf("%c", buffer_c[i]);
    }
    printf(" (%d bytes)\n", buffer_c_len_i);

    return 0;
}