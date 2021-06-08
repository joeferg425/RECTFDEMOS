/*
Clear-text password
Obfuscated flag

pass: Unbr4kable
flag: Bluesteel

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "obfuscate3.hpp"

using namespace std;

#define BUFSIZE 50
#define CTFNUM 4
#define XOR_VAL 0x66

int main(int argc, char** argv)
{
    int success = 0;
    unsigned char flag_ob[BUFSIZE] = { 0x24, 0x0A, 0x13, 0x03, 0x15, 0x12, 0x03, 0x03, 0x0A, 0x66 };
    const char *distraction1 = "1234567";
    const char *distraction2 = "12345";
    const char *password = "Unbr4kable";
    const char *distraction7 = "password1";
    const char *distraction8 = "12345";
    const char *distraction9 = "baseball";
    unsigned char input[BUFSIZE] = "";
    // char *flag = (char*)&i;
    unsigned char flag[BUFSIZE] = {0};
    int flag_len = 0;
    deobfuscate3(flag_ob, BUFSIZE, flag, &flag_len, XOR_VAL);

    printf("Please enter CTF%d password: ", CTFNUM);
    int c = '\0';
    // string s = "";
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
        printf("Sorry, '%s' is not the CTF%d password\n", input, CTFNUM);
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char*)flag);
    }

    return 0;
}


