/*
 * print out lines that larger than 80 characters.
 */
#include <stdio.h>

#define MAX_LINE_LENGTH 10

int main(void)
{
    char line[MAX_LINE_LENGTH + 1];
    char c;
    int i = 0;

    while ((c = getchar()) != EOF) {
        if (i < MAX_LINE_LENGTH) {
            line[i++] = c;
            if (c == '\n')
                i = 0;
        } else {
            if ( i == MAX_LINE_LENGTH) {
                line[++i] = '\0';
                printf("%s", line);
            }
            putchar(c);
            if (c == '\n')
                i = 0;
        }
    }

    return 0;
}
