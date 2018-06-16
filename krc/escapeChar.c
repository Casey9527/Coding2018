// C program to illustrate
// \a escape sequence
#include <stdio.h>
int main(void)
{
	printf("My mobile number is 7\a8\a7\a3\a9\a2\a3\a4\a0\a8\a\n");

    // Here we are using \v, which
    // is vertical tab character.
   // printf("Hello friends");
 
   printf("\v Welcome to GFG\n");

    printf("Hello\\GFG\n");


    // we are using \OOO escape sequence, here 
    // each O in "OOO" is one to three octal 
    // digits(0....7).
    char* s = "A\0725\n";
    printf("%s", s);

    // We are using \xhh escape sequence.
    // Here hh is one or more hexadecimal
    // digits(0....9, a...f, A...F).
    s = "B\x4a\n";
    printf("%s", s);

	// \b - backspace character transfers
	// the cursor one character back with 
	// or without deleting on different 
	// compilers.
	printf("Hello Geeks\b\b\b\bF");


	getchar();

	printf("This escape, \r, moves the active position to the initial position of the current line.");

	getchar();

    return 0;
}
