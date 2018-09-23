//《算法导论》最坏情况为线性的选择算法
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
		while (j >= start&&a[j] > key) {
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
		if (a[i] < key) {
			swap(&a[++j], &a[i]);
		}
	}
	swap(&a[++j], &a[end]);
	return j;
}

int FindKeyIndex(int a[],int start,int end) {
	int n = ceil(float((end - start + 1)) / STEP);
	int j;
	for (int i = start,k=0; i <= end; i+=STEP,k++) {
		j = (i + STEP - 1) <= end ? (i + STEP - 1) : end;
		InsertSort(a, i, j);
		//将找出的中位数置于数组的前部，这样可不用再临时开辟空间
		swap(&a[start + k], &a[(i + j) / 2]);
	}
	LinearSelect(a, start,start+n-1, start+(n-1)/2+1);
	return start + (n - 1) / 2;
}

int LinearSelect(int a[], int start, int end, int k) {
	if (start == end) {
		return a[start];
	}
	int keyIndex = FindKeyIndex(a, start, end);
	swap(&a[end], &a[keyIndex]);

	int p = Partation(a, start, end);

	if (k-1==p) {
		return a[p];
	}
	else if (k-1 < p) {
		LinearSelect(a, start, p - 1, k);
	}
	else {
		LinearSelect(a, p + 1, end, k);
	}
}

int main() {
	int a[] = { 9,1,2,8,4,5,3 };
	int len = sizeof(a) / sizeof(int);
	int n = 5;
	int d = LinearSelect(a, 0, len - 1, n);
	for (int i : a) {
		printf("%d\t", i);
	}
	printf("\n");
	printf("第%d小的数为%d\n", n,d);
	return 0;
}
