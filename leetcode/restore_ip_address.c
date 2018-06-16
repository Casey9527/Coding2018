/**
 * LC-93
 *
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 * Example: 
 * Input: "25525511135"
 * Output: ["255.255.11.135", "255.255.111.35"]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * get_vaid_octet()
 *  copy n char from s to one octet and append it with '\0'.
 */
int get_valid_octet(char *s, int n, char *octet)
{
    int value;
    
    if (n > 3)
        return -1;
    
    if (n > strlen(s))
        return -1;
        
    snprintf(octet, n + 1, "%s", s);
    value = atoi(octet);
    if (value < 0 || value > 255)
        return -1;
    
    if (value == 0 && n != 1)
        return -1;
    
    if (value != 0 && octet[0] == '0')
        return -1;
    
    return 0;
}

char** restoreIpAddresses(char* s, int* returnSize) {
    char **ret = NULL;
    char octets[4][4];
    char *valid_ip;
    int value;
    int i, j, k, len;

    len = strlen(s);

    if (!s) {
    	*returnSize = 0;
    	return NULL;
    }

    for (i = 1; i <= 3; i++) {	/* first octet */
        if (get_valid_octet(s, i, octets[0]) != 0)	
            continue;

    	for (j = 1; j <= 3; j++) { /* second octet */
            if (get_valid_octet(s + i, j, octets[1]) != '\0')
                continue;

			for (k = 1; k <= 3; k++) {	/* third octet */
                if (get_valid_octet(s + i + j, k, octets[2]) != 0)
                    continue;

				if (get_valid_octet(s + i + j + k, len - i - k - j, octets[3]) != 0) /* fourth octet */
                    continue;
                
				//printf("octets: %s.%s.%s.%s\n", octets[0], octets[1], octets[2], octets[3]);

				valid_ip = malloc((len + 4) * sizeof(char));
				if (!valid_ip) {
					printf("Cannot allocate memory\n");
					return NULL;
				}

				snprintf(valid_ip, len + 4, "%s.%s.%s.%s", octets[0], octets[1], octets[2], octets[3]);

				ret = (char**)realloc(ret, (*returnSize + 1) * sizeof(char *));
				if (!ret) {
					printf("Cannot allocate memory\n");
					return NULL;
				}
				ret[*returnSize] = valid_ip;
				(*returnSize)++;
			}	/* End of last two octets*/
    	} /* End of second octet */
    } /* End of first octet */

	return ret;
}

int main(int ac, char **av)
{
	if (ac != 2) {
		return -1;
	}

	char **ip_addresses;
	int size = 0;

	ip_addresses = restoreIpAddresses(av[1], &size);

	while (size) {
		printf("%s\n", ip_addresses[size - 1]);
		size--;
	}

	return 0;
}



