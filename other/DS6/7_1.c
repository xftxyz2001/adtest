#include <stdio.h>
#include <stdlib.h>

void swap(int k[], int low, int high)
{
    int temp = k[low];
    k[low] = k[high];
    k[high] = temp;
}

//交换顺序表中子表记录，是枢轴记录到位，并返回其所在位置
//此时在他之前（后）的记录均不大（小）于它
int Partition(int k[], int low, int high)
{
    int pivotkey;
    pivotkey = k[low]; //用子表第一个记录左枢轴记录
    while (low < high) //从表的两端交替向中间扫描
    {
        while (low < high && k[high] >= pivotkey)
            high--;
        swap(k, high, low); //将比枢轴记录小的记录交换到低端
        while (low < high && k[low] <= pivotkey)
            low++;
        swap(k, low, high); //将比枢轴记录大的记录交换到高端
    }
    return low; //返回枢轴所在位置
}

void Qsort(int k[], int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = Partition(k, low, high);
        for (int i = 0; i < 5; i++)
            printf("%d ", k[i]);
        printf("\n");

        Qsort(k, low, pivot - 1);  //对低子表进行递归排序
        Qsort(k, pivot + 1, high); //对高子表进行递归排序
    }
}

int main()
{
    int i;
    int a[5] = {4, 5, 3, 2, 1};
    Qsort(a, 0, 5);

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>

// #define MAX_LEN 1000
// int array[MAX_LEN];
// int size = 0;

// void show_array(int *array)
// {
//     for (int i = 0; i < size; i++)
//     {
//         printf("%d ", array[i]);
//     }
//     printf("\n");
// }

// int sub_quick_sort(int *arr, int low, int high)
// {
//     int pivot = arr[low];
//     while (low < high)
//     {
//         while (low < high && arr[high] >= pivot)
//             high--;
//         int temp = arr[high];
//         arr[high] = arr[low];
//         arr[low] = temp;

//         while (low < high && arr[low] <= pivot)
//             low++;
//         temp = arr[high];
//         arr[high] = arr[low];
//         arr[low] = temp;
//     }
//     return low;
// }

// void quick_sort(int *arr, int low, int high)
// {
//     int pivot;
//     if (low < high)
//     {
//         pivot = sub_quick_sort(arr, low, high);
//         show_array(arr);
//         quick_sort(arr, low, pivot - 1);
//         quick_sort(arr, pivot + 1, high);
//     }
// }

// int main(int argc, char const *argv[])
// {
//     scanf("%d", &size);
//     for (int i = 0; i < size; i++)
//     {
//         scanf("%d", &array[i]);
//     }
//     quick_sort(array, 0, size - 1);
//     return 0;
// }
