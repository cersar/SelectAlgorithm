//《算法导论》9.3-7 寻找两个同样大小有序数组的中位数
#include<stdio.h>
#include<math.h>
#include<assert.h>

int min(int a, int b) {
	return a < b ? a : b;
}

//这里中位数均是下中位数floor((n+1)/2)
//首先比较数组a和b的中位数，存在三种情况：
//1)median_a==median_b，此时联合数组的中位数为median_a
//原因：此时存在(floor((n+1)/2)-1)*2个数小于median_a和median_b，
//index_mediaA∈[n-1,n],index_mediaB∈[n,n+1],即中位数只能在a、b的中位数取到
//所以中位数（index=n)一定等于index_mediaA=index_mediaB
//2)median_a<median_b，此时取a中位数之后（保证和b元素个数相等）的部分和b中位数之前(含中位数)的部分，即a[ceil((n+1)/2)~end]、b[start~floor((n+1)/2))]
//原因：median_a<median_b则至少有2*floor((n+1)/2-1)+1>=n-1个数小于median_b故median_b之后（不包含）的数不可能为中位数，同理median_a之前（当n为偶数时不包含）的数不可能为中位数
//故余下继续寻找中位数的范围：a[ceil((n+1)/2)~end]、b[start~floor((n+1)/2))]
//3)median_a>median_b同2）
int MedianTwoArray(int a[], int b[],int aStart, int aEnd, int bStart,int bEnd) {
	assert(aEnd-aStart==bEnd-bStart);
	if (aEnd == aStart) {
		return min(a[aStart], b[bStart]);
	}
	int aMedian = a[(aStart + aEnd) / 2];
	int bMedian = b[(bStart + bEnd) / 2];
	if (aMedian == bMedian) {
		return aMedian;
	}
	else if (aMedian < bMedian) {
		aStart = ceil((aStart + aEnd) / 2.0);
		bEnd = (bStart + bEnd) / 2;
	}
	else {
		bStart = ceil((bStart + bEnd) / 2.0);
		aEnd = (aStart + aEnd) / 2;
	}
	MedianTwoArray(a, b, aStart, aEnd, bStart, bEnd);
}

int main() {
	int a[] = { 0,1,2,7,9,12 };
	int b[] = { 3,4,5,6,8,10 };
	int len = sizeof(a) / sizeof(int);
	printf("a:\t");
	for (int i : a) {
		printf("%d\t", i);
	}
	printf("\n");
	printf("b:\t");
	for (int i : b) {
		printf("%d\t", i);
	}
	printf("\n");
	int m = MedianTwoArray(a,b,0, len - 1, 0, len - 1);
	printf("中位数:%d\n", m);
	return 0;
}
