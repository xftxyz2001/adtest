#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *randomn(int n) // 生成n个随机数
{
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }

    // 对arr进行简单选择排序，使之有序
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
                min = j;
        }
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
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

double find_the_median_number(int *arr1, int m, int *arr2, int n)
{
    int i = 0, j = 0, k = (m + n) / 2, l = 0;
    int *arr = (int *)malloc(sizeof(int) * (k + 1));
    while (l <= k && i < m && j < n)
    {
        if (arr1[i] < arr2[j])
        {
            arr[l++] = arr1[i++];
        }
        else
        {
            arr[l++] = arr2[j++];
        }
    }
    while (l <= k && i < m)
    {
        arr[l++] = arr1[i++];
    }
    while (l <= k && j < n)
    {
        arr[l++] = arr2[j++];
    }
    return (m + n) % 2 == 0 ? (arr[k] + arr[k - 1]) / 2.0 : arr[k];
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    int m, n;
    printf("Please input the number of random numbers you want to generate: ");
    scanf("%d %d", &m, &n); // 输入m, n

    int *arr1 = randomn(m); // 生成随机数数组
    int *arr2 = randomn(n); // 生成随机数数组

    printf("The first array is: ");
    arr_print(arr1, m);
    printf("The second array is: ");
    arr_print(arr2, n);

    double num = find_the_median_number(arr1, m, arr2, n);
    printf("The median number is: %.2f\n", num);

    return 0;
}
