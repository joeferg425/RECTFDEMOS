/*
Obfuscated password
Obfuscated flag

pass: Oddball
flag: Velociraptor

*/

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;
#define BUFFSIZE 50

int main(int argc, char** argv)
{
    unsigned int success = 0;
    // unsigned int i1[2] = { 0xc4c8c89e, 0x00d8d8c2 };
    // unsigned int i2[4] = { 0xded8caac, 0xc2e4d2c6, 0xe4dee8e0, 0x0 };
    unsigned char upw[BUFFSIZE] = { 0xCF, 0xE4, 0xE4, 0xE2, 0xE1, 0xEC, 0xEC, 0x80 };
    char *pw = (char*)&upw;
    const char *distraction1 = "football";
    const char *distraction2 = "999999";
    // char *pw = (char*)&i1;
    const char *distraction7 = "qwerty";
    const char *distraction8 = "tacocat";
    const char *distraction9 = "abc123";
    string input = "";
    // char *flag = (char*)&i2;
    unsigned char uflag[BUFFSIZE] = { 0xD6, 0xE5, 0xEC, 0xEF, 0xE3, 0xE9, 0xF2, 0xE1, 0xF0, 0xF4, 0xEF, 0xF2, 0x80 };
    char * flag = (char*)&uflag;

    printf("Please enter the password: ");
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
    // de-obfuscate password
    for (int j = 0; j < BUFFSIZE; j++)
    {
        pw[j] = (char)(((unsigned char)pw[j]) - 0x80);
    }
    //de-obfuscate flag
    for (int j = 0; j < BUFFSIZE; j++)
    {
        flag[j] = (char)(((unsigned char)flag[j]) - 0x80);
    }
    success = strcmp(input.c_str(), pw);
    if (success)
    {
        printf("Sorry, '%s' is not the correct password\n", input.c_str());
    }
    else
    {
        printf("Success, flag #5 is '%s'\n", flag);
    }

    return 0;
}



