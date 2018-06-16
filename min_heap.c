#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int key;
	char *data;
} node_t;

typedef struct {
	node_t *nodes;
	int len;
	int size;
} heap_t;

heap_t* heap_new()
{
	return calloc(1, sizeof(heap_t));
}

void push(heap_t *h, int key, char *data)
{
	int i, j;
	if (h->len + 1 >= h->size) {
		h->size = h->size ? h->size * 2 : 4;
		h->nodes = realloc(h->nodes, h->size * sizeof(node_t));
		if (!h->nodes) {
			printf("Failed to resize the heap\n");
			exit(-1);
		}
	}

	for (i = h->len + 1, j = i / 2;
		 i > 1 && h->nodes[j].key > key;
		 i = j, j = i / 2) {
		h->nodes[i] = h->nodes[j];
	}

	h->nodes[i].key = key;
	h->nodes[i].data = data;
	++h->len;
}

char* pop(heap_t *h)
{
	node_t ret;
	int i, j, k;

	if (!h->len) {
		printf("Failed to pop. Queue is empty.\n");
		return NULL;
	}

	ret = h->nodes[1];
	h->nodes[1] = h->nodes[h->len];
	--h->len;

	i = 1;
	while (i != h->len + 1) {
		k = h->len + 1;
		j = 2 * i;

		if (j <= h->len && h->nodes[j].key < h->nodes[k].key)
			k = j;

		if (j + 1 <= h->len && h->nodes[j + 1].key < h->nodes[k].key)
			k = j + 1;

		h->nodes[i] = h->nodes[k];
		i = k;
	}

	return ret.data;
}

int main(void)
{
	heap_t *h = heap_new();
	if (!h) {
		printf("failed to allocate a heap\n");
		return -1;
	}

	push(h, 3, "Clear drains");
	push(h, 4, "Feed cat");
	push(h, 5, "Make tea");
	push(h, 1, "Solve RC tasks");
	push(h, 2, "Tax return");

	int i;
	for (i = 0; i < 5; i++)
		printf("%s\n", pop(h));

	return 0;
}


