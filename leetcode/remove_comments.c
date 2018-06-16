
#if 0
/*
 * LC-722: remove comments
 *

Tricky testcases:

1. once found /*, should move two steps or one step ? 
   if one step, "/*/" as comment start will lose "/*". 
   If two step, "/*/" as comment end will lose "*/"

d/*/e/*/f

2. if you found //, you cannot completely ignore the remaining line.

because line comment might be inside block comment

/*ab//cd*/

3. gather multi-lines together

/*abcd
  efgh
  lmn*/ijk

4. mixed

abcd//efg
hi/*jk*/lmn
opq/*rsj*/xyz



 */

#endif

/* 
 * append_one_char()
 *	Resize the string and append one character at the end.
 * *len is length before appending the character.
 */
int append_one_char(char **s_ref, int *len, char c)
{
    char *tmp;		/* 
    				 * tmp is a local variable whose value is assigned to *s_ref.
					 * The value is the address of string buffer.
					 * tmp is used in realloc(). Once resize succeed, its value
					 * represents address of the resized buffer. 
					 * we have to update *s_ref once we have a new buffer address.
    				 *
    				 */
    
    tmp = *s_ref;		
    tmp = realloc(tmp, *len * sizeof(char));
	if (!(tmp)) {
		printf("append_one_char failed\n");
		return -1;
	}

	tmp[*len] = c;
	(*len)++;
    *s_ref = tmp;	
    
	return 1;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeComments(char** source, int sourceSize, int* returnSize) {
	char **ret;
	int i, j;
	int in_block_comment;
    int in_line_comment;

    if (!source || sourceSize <= 0)
    	return NULL;

    ret = NULL;
    in_block_comment = 0;
    in_line_comment = 0;

   	char *sout = NULL;
    int o_len = 0;

    for (i = 0; i < sourceSize; i++) {
    	char *sin  = source[i];
        //printf("sin: %s\n", sin);
    	if (!sin)
    		return NULL;

    	int len = strlen(sin);
    	if (len <= 0)
    		continue;

        in_line_comment = 0;

    	for (j = 0; j < len; j++) {
    		char curr, next;
    		curr = sin[j];
    		next = sin[j + 1];

    		if (curr == '/') {
    			if (next == '/' && !in_block_comment) {
    				in_line_comment = 1;
                } else if (next == '*' && !in_line_comment && !in_block_comment) {
    				in_block_comment = 1;
                    if (j + 2 < len && sin[j + 2] == '/') {	// /*/
                        j++;
                    }
    			}
    		}

    		if (!in_block_comment && !in_line_comment) {
              //  printf("i: %d, %c\n", i, curr);
    			if (!append_one_char(&sout, &o_len, curr))
    				return NULL;
            }

    		if (curr == '*' && next == '/' && in_block_comment) {
    			in_block_comment = 0;
    			j++;
    		}
    	}

    	if (in_block_comment && !in_line_comment)
    		continue;

        if (!sout)
            continue;

    	if (!append_one_char(&sout, &o_len, '\0'))
    		return NULL;

    	ret = (char **)realloc(ret, (*returnSize + 1) * sizeof(char *));
    	if (!ret) {
    		printf("failed to resize line array\n");
    		return NULL;
    	}

       // printf("sout: %s\n", sout);
    	ret[*returnSize] = sout;
    	(*returnSize)++;
    	sout = NULL;
    	o_len = 0;

    }

    return ret;
}
