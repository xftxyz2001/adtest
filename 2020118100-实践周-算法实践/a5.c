#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *randomn(int n) // 生成n个随机数
{
    srand(time(NULL));
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000 - 500;
    }
    return arr;
}

void arr_print(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

long max3(long a, long b, long c)
{
    long max = a;
    if (b > max)
        max = b;
    if (c > max)
        max = c;
    return max;
}

// 求a[left..high]序列中最大连续子序列和
long maxSubSum(int a[], int left, int right)
{
    int i, j;
    long maxLeftSum, maxRightSum;
    long maxLeftBorderSum, leftBorderSum;
    long maxRightBorderSum, rightBorderSum;
    if (left == right) // 子序列只有一个元素时
    {
        if (a[left] > 0) // 该元素大于0时返回它
            return a[left];
        else // 该元素小于或等于0时返回0
            return 0;
    }
    int mid = (left + right) / 2;               // 求中间位置
    maxLeftSum = maxSubSum(a, left, mid);       // 求左边
    maxRightSum = maxSubSum(a, mid + 1, right); // 求右边
    maxLeftBorderSum = 0, leftBorderSum = 0;
    for (i = mid; i >= left; i--) // 求出以左边加上a[mid]元素
    {
        leftBorderSum += a[i]; // 构成的序列的最大和
        if (leftBorderSum > maxLeftBorderSum)
            maxLeftBorderSum = leftBorderSum;
    }
    maxRightBorderSum = 0, rightBorderSum = 0;
    for (j = mid + 1; j <= right; j++) // 求出a[mid]右边元素
    {
        rightBorderSum += a[j]; // 构成的序列的最大和
        if (rightBorderSum > maxRightBorderSum)
            maxRightBorderSum = rightBorderSum;
    }
    return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int main(int argc, char const *argv[])
{
    int n = 10;
    printf("请输入数组长度：");
    scanf("%d", &n);
    int *arr = randomn(n);

    printf("原始数组：");
    arr_print(arr, n);

    printf("最大连续子序列和为：%ld\n", maxSubSum(arr, 0, n - 1));
    return 0;
}
