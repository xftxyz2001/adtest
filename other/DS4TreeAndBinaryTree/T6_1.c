#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
int GetHeight(BinTree BT);

int main()
{
    BinTree BT = CreatBinTree();
    printf("%d\n", GetHeight(BT));
    return 0;
}
/* 你的代码将被嵌在这里 */

int GetHeight(BinTree BT)
{
    if (BT == NULL)
    {
        return 0; //空结点高度为0
    }
    else if (BT->Left == NULL && BT->Right == NULL)
    {
        return 1; //叶子结点高度为1
    }
    else
    {
        int l = GetHeight(BT->Left);  //左
        int r = GetHeight(BT->Right); //右
        return (l > r ? l : r) + 1;   //高度最大值+1
    }
}
