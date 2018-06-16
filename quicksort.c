



void quicksort(int *a, int len)
{
	int pivot;
	int i, j;

	if (len < 2)
		return;

	pivot = a[len / 2];

	for (i = 0, j = len - 1; ; i++, j--) {
		while (a[j] > pivot)
			j--;

		while (a[i] < pivot)
			i++;

		if (i >= j)
			break;
	
		int tmp = a[j];
		a[j] = a[i];
		a[i] = tmp;
	}

	quicksort(a, i);
	quicksort(a + i, len - i);
}
