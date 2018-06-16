#include <stdio.h>

#define MINLEN  11

int
get_line(char s[], int max);

int
main(void)
{
    int len, c, i;
    char line[MINLEN];

    while ((len = get_line(line, MINLEN)) != 0) {
        if ((len == MINLEN-1) && (line[len-1] != '\n')) {
            printf("%s", line);
            while ((c = getchar()) != EOF && c != '\n')
                putchar(c);
            putchar('\n');
        }
    }

    return 0;
}

int
get_line(char s[], int max) {
    int i, c;
    for (i=0; i<max-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}