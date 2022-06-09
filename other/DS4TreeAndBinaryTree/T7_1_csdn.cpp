#include <iostream>
using namespace std;
const int MAXN = 30000;
int pre[MAXN], sum[MAXN], ranking[MAXN], ar[1000];

void Initialise(int n);
int find(int x);
void Unite(int x, int y);
//增加ranking的优化算法
int main()
{

    int n, m;
    cin >> n >> m;
    Initialise(n);
    int t;
    while (m--)
    {

        cin >> t;
        for (int i = 1; i <= t; i++)
        {
            cin >> ar[i];
        }

        for (int i = 1; i <= t; i++)
        {
            for (int j = i + 1; j <= t; j++)
                Unite(ar[i], ar[j]); //对每一个朋友圈里的任意两个人并在一起
        }
    }

    int maxn = 0;
    for (int i = 1; i <= n; i++) //常规找最大值
    {
        if (sum[i] > maxn)
            maxn = sum[i];
    }

    cout << maxn;
    return 0;
}
void Initialise(int n)
{
    for (int i = 1; i <= n; i++)
    {
        pre[i] = i;     //初始化为每个人的上级都是自己
        sum[i] = 1;     //每个人都是一个朋友圈(仔细想想)，人数起初只有一个人
        ranking[i] = 1; //高度也都是1
    }
}
int find(int x)
{
    if (pre[x] == x) //递归出口
        return x;
    else
        return pre[x] = find(pre[x]); //如果查找的x不是根，那么通过递归认为直接把“根”找到并赋给pre[x]
}

void Unite(int x, int y) //这是效率比较低的算法
{
    int x_root = find(x);
    int y_root = find(y);
    if (x_root != y_root)
    {
        pre[x_root] = y_root;
        sum[y_root] += sum[x_root];
    }
}

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
