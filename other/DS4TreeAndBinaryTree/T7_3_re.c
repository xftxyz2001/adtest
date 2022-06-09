#include <stdio.h>
#include <malloc.h>

typedef struct TNode
{
    int Data;
    struct TNode *Left;
    struct TNode *Right;
} BinTree;

typedef BinTree *QueueElementType;

typedef struct Node
{
    QueueElementType data;
    struct Node *next;
} LinkQueueNode;
typedef struct
{
    LinkQueueNode *front;
    LinkQueueNode *rear;
} LinkQueue;
LinkQueue *InitQueue()
{
    LinkQueue *Q = (LinkQueue *)malloc(sizeof(LinkQueue));
    Q->front = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if (Q->front != NULL)
    {
        Q->rear = Q->front;
        Q->front->next = NULL;
    }
    return Q;
}
void EnterQueue(LinkQueue *Q, QueueElementType x)
{
    LinkQueueNode *newNode;
    if (newNode = (LinkQueueNode *)malloc(sizeof(LinkQueueNode)))
    {
        newNode->data = x;
        newNode->next = NULL;
        Q->rear->next = newNode;
        Q->rear = newNode;
    }
}

int isEmpty(LinkQueue *Q)
{
    return Q->front == Q->rear;
}

QueueElementType DeleteQueue(LinkQueue *Q)
{
    LinkQueueNode *p = Q->front->next;
    Q->front->next = p->next;
    if (Q->rear == p)
    { //只有一个元素，出队变空队
        Q->rear = Q->front;
    }
    QueueElementType x = p->data;
    free(p);
    return x;
}

BinTree *createBinaryTreeByPostInOrder(int *post, int *in, int n)
{
    int i = 0, k = 0, root = 0;
    if (n == 0) //空树
        return NULL;
    BinTree *T = (BinTree *)malloc(sizeof(BinTree));
    root = post[n - 1]; //根节点就是后序遍历的最后一位
    T->Data = root;
    for (i = 0; i < n; i++)
    {
        if (in[i] == root) //通过中序遍历，确定左右子树的长度
        {
            k = i;
            break;
        }
    }
    T->Left = createBinaryTreeByPostInOrder(post, in, k); //递归左右子树
    T->Right = createBinaryTreeByPostInOrder(post + k, in + k + 1, n - k - 1);
    return T;
}

void sequence(BinTree *T, int n) //层序遍历二叉树
{
    BinTree *q;
    LinkQueue *queue = InitQueue();
    int num = 0;
    if (T) //树不为空
    {
        EnterQueue(queue, T); //根节点入队列
        while (!isEmpty(queue))
        {
            q = DeleteQueue(queue);
            printf("%d", q->Data);
            if (++num < n)
                printf(" "); //格式控制：计数输出空格
            if (q->Left)     //左树不为空，入队
                EnterQueue(queue, q->Left);
            if (q->Right) //右树不为空，入队
                EnterQueue(queue, q->Right);
        }
    }
}

int main(int argc, char const *argv[])
{

    int N; //N：二叉树中结点的个数
    scanf("%d", &N);
    int *PostOrder = (int *)malloc(N * sizeof(int)); //后序遍历序列
    int *InOrder = (int *)malloc(N * sizeof(int));   //中序遍历序列
    for (int i = 0; i < N; i++)
        scanf("%d", &PostOrder[i]);
    for (int i = 0; i < N; i++)
        scanf("%d", &InOrder[i]);
    BinTree *tree = createBinaryTreeByPostInOrder(PostOrder, InOrder, N);
    sequence(tree, N);
    return 0;
}
