/*
Clear-text password
Obfuscated flag

pass: Unbr4kable
flag: Bluesteel

*/

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define BUFFSIZE 50
#define CTFNUM 4

int main(int argc, char** argv)
{
    int success = 0;
    char flag[BUFFSIZE] = { 0x24, 0x0A, 0x13, 0x03, 0x15, 0x12, 0x03, 0x03, 0x0A, 0x66 };
    const char *distraction1 = "1234567";
    const char *distraction2 = "12345";
    const char *pw = "Unbr4kable";
    const char *distraction7 = "password1";
    const char *distraction8 = "12345";
    const char *distraction9 = "baseball";
    string input = "";
    // char *flag = (char*)&i;

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
    // de-obfuscate flag
    for (int j = 0; j < BUFFSIZE; j++)
    {
        flag[j] = (char)(((unsigned char)flag[j]) ^ 0x66);
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


