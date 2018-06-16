#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* mystrncat(char *dst, const char *src, int src_len)
{
	int dst_len = 0;
	char *tmp;

	if (dst)
		dst_len = strlen(dst);
	printf("dst: %s, dst_len: %d, src: %s, src_len: %d\n",
			dst, dst_len, src, src_len);

	tmp = realloc(dst, (src_len + dst_len + 1) * sizeof(char));
	if (!tmp) {
		printf("mystrncat failed due to allocation failure\n");
		exit(-1);
	}

	snprintf(tmp + dst_len, src_len + 1, "%s", src);

	printf("tmp: %s\n", tmp);
	return tmp;
}

char* addBoldTag(char* s, char** dict, int dictSize)
{
	char *ret = NULL;
	int in_tag = 0;
	int input_len;
	int rightmost = 0;
	int i, j;

	if (!s)
		return NULL;

	if (!dict || dictSize <= 0)
		return NULL;

	input_len = strlen(s);

	for (i = 0; i < input_len; i++) {
		for (j = 0; j < dictSize; j++) {
			if (!dict[j])
				continue;
			int word_len = strlen(dict[j]);
			char *sub = malloc((word_len + 1) * sizeof(char));
			if (!sub) {
				printf("failed to allocate sub string\n");
				return NULL;
			}

			if (i + word_len <= input_len) {
				snprintf(sub, word_len + 1, "%s", s + i);
				printf("word: %s, sub: %s\n", dict[j], sub);
				if (strcmp(sub, dict[j]) == 0)
					rightmost = i + word_len > rightmost ? i + word_len : rightmost;
			}
			free(sub);
		}
		printf("in_tag: %d, i: %d, rightmost: %d\n", in_tag, i, rightmost);
		if (i < rightmost) {	/* Match */
			if (!in_tag) {
				ret = mystrncat(ret, "<b>", strlen("<b>"));
			}
			in_tag = 1;
		} else {				/* Not Match */
			if (in_tag) {
				ret = mystrncat(ret, "</b>", strlen("</b>"));
				in_tag = 0;
			}
		}

		ret = mystrncat(ret, s + i, 1);
	}

	if (in_tag)
		ret = mystrncat(ret, "</b>", strlen("</b>"));

	return ret;
}

int main(void)
{
	char s[] = "aaabbbcc";
	char *dict[2];

	dict[0] = NULL;
	dict[1] = NULL;

	printf("%s\n", addBoldTag(s, dict, sizeof(dict)/sizeof(char *)));

	return 0;
}
