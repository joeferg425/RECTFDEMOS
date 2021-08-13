/*
Obfuscated password
Obfuscated flag

pass: L324$@#LL@#$Ld2LL$23$5d
flag: wow, that's a pretty long string for a flag man...and there's not even any special characters or anything

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "get_input.hpp"
#include "crclike.hpp"

using namespace std;

#define BUFSIZE 512
#define INSIZE 32
#define CTFNUM 6
// #define DEBUG_PASSWORD 1

// struct definition
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
    // setup variables
    struct my_struct struk = {0};
    unsigned char password[BUFSIZE] = {0};
    unsigned char flag[BUFSIZE] = {0};
    unsigned char distraction01[BUFSIZE] = {0};
    unsigned char distraction02[BUFSIZE] = {0};
    unsigned char distraction03[BUFSIZE] = {0};
    unsigned char distraction04[BUFSIZE] = {0};
    unsigned char distraction05[BUFSIZE] = {0};
    int password_len = 0;
    int flag_len = 0;
    int distraction_len = 0;
    int c = '\0';
    int counter = 0;

    // strings
    unsigned char distraction01_ob[BUFSIZE] = {0x64, 0x11, 0x06, 0x07, 0x4C, 0x4D, 0x1B, 0x00, 0x17, 0x79};
    unsigned char distraction02_ob[BUFSIZE] = {0x70, 0x40, 0x5D, 0x1D, 0x40, 0x5D, 0x6D};
    unsigned char distraction03_ob[BUFSIZE] = {0x67, 0x56, 0x58, 0x1D, 0x00, 0x11, 0x17, 0x10, 0x52, 0x5D, 0x0F, 0x62};
    unsigned char distraction04_ob[BUFSIZE] = {0x25, 0x46, 0x06, 0x09, 0x00, 0x0D, 0x13, 0x2D, 0x3B, 0x0B, 0x00, 0x1D, 0x57, 0x25};
    unsigned char distraction05_ob[BUFSIZE] = {0x21, 0x56, 0x1F, 0x01, 0x04, 0x1E, 0x1A, 0x0A, 0x02, 0x0D, 0x5D, 0x31};
    unsigned char password_ob[BUFSIZE] = {0x4C, 0x7F, 0x01, 0x06, 0x10, 0x64, 0x63, 0x6F, 0x00, 0x0C, 0x63, 0x07, 0x68, 0x28, 0x56, 0x7E, 0x00, 0x68, 0x16, 0x01, 0x17, 0x11, 0x51, 0x64};
    unsigned char flag_ob[BUFSIZE] = {0x77, 0x18, 0x18, 0x5B, 0x0C, 0x54, 0x1C, 0x09, 0x15, 0x53, 0x54, 0x53, 0x41, 0x41, 0x50, 0x02, 0x17, 0x11, 0x00, 0x0D, 0x59, 0x4C, 0x03, 0x01, 0x09, 0x47, 0x53, 0x07, 0x06, 0x1B, 0x07, 0x09, 0x47, 0x46, 0x09, 0x1D, 0x52, 0x41, 0x41, 0x46, 0x0A, 0x0D, 0x06, 0x47, 0x4D, 0x0C, 0x0F, 0x40, 0x00, 0x00, 0x4F, 0x0F, 0x0A, 0x44, 0x54, 0x1C, 0x0D, 0x17, 0x17, 0x42, 0x54, 0x53, 0x4E, 0x01, 0x1B, 0x54, 0x45, 0x13, 0x13, 0x0B, 0x4E, 0x41, 0x0F, 0x17, 0x59, 0x53, 0x03, 0x15, 0x06, 0x0A, 0x08, 0x0D, 0x4C, 0x43, 0x0B, 0x09, 0x13, 0x13, 0x02, 0x17, 0x11, 0x17, 0x01, 0x53, 0x4F, 0x1D, 0x52, 0x41, 0x0F, 0x17, 0x0D, 0x1C, 0x01, 0x07, 0x09, 0x67};
    char *in = struk.input;
    char prompt[BUFSIZE] = {0};

    // de-obfuscation
    un_xorit(distraction01_ob, BUFSIZE, distraction01, &distraction_len);
#ifdef DEBUG_PASSWORD
    printf("dust8unny: %s\n", (char *)distraction01);
#endif
    un_xorit(password_ob, BUFSIZE, password, &password_len);
#ifdef DEBUG_PASSWORD
    printf("L324$@#LL@#$Ld2LL$23$5d: %s\n", (char *)password);
#endif
    un_xorit(distraction02_ob, BUFSIZE, distraction02, &distraction_len);
#ifdef DEBUG_PASSWORD
    printf("p0mp0m: %s\n", (char *)distraction02);
#endif
    un_xorit(distraction03_ob, BUFSIZE, distraction03, &distraction_len);
#ifdef DEBUG_PASSWORD
    printf("g1itterb0mb: %s\n", (char *)distraction03);
#endif
    un_xorit(flag_ob, BUFSIZE, flag, &flag_len);
#ifdef DEBUG_PASSWORD
    printf("%s\n", (char *)flag);
#endif
    un_xorit(distraction04_ob, BUFSIZE, distraction04, &distraction_len);
#ifdef DEBUG_PASSWORD
    printf("%%cellar_door%%: %s\n", (char *)distraction04);
#endif
    un_xorit(distraction05_ob, BUFSIZE, distraction05, &distraction_len);
#ifdef DEBUG_PASSWORD
    printf("!whimsical1: %s\n", (char *)distraction05);
#endif

    // prompt for input
    sprintf(prompt, "Please enter CTF%d password:  >>", CTFNUM);
    printf("%s\n", prompt);
    if (argc < 2)
    {
        while (((c = getchar()) != EOF) && (c != '\n') && (counter < (BUFSIZE - 1)))
        {
            if (c == '\n')
            {
                break;
            }
            struk.suc = (char)(strcmp((char *)password, struk.input) == 0);
            in[counter] = c;
            counter++;
        }
        in[counter] = 0;
    }
    else
    {
        strcpy((char *)struk.input, argv[1]);
        counter = strlen(argv[1]);
        if (struk.input[counter] != 0)
        {
            struk.input[counter] = 0;
            counter++;
        }
    }

    // test for correct password
    if (!struk.suc)
    {
        struk.suc = (char)(strcmp((char *)password, struk.input) == 0);
    }

    if (struk.suc == 0)
    {
        printf("Sorry, '%s' is not the CTF%d password\n", in, CTFNUM);
#ifdef DEBUG_PASSWORD
        printf("CTF%d password is \"%s\"\n", CTFNUM, (char *)password);
#endif
    }
    else
    {
        printf("Success, CTF%d flag is '%s'\n", CTFNUM, flag);
    }
    return 0;
}
