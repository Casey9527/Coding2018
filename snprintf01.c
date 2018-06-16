#include <stdio.h>
#include <string.h>

int main(int ac, char *av[])
{
	if (ac != 2)
		return -1;

	char s[15];

	snprintf(s, strlen(av[1]) + 2, "%s-", av[1]);

	printf("s: %s\n", s);

	printf("-1/2 = %d\n", -1 / 2);
	return 0;
}
