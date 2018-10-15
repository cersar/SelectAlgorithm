/*返回小于key最大值的索引,如不存在则返回low-1
算法正确性：
循环不变量: 
1) a[low-1]<key
2) a[high+1]>=key
3) low-high<=1
证明：
1)初始情况，low<=high, a[low-1]、a[high+1]不属于数组a,
令为a[low-1]无穷小,a[high+1]无穷大，满足循环不变量
2)假设前k次迭代(总迭代次数大于k)，有a[low(k)-1]<key、a[high(k)+1]<key、low(k)<=high(k)
3)第k+1次迭代时，上一次迭代分两种情况：
	a)a[mid(k)] >= key,这时high(k+1)=mid(k)-1,low(k+1)=low(k),
	由于low(k+1)=low(k)，a[low(k)-1]<key,所以有a[low(k+1)-1]<key
    由于high(k+1)=mid(k)-1,a[mid(k)] >= key,所以有a[high(k+1)+1]>=key
	由于low(k)<=high(k)，所以high(k+1)=mid(k)-1>=low(k)-1=low(k+1)-1，即low(k+1)-high(k+1)<=1
	b)a[mid(k)] < key,这时low(k+1)=mid(k)+1,high(k+1)=high(k),同理可证

综上，可知第k+1次迭代时循环不变量依然成立

由于每一次迭代数组的查找范围均会减少，故一定会经过迭代达到low > high的状态，此时循环结束，由循环不变量可知：
high=low-1,a[low-1]<key,a[low]>=key，故low-1为小于key最大值的索引
*/

int minX(int key, int a[], int low, int high) {
	if (low > high) {
		return low-1;
	}
	//当low<=high时,mid范围[low,high]
	//当low=high时，mid=high
	//当low=high或low=high-1时，mid=low
	int mid = (low + high) / 2;
	if (a[mid] >= key) {
		return minX(key, a, low, mid-1);
	}
	else {
		return minX(key, a, mid+1, high);
	}
}
