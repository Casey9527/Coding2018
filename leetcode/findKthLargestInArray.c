
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *nodes;
    int len;
    int size;
} heap_t;

heap_t *heap_new()
{
    return calloc(1, sizeof(heap_t));
}

void push(heap_t *h, int key)
{
	int i, j;
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = realloc(h->nodes, h->size * sizeof(int));
        if (!h->nodes) {
            printf("Failed to resize the heap\n");
            exit(-1);
        }
    }

    i = h->len + 1;
    j = i / 2;

    while (i > 1 && h->nodes[j] < key) {
		h->nodes[i] = h->nodes[j];
		i = j;
		j = i / 2;
	}

	h->nodes[i] = key;
	++h->len;
	printf("push: %d\n", key);
}

int pop(heap_t *h)
{
	int ret;
	int i, j, k;
	if (!h->len) {
		printf("Failed to pop. Queue is empty.\n");
		return -1;
	}

	ret = h->nodes[1];
	h->nodes[1] = h->nodes[h->len];

	i = 1;
	while (i < h->len) {
		k = h->len;
		j = 2 * i;
		if (j <= h->len - 1 && h->nodes[j] > h->nodes[k])
			k = j;
		if (j + 1 <= h->len - 1 && h->nodes[j + 1] > h->nodes[k])
			k = j + 1;

		h->nodes[i] = h->nodes[k];
		i = k;
	}

	--h->len;
	printf("pop: %d\n", ret);
	return ret;
}

int findKthLargest(int* nums, int numsSize, int k)
{
	int ret;
	int i;
	heap_t *h = heap_new();
	if (!h) {
		printf("failed to allocate heap\n");
		return -1;
	}

	printf("numsSize: %d, k: %d\n", numsSize, k);

	for (i = 0; i < numsSize; i++)
		push(h, nums[i]);

	printf("begin pop\n");

	for (i = 0; i < k; i++)
		ret = pop(h);

	return ret;
}


int main(int ac, char *av[])
{
	if (ac != 2)
		return -1;

	int a[] = {3,2,3,1,2,4,5,5,6};
	int ret;

	ret = findKthLargest(a, sizeof(a) / sizeof(int), atoi(av[1]));
	printf("ret: %d\n", ret);

	return 0;
}
