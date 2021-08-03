/*
Clear-text password
Obfuscated flag

pass: Unbr4kable
flag: Bluesteel

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "get_input.hpp"
#include "char2byte_xor.hpp"

using namespace std;

#define BUFSIZE 50
#define CTFNUM 4
#define XOR_VAL 0x66
// #define DEBUG_PASSWORD 1

int main(int argc, char **argv)
{
    // setup variables
    int success = 0;
    unsigned char input[BUFSIZE] = {0};
    unsigned char flag[BUFSIZE] = {0};
    int flag_len = 0;
    int c = '\0';
    int counter = 0;

    // strings
    unsigned char flag_ob[BUFSIZE] = {0x24, 0x0A, 0x13, 0x03, 0x15, 0x12, 0x03, 0x03, 0x0A, 0x66};
    const char *distraction01 = "1234567";
    const char *distraction02 = "23456";
    const char *password = "Unbr4kable";
    const char *distraction03 = "password1";
    const char *distraction04 = "54321";
    const char *distraction05 = "baseball";
    const char *distraction06 = "867-5309";
    char prompt[BUFSIZE] = {0};
    char2byte_xor(flag_ob, BUFSIZE, flag, &flag_len, XOR_VAL);

    // prompt user for password
    sprintf(prompt, "Please enter CTF%d password: ", CTFNUM);
    get_input(argc, argv, prompt, input, BUFSIZE);

    // compare password against input
    success = strcmp((char *)input, (char *)password);
    if (success)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", input, CTFNUM);
#ifdef DEBUG_PASSWORD
        printf("CTF%d password is \"%s\"\n", CTFNUM, (char *)password);
#endif
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char *)flag);
    }

    // this is here as a distraction
    if ((strcmp((char *)password, (char *)input) == 1000) ||
        (strcmp((char *)flag, (char *)input) == 1000) ||
        (strcmp(distraction01, (char *)input) == 1000) ||
        (strcmp(distraction02, (char *)input) == 1000) ||
        (strcmp(distraction03, (char *)input) == 1000) ||
        (strcmp(distraction04, (char *)input) == 1000) ||
        (strcmp(distraction05, (char *)input) == 1000) ||
        (strcmp(distraction06, (char *)input) == 1000))
    {
        printf("%s %s %s %s %s %s",
               distraction01,
               distraction02,
               distraction03,
               distraction04,
               distraction05,
               distraction06);
    }

    return 0;
}
