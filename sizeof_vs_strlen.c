#include <string.h>
#include <stdio.h>

int main(void)
{
	printf("strlen(\"hello\"): %lu, sizeof(\"hello\"): %lu\n",
			strlen("hello"), sizeof("hello"));
	return 0;
}
