//《算法导论》期望为线性运行时间的选择算法
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int RandomPartation(int a[], int start, int end) {
	int k = rand() % (end - start + 1) + start;
	swap(&a[k], &a[end]);
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

int RandomSelect(int a[], int start, int end, int k) {
	if (start == end) {
		return a[start];
	}

	int p = RandomPartation(a, start, end);

	if (k-1==p) {
		return a[p];
	}
	else if (k-1 < p) {
		RandomSelect(a, start, p - 1, k);
	}
	else {
		RandomSelect(a, p + 1, end, k);
	}
}

int main() {
	srand(time(NULL));
	int a[] = { 9,1,2,8,4,5,3 };
	int len = sizeof(a) / sizeof(int);
	int n = 2;
	int d = RandomSelect(a, 0, len - 1, n);
	for (int i : a) {
		printf("%d\t", i);
	}
	printf("\n");
	printf("第%d小的数为%d\n", n,d);
	return 0;
}
