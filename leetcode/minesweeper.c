#include <stdio.h>
#include <stdlib.h>

void updateBoard_helper(char **bd, int row, int col, int x, int y)
{
	int cnt = 0;
	int i, j;

	/* unreveal a mine */
	if (bd[x][y] == 'M') {
		bd[x][y] = 'X';
		return;
	}

	/* revealed cells */
	if (bd[x][y] != 'E') {
		return;
	}

	/* adjacent mine count */
	for (i = x - 1; i <= x + 1; i++) {
		if (i < 0 || i >= row)
			continue;
		for (j = y - 1; j <= y + 1; j++) {
			if (j < 0 || j >= col)
				continue;
//			if (i == x && j == y)
//				continue;
			if (bd[i][j] == 'M')
				cnt++;
		}
	}

	if (cnt != 0) {
		bd[x][y] = cnt - 0 + '0';
	} else {
		bd[x][y] = 'B';
		for (i = x - 1; i <= x + 1; i++) {
			if (i < 0 || i >= row)
				continue;
			for (j = y - 1; j <= y + 1; j++) {
				if (j < 0 || j >= col)
					continue;
//				if (i == x && j == y)
//					continue;
				if (bd[i][j] == 'E')
					updateBoard_helper(bd, row, col, i, j);
			}
		}
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** updateBoard(char** board, int boardRowSize, int boardColSize, int* click,
                   int clickSize, int** columnSizes, int* returnSize)
{
	int i, j;
	int *columnSizes_deref;
	/* Sanity check */
    if (!board || boardColSize <= 0 || boardRowSize <= 0)
    	goto error;

    if (!click || clickSize != 2)
    	goto error;

	/* Return board */
    char **bd = (char **)malloc(boardRowSize * sizeof(char *));
    if (!bd) {
    	printf("failed to allocate return board\n");
    	goto error;
    }

	/* Each row of return board */
    for (i = 0; i < boardRowSize; i++) {
    	bd[i] = (char *)malloc(boardColSize * sizeof(char));
    	if (!bd[i]) {
    		printf("failed to allocate row of return board\n");
    		goto bd_alloc_fail;
    	}
    }

    for (i = 0; i < boardRowSize; i++)
    	for (j = 0; j < boardColSize; j++)
    			bd[i][j] = board[i][j];

    /* Row size of return board */
    *returnSize = boardRowSize;

    /* columnSizes[] */
	columnSizes_deref = *columnSizes;
    columnSizes_deref = (int *)malloc(*returnSize * sizeof(int));
    if (!columnSizes_deref) {
    	printf("failed to allocate columnSizes\n");
    	goto bd_alloc_fail;
    }

    for (j = 0; j < *returnSize; j++)
        columnSizes_deref[j] = boardColSize;

	*columnSizes = columnSizes_deref;

    updateBoard_helper(bd, boardRowSize, boardColSize, click[0], click[1]);
    return bd;

bd_alloc_fail:
	while (--i >= 0) {
		free(bd[i]);
	}

	free(bd);

error:
   	*returnSize = 0;
   	*columnSizes = NULL;
    return NULL;
}

int main(void)
{
	char **rbd;
	int *columnSizes;
	int returnSize;
	int click[2] = {1, 2};
	int i, j;

	char *bd[4] = { "B1E1B",
					"B1M1B",
					"B111B",
					"BBBBB"};
/*
	int click[2] = {3, 0};
	char *bd[4] = { "EEEEE",
					"EEMEE",
					"EEEEE",
					"EEEEE"};
*/
	rbd = updateBoard(bd, 4, 5, click, 2, &columnSizes, &returnSize);

	for (i = 0; i < returnSize; i++) {
		for (j = 0; j < columnSizes[i]; j++)
			printf("%c ", rbd[i][j]);
		printf("\n");
	}
	return 0;
}
