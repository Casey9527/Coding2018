
#include <stdio.h>

int main(void)
{
	int inspace;
	char c;

	inspace = 0;

	while ((c = getchar()) != EOF) {

		if (c == ' ') {
			if (!inspace) {
				putchar(c);
				inspace = 1;
			}
		} else {
			putchar(c);
			inspace = 0;
		}

	}

	return 0;
}