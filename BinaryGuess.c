#include<stdio.h>
#include<math.h>

//猜测次数~1lgN，前提是允许猜测范围为-N~2N的数字
int binaryGuess1(int key, int N) {
	int low = 1;
	int high = N;
	int mid;
	int last = 1;
	int current;
	int cnt = 1;
	printf("第1次猜测：1\n");
	//每一次迭代都有key∈[low,high]，且current+last = low+high，由于(current+last)/2=mid，可通过判断current是远离还是靠近，判断下一次的搜索区间：
	//1）若current相较last远离，则取下一次取靠近last的half区间
	//2）若current相较last靠近，则取下一次取靠近current的half区间
	//current的范围是[-N,2N]可通过数学归纳法证明
	//详细请见：https://blog.csdn.net/vmxplus/article/details/45874583
	while (low<=high) {
		//每一次current的更新算一次猜测
		current = low + high - last;
		mid = (low + high) / 2;
		cnt++;
		printf("low=%d,high=%d\t", low, high);
		printf("第%d猜测：%d，上一次猜测：%d\n", cnt,current, last);
		if (abs(current - key) == abs(last - key)) {
			printf("correct!\tkey=%d\n", mid);
			return cnt;
		}
		else if (abs(current - key) < abs(last - key)) {
			if (current < last) {
				high = mid-1;
			}
			else {
				low = mid+1;
			}
		}
		else {
			if (current < last) {
				low = mid+1;
			}
			else {
				high = mid-1;
			}
		}
		last = current;
	}
	return cnt;
}

//猜测次数~2lgN
int binaryGuess2(int key, int N) {
	int low = 1;
	int high = N;
	int mid;
	int cnt = 0;
	while (low <= high) {
		mid = (low + high)/2;
		printf("第%d次猜测：%d\t第%d次猜测：%d\n", cnt+1,low, cnt+2,high);
		cnt+=2;
		//通过猜测low和high，根据high相较于low是远离还是靠近决定下一次搜索的区域
		if (abs(low - key) == abs(high - key)) {
			printf("correct!\tkey=%d\n", mid);
			return cnt;
		}
		else if (abs(low - key) < abs(high - key)) {
			high = mid-1;
		}
		else {
			low = mid+1;
		}
	}
	return cnt;
}

int main(int argc, const char * argv[]) {
	printf("%d\n\n", binaryGuess1(911,10000));
	printf("%d\n", binaryGuess2(911, 10000));
	return 0;
}
