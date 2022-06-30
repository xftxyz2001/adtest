#include <iostream>

using namespace std;

int randd(int n)
{
    return rand() % n;
}

class Queen
{
    friend void nQueen(int);

private:
    bool Place(int k);            //测试皇后k置于第x[k]列的合法性
    void Backtrack(int t);        //★解n后问题的回溯法
    bool QueensLV(int stopVegas); //★随机放置n个皇后的拉斯维加斯算法
    int n, *x, *y;
};
bool Queen::Place(int k)
{ //测试皇后k置于第x[k]列的合法性
    for (int j = 1; j < k; j++)
        if ((abs(k - j) == abs(x[j] - x[k])) || (x[j] == x[k]))
            return false;
    return true;
}
void Queen::Backtrack(int t)
{
    if (t > n) // t来记当前已经放置的皇后数
    {
        for (int i = 1; i <= n; i++)
            y[i] = x[i];
        return;
    } //已找到一个解并复制给y.
    else
    {
        for (int i = 1; i <= n; i++)
            x[t] = i;
        if (Place(t))
            Backtrack(t + 1);
    }
}
bool Queen::QueensLV(int stopVegas)
{ //随机放置n个皇后的拉斯维加斯算法
    int k = 1;
    int count = 1;
    // 1≤stopVegas≤n表示允许随机放置的皇后数
    while ((k <= stopVegas) && (count > 0))
    {
        count = 0;
        int j = 0;
        for (int i = 1; i <= n; i++)
        {
            x[k] = i;
            if (Place(k))
                if (randd(++count) == 0)
                    j = i; //随机位置
        }
        if (count > 0)
            x[k++] = j;
    }
    return (count > 0); // count>0表示成功放置
}
void nQueen(int n)
{ //与回溯法相结合的解n后问题的拉斯维加斯算法
    Queen x;
    x.n = n;
    int *q = new int[n + 1];
    int *p = new int[n + 1];
    for (int i = 0; i <= n; i++)
    {
        p[i] = 0;
        q[i] = 0;
    }
    x.x = q;
    x.y = p;
    int stop = 5;
    while (!x.QueensLV(stop))
        ;
    x.Backtrack(stop + 1);
    for (int i = 1; i <= 5; i++)
        cout << p[i] << " ";
    cout << endl;
    delete[] p;
    delete[] q;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    nQueen(8);
    return 0;
}
