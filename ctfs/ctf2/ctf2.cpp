/*
Clear-text password
Clear-text flag

pass: Fo0B4r
flag: down with gravity

*/

#include <stdio.h>
#include <string.h>
#include "obfuscate1.hpp"

using namespace std;

#define BUFSIZE 256
#define CTFNUM 2

int main(int argc, char** argv)
{
    // this is here to demonstrate that obfuscation in code is not good enough
    // unsigned int i[25] = { 0x30393834, 0x33376d66, 0x33726339, 0x39383334, 0x265e755e, 0x74242565, 0x77616674, 0x265e2425, 0x68265e72, 0x64627528, 0x20292825, 0x42306f46, 0x00007234, 0x39392928, 0x4a282a4a, 0x55662425, 0x44456f38, 0x6e68386e, 0x68366462, 0x37367666, 0x5e434443, 0x56763736, 0x66725656, 0x265e5646, 0x66632929 };
    unsigned int password_i[BUFSIZE] = { 0x42306F46, 0x00007234 };
    char d1[100] = "up with flags!";
    unsigned char password_c[BUFSIZE] = {0};
    int password_len = 0;
    char flag[100] = "down with gravity";
    char d3[100] = "imaginary numbers are unrealistic";
    char d4[100] = "syntax stupid is";
    char d5[100] = "ninety-nine problems and math is one";
    char d6[100] = "cooking theory is food for thought";
    char d7[100] = "oct31 = dec25";
    char d8[100] = "read terry pratchett";
    deobfuscate1(password_i, BUFSIZE, password_c, &password_len);

    printf("Please enter CTF%d password: ", CTFNUM);
    int c = '\0';
    unsigned char input[BUFSIZE] = {0};
    int counter = 0;
    while (((c = getchar()) != EOF) && (counter < (BUFSIZE - 1)))
    {
        if (c == '\n')
        {
            break;
        }
        input[counter] = (unsigned char)c;
        counter++;
    }
    // check the input
    if (strcmp((char*)password_c, (char*)input) != 0)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char*)input, CTFNUM);
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, flag);
    }

    return 0;
}

