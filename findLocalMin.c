/* 寻找局部最小值，数组中元素互不相等
* 局部最小值定义：
* 1)array长度N<=2时，min(array)为局部最小值
* 2)array长度N>2时：
*    a)如果i∈(0,N-1),且array[i]<array[i-1]&&array[i]<array[i+1]，则array[i]为局部最小值
*    a)如果i=0,且array[i]<array[i+1]，则array[i]为局部最小值
*    a)如果i=N-1,且array[i]<array[i-1]，则array[i]为局部最小值
* 循环不变量:
* 假设a[low-1]=a[high+1]为正无穷
* 1) a[low(k)]<a[low(k)-1]
* 2) a[high(k)]<a[high(k)+1]
* 证明：
* 1)第1次迭代有low(1)=low<=high(1)=high，a[low]<a[low-1]且a[high]<a[high+1]
* 2)假设前k次迭代循环不变量成立，即low(k)<=high(k),a[low(k)]<a[low(k)-1],a[high(k)]<a[high(k)+1]
* 3)第k+1次迭代时，分两种情况：
*	a)a[mid(k)] > a[mid(k) - 1]，此时low(k+1)=low(k)，high(k+1) = mid(k)-1，
*       a[low(k+1)]=a[low(k)]<a[low(k)-1]=a[low(k+1)-1],a[high(k+1)]=a[mid(k)-1]<a[mid(k)]=a[high(k+1)+1]
*       b)a[mid(k)] > a[mid(k) + 1]，此时high(k+1)=high(k)，low(k+1) = mid(k)+1，
*	  a[high(k+1)]=a[high(k)]<a[high(k)+1]=a[high(k+1)+1],a[low(k+1)]=a[mid(k)+1]<a[mid(k)]=a[low(k+1)-1]
*
* 由于每次迭代都会导致[low(k),high(k)]的范围减小，故若迭代判断中a[mid] < a[mid - 1]&&a[mid] < a[mid + 1]不成立，
* 则一定可以达到high(n)-low(n) < 2，使得循环可以正常终止，
* 由循环不变量，有a[low(n)]<a[low(n)-1]且a[high(n)]<a[high(n)+1]
* 此时分两种情况：
* 1）high(n)= low(n),此时a[low(n)]=a[high(n)]<a[low(n)-1]=a[high(n)-1],a[low(n)]=a[high(n)]<a[low(n)+1]=a[high(n)+1]
* low=high为局部最小值点
* 2）high(n)= low(n)+1：
*	a)若a[low(n)]<a[high(n)],则a[low(n)]<a[low(n)-1]&&a[low(n)]<a[high(n)]=a[low(n)+1],
*	low为局部最小值点
*	b)若a[high(n)]<a[low(n)],则a[high(n)]<a[high(n)+1]&&a[high(n)]<a[low(n)]=a[high(n)-1],
*	high为局部最小值点
*/

int findLocalMin(int a[], int low, int high) {
	if (high-low < 2) {
		if (a[low] < a[high]) {
			return low;
		}
		else {
			return high;
		}
		
	}
	int mid = (low + high) / 2;
	if (a[mid] > a[mid - 1]) {
		return findLocalMin(a, low, mid - 1);
	}
	else if(a[mid] > a[mid + 1]){
		return findLocalMin(a, mid + 1, high);
	}
	else {
		return mid;
	}
}
