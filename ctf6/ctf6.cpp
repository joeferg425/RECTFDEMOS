/*
Capture the flag demo 6.
Obfuscated password
Obfuscated flag

pass: L324$@#LL@#$Ld2LL$23$5d
flag: wow, that's a pretty long string for a flag man...and there's not even any special characters or anything

Cross-compiled in 64bit Ubuntu 14
g++ -s CTF6.c -fno-stack-protector -o CTF6
-s : strip symbols
-fno-stack-protector : don't protect against stack overflow
*/

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

#ifdef __GNUC__
struct __attribute__((packed)) my_struct
#else
__pragma(pack(push, 1)) struct my_struct __pragma(pack(pop))

#endif
{
    char input[8];
    long int suc;
    char pw1[8];
    char pw2[8];
    char pw3[8];
    char pw4[8];
} typedef struccy;

#define FLAG_LEN 28

int main(int argc, char **argv)
{
    struct my_struct strucky;

    unsigned int i[6] =
        {
            0x68646698,
            0x98468048,
            0x48468098,
            0x9864c898,
            0x66644898,
            0x00c86a48};
    char *pw = NULL, *flag = NULL;
    unsigned int f[FLAG_LEN] =
        {
            0x58eedeee,
            0xc2d0e840,
            0x40e64ee8,
            0xe4e040c2,
            0xf2e8e8ca,
            0xdcded840,
            0xe8e640ce,
            0xcedcd2e4,
            0xe4decc40,
            0xcc40c240,
            0x40cec2d8,
            0x5cdcc2da,
            0xdcc25c5c,
            0xd0e840c8,
            0x4ecae4ca,
            0xdedc40e6,
            0xecca40e8,
            0xc240dcca,
            0xe640f2dc,
            0xd2c6cae0,
            0xc640d8c2,
            0xc2e4c2d0,
            0xe4cae8c6,
            0xe4de40e6,
            0xf2dcc240,
            0xdcd2d0e8,
            0x000000ce,
            0x00000000};

    strucky.pw1[0] = 0;
    strucky.pw2[0] = 0;
    strucky.pw3[0] = 0;
    strucky.pw4[0] = 0;
    strucky.suc = 0;

    pw = (char *)&i;
    flag = (char *)&f;

    int count = 0;
    // de-obfuscate flag
    for (count = 0; count < ((FLAG_LEN - 1) * 4) + 1; count++)
    {
        flag[count] = (char)((unsigned char)flag[count] / 2);
    }
    // de-obfuscate password
    for (count = 0; count < (6 * 4) + 1; count++)
    {
        pw[count] = (char)((unsigned char)pw[count] / 2);
    }

    printf("Please enter the password: ");
    int c = '\0', charcount = 0;
    char *in = strucky.input;
    while ((c = getchar()) != EOF)
    {
        // input = (char *)realloc(input, sizeof(char) * charcount);
        char cc = (char)c;
        if (cc == '\n')
        {
            break;
        }
        strucky.suc = (char)(strcmp(pw, strucky.input) == 0);
        in[charcount] = cc;
        // printf("%s\n", input);
        charcount++;
    }
    // strcmp returns zero when strings are equal
    // remove the & 64 and any buffer overflow with a character
    // whose value is odd will result in success
    // I added the 64 so there was a smaller chance of
    // first-attempt lucky success
    // (64 & true) == 65 == 'A'
    // strcpy(strucky.pw1, input);

    if (strucky.suc == 0)
    {
        printf("Sorry, '%s' is not the correct password\n", in);
    }
    else
    {
        printf("'%s' is correct \n", in);
        printf("Success, flag #6 is '%s'\n", flag);
    }
    //printf("%s\n", strucky.pw1);
    //printf("%ld\n", strucky.suc);
    //printf("%s\n", strucky.pw2);
    //printf("%s\n", strucky.pw3);
    //printf("%s\n", strucky.pw4);

    // free(input);
    return 0;
}
