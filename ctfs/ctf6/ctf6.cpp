/*
Obfuscated password
Obfuscated flag

pass: L324$@#LL@#$Ld2LL$23$5d
flag: wow, that's a pretty long string for a flag man...and there's not even any special characters or anything

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "obfuscate5.hpp"

using namespace std;

#define BUFSIZE 512
#define INSIZE 32
#define CTFNUM 6

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
};

int main(int argc, char **argv)
{
    struct my_struct struk;
    unsigned char password_ob[BUFSIZE] = { 0x4C, 0x7F, 0x01, 0x06, 0x10, 0x64, 0x63, 0x6F, 0x00, 0x0C, 0x63, 0x07, 0x68, 0x28, 0x56, 0x7E, 0x00, 0x68, 0x16, 0x01, 0x17, 0x11, 0x51, 0x64 };
    unsigned char password[BUFSIZE] = {0};
    unsigned char flag_ob[BUFSIZE] = { 0x77, 0x18, 0x18, 0x5B, 0x0C, 0x54, 0x1C, 0x09, 0x15, 0x53, 0x54, 0x53, 0x41, 0x41, 0x50, 0x02, 0x17, 0x11, 0x00, 0x0D, 0x59, 0x4C, 0x03, 0x01, 0x09, 0x47, 0x53, 0x07, 0x06, 0x1B, 0x07, 0x09, 0x47, 0x46, 0x09, 0x1D, 0x52, 0x41, 0x41, 0x46, 0x0A, 0x0D, 0x06, 0x47, 0x4D, 0x0C, 0x0F, 0x40, 0x00, 0x00, 0x4F, 0x0F, 0x0A, 0x44, 0x54, 0x1C, 0x0D, 0x17, 0x17, 0x42, 0x54, 0x53, 0x4E, 0x01, 0x1B, 0x54, 0x45, 0x13, 0x13, 0x0B, 0x4E, 0x41, 0x0F, 0x17, 0x59, 0x53, 0x03, 0x15, 0x06, 0x0A, 0x08, 0x0D, 0x4C, 0x43, 0x0B, 0x09, 0x13, 0x13, 0x02, 0x17, 0x11, 0x17, 0x01, 0x53, 0x4F, 0x1D, 0x52, 0x41, 0x0F, 0x17, 0x0D, 0x1C, 0x01, 0x07, 0x09, 0x67 };
    unsigned char flag[BUFSIZE] = {0};
    int password_len = 0;
    int flag_len = 0;

    deobfuscate5(password_ob, BUFSIZE, password, &password_len);
    deobfuscate5(flag_ob, BUFSIZE, flag, &flag_len);

    struk.str1[0] = 0;
    struk.str2[0] = 0;
    struk.str3[0] = 0;
    struk.str4[0] = 0;
    struk.suc = 0;

    // int count = 0;
    // for (count = 0; count < BUFSIZE; count++)
    // {
    //     uflag[count+1] = ((unsigned char)uflag[count] ^ uflag[count+1]);
    // }
    // for (count = 0; count < BUFSIZE; count++)
    // {
    //     upassword[count+1] = ((unsigned char)upassword[count] ^ upassword[count+1]);
    // }

    printf("Please enter CTF%d password: ", CTFNUM);
    int c = '\0';
    char *in = struk.input;
    int counter = 0;
    while (((c = getchar()) != EOF) && (c != '\n') && (counter < (BUFSIZE - 1)))
    {
        if (c == '\n')
        {
            break;
        }
        struk.suc = (char)(strcmp((char*)password, struk.input) == 0);
        in[counter] = c;
        counter++;
    }
    in[counter] = 0;
    if (!struk.suc)
    {
        struk.suc = (char)(strcmp((char*)password, struk.input) == 0);
    }

    if (struk.suc == 0)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", in, CTFNUM);
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, flag);
    }
    return 0;
}
