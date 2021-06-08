/*
Obfuscated password
Obfuscated flag

pass: Oddball
flag: Velociraptor

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "obfuscate4.hpp"

using namespace std;

#define BUFSIZE 50
#define CTFNUM 5
#define MINUS_VAL 0x80

int main(int argc, char** argv)
{
    unsigned int success = 0;
    unsigned char password_ob[BUFSIZE] = { 0xCF, 0xE4, 0xE4, 0xE2, 0xE1, 0xEC, 0xEC, 0x80 };
    unsigned char password[BUFSIZE] = {0};
    int password_len = 0;
    const char *distraction1 = "football";
    const char *distraction2 = "999999";
    const char *distraction7 = "qwerty";
    const char *distraction8 = "tacocat";
    const char *distraction9 = "abc123";
    unsigned char flag_ob[BUFSIZE] = { 0xD6, 0xE5, 0xEC, 0xEF, 0xE3, 0xE9, 0xF2, 0xE1, 0xF0, 0xF4, 0xEF, 0xF2, 0x80 };
    unsigned char flag[BUFSIZE] = {0};
    int flag_len = 0;
    unsigned char input[BUFSIZE] = {0};

    deobfuscate4(password_ob, BUFSIZE, password, &password_len, MINUS_VAL);
    deobfuscate4(flag_ob, BUFSIZE, flag, &flag_len, MINUS_VAL);

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
    success = strcmp((char*)input, (char*)password);
    if (success)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char*)input, CTFNUM);
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char*)flag);
    }

    return 0;
}



