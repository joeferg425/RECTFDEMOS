/*
Capture the flag demo 4.
Clear-text password 
Obfuscated flag

pass: Unbr4kable
flag: Bluesteel

Cross-compiled in 64bit Ubuntu 14
g++ -m32 -s CTF4.c -o CTF4
-m32 : cross-compile for 32 bit
-s : strip symbols
*/

#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
	int success = 0, i[3] = { 0xcaead884, 0xcacae8a6, 0x000000d8 };
	const char *distraction1 = "1234567";
	const char *distraction2 = "12345";
	const char *pw = "Unbr4kable";
	const char *distraction7 = "password1";
	const char *distraction8 = "12345";
	const char *distraction9 = "baseball";
	string input = "";
	char *flag = (char*)&i;
	
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
	// de-obfuscate flag
	for (int j = 0; j < 12; j++)
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
		printf("Success, flag #4 is '%s'\n", flag);
	}
	
	return 0;
}


