#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Longest word in dictionary
 */
char* longestWord(char** words, int wordsSize) {
	char *ret = NULL;
	int len = 0;
	int i, j, k;
	char *sub = malloc(30 * sizeof(char));
	if (!sub) {
		printf("failed to allocate sub string\n");
		exit(-1);
	}

	for (i = 0; i < wordsSize; i++) {	/* Iterate each word */
		int word_len = strlen(words[i]);
		int found;
		printf("ret: %s\n", ret);
		for (j = 0; j < word_len; j++) {	/* Make substring one char at a time */
			found = 0;
			snprintf(sub, j + 2, "%s", words[i]);
			printf("sub: %s\n", sub);
			for (k = 0; k < wordsSize; k++) {	/* Check if substring exist in dict */
				if (strcmp(words[k], sub) == 0) {	/* Substring found */
					found = 1;
					break;
				}
			}
			if (!found)	/* Skip this word */
				break;
		}

		if (!found)
			continue;

		if (!ret) {
			ret = words[i];
			len = word_len;
			continue;
		}

		if (len < word_len) {
			len = word_len;
			ret = words[i];
			continue;
		}

		if (len == word_len) {
			if (strcmp(words[i], ret) < 0)
				ret = words[i];
		}
	}

	free(sub);
	return ret;
}

int main(void)
{
	char *words[] =
//		{"w", "wo", "wor", "worl", "world"};
//	 	{"a", "banana", "app", "appl", "ap", "apply", "apple"};
//		{"b","br","bre","brea","break","breakf","breakfa","breakfas",
//		"breakfast","l","lu","lun","lunc","lunch","d","di","din","dinn","dinne","dinner"};
//		{"yo","ew","fc","zrc","yodn","fcm","qm","qmo","fcmz","z","ewq","yod","ewqz","y"};
//		{"k","lg","it","oidd","oid","oiddm","kfk","y","mw","kf","l","o","mwaqz","oi","ych","m","mwa"};
		{"ogz","eyj","e","ey","hmn","v","hm","ogznkb","ogzn","hmnm","eyjuo","vuq","ogznk","og","eyjuoi","d"};
	char *ret = NULL;

	ret = longestWord(words, sizeof(words)/sizeof(char *));
	
	printf("ret: %s\n", ret);
}
