/*
 *
 *
 * LC-75: Sort Colors
 *
 *
 */

void swap(int *nums, int i, int j)
{
	int tmp;
	tmp = nums[i];
	nums[i] = nums[j];
	nums[j] = tmp;
}

void sortColors(int* nums, int numsSize) {
	if (!nums || numsSize <= 0)
		return;

	int l, r;
	int i;

	i = 0;
	l = 0;
	r = numsSize - 1;

	while (i <= r) {
		if (nums[i] == 0) {
			swap(nums, i, l);
			l++, i++;
		} else if (nums[i] == 2) {
			swap(nums, i, r);
			r--;
		} else {
			i++;
		}
	}
}