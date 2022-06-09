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

// void PreorderTraversal(BinTree BT)
// {
//     Stack s = CreateStack();
//     while (BT != NULL && !IsEmpty(s))
//     {
//         if (BT != NULL)
//         {
//             showData(BT);
//             Push(s, BT);
//             BT = BT->Left;
//         }
//         else
//         {
//             BT = Pop(s);
//             BT = BT->Right;
//         }
//     }
// }
// void PreorderTraversal(BinTree BT)
// { //前序遍历非递归算法

//     Stack s = CreateStack();
//     Push(s, BT); //先将根节点压进栈中
//     while (BT != NULL && !IsEmpty(s))
//     {
//         BT = Pop(s);  //弹出栈顶的节点赋给p
//         showData(BT); //用输出来代替对节点的处理
//         if (BT->Right != NULL)
//         {
//             Push(s, BT->Right); //如果弹出节点的右孩子不为空则压入栈
//         }                       //注意，这里的重点是一定要先将右孩子压入栈，再将左孩子压入
//         if (BT->Left != NULL)
//         {
//             Push(s, BT->Left); //如果弹出节点的左孩子不为空则压入栈
//         }
//     }
// }

void PreorderTraversal(BinTree BT)
{
    if (BT != NULL)
    {

        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
        showData(BT);
    }
}

void PostorderTraversal(BinTree BT)
{
    Stack s = CreateStack();
    BinTree p = BT, q = NULL;
    while (p != NULL || !IsEmpty(s))
    {
        if (p != NULL) //访问左子树
        {
            Push(s, p);
            p = p->Left;
        }
        else
        {
            p = Peek(s);
            if (p->Right == NULL || p->Right == q)
            {
                showData(p);
                q = p;
                Pop(s);
                p = NULL;
            }
            else
            {
                p = p->Right;
            }
        }
    }
}
void InorderTraversal(BinTree BT)
{
    Stack s = CreateStack();
    while (BT != NULL && !IsEmpty(s))
    {
        if (BT != NULL)
        {
            Push(s, BT);
            BT = BT->Left;
        }
        else
        {
            BT = Pop(s);
            showData(BT);
            BT = BT->Right;
        }
    }
}
