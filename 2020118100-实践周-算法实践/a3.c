#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *randomn(int n) // 生成n个随机数
{
    srand(time(NULL));
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
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

void arr_print_2(int *arr, int pivot, int n)
{
    printf("第一部分：");
    for (int i = 0; i < pivot; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("第二部分：");
    for (int i = pivot; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int subpartition(int *arr, int left, int right)
{
    int pivot = arr[left];
    while (left < right)
    {
        while (left < right && arr[right] >= pivot)
        {
            right--;
        }
        arr[left] = arr[right];
        while (left < right && arr[left] <= pivot)
        {
            left++;
        }
        arr[right] = arr[left];
    }
    arr[left] = pivot;
    return left;
}

int partition(int *arr, int n)
{
    int left = 0;
    int right = n - 1;
    int pivot = subpartition(arr, left, right);
    while (pivot != n / 2)
    {
        if (pivot < n / 2)
        {
            pivot = subpartition(arr, pivot + 1, right);
        }
        else
        {
            pivot = subpartition(arr, left, pivot - 1);
        }
    }
    return pivot;
}

int main(int argc, char const *argv[])
{
    int n = 0;
    printf("请输入数组长度：");
    scanf("%d", &n);

    int *arr = randomn(n);
    printf("原始数组：");
    arr_print(arr, n);

    int pivot = partition(arr, n);
    printf("pivot: %d\n", pivot);
    arr_print_2(arr, pivot, n);
    return 0;
}
