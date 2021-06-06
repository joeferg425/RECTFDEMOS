/*
hashed password (md5)

pass: overkill
flag: those aren't my waffles

*/

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "md5.hpp"

using namespace std;

#define BUFFSIZE 512

#define ITEM_COUNT 5

int main(int argc, char **argv)
{
    unsigned char hashes[ITEM_COUNT][BUFFSIZE] = \
    {
        { 0x0A, 0x0F, 0x6B, 0x88, 0x35, 0x4D, 0xE7, 0xAF, 0xE8, 0x4B, 0x8A, 0x07, 0xDF, 0xAD, 0xCC, 0x26 },
    };
    char flags[ITEM_COUNT][BUFFSIZE] = \
    {
        "those aren't my waffles",
    };
    char input[BUFFSIZE] = {0};
    char hash[BUFFSIZE] = {0};

    printf("Please enter the password: ");
    int c = '\0', charcount = 0;
    while (((c = getchar()) != EOF) && (c != '\n') && (charcount < (BUFFSIZE - 1)))
    {
        if (c == '\n')
        {
            break;
        }
        input[charcount] = c;
        charcount++;
    }
    input[charcount] = 0;

    md5((uint8_t*)input, charcount, (uint8_t*)hash);

    if (strcmp((char*)hashes[0], hash) != 0)
    {
        printf("Sorry, '%s' is not the correct password\n", input);
    }
    else
    {
        printf("'%s' is correct \n", input);
        printf("Success, flag #6 is '%s'\n", flags[0]);
    }
    return 0;
}
