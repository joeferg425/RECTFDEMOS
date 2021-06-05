#include <stdio.h>
#include <string.h>

#define BUFFSIZE 1024

int main(int argc, char** argv)
{
    char buffer_c[BUFFSIZE] = {0};
    unsigned int *buffer_i = NULL;
    char c = 0;
    int buffer_c_len_i = 0;
    int buffer_i_len_i = 0;
    if (argc < 2)
    {
        for (buffer_c_len_i = 0; buffer_c_len_i < BUFFSIZE, (c = getchar()) != EOF; buffer_c_len_i++)
        {
            if (c == '\n')
            {
                break;
            }
            buffer_c[buffer_c_len_i] = c;
        }
        buffer_c[buffer_c_len_i] = 0;
        buffer_c_len_i++;
    }
    else
    {
        strcpy(buffer_c, argv[1]);
        buffer_c_len_i = strlen(argv[1]);
    }
    buffer_i = (unsigned int*)&buffer_c;
    buffer_i_len_i = (buffer_c_len_i / 4);
    if ((buffer_c_len_i % 4) != 0)
    {
        buffer_i_len_i++;
    }
    for (int i = 0; i < buffer_i_len_i; i++)
    {
        printf("0x%08X, ", buffer_i[i]);
    }
    printf("\n");

    return 0;
}