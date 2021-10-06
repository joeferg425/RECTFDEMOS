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
#include "get_input.hpp"

using namespace std;

#define BUFSIZE 512
#define ITEM_COUNT 5
#define CTFNUM 7

int main(int argc, char **argv)
{
    unsigned char input[BUFSIZE] = {0};
    char prompt[BUFSIZE] = {0};
    char hash[BUFSIZE] = {0};
    int charcount = 0;
    unsigned char hashes[ITEM_COUNT][BUFSIZE] =
        {
            {0x0A, 0x0F, 0x6B, 0x88, 0x35, 0x4D, 0xE7, 0xAF, 0xE8, 0x4B, 0x8A, 0x07, 0xDF, 0xAD, 0xCC, 0x26},
        };
    char flags[ITEM_COUNT][BUFSIZE] =
        {
            "those aren't my waffles",
        };

    // prompt for password
    sprintf(prompt, "Please enter CTF%d password: ", CTFNUM);
    get_input(argc, argv, prompt, input, BUFSIZE);

    md5((uint8_t *)input, charcount, (uint8_t *)hash);
    md5((uint8_t *)flags[0], charcount, (uint8_t *)hashes[BUFSIZE-1]);

    if (strcmp((char *)hashes[0], hash) != 0)
    {
        printf("Sorry '");
        printf((char*)input);
        printf("' is not the CTF%d password\n", CTFNUM);
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, flags[0]);
    }
    return 0;
}
