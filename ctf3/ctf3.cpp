/*
Capture the flag demo 3.
Obfuscated password
Clear-text flag

pass: tinker
flag: G0ld1

Cross-compiled in 64bit Ubuntu 14
g++ -m32 -s CTF3.c -o CTF3
-m32 : cross-compile for 32 bit
-s : strip symbols
*/

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define BUFFSIZE 25

const char *str = "G0ld1";

int main(int argc, char** argv)
{
    int success = 0;
    // int password_i[BUFFSIZE] = { 0x00C2CAF2 };
    unsigned int password_i[BUFFSIZE] = { 0xD6DCD2E8, 0x0000E4CA };
    const char *distratction1 = "Silver2";
    const char *distratction2 = "Bronze33";
    const char *distratction3 = "PlatinumBaby!";
    const char* flag = "Unobtanium9000";
    string input = "";
    char *pw = (char*)&password_i;

    printf("Please enter the password: ");
    flag = str;
    int c = '\0';
    string s = "";
    while ((c = getchar()) != EOF)
    {
        char cc = (char)c;
        if (cc == '\n')
        {
            break;
        }
        input += cc;
    }
    // this de-obfuscates the string
    for (int i = 0; i < BUFFSIZE; i++)
    {
        password_i[i] = (password_i[i] / 2);
    }
    success = strcmp(input.c_str(), pw);
    if (success)
    {
        printf("Sorry, '%s' is not the correct password\n", input.c_str());
    }
    else
    {
        printf("Success, flag #3 is '%s'\n", flag);
    }

    return 0;
}


