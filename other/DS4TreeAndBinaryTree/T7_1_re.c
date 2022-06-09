#include <stdio.h>

#define MAXSIZE 30000
int pre[MAXSIZE], sum[MAXSIZE], ranking[MAXSIZE], ar[1000];

void Initialise(int n) //初始化
{
    for (int i = 1; i <= n; i++)
    {
        pre[i] = i;     //每个人的上级都是自己
        sum[i] = 1;     //每个人都是一个朋友圈，人数起初只有一个人
        ranking[i] = 1; //高度都是1
    }
}
int find(int x)
{
    if (pre[x] == x) //递归出口
        return x;
    else
        return pre[x] = find(pre[x]); //如果查找的x不是根，那么通过递归认为直接把“根”找到并赋给pre[x]
}

void Unite(int x, int y)
{
    int x_root = find(x);
    int y_root = find(y);
    if (x_root != y_root)
    {
        pre[x_root] = y_root;
        sum[y_root] += sum[x_root];
    }
}

int main()
{
    int n = 0, m = 0, max = 0, club_person_amount, i, j;
    scanf("%d", &n); //人数
    scanf("%d", &m); //俱乐部数
    Initialise(n);   //初始化
    while (m--)
    {
        scanf("%d", &club_person_amount);
        for (i = 1; i <= club_person_amount; i++)
            scanf("%d", &ar[i]);
        for (i = 1; i <= club_person_amount; i++)
            for (j = i + 1; j <= club_person_amount; j++)
                Unite(ar[i], ar[j]); //对每一个朋友圈里的任意两个人并在一起
    }
    for (int i = 1; i <= n; i++) //常规找最大值
        if (sum[i] > max)
            max = sum[i];
    printf("%d", max);
    return 0;
}

/*
void Unite(int x, int y) //这是优化过的算法
{
    int x_root = find(x);
    int y_root = find(y); //找到二者的根
    if (x_root == y_root)
        return; //如果在同一颗树上就不需要进一步操作了

    if (ranking[x_root] < ranking[y_root]) //当x_root高度小于y_root
    {
        pre[x_root] = y_root;       //那么让y_root作为x_root的根
        sum[y_root] += sum[x_root]; //把x_root的朋友圈并到y_root的朋友圈中
    }
    else
    {
        if (ranking[x_root] == ranking[y_root])
            ranking[x_root]++;      //如果x_root与y_root的高度相同，
                                    //二者均可为对方的根，为了统一操作，这里应当让x_root为根(简单想想)
        pre[y_root] = x_root;       //让x_root作为y_root的根；
        sum[x_root] += sum[y_root]; //把y_root的朋友圈并到x_root的朋友圈中
    }
}
*/