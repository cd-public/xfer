#include <stdio.h>

void swap(int *arr, int len, int i, int j)
{
	int temp = arr[i];
	if (arr[i] > arr[j] && i < j && i < len && j < len)
	{
		arr[i] = arr[j];
		arr[j] = temp;
	}
	return;
}

void help(int *arr, int len, int i, int j)
{
	if (i + 1 >= j)
	{
		swap(arr, len, i, j);
		return;
	}
	int old_i = i;
	int old_j = j;
	int pivot = arr[i + (j-i)/2];
	while (i + 1 < j)
	{
		while (arr[i] < pivot)
		{
			i++;
		}
		while (arr[j] >= pivot && j > i)
		{
			j--;
		}
		swap(arr, len, i, j);
		help(arr, len, old_i, i);
		if (i + 1 < len)
		{
			help(arr, len, i+1, old_j);
		}
	}
	return;
}

void ssort(int *arr, int len)
{
	help(arr, len, 0, len);
	return;
}

void print_arr(int *arr, int len)
{
	char *prefix = "\n[";
	for ( int i = 0 ; i < len ; i++ )
	{
		printf("%s%d", prefix, arr[i]);
		prefix = ", ";
	}
	printf("]\n");
}

int main()
{
	int arr[8] = {4,8,2,6,5,1,7,3};
	print_arr(arr,8);
	ssort(arr,8);
	print_arr(arr,8);
	return 0;
}
