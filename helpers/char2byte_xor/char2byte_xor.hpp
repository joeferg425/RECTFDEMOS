#ifndef __char2byte_xor__
#define __char2byte_xor__
#include <stdio.h>
#include <string.h>

// #define DEBUG_OBFUSCATION3 1

int char2byte_xor(unsigned char *in_buffer_c, int in_buffer_len_i, unsigned char *out_buffer_c, int *out_buffer_len_i, unsigned char crypto_xor)
{
    int result_i = 0;

#ifdef DEBUG_OBFUSCATION3
    printf("char2byte_xor: Input       : ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("%c", (char)in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", in_buffer_len_i);
#endif

    (*out_buffer_len_i) = in_buffer_len_i;
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        out_buffer_c[i] = (in_buffer_c[i] ^ crypto_xor);
    }

#ifdef DEBUG_OBFUSCATION3
    printf("char2byte_xor: Input  (hex): ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("0x%02X, ", in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", in_buffer_len_i);

    printf("char2byte_xor: Output (hex): ");
    for (int i = 0; i < (*out_buffer_len_i); i++)
    {
        printf("0x%02X, ", out_buffer_c[i]);
    }
    printf(" (%d bytes)\n", (*out_buffer_len_i));
#endif

    return result_i;
}

#endif