#include <stdio.h>
#include <stdlib.h>

int findKthLargest(int* nums, int numsSize, int k)
{
	printf("**********\n");
	printf("nums[0]: %d, numsSize: %d, k: %d\n", nums[0], numsSize, k);
	if (numsSize < 2)
		return nums[0];

	int pivot;
	int i, j, idx;

	pivot = nums[numsSize / 2];

	/* Partition */
	for (i = 0, j = numsSize - 1; ; i++, j--) {
		while (nums[i] > pivot)
			i++;

		while (nums[j] < pivot)
			j--;

		if (i >= j)
			break;

		int tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp;
	}

	for (idx = 0; idx < numsSize; idx++)
		printf("%d ", nums[idx]);
	printf("\n**********\n");

	if (k > i)
		return findKthLargest(nums + i, numsSize - i, k - i);
	else
		return findKthLargest(nums, i, k);
}

int main(int ac, char *av[])
{
	if (ac !=  2)
		return -1;

	int ret;
	int a[] = {3, 2, 3, 1, 2, 4, 5, 5, 6};

	ret = findKthLargest(a, sizeof(a) / sizeof(int), atoi(av[1]));
	printf("ret: %d\n", ret);

	return 0;
}
