#include <stdio.h>

int n, arr[50];
int canuse;

int arr_print(int cur) // 判断并输出数组（排列后的结果），返回判断结果
{
    int ok = cur >= n;
    if (ok)
    {
        for (int i = 1; i <= n; i++)
        {
            printf("%d", arr[i]);
            if (i != n)
                printf(" ");
        }
        printf("\n");
    }
    return ok;
}

void full_permutation(int cur)
{
    for (int i = 1; i <= n; i++) // i为当前处理的数字
    {
        canuse = 1;                   // 标记为1，表示当前数字可以使用
        for (int j = 1; j < cur; j++) // 从结果数组开头扫描到cur的前一位
        {
            if (arr[j] == i) // 当前处理的数字已被使用
            {
                canuse = 0; // 标记为0，表示当前数字不可以使用
                break;
            }
        }
        if (!canuse)                   // 当前数字不可以使用
            continue;                  // 继续扫描下一个数字
        arr[cur] = i;                  // 当前数字可以使用，放入结果数组cur位置
        if (!arr_print(cur))           // 如果没打印出来
            full_permutation(cur + 1); // 继续下一次递归调用
    }
}

int main(int argc, char const *argv[])
{
    scanf("%d", &n);     // 输入n
    full_permutation(1); // 开始递归
    return 0;
}
