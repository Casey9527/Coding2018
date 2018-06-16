#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char *s, int i, int j)
{
	char tmp = s[i];
	s[i] = s[j];
	s[j] = tmp;
}

void str_permutations_sub(char *s, int pos, int n)
{
	int i;

	if (s[pos + 1] == '\0') {
		printf("%s\n", s);
		return;
	}

	for (i = pos; i < n; i++) {
		swap(s, pos, i);
		str_permutations_sub(s, pos + 1, n);
		swap(s, pos, i);
	}
}

void str_permutations(char *s, int n)
{
	if (!s)
		return;
	str_permutations_sub(s, 0, n);
}

int main(int ac, char **av)
{
	if (ac != 2) {
		printf("usage: %s <string>\n", av[0]);
		return -1;
	}

	str_permutations(av[1], strlen(av[1]));

	return 0;
}
