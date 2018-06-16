#include <stdio.h>

void print_x()
{
	static int x = 0;
	printf("x: %d\n", x);
	x = x + 1;
}

int main(void)
{
	print_x();

	print_x();

	return 0;
}
