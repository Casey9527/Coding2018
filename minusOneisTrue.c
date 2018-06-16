
/*
 * Keep in mind: in C only zero is false in while() or if()
 * Other integers are all true.
 */

#include <stdio.h>

int main(void)
{
	// -1 is true in if/while expression
	while (-1) {

		printf("-1 is true\n");

	}


	return 0;
}
