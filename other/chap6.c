#include <stdio.h>
#include <stdlib.h>

// 定义二叉树
typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 给定二叉树的前序、中序遍历序列，构造二叉树
BiTree CreateBiTree2(char *pre, char *in, int n)
{
    if (n == 0)
        return NULL;
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root->data = pre[0];
    int i;
    for (i = 0; i < n; i++)
    {
        if (in[i] == root->data)
            break;
    }
    root->lchild = CreateBiTree2(pre + 1, in, i);
    root->rchild = CreateBiTree2(pre + i + 1, in + i + 1, n - i - 1);
    return root;
}

// 栈
typedef struct Stack
{
    BiTNode *data;
    struct Stack *next;
} Stack;

// 初始化栈
Stack *InitStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = NULL;
    s->next = NULL;
    return s;
}
// 判断栈是否为空
int IsEmpty(Stack *s)
{
    return s->data == NULL;
}
// 入栈
void Push(Stack *s, BiTNode *data)
{
    Stack *p = (Stack *)malloc(sizeof(Stack));
    p->data = data;
    p->next = s->next;
    s->next = p;
}
// 出栈
BiTNode *Pop(Stack *s)
{
    if (IsEmpty(s))
        return NULL;
    Stack *p = s->next;
    s->next = p->next;
    return p->data;
}

// 前序遍历非递归
void PreOrderTraverse(BiTree T)
{
    Stack *s = InitStack();
    BiTNode *p = T;
    while (p || !IsEmpty(s))
    {
        while (p)
        {
            printf("%c ", p->data);
            Push(s, p);
            p = p->lchild;
        }
        p = Pop(s);
        p = p->rchild;
    }
}

// 交换二叉树的左右子树
void SwapChild(BiTree T)
{
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
}

void BiTreeSwap(BiTree T)
{
    if (T == NULL)
        return;
    SwapChild(T);
    BiTreeSwap(T->lchild);
    BiTreeSwap(T->rchild);
}

/*
// 二叉树的顺序存储结构
typedef struct
{
    char *data;
    int length;
} SqBiTree;

// 先序遍历
void PreOrder(SqBiTree *T, int n)
{
    if (n <= T->length && T->data[n] != 0)
    {
        printf("%c", T->data[n]);
        PreOrder(T, 2 * n);
        PreOrder(T, 2 * n + 1);
    }
}
*/

/*



// 初始化二叉树
void InitBiTree(SqBiTree *T, int length)
{
    T->data = (int *)malloc(sizeof(int) * (length + 2));
    T->length = length;
}

// 创建二叉树
void CreateBiTree(SqBiTree *T)
{
    int i;
    for (i = 1; i <= T->length; i++)
    {
        T->data[i] = i;
    }
}

// 给定二叉树的后序、中序遍历序列，构造二叉树
BiTree CreateBiTree(char *post, char *in, int n)
{
    if (n == 0)
        return NULL;
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root->data = post[n - 1];
    int i;
    for (i = 0; i < n; i++)
    {
        if (in[i] == root->data)
            break;
    }
    // root->lchild = CreateBiTree(post, in, i);
    // root->rchild = CreateBiTree(post + i, in + i + 1, n - i - 1);
    return root;
}



// 输出树形结构，逆中序遍历
void PrintBiTree(BiTree T)
{
    if (T == NULL)
        return;
    PrintBiTree(T->rchild);
    printf("%c ", T->data);
    PrintBiTree(T->lchild);
}

// 前序遍历
void PreOrder(BiTree T)
{
    if (T == NULL)
        return;
    printf("%c ", T->data);
    PreOrder(T->lchild);
    PreOrder(T->rchild);
}

// 中序遍历
void InOrder(BiTree T)
{
    if (T == NULL)
        return;
    InOrder(T->lchild);
    printf("%c ", T->data);
    InOrder(T->rchild);
}

// 后序遍历
void PostOrder(BiTree T)
{
    if (T == NULL)
        return;
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    printf("%c ", T->data);
}

// 队列
typedef struct
{
    BiTree *base;
    int front, rear;
} Queue;

// 初始化队列
void InitQueue(Queue *Q)
{
    Q->base = (BiTree *)malloc(sizeof(BiTree) * 100);
    Q->front = Q->rear = 0;
}

// 入队
void EnQueue(Queue *Q, BiTree T)
{
    Q->base[Q->rear++] = T;
}
// 判断队列是否为空
int IsEmpty(Queue *Q)
{
    return Q->front == Q->rear;
}
// 出队
BiTree DeQueue(Queue *Q)
{
    return Q->base[Q->front++];
}

// 层序遍历
void LevelOrder(BiTree T)
{
    Queue Q;
    InitQueue(&Q);
    EnQueue(&Q, T);
    while (!IsEmpty(&Q))
    {
        BiTree p = DeQueue(&Q);
        printf("%c ", p->data);
        if (p->lchild)
            EnQueue(&Q, p->lchild);
        if (p->rchild)
            EnQueue(&Q, p->rchild);
    }
}

// 给定结点个数，构建完全二叉树
BiTree CreateCompleteBiTree(int n)
{
    if (n == 0)
        return NULL;
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root->data = 'A' + n - 1;
    root->lchild = CreateCompleteBiTree(n - 1);
    root->rchild = CreateCompleteBiTree(n - 1);
    return root;
}

// 给定一棵完全二叉树的节点个数，求该树的叶子节点个数
int LeafNum(BiTree T)
{
    if (T == NULL)
        return 0;
    if (T->lchild == NULL && T->rchild == NULL)
        return 1;
    return LeafNum(T->lchild) + LeafNum(T->rchild);
}

int main(int argc, char const *argv[])
{
    // char post[] = "DABEC";
    // char in[] = "DEBAC";
    // int n = sizeof(post) / sizeof(char);
    // BiTree T = CreateBiTree(post, in, n);
    // PreOrder(T);
    // printf("\n");
    // LevelOrder(T);
    // printf("\n");
    // char pre[] = "EBADCFHGIKJ";
    // char in[] = "ABCDEFGHIJK";
    // int n = sizeof(pre) / sizeof(char);
    // BiTree T = CreateBiTree2(pre, in, n);
    // PreOrder(T);
    // printf("\n");
    // PostOrder(T);
    // LevelOrder(T);
    // printf("\n");
    BiTree T = CreateCompleteBiTree(520);
    printf("%d\n", LeafNum(T));
    return 0;
}
*/