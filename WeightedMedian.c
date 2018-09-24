//《算法导论》最坏情况为线性的选择算法
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define STEP 5

double LinearSelect(double a[], int start, int end, int k);

void swap(double *a, double *b) {
	double tmp = *a;
	*a = *b;
	*b = tmp;
}

void InsertSort(double a[], int start, int end) {
	double key;
	int j;
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

int Partation(double a[], int start, int end) {
	int j = start - 1;
	double key = a[end];
	for (int i = start; i <= end; ++i) {
		if (a[i] < key) {
			swap(&a[++j], &a[i]);
		}
	}
	swap(&a[++j], &a[end]);
	return j;
}

int FindKeyIndex(double a[], int start, int end) {
	int n = ceil(double((end - start + 1)) / STEP);
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

double LinearSelect(double a[], int start, int end, int k) {
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
		return LinearSelect(a, start, p - 1, k);
	}
	else {
		return LinearSelect(a, p + 1, end, k);
	}
}

double WeightedMedian(double a[],int start,int end,double l_thred,double r_thred) {
	if (start == end) {
		return a[start];
	}
	int mid = (start + end) / 2;
	double median = LinearSelect(a, start, end, mid + 1);
	double sum_left = 0, sum_right = 0;
	for (int i = start; i < mid; ++i) {
		sum_left += a[i];
	}
	for (int i = mid+1; i <= end; ++i) {
		sum_right += a[i];
	}
	if (sum_left >= l_thred) {
		return WeightedMedian(a, start, mid-1, l_thred, sum_left - l_thred);
	}
	else if (sum_right > r_thred) {
		return WeightedMedian(a, mid + 1, end, sum_right - r_thred, r_thred);
	}
	else {
		return median;
	}
}

int main() {
	double a[] = { 0.25,0.35,0.05,0.15,0.05,0.15 };
	int len = sizeof(a) / sizeof(double);
	for (double i : a) {
		printf("%.2f\t", i);
	}
	printf("\n");
	double d = WeightedMedian(a, 0, len - 1, 0.5, 0.5);

	printf("加权中位数为%.2f\n",d);
	return 0;
}
