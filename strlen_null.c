#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s;

	printf("strlen(%s): %lu\n", s, strlen(s));

	printf("strlen(%s): %lu\n", "</b>", strlen("</b>"));
	return 0;
}
