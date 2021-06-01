/*
Capture the flag demo 6.
Obfuscated password 
Obfuscated flag 

pass: L324$@#LL@#$Ld2LL$23$5d
flag: wow, that's a pretty long string for a flag man...and there's not even any special characters or anything

Cross-compiled in 64bit Ubuntu 14
g++ -m32 -s CTF6.c -fno-stack-protector -o CTF6
-m32 : cross-compile for 32 bit
-s : strip symbols
-fno-stack-protector : don't protect against stack overflow
*/

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
	int i[6] = 
	{ 
		0x68646698,
		0x98468048,
		0x48468098,
		0x9864c898,
		0x66644898,
		0x00c86a48
	};
	char *pw = NULL, *flag = NULL, *input = NULL, output[27], ret;
	int  f[27] = 
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
		0x000000ce
	};
	
	pw = (char*)&i;
	flag = (char*)&f;
	
	int count = 0;
	// de-obfuscate flag
	for (count = 0; count < (27*4)+1; count++)
	{
		flag[count] = (char)((unsigned char)flag[count] / 2);
	}
	// de-obfuscate password
	for (count = 0; count < (6*4)+1; count++)
	{
		pw[count] = (char)((unsigned char)pw[count] / 2 );
	}

	printf("Please enter the password: ");
	int c = '\0', charcount = 0;
	while ((c = getchar()) != EOF)
	{
		input = (char*)realloc(input, sizeof(char) * charcount);
		char cc = (char)c;
		if (cc == '\n')
		{
			break;
		}
		input[charcount] = cc;
		charcount++;
	}
	// strcmp returns zero when strings are equal
	// remove the & 64 and any buffer overflow with a character
	// whose value is odd will result in success
	// I added the 64 so there was a smaller chance of 
	// first-attempt lucky success
	// (64 & true) == 65 == 'A'
	ret = (strcmp(pw, input) == 0) & 64;
	strcpy(output, input);
	char x = 1;
	if (ret != 'A')
	{
		printf("Sorry, '%s' is not the correct password\n", output);
	}
	else
	{
		printf("Success, flag #6 is '%s'\n", flag);
	}

	free(input);
	return 0;
}


