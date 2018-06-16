#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s = NULL;
	int a = strcmp("ab", s);

	printf("a: %d\n", a);

	return 0;
}
