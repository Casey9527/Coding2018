
#include <stdio.h>


int main(void)
{
	char non_const_str[] = "kexinc";
	char *s = "KEXINC";
	int i = 0;
	int j = 0;

	while (s[i++] != 'N')
		;

	printf("s[i]: %c\n", s[i]);

	while (s[j] != 'N') {
		j++;
	}

	printf("s[j]: %c\n", s[j]);


	non_const_str[0] = 'e';	// yes, it is non-const mutable string.

	printf("%s\n", non_const_str);

	return 0;
}