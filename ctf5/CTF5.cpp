/*
Capture the flag demo 5.
Obfuscated password
Obfuscated flag 

pass: Oddball
flag: Velociraptor

Cross-compiled in 64bit Windows 7 using Visual Studio 2013
*/

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
	unsigned int success = 0, i1[2] = { 0xc4c8c89e, 0x00d8d8c2 }, i2[4] = { 0xded8caac, 0xc2e4d2c6, 0xe4dee8e0, 0x0 };
	const char *distraction1 = "football";
	const char *distraction2 = "999999";
	char *pw = (char*)&i1;
	const char *distraction7 = "qwerty";
	const char *distraction8 = "tacocat";
	const char *distraction9 = "abc123";
	string input = "";
	char *flag = (char*)&i2;

	printf("Please enter the password: ");
	int c = '\0';
	string s = "";
	while ((c = getchar()) != EOF)
	{
		char cc = (char)c;
		if (cc == '\n')
		{
			break;
		}
		input += cc;
	}
	// de-obfuscate password
	for (int j = 0; j < 2 * 4; j++)
	{
		pw[j] = (char)(((unsigned char)pw[j]) / 2);
	}
	//de-obfuscate flag
	for (int j = 0; j < 3 * 4; j++)
	{
		flag[j] = (char)(((unsigned char)flag[j]) / 2);
	}
	success = strcmp(input.c_str(), pw);
	if (success)
	{
		printf("Sorry, '%s' is not the correct password\n", input.c_str());
	}
	else
	{
		printf("Success, flag #5 is '%s'\n", flag);
	}

	return 0;
}



