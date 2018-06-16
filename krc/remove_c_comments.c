#include <stdio.h>

enum pattern {
	QUOTE,
	SLASH_SLASH,
	SLASH_STAR,
	STAR_SLASH,
};

int get_pattern(char c1, char c2)
{
	if (c2 == '"')		/* Only check current char */
		return QUOTE;

	if (c1 == '/' && c2 == '/')
		return SLASH_SLASH;

	if (c1 == '/' && c2 == '*')
		return SLASH_STAR;

	if (c1 == '*' && c2 == '/')
		return STAR_SLASH;

	return -1;
}


void remove_c_comments(FILE *f, FILE *o)
{
	char p;
	char c;
	int pat;

	if (!f || !o)
		return;

	p = -1;
	while ((c = fgetc(f)) != EOF) {
		
			pat = get_pattern(p, c);
			if (pat == QUOTE) {									/* Quote */
				printf("%c%c\n", p, c);
				while ((c = fgetc(f)) != ';' && c != EOF)
					fputc(c, o);
				// c = ; or c = EOF
			} else if (pat == SLASH_SLASH) {					/* Slash-slash */
				while ((c = fgetc(f)) != '\n' && c != EOF)
					;
				// c = '\n' or c = EOF
			} else if (pat == SLASH_STAR) {						/* Slash-star */

				p = fgetc(f);
				if (p == EOF)
					break;

				for (c = fgetc(f); c != EOF; p = c) {
					if (get_pattern(p, c) == STAR_SLASH)
						break;
				}
				
				if (c != EOF) {
					c = fgetc(f);
				}
				// c = EOF or other
			}

			if (c == EOF)
				break;

			fputc(c, o);

			p = c;
	}
}

int main(int ac, char **av)
{
	if (ac != 3)
		return -1;

	FILE *f = fopen(av[1], "r");
	if (!f) {
		printf("cannot open input file\n");
		return -1;
	}

	FILE *o = fopen(av[2], "w");
	if (!o) {
		printf("cannot open output file\n");
		return -1;
	}

	remove_c_comments(f, o);

	fclose(f);
	fclose(o);
	return 0;
}

