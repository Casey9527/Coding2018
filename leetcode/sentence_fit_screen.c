/*
 * LC418 - Sentence Screen Fitting
 */

int wordsTyping(char** sentence, int sentenceSize, int rows, int cols)
{
    int cnt_in_use = 0;
    int i;
    int len = 0;
    char *formatted_str, *tmp;

    if (!sentence)
        return 0;

    if (sentenceSize <= 0 || rows <= 0 || cols <= 0)
        return 0;

    /* calculate size of formatted string */
    for (i = 0; i < sentenceSize; i++) {
		len += strlen(sentence[i]);
        len += 1;
    }

    /* create the formatted string */
    formatted_str = malloc((len + 1) * sizeof(char));
    if (!formatted_str)
        return 0;

    tmp = formatted_str;
    for (i = 0; i < sentenceSize; i++) {
        int n = strlen(sentence[i]);
		/*
		 * snprintf(char * restrict str, size_t size, const char * restrict format, ...);
		 *
		 * NOTE: snprintf write at most @size char to output string
		 * including terminating NULL. So at most (n - 1) chars of
		 * the format string is written to output string.
		 */
        snprintf(tmp, n + 2, "%s ", sentence[i]);
        tmp += n + 1;
    }

    for (i = 0; i < rows; i++) {
        cnt_in_use += cols;		/* cnt_in_use: all spaces in use */

		/* (cnt_in_use % len): index of next char in formatted string */
        if (formatted_str[cnt_in_use % len] == ' ') {
			/* The next char to be stored is a space, e.g. space in ab_cde,
			 * which means the current line ends with no space.
			 * Since we add a space in formatted string, we don't want to
			 * miss it in cnt_in_use so make it up.
			 */
            ++cnt_in_use;
        } else {
			/*
			 * We don't want to break same word.
			 * e.g. ab_cde, if next char is c then it's fine,
			 * but if it is d or e, we have to retreat.
			 */
            while (cnt_in_use > 0 && formatted_str[(cnt_in_use - 1) % len] != ' ')
            --cnt_in_use;
        }
    }

    return cnt_in_use / len;
}
