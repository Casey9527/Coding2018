/*
 * Find palindrome which is centered with s[l], s[r]
 * l might be equal to r
 */
void find_palindrome(char *s, int len, int *l, int *r)
{
    while (*l >= 0 && *r <= len - 1) {
        if (s[*l] != s[*r])
            break;
        (*l)--;
        (*r)++;
    }
    //printf("l: %d, r: %d\n", *l, *r);
}

char* longestPalindrome(char* s) {
    int maxlen;
    int len;
    int pos;
    char *max_palindrome;
    int i, l, r;
    
    if (!s)
        return NULL;
    
    len = strlen(s);  
    if (len <= 0)
        return NULL;
    
    pos = NULL;
    maxlen = 0;

    for (i = 0; i < len; i++) {
        // centered at one character
        l = i;
        r = i;
        find_palindrome(s, len, &l, &r);
        if (maxlen < r - l - 1) {
            maxlen = r - l - 1;
            pos = l + 1;
        }
        
        // centered at two character
        l = i;
        r = i + 1;
        find_palindrome(s, len, &l, &r);
        if (maxlen < r - l - 1) {
            maxlen = r - l - 1;
            pos = l + 1;
        }
    }
    
    max_palindrome = malloc((maxlen + 1) * sizeof(char));
    if (!max_palindrome) {
        printf("cannot allocate memory\n");
        return NULL;
    }
    snprintf(max_palindrome, maxlen + 1, "%s", s + pos);
    return max_palindrome;
}