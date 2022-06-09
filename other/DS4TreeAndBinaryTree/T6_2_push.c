#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    false,
    true
} bool;

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
    int flag;
};

/*------堆栈的定义-------*/
typedef Position SElementType;
typedef struct SNode *PtrToSNode;
struct SNode
{
    SElementType Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

/* 裁判实现，细节不表 */
Stack CreateStack();
bool IsEmpty(Stack S);
bool Push(Stack S, SElementType X);
SElementType Pop(Stack S);  /* 删除并仅返回S的栈顶元素 */
SElementType Peek(Stack S); /* 仅返回S的栈顶元素 */
/*----堆栈的定义结束-----*/

BinTree CreateBinTree(); /* 裁判实现，细节不表 */

/* 函数接口定义 */
void InorderTraversal(BinTree BT);
void PreorderTraversal(BinTree BT);
void PostorderTraversal(BinTree BT);

int main()
{
    BinTree BT = CreateBinTree();
    printf("Inorder:");
    InorderTraversal(BT);
    printf("\n");
    printf("Preorder:");
    PreorderTraversal(BT);
    printf("\n");
    printf("Postorder:");
    PostorderTraversal(BT);
    printf("\n");
    return 0;
}

/* 你的代码将被嵌在这里 */

void showData(BinTree BT)
{
    printf(" %c", BT->Data);
}

void InorderTraversal(BinTree BT)
{
    Stack S = CreateStack();
    while (BT || !IsEmpty(S))
    {
        while (BT)
        {
            Push(S, BT);
            BT = BT->Left; //有左子树，先遍历左子树
        }
        BT = Pop(S);    //没有左子树，出栈
        showData(BT);   //遍历根结点
        BT = BT->Right; //遍历右子树
    }
}
void PreorderTraversal(BinTree BT)
{
    Stack S = CreateStack();
    while (BT || !IsEmpty(S))
    {
        while (BT)
        {
            Push(S, BT);
            showData(BT);  //遍历根结点
            BT = BT->Left; //遍历左子树
        }
        BT = Pop(S);    //左子树为空，出栈
        BT = BT->Right; //遍历右子树
    }
}
void PostorderTraversal(BinTree BT)
{
    Stack S = CreateStack();
    while (BT || !IsEmpty(S))
    {
        while (BT) //结点不为空，入栈，去到左子树
        {
            Push(S, BT);
            BT = BT->Left;
        }
        BT = Peek(S);
        if (BT->flag != 1) //未遍历过
        {
            BT->flag = 1;
            BT = BT->Right; //遍历右子树
        }
        else
        {
            BT = Pop(S);  //出栈
            showData(BT); //遍历根结点
            BT = NULL;
        }
    }
}
