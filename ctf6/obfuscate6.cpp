#include <stdio.h>
#include <string.h>

#define BUFFSIZE 1024

int main(int argc, char** argv)
{
    char buffer_c[BUFFSIZE] = {0};
    // unsigned int *buffer_i = NULL;
    char c = 0;
    int i;
    int buffer_len_i = 0;
    if (argc < 2)
    {
        for (buffer_len_i = 0; buffer_len_i < BUFFSIZE, (c = getchar()) != EOF; buffer_len_i++)
        {
            if (c == '\n')
            {
                break;
            }
            buffer_c[buffer_len_i] = c;
        }
        buffer_c[buffer_len_i] = 0;
    }
    else
    {
        strcpy(buffer_c, argv[1]);
        buffer_len_i = strlen(argv[1]);
    }
    buffer_len_i++;
    for (i = 0; i < buffer_len_i; i++)
    {
        printf("0x%02X, ", buffer_c[i]);
    }
    printf("\n");
    char last = buffer_c[0];
    char next = 0;
    for (i = 1; i < buffer_len_i; i++)
    {
        next = buffer_c[i];
        buffer_c[i] = ((unsigned char)buffer_c[i] ^ last);
        last = next;
        /*
        1=0+1
        2=1+2
        */
    }
    // printf("%d chars\n", i);
    // for (i = 0; i < buffer_len_i; i++)
    // {
    //     printf("0x%02X, ", buffer_c[i]);
    // }
    // printf("\n");
    for (i = 0; i < buffer_len_i; i++)
    {
        buffer_c[i+1] = ((unsigned char)buffer_c[i] ^ buffer_c[i+1]);
    }
    for (i = 0; i < buffer_len_i; i++)
    {
        printf("0x%02X, ", buffer_c[i]);
    }
    printf("\n");
    // for (i = 0; i < buffer_len_i; i++)
    // {
    //     printf("%c", buffer_c[i]);
    // }
    // printf("\n");

    return 0;
}