
#include <stdio.h>

#define PRINT(fmt, args...)	\
	printf(fmt, args)


int main(void)
{
	PRINT("your input: %s, a number: %d\n", "Hello world", 5);
	return 0;
}