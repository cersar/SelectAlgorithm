//《算法导论》9.3-7 与中位数最邻近的k个数
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define STEP 5

int LinearSelect(int a[], int start, int end, int k);

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void InsertSort(int a[], int start, int end) {
	int key, j;
	for (int i = start + 1; i <= end; ++i) {
		key = a[i];
		j = i - 1;
		while (j >= start&&abs(a[j]) > abs(key)) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

int Partation(int a[], int start, int end) {
	int j = start - 1;
	int key = a[end];
	for (int i = start; i <= end; ++i) {
		if (abs(a[i]) < abs(key)) {
			swap(&a[++j], &a[i]);
		}
	}
	swap(&a[++j], &a[end]);
	return j;
}

int FindKeyIndex(int a[], int start, int end) {
	int n = ceil(float((end - start + 1)) / STEP);
	int j;
	for (int i = start, k = 0; i <= end; i += STEP, k++) {
		j = (i + STEP - 1) <= end ? (i + STEP - 1) : end;
		InsertSort(a, i, j);
		//将找出的中位数置于数组的前部，这样可不用再临时开辟空间
		swap(&a[start + k], &a[(i + j) / 2]);
	}
	LinearSelect(a, start, start + n - 1, start + (n - 1) / 2 + 1);
	return start + (n - 1) / 2;
}

int LinearSelect(int a[], int start, int end, int k) {
	if (start == end) {
		return a[start];
	}
	int keyIndex = FindKeyIndex(a, start, end);
	swap(&a[end], &a[keyIndex]);

	int p = Partation(a, start, end);

	if (k - 1 == p) {
		return a[p];
	}
	else if (k - 1 < p) {
		LinearSelect(a, start, p - 1, k);
	}
	else {
		LinearSelect(a, p + 1, end, k);
	}
}

int Median(int a[],int start,int end) {
	int mid = (start + end)/2;
	return LinearSelect(a, start, end, mid + 1);
}

void MedianKNeighbor(int a[], int start, int end, int k) {
	int *tmp = (int *)malloc(sizeof(int)*(end - start + 1));
	int median = Median(a, start, end);
	swap(&a[end], &a[(start + end) / 2]);
	for (int i = start; i < end; i++) {
		tmp[i] = a[i] - median;
	}
	LinearSelect(tmp, start, end - 1, start+k);
	printf("median = %d\n", median);
	for (int i = start; i < start + k; ++i) {
		printf("%d\t", median+tmp[i]);
	}
	printf("\n");
	free(tmp);
}

int main() {
	int a[] = { 7,9,1,2,8,4,5,3};
	int len = sizeof(a) / sizeof(int);
	int k = 4;
		for (int i : a) {
		printf("%d\t", i);
	}
	printf("\n");
	MedianKNeighbor(a, 0, len - 1,k);
	return 0;
}
