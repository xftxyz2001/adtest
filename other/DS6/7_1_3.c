#include <stdio.h>

int n;

void swap(int *arr, int i, int j)
{
    int t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
}

void quicksort(int *arr, int start, int end)
{
    if (start >= end)
        return;
    int i = start, j = end;
    int key = arr[i];
    int temp;
    while (i != j)
    {
        while (i < j && arr[j] > key)
            j--;
        while (i < j && arr[i] <= key)
            i++;
        if (i < j)
            swap(arr, i, j);
    }
    swap(arr, start, i);
    int flag = 1;
    for (int k = 0; k < n; k++)
    {
        printf("%d ", arr[k]);
        if (k != 0 && arr[k - 1] > arr[k])
            flag = 0;
    }
    printf("\n");
    if (flag)
        return;
    quicksort(arr, start, j - 1);
    quicksort(arr, i + 1, end);
}
int main()
{

    int a[1001];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    quicksort(a, 0, n - 1);
    for (int k = 0; k < n; k++)
    {
        printf("%d ", a[k]);
    }
    return 0;
}
