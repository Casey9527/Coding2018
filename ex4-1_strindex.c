/*
 * strindex(s, t)
 * Return the position of the rightmost occurrence of t in s.
 */

#include <stdio.h>

char *strindex(const char *s, const char *t)
{
    if (*t == '\0') {
        return (char *)s;
    }
	char *ret = NULL;
    char *src, *tar;

	while (*s) {
		tar = (char *)t;
        src = (char *)s;

		while (1) {
			if (*tar == '\0') {
                ret = (char *)s;    /* Update when there is a match */
                break;
            }
            if (*tar != *src) {
                break;
            }
            tar++, src++;
		}
        ++s;
	}
    return ret;
}

int main(int ac, char *av[])
{
    if (ac != 3) {
        printf("Usage: %s <haystack> <needle>\n", av[0]);
        return -1;
    }

    char *s = av[1];
    char *t = av[2];

    printf("strindex(%s, %s): %s\n", av[1], av[2], strindex(av[1], av[2]));
    return 0;
}
