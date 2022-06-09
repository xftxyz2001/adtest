#include <iostream>
using namespace std;
int n;

void qsort(int* a, int start, int end) {
	if (start >= end) return;//此时排序已经完成或
	int l, r;
	l = start;
	r = end;
	int pivot = a[l];//通常取最左边的数为比较的枢纽
	while (l < r)//开始排序
	{
		while (l<r && a[r]>pivot)
		{
			r--;//先从右下标开始与pivot比较，如果比pivot小则停止向左滑动
		}
		if (l < r)
		{
			a[l] = a[r];//，并与左边l指向的位置进行赋值
		}
		while (l < r && a[l] < pivot)//右边对l指向的位置赋值完，交换到l开始滑动
		{
			l++;
		}
		if (l < r)
		{
			a[r] = a[l];
		}
	}
	a[l] = pivot;//此时左右指针重合，在此位置用pivot赋值
	int flag = 1;
	for (int i = 0; i <= n - 1; i++)
	{
		cout << a[i] << " ";
		if (i != 0)
		{
			if (a[i] < a[i - 1]) flag = 0;
		}
	}
	cout << endl;
	if (flag == 1) return;
	qsort(a, start, l - 1);
	qsort(a, l + 1, end);
}


int main() {
	int i;
	cin >> n;
	int arr[n];

	for (i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	qsort(arr, 0, n - 1);

	for (i = 0; i <= n - 1; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return 0;
}