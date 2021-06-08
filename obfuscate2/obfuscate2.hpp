#ifndef __OBFUSCATE2__
#define __OBFUSCATE2__
#include <stdio.h>
#include <string.h>

// #define DEBUG_OBFUSCATION2 1

int obfuscate2(unsigned char* in_buffer_c, int in_buffer_len_i, unsigned int* out_buffer_c, int* out_buffer_len_i)
{
    int result_i = 0;

    #ifdef DEBUG_OBFUSCATION2
    printf("obfuscate2: Input       : ");
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
        out_buffer_c[i] *= 2;
    }

    #ifdef DEBUG_OBFUSCATION2
    printf("obfuscate2: Input  (hex): ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("0x%02X, ", in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", in_buffer_len_i);

    printf("obfuscate2: Output (hex): ");
    for (int i = 0; i < (*out_buffer_len_i); i++)
    {
        printf("0x%08X, ", out_buffer_c[i]);
    }
    printf(" (%d ints)\n", (*out_buffer_len_i));
    #endif

    return result_i;
}
int deobfuscate2(unsigned int* in_buffer_c, int in_buffer_len_i, unsigned char* out_buffer_c, int *out_buffer_len_i)
{
    int result_i = 0;

    #ifdef DEBUG_OBFUSCATION2
    printf("deobfuscate2: Input       : ");
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
        in_buffer_c[i] /= 2;
    }
    strncpy((char*)out_buffer_c, (char*)in_buffer_c, in_buffer_len_i);

    #ifdef DEBUG_OBFUSCATION2
    printf("deobfuscate2: Output  (hex): ");
    for (int i = 0; i < *out_buffer_len_i; i++)
    {
        printf("0x%02X, ", in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", *out_buffer_len_i);

    printf("deobfuscate2: Output (str): ");
    for (int i = 0; i < *out_buffer_len_i; i++)
    {
        printf("%c", out_buffer_c[i]);
    }
    printf(" (%d bytes)\n", *out_buffer_len_i);
    #endif

    return result_i;
}

#endif