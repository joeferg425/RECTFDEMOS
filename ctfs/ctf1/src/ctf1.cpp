/*
Clear-text password
Clear-text flag

pass: Super$ecretPW1
flag: corn is gross

*/

#include <stdio.h>
#include <string.h>

using namespace std;

#define CTFNUM 1
#define BUFSIZE 256
// #define DEBUG_PASSWORD 1

int main(int argc, char **argv)
{
    // setup variables
    int c = '\0';
    unsigned char input[BUFSIZE] = {0};
    int counter = 0;

    // these are here so the strings window doesnt just show flag and password
    const char *distraction01 = "ImAP4$$word";
    const char *distraction02 = "$uperTr00per";
    const char *distraction03 = "T8ter";
    const char *distraction04 = "T8terT0t";
    const char *distraction05 = "weeeooweeeooo";
    const char *distraction06 = "willywonk4";
    const char *distraction07 = "password1";
    const char *distraction08 = "12345";
    const char *distraction09 = "baseball";
    const char *distraction10 = "word";
    const char *flag = "corn is gross";
    const char *password = "Super$ecretPW1";

    // prompt user for input
    printf("Please enter CTF%d password:  >> ", CTFNUM);

    // read input from user
    while (((c = getchar()) != EOF) && (counter < (BUFSIZE - 1)))
    {
        if (c == '\n')
        {
            break;
        }
        input[counter] = (unsigned char)c;
        counter++;
    }

    // compare input to password
    if (strcmp(password, (char*)input) != 0)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", (char*)input, CTFNUM);
        #ifdef DEBUG_PASSWORD
        printf("CTF%d password is \"%s\"\n", CTFNUM, (char*)password);
        #endif
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, flag);
    }

    // this is here as a distraction
    if ((strcmp(password, (char*)input) == 1000) ||
        (strcmp(flag, (char*)input) == 1000) ||
        (strcmp(distraction01, (char*)input) == 1000) ||
        (strcmp(distraction02, (char*)input) == 1000) ||
        (strcmp(distraction03, (char*)input) == 1000) ||
        (strcmp(distraction04, (char*)input) == 1000) ||
        (strcmp(distraction05, (char*)input) == 1000) ||
        (strcmp(distraction06, (char*)input) == 1000) ||
        (strcmp(distraction06, (char*)input) == 1000) ||
        (strcmp(distraction07, (char*)input) == 1000) ||
        (strcmp(distraction08, (char*)input) == 1000) ||
        (strcmp(distraction09, (char*)input) == 1000) ||
        (strcmp(distraction10, (char*)input) == 1000))
    {
        printf("%s %s %s %s %s %s %s %s %s %s",
            distraction01,
            distraction02,
            distraction03,
            distraction04,
            distraction05,
            distraction06,
            distraction07,
            distraction08,
            distraction09,
            distraction10);
    }

    return 0;
}
