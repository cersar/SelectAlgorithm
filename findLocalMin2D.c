#include<stdio.h>
#include<stdlib.h>
#include<crtdbg.h>

/* 寻找矩阵局部最小值，假设矩阵中元素互不相等，时间复杂度O(n)
* 二维数组array(M,N)局部最小值定义：
* M>=3并且N>=3：
*    1)如果i∈(0,M-1)且j∈(0,N-1),且array[i]<array[i-1]&&array[i]<array[i+1]，则array[i]为局部最小值
*    2)如果i=0,且array[i]<array[i+1]，则array[i]为局部最小值
*    3)如果i=N-1,且array[i]<array[i-1]，则array[i]为局部最小值
*/

typedef struct point {
	int row;
	int col;
}point;

//寻找田字最小值点
point min(int **a, point leftUp, point rightDown, point mid) {
	point minPoint = leftUp;
	for (int i = leftUp.row; i <= rightDown.row; ++i) {
		if (a[i][leftUp.col] < a[minPoint.row][minPoint.col]) {
			minPoint.row = i;
			minPoint.col = leftUp.col;
		}
		if (a[i][mid.col] < a[minPoint.row][minPoint.col]) {
			minPoint.row = i;
			minPoint.col = mid.col;
		}
		if (a[i][rightDown.col] < a[minPoint.row][minPoint.col]) {
			minPoint.row = i;
			minPoint.col = rightDown.col;
		}
	}
	for (int i = leftUp.col; i <= rightDown.col; ++i) {
		if (a[leftUp.row][i] < a[minPoint.row][minPoint.col]) {
			minPoint.row = leftUp.row;
			minPoint.col = i;
		}
		if (a[mid.row][i] < a[minPoint.row][minPoint.col]) {
			minPoint.row = mid.row;
			minPoint.col = i;
		}
		if (a[rightDown.row][i] < a[minPoint.row][minPoint.col]) {
			minPoint.row = rightDown.row;
			minPoint.col = i;
		}
	}
	return minPoint;
}

int Quadrant(point origin, point p) {
	if (p.row < origin.row&&p.col < origin.col) {
		return 1;
	}
	if (p.row < origin.row&&p.col > origin.col) {
		return 2;
	}
	if (p.row > origin.row&&p.col < origin.col) {
		return 3;
	}
	if (p.row > origin.row&&p.col > origin.col) {
		return 4;
	}
	return 0;
}

bool validation(int** a, int M, int N, point *leftUp, point *rightDown, point midPoint, point minPoint) {
	point p;
	if (minPoint.col != 0 && a[minPoint.row][minPoint.col - 1] < a[minPoint.row][minPoint.col]) {
		p.row = minPoint.row;
		p.col = minPoint.col - 1;
	}
	else if (minPoint.col != N - 1 && a[minPoint.row][minPoint.col + 1] < a[minPoint.row][minPoint.col]) {
		p.row = minPoint.row;
		p.col = minPoint.col + 1;
	}
	else if (minPoint.row != 0 && a[minPoint.row - 1][minPoint.col] < a[minPoint.row][minPoint.col]) {
		p.row = minPoint.row - 1;
		p.col = minPoint.col;
	}
	else if (minPoint.row != M - 1 && a[minPoint.row + 1][minPoint.col] < a[minPoint.row][minPoint.col]) {
		p.row = minPoint.row + 1;
		p.col = minPoint.col;
	}
	else {
		return true;
	}
	switch (Quadrant(midPoint, p)) {
	case 1:
		rightDown->row = midPoint.row;
		rightDown->col = midPoint.col;
		break;
	case 2:
		leftUp->col = midPoint.row;
		rightDown->row = midPoint.row;
		break;
	case 3:
		leftUp->row = midPoint.row;
		rightDown->col = midPoint.col;
		break;
	case 4:
		leftUp->row = midPoint.row;
		leftUp->col = midPoint.col;
		break;
	default: break;
	}
	return false;
}

