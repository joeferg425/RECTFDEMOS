#ifndef __char2int__
#define __char2int__
#include <stdio.h>
#include <string.h>

// #define DEBUG_OBFUSCATION1 1

int char2int(unsigned char* in_buffer_c, int in_buffer_len_i, unsigned int* out_buffer_c, int* out_buffer_len_i)
{
    int result_i = 0;

    #ifdef DEBUG_OBFUSCATION1
    printf("char2int: Input       : ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("%c", (char)in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", in_buffer_len_i);
    #endif

    out_buffer_c[0] = 0;
    *out_buffer_len_i = (in_buffer_len_i / 4);
    strncpy((char*)out_buffer_c, (char*)in_buffer_c, in_buffer_len_i);
    if ((in_buffer_len_i % 4) != 0)
    {
        (*out_buffer_len_i)++;
    }

    #ifdef DEBUG_OBFUSCATION1
    printf("char2int: Input  (hex): ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("0x%02X, ", in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", in_buffer_len_i);

    printf("char2int: Output (hex): ");
    for (int i = 0; i < (*out_buffer_len_i); i++)
    {
        printf("0x%08X, ", out_buffer_c[i]);
    }
    printf(" (%d ints)\n", (*out_buffer_len_i));
    #endif

    return result_i;
}
int int2char(unsigned int* in_buffer_c, int in_buffer_len_i, unsigned char* out_buffer_c, int *out_buffer_len_i)
{
    int result_i = 0;

    #ifdef DEBUG_OBFUSCATION1
    printf("int2char: Input       : ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("0x%08X, ", in_buffer_c[i]);
    }
    printf(" (%d ints)\n", in_buffer_len_i);
    #endif

    out_buffer_c[0] = 0;
    (*out_buffer_len_i) = (in_buffer_len_i * 4);
    strncpy((char*)out_buffer_c, (char*)in_buffer_c, in_buffer_len_i);

    #ifdef DEBUG_OBFUSCATION1
    printf("int2char: Output  (hex): ");
    for (int i = 0; i < *out_buffer_len_i; i++)
    {
        printf("0x%02X, ", in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", *out_buffer_len_i);

    printf("int2char: Output (str): ");
    for (int i = 0; i < *out_buffer_len_i; i++)
    {
        printf("%c", out_buffer_c[i]);
    }
    printf(" (%d bytes)\n", *out_buffer_len_i);
    #endif

    return result_i;
}

#endif