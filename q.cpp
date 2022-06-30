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
    bool Place(int k);   //测试皇后k置于第x[k]列的合法性
    bool QueensLV(void); //随机放置n个皇后拉斯维加斯算法
    int n;               //皇后个数
    int *x;              //解向量
};
bool Queen::Place(int k)
{ //测试皇后k置于第x[k]列的合法性
    for (int j = 1; j < k; j++)
        if ((abs(k - j) == abs(x[j] - x[k])) || (x[j] == x[k]))
            return false;
    return true;
}
bool Queen::QueensLV(void)
{ //随机放置n个皇后的拉斯维加斯算法
    int k = 1;
    int count = 1;
    while ((k <= n) && (count > 0))
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
{
    Queen x;
    //初始化x
    x.n = n;
    int *p = new int[n + 1];
    for (int i = 0; i <= n; i++)
        p[i] = 0;
    x.x = p;
    //反复调用随机放置n个皇后的拉斯维加斯算法，直至放置成功
    while (!x.QueensLV())
        ;
    for (int i = 1; i <= n; i++)
        cout << p[i] << " ";
    delete[] p;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    nQueen(8);
    return 0;
}
