#include <stdio.h>

int main(int ac, char *av[])
{
//	if (ac != 2)
//		return 1;

	printf("%s\n", av[0]);

	char *s = av[1];

	printf("%s\n", s);

	return 0;
}
