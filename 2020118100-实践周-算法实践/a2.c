#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int countg = 0;

double *randomn(int n) // 生成n个随机数
{
    srand(time(NULL));
    double *arr = (double *)malloc(sizeof(double) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000 / 100.0;
    }
    return arr;
}

void arr_print(double *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%.2f ", arr[i]);
    }
    printf("\n");
}

int find_max_min_non_recursive(double *arr, int n, double *max, double *min)
{
    int count = 0;
    *max = *min = arr[0];
    for (int i = 1; ++count && i < n; i++)
    {
        if (++count && arr[i] > *max)
            *max = arr[i];
        else if (++count && arr[i] < *min)
            *min = arr[i];
    }
}

void find_max_min_recursive(double *arr, int left, int right, double *max, double *min)
{
    if (++countg && left == right)
    {
        if (++countg && arr[left] > *max)
            *max = arr[left];
        else if (++countg && arr[left] < *min)
            *min = arr[left];
        return;
    }
    int mid = (left + right) / 2;
    find_max_min_recursive(arr, left, mid, max, min);
    find_max_min_recursive(arr, mid + 1, right, max, min);
}

int main(int argc, char const *argv[])
{
    int n;
    printf("Please input the number of random numbers you want to generate: ");
    scanf("%d", &n);          // 输入n
    double *arr = randomn(n); // 生成随机数数组
    arr_print(arr, n);        // 打印数组

    // 非递归实现
    printf("non-recursive:\n");
    double max, min;
    int count = find_max_min_non_recursive(arr, n, &max, &min);
    printf("count: %d\n", count);
    printf("max: %.2f\n", max);
    printf("min: %.2f\n", min);

    // 递归实现
    printf("recursive:\n");
    double max1 = arr[0], min1 = arr[0];
    find_max_min_recursive(arr, 0, n - 1, &max1, &min1);
    printf("count: %d\n", countg);
    printf("max: %.2f\n", max1);
    printf("min: %.2f\n", min1);
    return 0;
}
