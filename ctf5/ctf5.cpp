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
#define CTFNUM 5

int main(int argc, char** argv)
{
    unsigned int success = 0;
    unsigned char upw[BUFFSIZE] = { 0xCF, 0xE4, 0xE4, 0xE2, 0xE1, 0xEC, 0xEC, 0x80 };
    char *pw = (char*)&upw;
    const char *distraction1 = "football";
    const char *distraction2 = "999999";
    const char *distraction7 = "qwerty";
    const char *distraction8 = "tacocat";
    const char *distraction9 = "abc123";
    string input = "";
    unsigned char uflag[BUFFSIZE] = { 0xD6, 0xE5, 0xEC, 0xEF, 0xE3, 0xE9, 0xF2, 0xE1, 0xF0, 0xF4, 0xEF, 0xF2, 0x80 };
    char * flag = (char*)&uflag;

    printf("Please enter CTF%d password: ", CTFNUM);
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
        printf("Sorry, '%s' is not the CTF%d password\n", input.c_str(), CTFNUM);
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, flag);
    }

    return 0;
}



