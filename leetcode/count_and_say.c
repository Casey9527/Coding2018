/*
 * LC-38: Count and say
 *
 * Few points needs to clarify

 * 1. snprintf(s, n, "format"...) print at most n-1 of characters to the string
 * 2. char *dst; sizeof(dst) return how many bytes the pointer dst takes.
 * 3. calloc(count, size_of_single_unit)
 * 4. realloc(buffer, new_size)
 * 5. while((s[j++])); and while(s[j]) {j++} are different regards the final value of j;
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* countAndSay(int n) {
    char *src;
    char *dst;
    
    if (n <= 0)
        return NULL;
    
    src = malloc(sizeof("1"));
    if (!src) {
        printf("cannot allocate memory\n");
        return NULL;
    }
    
    snprintf(src, sizeof("1"), "1");
    
    if (n == 1)
        return src;

    while (--n) {
        dst = calloc(2 * strlen(src) + 1, sizeof(char)); 
        printf("allocate %lu bytes\n", 2 * strlen(src) + 1);
        if (!dst) {
            printf("calloc failed\n");
            return NULL;
        }

        char c;
        char *tmp;
        int count;
        int i = 0;
        int j = 0;

        while (1) {
            c = src[i];
            count = 0;
            
            while (src[i] == c && src[i] != '\0')
                count++, i++;
            
            sprintf(dst + j, "%d%c", count, c);
            /*
             * or use 
             * while (dst[j]) {j++}
             */
            while (dst[++j])
                ;

            //printf("inner dst: %s\n", dst);
            //printf("j: %d\n", j);
            
            if (src[i] == '\0')
                break;
        }
        
        dst[j] = '\0';  // do this explicitly even though we used calloc
        printf("n: %d, dst: %s\n", n, dst);
        tmp = src;
        src = dst;
        dst = realloc(dst, strlen(dst) + 1);
        if (!dst) {
            printf("resize string failed\n");
            return NULL;
        }

        free(tmp);
    }
    
    return dst;
}

int main(int ac, char **av)
{
    if (ac == 1) {
        return -1;
    }

    char *ret;

    ret = countAndSay(atoi(av[1]));

  //  printf("ret: %s\n", ret);

    return 0;
}