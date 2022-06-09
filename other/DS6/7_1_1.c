#include <stdio.h>

#define MAX_LEN 1000
int array[MAX_LEN];
int size = 0;

void show_array()
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void quick_sort(int *a, int start, int end)
{
    if (start >= end)
        return;
    int left = start, right = end;
    int pivot = a[left];
    while (left < right)
    {
        while (left < right && a[right] > pivot)
        {
            right--;
        }
        if (left < right)
        {
            a[left] = a[right];
        }
        while (left < right && a[left] < pivot)
        {
            left++;
        }
        if (left < right)
        {
            a[right] = a[left];
        }
    }
    a[left] = pivot;
    show_array();
    quick_sort(a, start, left - 1);
    quick_sort(a, left + 1, end);
}

int main(int argc, char const *argv[])
{
    scanf("%d", &size);
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &array[i]);
    }
    quick_sort(array, 0, size - 1);
    return 0;
}
