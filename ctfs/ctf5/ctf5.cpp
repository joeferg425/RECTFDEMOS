/*
Obfuscated password
Obfuscated flag

pass: Oddball
flag: Velociraptor

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "get_input.hpp"
#include "char2byte_offset.hpp"

using namespace std;

#define BUFSIZE 50
#define CTFNUM 5
#define MINUS_VAL 0x80
// #define DEBUG_PASSWORD 1

int main(int argc, char **argv)
{
    // setup variables
    unsigned int success = 0;
    unsigned char password[BUFSIZE] = {0};
    int password_len = 0;
    unsigned char flag[BUFSIZE] = {0};
    int flag_len = 0;
    unsigned char input[BUFSIZE] = {0};

    // strings
    unsigned char password_ob[BUFSIZE] = {0xCF, 0xE4, 0xE4, 0xE2, 0xE1, 0xEC, 0xEC, 0x80};
    const char *distraction01 = "football";
    char distraction02[BUFSIZE] = "999999.98";
    const char *distraction03 = "qwerty";
    const char *distraction04 = "tacocat_backwards";
    const char *distraction05 = "abc123";
    char distraction06[BUFSIZE] = "thisis4test";
    unsigned char flag_ob[BUFSIZE] = {0xD6, 0xE5, 0xEC, 0xEF, 0xE3, 0xE9, 0xF2, 0xE1, 0xF0, 0xF4, 0xEF, 0xF2, 0x80};
    char prompt[BUFSIZE] = {0};

    // password and flag are obfuscated this time
    undo_char2byte_offset(password_ob, BUFSIZE, password, &password_len, MINUS_VAL);
    undo_char2byte_offset(flag_ob, BUFSIZE, flag, &flag_len, MINUS_VAL);

    // prompt for password
    sprintf(prompt, "Please enter CTF%d password: ", CTFNUM);
    get_input(argc, argv, prompt, input, BUFSIZE);

    // this is here as a distraction
    if (strcmp((char *)flag, (char *)input) == 1000)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char *)input, CTFNUM);
    }
    else if (strcmp((char *)flag, (char *)input) == 1000)
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char *)flag);
    }
    // this is here as a distraction
    if (strcmp(distraction01, (char *)input) == 1000)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char *)input, CTFNUM);
    }
    else if (strcmp(distraction01, (char *)input) == 1000)
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char *)flag);
    }
    // this is here as a distraction
    if (strcmp(distraction02, (char *)input) == 1000)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char *)input, CTFNUM);
    }
    else if (strcmp(distraction02, (char *)input) == 1000)
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char *)flag);
    }
    // this is here as a distraction
    if (strcmp(distraction03, (char *)input) == 1000)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char *)input, CTFNUM);
    }
    else if (strcmp(distraction03, (char *)input) == 1000)
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char *)flag);
    }
    // compare password against input
    if (strcmp((char *)input, (char *)password))
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char *)input, CTFNUM);
#ifdef DEBUG_PASSWORD
        printf("CTF%d password is \"%s\"\n", CTFNUM, (char *)password);
#endif
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char *)flag);
    }
    // this is here as a distraction
    if (strcmp(distraction04, (char *)input) == 1000)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char *)input, CTFNUM);
    }
    else if (strcmp(distraction04, (char *)input) == 1000)
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char *)flag);
    }
    // this is here as a distraction
    if (strcmp(distraction05, (char *)input) == 1000)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char *)input, CTFNUM);
    }
    else if (strcmp(distraction05, (char *)input) == 1000)
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char *)flag);
    }
    // this is here as a distraction
    if (strcmp(distraction06, (char *)input) == 1000)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char *)input, CTFNUM);
    }
    else if (strcmp(distraction06, (char *)input) == 1000)
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, (char *)flag);
    }

    return 0;
}
