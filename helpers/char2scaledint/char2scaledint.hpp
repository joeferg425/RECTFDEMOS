#ifndef __char2scaledint__
#define __char2scaledint__
#include <stdio.h>
#include <string.h>

// #define DEBUG_OBFUSCATION2 1

int char2scaledint(unsigned char* in_buffer_c, int in_buffer_len_i, unsigned int* out_buffer_c, int* out_buffer_len_i, int multiplier)
{
    int result_i = 0;

    #ifdef DEBUG_OBFUSCATION2
    printf("char2scaledint: Input       : ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("%c", (char)in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", in_buffer_len_i);
    #endif

    out_buffer_c[0] = 0;
    (*out_buffer_len_i) = (in_buffer_len_i / 4);
    strncpy((char*)out_buffer_c, (char*)in_buffer_c, in_buffer_len_i);
    if ((in_buffer_len_i % 4) != 0)
    {
        (*out_buffer_len_i)++;
    }
    for (int i = 0; i < (*out_buffer_len_i); i++)
    {
        out_buffer_c[i] *= multiplier;
    }

    #ifdef DEBUG_OBFUSCATION2
    printf("char2scaledint: Input  (hex): ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("0x%02X, ", in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", in_buffer_len_i);

    printf("char2scaledint: Output (hex): ");
    for (int i = 0; i < (*out_buffer_len_i); i++)
    {
        printf("0x%08X, ", out_buffer_c[i]);
    }
    printf(" (%d ints)\n", (*out_buffer_len_i));
    #endif

    return result_i;
}
int scaledint2char(unsigned int* in_buffer_c, int in_buffer_len_i, unsigned char* out_buffer_c, int *out_buffer_len_i, int divisor)
{
    int result_i = 0;

    #ifdef DEBUG_OBFUSCATION2
    printf("scaledint2char: Input       : ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("0x%08X, ", in_buffer_c[i]);
    }
    printf(" (%d ints)\n", in_buffer_len_i);
    #endif

    out_buffer_c[0] = 0;
    (*out_buffer_len_i) = (in_buffer_len_i * 4);
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        in_buffer_c[i] /= divisor;
    }
    strncpy((char*)out_buffer_c, (char*)in_buffer_c, in_buffer_len_i);

    #ifdef DEBUG_OBFUSCATION2
    printf("scaledint2char: Output  (hex): ");
    for (int i = 0; i < *out_buffer_len_i; i++)
    {
        printf("0x%02X, ", in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", *out_buffer_len_i);

    printf("scaledint2char: Output (str): ");
    for (int i = 0; i < *out_buffer_len_i; i++)
    {
        printf("%c", out_buffer_c[i]);
    }
    printf(" (%d bytes)\n", *out_buffer_len_i);
    #endif

    return result_i;
}

#endif