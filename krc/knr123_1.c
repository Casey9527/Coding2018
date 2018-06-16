/******************************************************
"Write a program to remove all comments from a C program. 
Don't forget to handle quoted strings and character 
constants properly. C comments do not nest."

Author: Rick Dearman (rick@ricken.demon.co.uk) 
******************************************************/

#include <stdio.h>

#define MAXLINE 1000 /* max input line size */
char line[MAXLINE]; /*current input line*/

int fget_line(FILE *f)
{
  int c, i;
  extern char line[];
  
  for (i = 0; i < MAXLINE - 1 && (c = fgetc(f)) != EOF && c != '\n'; ++i)
    line[i] = c;

  if(c == '\n') {
      line[i] = c;
      ++i;
  }

  line[i] = '\0';
  return i;
}

int main(int ac, char **av)
{

  FILE *in, *out;
  int in_comment,len;
  int in_quote;
  int t;
 
  if (ac != 3) {
    return -1;
  } 

  in = fopen(av[1], "r");
  out = fopen(av[2], "w");

  if (!out || !in) {
    printf("cannot open file\n");
    return -1;
  }

  in_comment = in_quote = t = 0;
  while ((len = fget_line(in)) > 0 ) {
      t = 0;

      while (t < len) {
	       if (line[t] == '"')
		        in_quote = 1;

	       if (!in_quote) {
          	if (line[t] == '/' && line[t + 1] == '*') {
              t = t + 2;
              in_comment = 1;
            }

          	if (line[t] == '*' && line[t+1] == '/') {
              t = t + 2;
              in_comment = 0;
            }

          	if (in_comment == 1) {
              t++;
            } else {
              fputc(line[t], out);
              t++;
            }
	       } else {
              fputc(line[t], out);
              t++;
	       }
      }
    }

    fclose(in);
    fclose(out);

  return 0;
}