/*
*循环不变量(总迭代次数N>1时)：
*1)rightDown(k).row > leftUp(k).row+1 && rightDown(k).col > leftUp(k).col+1
*2)存在i∈(leftUp(k).row,rightDown(k).row),j∈(leftUp(k).col,rightDown(k).col),使得
*a[i,j]>max({a[p,q]|(p∈{leftUp(k).row,rightDown(k).row},q∈[leftUp(k).col,rightDown(k).col])或
*(q∈{leftUp(k).col,rightDown(k).col},p∈[leftUp(k).row,rightDown(k).row])d})
*证明：
*1）初始j=1时，rightDown(1).row > leftUp(1).row+1 && rightDown(1).col > leftUp(1).col+1
由于总迭代次数N>1,存在i∈(leftUp(1).row,rightDown(1).row),j∈(leftUp(1).col,rightDown(1).col),使得
*a[i,j]>max({a[p,q]|(p∈{leftUp(1).row,rightDown(1).row},q∈[leftUp(1).col,rightDown(1).col])或
*(q∈{leftUp(1).col,rightDown(1).col},p∈[leftUp(1).row,rightDown(1).row])d})
2）假设j=k时,有rightDown(k).row > leftUp(k).row+1 && rightDown(k).col > leftUp(k).col+1
*存在i∈(leftUp(k).row,rightDown(k).row),j∈(leftUp(k).col,rightDown(k).col),使得
*a[i,j]>max({a[p,q]|(p∈{leftUp(k).row,rightDown(k).row},q∈[leftUp(k).col,rightDown(k).col])或
*(q∈{leftUp(k).col,rightDown(k).col},p∈[leftUp(k).row,rightDown(k).row])d})
3)j=k+1时，设p(k)为第k轮迭代大于田(k)的点，则经过validation过程后，range(k+1)更新为p(k)所在象限，即p(k)∈(leftUp(k+1),rightDown(k+1))
*即(leftUp(k+1),rightDown(k+1))范围内至少包含一个点，可知rightDown(k+1).row > leftUp(k+1).row+1 && rightDown(k+1).col > leftUp(k+1).col+1
*同时存在p(k).row∈(leftUp(k+1).row,rightDown(k+1).row)，p(k).col∈(leftUp(k+1).col,rightDown(k+1).col),
*使得p(k)>max({a[p,q]|(p∈{leftUp(k+1).row,rightDown(k+1).row},q∈[leftUp(k+1).col,rightDown(k+1).col])或
*(q∈{leftUp(k+1).col,rightDown(k+1).col},p∈[leftUp(k+1).row,rightDown(k+1).row])})
*
*由于递归过程中，要么提前找到极值点返回，要么不断递归减少range，直到(rightDown(N).row - leftUp(N).row) <= 2||
*(rightDown(N).col - leftUp(N).col) <= 2,由循环不变量：rightDown(N).row > leftUp(N).row+1 && rightDown(N).col > leftUp(N).col+1
*可知至少减少到rightDown.col-leftUp(N).col=2或rightDown(N).row - leftUp(N).row = 2，此时，min(田(N))一定是一个极小值点

*时间复杂度T(N)=O(N)
*证明:T(N)=T(N/2)+cN,由主定理可知T(N)=O(N)
*/

point findLocalMin2D(int** a, int M, int N, point leftUp, point rightDown) {
	point midPoint;
	midPoint.row = (rightDown.row + leftUp.row) / 2;
	midPoint.col = (rightDown.col + leftUp.col) / 2;
	point minPoint = min(a, leftUp, rightDown, midPoint);
	if (validation(a, M, N, &leftUp, &rightDown, midPoint, minPoint)) {
		return minPoint;
	}
	else {
		return findLocalMin2D(a, M, N, leftUp, rightDown);
	}
}


int main() {
	int data[5][5] = { 10,6,5,7,17,
		4,2,16,1,18,
		14,9,8,11,19,
		12,3,15,13,20,
		21,22,23,24,25 };
	int M = 5, N = 5;
	int **a = (int **)malloc(sizeof(int *) * M);
	for (int i = 0; i < M; ++i) {
		a[i] = (int *)malloc(sizeof(int) * N);
		for (int j = 0; j < N; ++j) {
			a[i][j] = data[i][j];
		}
	}
	point leftUp = { 0,0 };
	point rightDown = { M - 1,N - 1 };
	point min = findLocalMin2D(a, M, N, leftUp, rightDown);
	printf("局部极小值坐标:(%d,%d)，值:%d\n", min.row, min.col, a[min.row][min.col]);
	for (int i = 0; i < M; ++i) {
		free(a[i]);
	}
	free(a);
	_CrtCheckMemory();
	return 0;
}
