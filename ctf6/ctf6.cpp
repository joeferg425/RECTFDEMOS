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

#define BUFFSIZE 512
#define INSIZE 32
#ifdef __GNUC__
struct __attribute__((packed)) my_struct
#else
__pragma(pack(push, 1)) struct my_struct __pragma(pack(pop))

#endif
{
    char input[INSIZE];
    long int suc;
    char str1[INSIZE];
    char str2[INSIZE];
    char str3[INSIZE];
    char str4[INSIZE];
} typedef struccy;

// #define FLAG_LEN 28

int main(int argc, char **argv)
{
    struct my_struct strucky;

    // unsigned int i[6] =
    //     {
    //         0x68646698,
    //         0x98468048,
    //         0x48468098,
    //         0x9864c898,
    //         0x66644898,
    //         0x00c86a48};
    // char *pw = NULL, *flag = NULL;
    // unsigned int f[FLAG_LEN] =
    //     {
    //         0x58eedeee,
    //         0xc2d0e840,
    //         0x40e64ee8,
    //         0xe4e040c2,
    //         0xf2e8e8ca,
    //         0xdcded840,
    //         0xe8e640ce,
    //         0xcedcd2e4,
    //         0xe4decc40,
    //         0xcc40c240,
    //         0x40cec2d8,
    //         0x5cdcc2da,
    //         0xdcc25c5c,
    //         0xd0e840c8,
    //         0x4ecae4ca,
    //         0xdedc40e6,
    //         0xecca40e8,
    //         0xc240dcca,
    //         0xe640f2dc,
    //         0xd2c6cae0,
    //         0xc640d8c2,
    //         0xc2e4c2d0,
    //         0xe4cae8c6,
    //         0xe4de40e6,
    //         0xf2dcc240,
    //         0xdcd2d0e8,
    //         0x000000ce,
    //         0x00000000};
    unsigned char upassword[BUFFSIZE] = { 0x4C, 0x7F, 0x01, 0x06, 0x10, 0x64, 0x63, 0x6F, 0x00, 0x0C, 0x63, 0x07, 0x68, 0x28, 0x56, 0x7E, 0x00, 0x68, 0x16, 0x01, 0x17, 0x11, 0x51, 0x64 };
    char* password = (char*)&upassword;
    unsigned char uflag[BUFFSIZE] = { 0x77, 0x18, 0x18, 0x5B, 0x0C, 0x54, 0x1C, 0x09, 0x15, 0x53, 0x54, 0x53, 0x41, 0x41, 0x50, 0x02, 0x17, 0x11, 0x00, 0x0D, 0x59, 0x4C, 0x03, 0x01, 0x09, 0x47, 0x53, 0x07, 0x06, 0x1B, 0x07, 0x09, 0x47, 0x46, 0x09, 0x1D, 0x52, 0x41, 0x41, 0x46, 0x0A, 0x0D, 0x06, 0x47, 0x4D, 0x0C, 0x0F, 0x40, 0x00, 0x00, 0x4F, 0x0F, 0x0A, 0x44, 0x54, 0x1C, 0x0D, 0x17, 0x17, 0x42, 0x54, 0x53, 0x4E, 0x01, 0x1B, 0x54, 0x45, 0x13, 0x13, 0x0B, 0x4E, 0x41, 0x0F, 0x17, 0x59, 0x53, 0x03, 0x15, 0x06, 0x0A, 0x08, 0x0D, 0x4C, 0x43, 0x0B, 0x09, 0x13, 0x13, 0x02, 0x17, 0x11, 0x17, 0x01, 0x53, 0x4F, 0x1D, 0x52, 0x41, 0x0F, 0x17, 0x0D, 0x1C, 0x01, 0x07, 0x09, 0x67 };
    char* flag = (char*)&uflag;

    strucky.str1[0] = 0;
    strucky.str2[0] = 0;
    strucky.str3[0] = 0;
    strucky.str4[0] = 0;
    strucky.suc = 0;

    // pw = (char *)&i;
    // flag = (char *)&f;

    int count = 0;
    // de-obfuscate flag
    // for (count = 0; count < ((FLAG_LEN - 1) * 4) + 1; count++)
    // {
    //     flag[count] = (char)((unsigned char)flag[count] / 2);
    // }
    for (count = 0; count < BUFFSIZE; count++)
    {
        uflag[count+1] = ((unsigned char)uflag[count] ^ uflag[count+1]);
    }
    // printf("%s\n", flag);
    // de-obfuscate password
    // for (count = 0; count < (6 * 4) + 1; count++)
    // {
    //     pw[count] = (char)((unsigned char)pw[count] / 2);
    // }
    for (count = 0; count < BUFFSIZE; count++)
    {
        upassword[count+1] = ((unsigned char)upassword[count] ^ upassword[count+1]);
    }
    // printf("%s\n", password);

    printf("Please enter the password: ");
    int c = '\0', charcount = 0;
    char *in = strucky.input;
    while (((c = getchar()) != EOF) && (c != '\n'))
    {
        // input = (char *)realloc(input, sizeof(char) * charcount);
        // char cc = (char)c;
        if (c == '\n')
        {
            break;
        }
        strucky.suc = (char)(strcmp(password, strucky.input) == 0);
        in[charcount] = c;
        // printf("%s\n", input);
        charcount++;
    }
    in[charcount] = 0;
    if (!strucky.suc)
    {
        strucky.suc = (char)(strcmp(password, strucky.input) == 0);
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
