
#ifndef __GET_INPUT__
#define __GET_INPUT__
#include <stdio.h>
#include <string.h>

int get_input(int argc, char **argv, const char *prompt, unsigned char *buffer_c, int buffer_size_i)
{
    int buffer_len_i = -1;
    char c = 0;
    if (argc < 2)
    {
        printf("%s >> ", prompt);
        for (buffer_len_i = 0; buffer_len_i < (buffer_size_i - 1), (c = getchar()) != EOF; buffer_len_i++)
        {
            if (c == '\n')
            {
                break;
            }
            buffer_c[buffer_len_i] = (unsigned char)c;
        }
        buffer_c[buffer_len_i] = 0;
        buffer_len_i++;
    }
    else
    {
        strcpy((char *)buffer_c, argv[1]);
        buffer_len_i = strlen(argv[1]);
        if (buffer_c[buffer_len_i] != 0)
        {
            buffer_c[buffer_len_i] = 0;
            buffer_len_i++;
        }
    }
    return buffer_len_i;
}

#endif