/*
Obfuscated password
Clear-text flag

pass: G0ld1
flag: Unobtanium9000

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "obfuscate2.hpp"

using namespace std;

#define BUFSIZE 25
#define CTFNUM 3

int main(int argc, char** argv)
{
    int success = 0;
    unsigned int password_i[BUFSIZE] = { 0xC8D8608E, 0x00000062 };
    const char *distratction1 = "Silver2";
    const char *distratction2 = "Bronze33";
    const char *distratction3 = "PlatinumBaby!";
    const char* flag = "Unobtanium9000";
    unsigned char password_c[BUFSIZE] = { 0 };
    char input[BUFSIZE] = {0};
    char password[BUFSIZE] = {0};
    int password_len = 0;
    deobfuscate2(password_i, BUFSIZE, password_c, &password_len);

    printf("Please enter CTF%d password: ", CTFNUM);
    int c = '\0';
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
    // input[counter] = 0;
    // this de-obfuscates the string
    success = strcmp((char*)input, (char*)password_c);
    if (success)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", input, CTFNUM);
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, flag);
    }

    return 0;
}


