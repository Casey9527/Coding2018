
/*
 * Ex1-20-10
 * backslash to \\, tab to \t, backspace to \b
 */
#include <stdio.h>

int main(void)
{
	char c;
	
	while ((c = getchar()) != EOF) {
		if (c == '\\') {
			putchar('\\');
			putchar('\\');
		} else if (c == '\t') {
			putchar('\\');
			putchar('t');
		} else if (c == '\b') {
			putchar('\\');
			putchar('b');
		} else {
			putchar(c);
		}

	}

	return 0;
}