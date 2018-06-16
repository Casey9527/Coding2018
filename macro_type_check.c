#include <stdio.h>

#define max(a, b) ({		\
	typeof(a) _a = (a);		\
	typeof(b) _b = (b);		\
	(void) (&_a == &_b);	\
	_a > _b ? _a : _b; })	\

int main(void) {
	int a = 5;
	int b = 6;

	int c;

	c = max(a, b);

	printf("c: %d\n", c);

	return 0;
}