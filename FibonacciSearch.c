#include<stdio.h>
#include<stdlib.h>
#include<crtdbg.h>

/*
*斐波那契查找
*原理：F[n-1]作为数组(1...F[n])的分割点，当n趋向于无穷时，这种分割趋向于黄金分割
*/

void fibonacci(int * F) {
	F[0] = 0;
	F[1] = 1;
	for (int i = 2; i<50; ++i)
		F[i] = F[i - 1] + F[i - 2];
}

int fibonacciSearch(int a[], int key, int n) {
	int index = -1;
	int F[50];
	fibonacci(F);

	// 获取斐波那契分割数值下标
	// 在斐波那契数列F[K],使得数组大小<=F[k]
	int k = 0;
	while (n > F[k]) {
		k++;
	}

	// 创建临时数组，长度为 F[k]
	int *tmp = (int *)malloc(sizeof(int)*F[k]);
	for (int i = 0; i<n; i++) {        // 前面填充为原数组中的内容
		tmp[i] = a[i];
	}

	//多余的值赋值INI_MAX
	for (int i = n; i<F[k]; ++i) { // 后面填充为原数组最后一个元素的值
		tmp[i] = INT_MAX;
	}

	/*循环不变量：
	*第k次循环：
	*high(k)-low(k)+1=F[i(k)]（i(k)>=2)
	*证明：
	*1)初始情形，high(1)=F[k] - 1，low(1)= 0，故high(1)-low(1)=F[i(1)]
	*2)假设第k次迭代，循环不变量成立，即high(k)-low(k)+1=F[i(k)]
	*则第k+1次迭代，进入迭代分两种情况：
	*	a)key < tmp[mid(k)],此时mid(k)=low(k) + F[i(k) - 1] - 1,
	*	  high(k+1) = mid(k),low(k+1)=low(k),i(k+1)=i(k)-1,则high(k+1)-low(k+1)+1=mid(k)-low(k)+1=F[i(k) - 1]=F[i(k+1)]
	*	b)key > tmp[mid(k)],此时mid(k)=low(k) + F[i(k) - 1] - 1,
	*	  high(k+1) = high(k),low(k+1)=mid(k)+1,i(k+1)=i(k)-2,
	*	  则high(k+1)-low(k+1)+1 = high(k)-mid(k) = high(k)-low(k)+1-F[i(k) - 1] = F[i(k)]-F[i(k) - 1]=F[i(k) - 2]=F[i(k+1)]
	*   故第k+1次迭代循环不变量依然成立
	*3)由于i(k)不断减小，可知必定可以达到i(k)<3，使得循环结束。
	*循环结束时，i(k)=2或1,F[i(k)]=1，说明循环结束时还剩一个元素需要判断
	*故进一步检查key是否等于a[low]即可结束查询
	*/
	int low = 0;
	int high = F[k] - 1;
	int mid;
	while (k>=3) {
		mid = low + F[k - 1] - 1;
		printf("low=%d\thigh=%d\t", low,high);
		printf("F[%d]=%d\n",k-1, F[k - 1]);
		if (key < tmp[mid]) {
			// 查找前半部分，高位指针移动
			high = mid;
			k--;
		}
		else if(key > tmp[mid]){
			// 查找后半部分，低位指针移动
			low = mid+1;
			k -= 2;
		}
		else {
			index = mid;
			break;
		}
	}
	if (key == a[low]) {
		index = low;
	}
	free(tmp);
	return index;
}

int main(int argc, const char * argv[]) {
	int a[] = { 0,16,24,35,47,59,62,73,88,99 };
	int key = 0;
	int index = fibonacciSearch(a, key, 10);
	if (index != -1) {
		printf("%d\n", index);
	}
	else {
		printf("Not Found!!\n");
	}
	return 0;
}
