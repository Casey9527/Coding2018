#include <stdio.h>


int main()
{
	int a = -2147483648;
	printf("INT_MIN - 1: %d\n", a - 1);

	int b = 2147483647;
	printf("INT_MAX + 1: %d\n", b + 1);

	int c = 1052254545;
	printf("1052254545 * 10: %d\n", 1052254545 * 10);
	return 0;
}
