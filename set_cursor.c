
#include <stdio.h>	/* printf() */
#include <stdlib.h>	/* atoi() */

void SetCursorPos(int XPos, int YPos)
{
 printf("\033[%d;%dH", YPos+1, XPos+1);
}

int main(int ac, char **av)
{
	int x;
	int y;

	if (ac != 3)
		return -1;

	x = atoi(av[1]);
	y = atoi(av[2]);

	SetCursorPos(x, y);

	return 0;
}
