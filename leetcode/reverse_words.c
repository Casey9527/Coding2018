#include <stdio.h>
#include <string.h>


void reverse_string(char *s, int l, int r)
{
	char tmp;

	while (l < r) {
		tmp = s[l];
		s[l] = s[r];
		s[r] = tmp;
        l++, r--;
	}
}

void reverseWords(char *s)
{
	int len;
	int pos;
	int word_start;
	int i;

	if (!s)
		return;

	len = strlen(s);
	if (len <= 0)
		return;

	pos = 0;

	// step 1: reverse single word and remove extra space

	for (i = 0; i < len; i++) {
		if (s[i] == ' ') {
			continue;
		}

		word_start = pos;

		while (i < len && s[i] != ' ') {
			s[pos++] = s[i++];
		}

		reverse_string(s, word_start, pos - 1);

		if (s[i] == ' ')
			s[pos++] = ' ';
	}

	if (s[pos - 1] == ' ')
		pos = pos - 1;

	s[pos] = '\0';

	// step 2: reverse the whole string 
	reverse_string(s, 0, pos - 1);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return -1;

	char *s;

	printf("before:<%s>\n", av[1]);
	reverseWords(av[1]);
	printf("after: <%s>\n", av[1]);

	return 0;
}

