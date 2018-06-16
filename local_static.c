/*
 * Local static variable is initialized to zero by default.
 */

#include <stdio.h>

void print_x()
{
	static int x;
	printf("x: %d\n", x);
	x = x + 1;
}

int main(void)
{
	print_x();

	print_x();

	return 0;
}
