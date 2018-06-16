#include <stdio.h>

#define PATH_MAX	1024

int main(void)
{
	FILE *fp;
	int status;
	char path[PATH_MAX];

	fp = popen("ls *", "r");
	if (fp == NULL) {
		printf("popen failed\n");
		return -1;
	}

	while (fgets(path, PATH_MAX, fp) != NULL)
		printf("%s", path);

	pclose(fp);
}
