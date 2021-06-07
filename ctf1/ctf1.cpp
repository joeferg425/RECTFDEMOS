/*
Clear-text password
Clear-text flag

pass: Super$ecretPW1
flag: corn is gross

*/

#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;
#define flag "corn is gross"
#define adminpw "Super$ecretPW1"
#define CTFNUM 1

int main(int argc, char **argv)
{
    // these are here so the strings window doesnt just show flag and password
    const char *distraction1 = "ImAP4$$word";
    const char *distraction2 = "$uperTr00per";
    const char *distraction3 = "T8ter";
    const char *distraction4 = "T8terT0t";
    const char *distraction5 = "weeeooweeeooo";
    const char *distraction6 = "willywonk4";
    const char *distraction7 = "password1";
    const char *distraction8 = "12345";
    const char *distraction9 = "baseball";
    const char *distraction10 = "word";
    printf("Please enter CTF%d password: ", CTFNUM);
    int c = '\0';
    string s = "";
    // yes, i know there are ways of reading a line at a time
    while ((c = getchar()) != EOF)
    {
        char cc = (char)c;
        if (cc == '\n')
        {
            break;
        }
        s += cc;
    }
    // check the input
    if (s != adminpw)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", s.c_str(), CTFNUM);
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, flag);
    }
    // this is here so the compiler doesn't optimize out the strings
    if (1 == 2)
    {
        printf("%s %s %s %s %s %s %s %s %s %s",
               distraction1,
               distraction2,
               distraction3,
               distraction4,
               distraction5,
               distraction6,
               distraction7,
               distraction8,
               distraction9,
               distraction10);
    }

    return 0;
}
