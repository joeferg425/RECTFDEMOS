/*
Capture the flag demo 3.
Obfuscated password
Clear-text flag

pass: yea
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

const char *str = "G0ld1";

int main(int argc, char** argv)
{
    int success = 0, i = 0x00C2CAF2;
    const char *distratction1 = "Silver2";
    const char *distratction2 = "Bronze33";
    const char *distratction3 = "PlatinumBaby!";
    const char* flag = "Unobtanium9000";
    string input = "";
    char *pw = (char*)&i;

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
    i = i / 2;
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


