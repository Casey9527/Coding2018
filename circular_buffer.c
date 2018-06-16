
/*
 * http://www.mathcs.emory.edu/~cheung/Courses/171/Syllabus/8-List/array-queue2.html
 */

#include <stdio.h>
#include <stdlib.h>

#define RING_BUFFER_ACTIVE_SIZE	5
#define RING_BUFFER_SIZE	(RING_BUFFER_ACTIVE_SIZE + 1)

struct ring_buffer {
	int read;
	int write;
	int size;
	int *a;
};

struct ring_buffer * ring_buffer_init(int size)
{
	struct ring_buffer *rb;

	rb = malloc(1 * sizeof(struct ring_buffer));
	if (!rb) {
		printf("failed to allocate ring_buffer\n");
		return NULL;
	}

	rb->read = rb->write = 0;
	rb->size = size;

	rb->a = calloc(size, sizeof(int));
	if (!rb->a) {
		printf("failed to allocate ring buffer array with size %d\n", size);
		free(rb);
		return NULL;
	}

	return rb;
}

void ring_buffer_enqueue(struct ring_buffer *rb, int num)
{
	if ((rb->write + 1) % rb->size == rb->read) {
			printf("QUEUE FULL\n");
			return;
	}

	rb->a[rb->write] = num;
	rb->write = (rb->write + 1) % rb->size;
}

int ring_buffer_dequeue(struct ring_buffer *rb)
{
	int ret;

	if (rb->read == rb->write) {
		printf("QUEUE EMPTY\n");
		return -1;
	}

	ret = rb->a[rb->read];
	rb->read = (rb->read + 1) % rb->size;

	return ret;
}

void ring_buffer_print(struct ring_buffer *rb)
{
	int i;

	if (rb->read == rb->write) {
		printf("QUEUE EMPTY\n");
		return;
	}

	for (i = rb->read; i != rb->write; i = (i + 1) % rb->size)
		printf("%d ", rb->a[i]);

	printf("\n");
}

int main(void)
{
	char cmd;
	int n;
	struct ring_buffer *rb;

	rb = ring_buffer_init(RING_BUFFER_SIZE);
	if (!rb)
		return -1;

	while(1) {
		printf("Input: ");
		scanf(" %c", &cmd);	// use the space to match the newline left in buffer
		switch (cmd) {
			case 'd' :
					ring_buffer_dequeue(rb);
				break;
			case 'e': 
					printf("Num: ");
					scanf(" %d", &n);
					ring_buffer_enqueue(rb, n);
				break;
			case 'p' :
				ring_buffer_print(rb);
				break;
			case 'q' :
				goto end;
		}
	}

end:
	return 0;
}

