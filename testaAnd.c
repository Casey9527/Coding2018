#include <stdio.h>
#include <stdlib.h>

#define MSG_CMSG_COMPAT 0x80000000

int main(int ac, char **av)
{
	if (ac != 2) {
		printf("usage: %s <flag_value>", av[0]);
		return -1;
	}
	int flags = atoi(av[1]);
	printf("flags: %d, MSG_CMSG_COMPAT: %d, &: %d\n", flags, MSG_CMSG_COMPAT, MSG_CMSG_COMPAT & flags);
	return 0;
}
