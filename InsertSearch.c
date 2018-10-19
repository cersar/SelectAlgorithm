#include<stdio.h>
#include<math.h>

int insert_search(int a[], int key, int n) {
	if (n==1) {
		return a[0]==key;
	}
	else {
		int low = 0;
		int high = n - 1;
		int index = -1;
		int time = 0;
		int mid;
		while (key >= a[low] && key <= a[high]) {
			// n>=2且a中元素互异时，进入第k次迭代时都有low(k)!=high(k)
			// 反证法，若进入第k次迭代时，有low(k)=high(k)，根据上一次迭代的两种情况：
			// 1）low(k)=low(k-1)，此时mid(k-1)=low(k-1),a[mid(k-1)]=key,迭代应该在k-1轮结束，矛盾
			// 2）high(k)=high(k-1)，此时mid(k-1)=high(k-1),a[mid(k-1)]=key,迭代应该在k-1轮结束，矛盾
			// 综上进入第k次迭代时，有low(k)!=high(k)，即mid更新式的分母不可能除0
			// 由于每一次搜索都保证key∈[a[low(k)],a[high(k)]]，且迭代搜索范围逐渐减小，若a[low~high]中存在key，一定会被找到
			mid = low + (key - a[low]) / ((a[high] - a[low]) * 1.0)*(high - low);
			printf("查找次数：%d, 当前low=%d,high=%d,mid=%d\n", ++time, low, high, mid);
			if (a[mid] == key) {
				index = mid;
				break;
			}
			else if (key<a[mid]) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		return index;
	}
}


int main(int argc, const char * argv[]) {
	int a[] = { 1,19,88,109,200,230,270,299,900,1000,1001,5000,5010,5400,5900,7000,8000,8099,9012,9099,9999,10002,12093,15432 };
	int value = 109;
	printf("插值查找\n");
	int index = insert_search(a, value, 20);
	if (index > -1) {
		printf("找到了，下标是：%d\n", index);
	}
	else {
		printf("Not Found!!\n");
	}
	return 0;
}
