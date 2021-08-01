/*
int password
Clear-text flag

pass: Fo0B4r
flag: down with gravity

*/

#include <stdio.h>
#include <string.h>
#include "get_input.hpp"
#include "char2int.hpp"

using namespace std;

#define BUFSIZE 256
#define CTFNUM 2
// #define DEBUG_PASSWORD 1

int main(int argc, char **argv)
{
    // setup variables
    int c = '\0';
    unsigned char input[BUFSIZE] = {0};
    int counter = 0;
    unsigned char password[BUFSIZE] = {0};
    int password_len = 0;

    // "obfuscated" password
    unsigned int password_i[BUFSIZE] = {0x42306F46, 0x00007234};
    // distractions and flag
    char distraction01[BUFSIZE] = "up with flags!";
    char flag[BUFSIZE] = "down with gravity";
    char distraction02[BUFSIZE] = "imaginary numbers are unrealistic";
    char distraction03[BUFSIZE] = "syntax stupid is";
    // de-obfuscate password in the middle of all this because
    undo_char2int(password_i, BUFSIZE, password, &password_len);
    char distraction04[BUFSIZE] = "ninety-nine problems and math is one";
    char distraction05[BUFSIZE] = "cooking theory is food for thought";
    char distraction06[BUFSIZE] = "oct31 = dec25";
    char distraction07[BUFSIZE] = "read terry pratchett";
    char prompt[BUFSIZE] = "";

    // prompt user for password
    sprintf(prompt, "Please enter CTF%d password: ", CTFNUM);
    counter = get_input(argc, argv, prompt, input, BUFSIZE);

    // compare the input against the password
    if (strcmp((char *)password, (char *)input) != 0)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char *)input, CTFNUM);
#ifdef DEBUG_PASSWORD
        printf("CTF%d password is \"%s\"\n", CTFNUM, (char *)password);
#endif
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, flag);
    }

    // this is here as a distraction
    if ((strcmp((char *)password, (char *)input) == 1000) ||
        (strcmp(flag, (char *)input) == 1000) ||
        (strcmp(distraction01, (char *)input) == 1000) ||
        (strcmp(distraction02, (char *)input) == 1000) ||
        (strcmp(distraction03, (char *)input) == 1000) ||
        (strcmp(distraction04, (char *)input) == 1000) ||
        (strcmp(distraction05, (char *)input) == 1000) ||
        (strcmp(distraction06, (char *)input) == 1000) ||
        (strcmp(distraction07, (char *)input) == 1000))
    {
        printf("%s %s %s %s %s %s %s",
               distraction01,
               distraction02,
               distraction03,
               distraction04,
               distraction05,
               distraction06,
               distraction07);
    }

    return 0;
}
