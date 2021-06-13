#ifndef __OBFUSCATE5__
#define __OBFUSCATE5__
#include <stdio.h>
#include <string.h>

// #define DEBUG_OBFUSCATION5 1

int obfuscate5(unsigned char* in_buffer_c, int in_buffer_len_i, unsigned char* out_buffer_c, int* out_buffer_len_i)
{
    int result_i = 0;

    #ifdef DEBUG_OBFUSCATION5
    printf("obfuscate5  : Input (str) : ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("%c", (char)in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", in_buffer_len_i);
    printf("obfuscate5  : Input (Hex) : ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("0x%02X, ", (char)in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", in_buffer_len_i);
    #endif

    char last = in_buffer_c[0];
    out_buffer_c[0] = in_buffer_c[0];
    char next = 0;
    for (int i = 1; i < in_buffer_len_i; i++)
    {
        next = in_buffer_c[i];
        out_buffer_c[i] = ((unsigned char)in_buffer_c[i] ^ last);
        last = next;
    }
    *out_buffer_len_i = in_buffer_len_i;
    #ifdef DEBUG_OBFUSCATION5
    printf("obfuscate5  : Output (hex): ");
    for (int i = 0; i < (*out_buffer_len_i); i++)
    {
        printf("0x%02X, ", out_buffer_c[i]);
    }
    printf(" (%d bytes)\n", (*out_buffer_len_i));

    #endif

    return result_i;
}
int deobfuscate5(unsigned char* in_buffer_c, int in_buffer_len_i, unsigned char* out_buffer_c, int *out_buffer_len_i)
{
    int result_i = 0;

    #ifdef DEBUG_OBFUSCATION5
    printf("deobfuscate5: Input       : ");
    for (int i = 0; i < in_buffer_len_i; i++)
    {
        printf("0x%02X, ", in_buffer_c[i]);
    }
    printf(" (%d bytes)\n", in_buffer_len_i);
    #endif

    *out_buffer_len_i = in_buffer_len_i;
    out_buffer_c[0] = in_buffer_c[0];
    for (int i = 0; i < (in_buffer_len_i-1); i++)
    {
        out_buffer_c[i+1] = (out_buffer_c[i] ^ in_buffer_c[i+1]);
    }

    #ifdef DEBUG_OBFUSCATION5
    printf("deobfuscate5: Output (hex): ");
    for (int i = 0; i < (*out_buffer_len_i); i++)
    {
        printf("0x%02X, ", out_buffer_c[i]);
    }
    printf(" (%d bytes)\n", (*out_buffer_len_i));

    printf("deobfuscate5: Output (str): ");
    for (int i = 0; i < (*out_buffer_len_i); i++)
    {
        printf("%c", out_buffer_c[i]);
    }
    printf(" (%d bytes)\n", (*out_buffer_len_i));
    #endif

    return result_i;
}

#endif