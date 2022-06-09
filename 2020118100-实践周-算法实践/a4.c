#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/**
 * 设有n=2k个选手要进行网球循环赛，要求设计一个满足以下要求的比赛日程表：
 * 1. 每个选手必须与其他n-1个选手各赛一次。
 * 2. 每个选手一天只能赛一次。
 * 3. 循环赛在n-1天之内结束。
 */

int **new_schedule(int n)
{
    int **schedule = (int **)malloc(sizeof(int *) * (n + 1));
    for (int i = 0; i <= n; i++)
    {
        schedule[i] = (int *)malloc(sizeof(int) * (n + 1));
    }
    return schedule;
}

// 进行循环赛日程安排，生成日程表
void create_schedule(int k, int n, int **schedule)
{
    // 设置日程表第一行的值
    for (int i = 1; i <= n; i++)
        schedule[1][i] = i;

    // 每次填充的起始填充位置
    int begin = 1;

    // 用分治法分separate份，循环求解
    for (int separate = 1; separate <= k; separate++)
    {
        n /= 2; // 日程表进行划分
        // flag为每一小份的列的标记
        for (int flag = 1; flag <= n; flag++)
        {
            for (int i = begin + 1; i <= 2 * begin; i++) // 操作行
            {
                for (int j = begin + 1; j <= 2 * begin; j++) // 操作列
                {
                    // 把左上角的值赋给右下角
                    schedule[i][j + (flag - 1) * begin * 2] = schedule[i - begin][j + (flag - 1) * begin * 2 - begin];
                    // 把右上角的值赋给左下角
                    schedule[i][j + (flag - 1) * begin * 2 - begin] = schedule[i - begin][j + (flag - 1) * begin * 2];
                }
            }
        }
        // 进入日程表的下一个划分进行填充
        begin *= 2;
    }
}

// 打印日程表
void show_schedule(int **schedule, int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d\t", schedule[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n = 0, k = 0;

    printf("请输入k(k>=0)，有n=2k个选手要进行网球循环赛：");
    scanf("%d", &k); // 输入k

    n = pow(2, k); // 选手数

    // 分配日程表空间
    int **schedule = new_schedule(n);

    // 进行循环赛日程安排，生成日程表
    create_schedule(k, n, schedule);

    // 显示输出
    show_schedule(schedule, n);

    return 0;
}
