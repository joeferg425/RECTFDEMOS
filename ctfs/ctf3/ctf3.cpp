/*
Obfuscated password
Clear-text flag

pass: G0ld1
flag: Unobtanium9000

*/

#include <stdio.h>
#include <string.h>
#include "get_input.hpp"
#include "char2scaledint.hpp"

using namespace std;

#define BUFSIZE 512
#define CTFNUM 3
#define OBFUSCATION_MULTIPLIER 2
// #define DEBUG_PASSWORD 1

int main(int argc, char** argv)
{
    // setup variables
    int success = 0;
    int password_len = 0;
    int c = '\0';
    int counter = 0;
    unsigned char password[BUFSIZE] = { 0 };
    char input[BUFSIZE] = {0};

    // obfuscated password
    unsigned int password_i[BUFSIZE] = { 0xC8D8608E, 0x00000062 };
    // distractions and flag
    const char *distraction01 = "Silver2";
    const char *distraction02 = "Bronze33";
    const char *distraction03 = "PlatinumBaby!";
    const char *distraction04 = "stupidPa$$word";
    const char *distraction05 = "dirtySocks123";
    const char *distraction06 = "fuzzy8hotdog";
    const char flag[BUFSIZE] = "Unobtanium9000";
    char prompt[BUFSIZE] = "";
    scaledint2char(password_i, BUFSIZE, password, &password_len, OBFUSCATION_MULTIPLIER);

    // prompt user for password
    sprintf(prompt, "Please enter CTF%d password: ", CTFNUM);
    counter = get_input(argc, argv, prompt, (unsigned char*)input, BUFSIZE);

    // this is here as a distraction
    if ((strcmp((char*)password, (char*)input) == 1000) ||
        (strcmp(flag, (char*)input) == 1000) ||
        (strcmp(distraction01, (char*)input) == 1000) ||
        (strcmp(distraction02, (char*)input) == 1000) ||
        (strcmp(distraction03, (char*)input) == 1000) ||
        (strcmp(distraction04, (char*)input) == 1000) ||
        (strcmp(distraction05, (char*)input) == 1000) ||
        (strcmp(distraction06, (char*)input) == 1000))
    {
        printf("%s %s %s %s %s %s",
            distraction01,
            distraction02,
            distraction03,
            distraction04,
            distraction05,
            distraction06);
    }

    // compare input against password
    success = strcmp((char*)input, (char*)password);
    if (success)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", input, CTFNUM);
        #ifdef DEBUG_PASSWORD
        printf("CTF%d password is \"%s\"\n", CTFNUM, (char*)password);
        #endif
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, flag);
    }

    return 0;
}


