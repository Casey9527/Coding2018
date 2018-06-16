
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareVersion(char* version1, char* version2)
{
	char *word1, *brkt1;
	char *word2, *brkt2;

	if (!version1 || !version2)
		return -1;

	for (word1 = strtok_r(version1, ".", &brkt1), word2 = strtok_r(version2, ".", &brkt2);
		 word1 || word2;
		 word1 = strtok_r(NULL, ".", &brkt1), word2 = strtok_r(NULL, ".", &brkt2))
	{
		int num1, num2;
		
		if (!word1)
			num1 = 0;
		else
			num1 = atoi(word1);

		if (!word2)
			num2 = 0;
		else
			num2 = atoi(word2);

		//printf("num1: %d, num2: %d\n", num1, num2);

		if (num1 == num2)
			continue;

		return num1 > num2 ? 1 : -1;
	}

	return 0;
}

int main(int ac, char **av)
{
	if (ac != 3)
		return -1;

	int ret;

	ret = compareVersion(av[1], av[2]);
	printf("result: %d\n", ret);

	return 0;
}