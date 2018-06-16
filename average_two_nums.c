
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define AVG(a, b) ({										\
		typeof(a) _a = (a);									\
		typeof(b) _b = (b);									\
		(void) (&_a == &_b);								\
		((_a >> 1) + (_b >> 1) + ((_a & 1) & (_b & 1)));})	\

int main(int ac, char **av)
{
	if (ac != 3)
		return -1;

	int a, b, c;
	a = atoi(av[1]);
	b = atoi(av[2]);

	c = AVG(a, b);

	printf("INT_MAX: %d, INT_MIN: %d\n", INT_MAX, INT_MIN);
	printf("sizeof int: %lu\n", sizeof(int));

	printf("%d\n", c);

	return 0;
}