#include <stdio.h>
#include <stdlib.h>

#define ERROR 1e8
typedef int ElementType;
typedef enum
{
    push,
    pop,
    end
} Operation;
typedef enum
{
    false,
    true
} bool;
typedef int Position;
// 其中Tag是堆栈编号，取1或2；MaxSize堆栈数组的规模；Stack结构定义如下：
struct SNode
{
    ElementType *Data;
    Position Top1, Top2;
    int MaxSize;
};
typedef struct SNode *Stack;
// 函数接口定义
Stack CreateStack(int MaxSize);
bool Push(Stack S, ElementType X, int Tag);
ElementType Pop(Stack S, int Tag);
// 注意：如果堆栈已满，Push函数必须输出“Stack Full”并且返回false；
// 如果某堆栈是空的，则Pop函数必须输出“Stack Tag Empty”（其中Tag是该堆栈的编号），并且返回ERROR。

Operation GetOp();                 /* details omitted */
void PrintStack(Stack S, int Tag); /* details omitted */

int main()
{
    int N, Tag, X;
    Stack S;
    int done = 0;

    scanf("%d", &N);
    S = CreateStack(N);
    while (!done)
    {
        switch (GetOp())
        {
        case push:
            scanf("%d %d", &Tag, &X);
            if (!Push(S, X, Tag))
                printf("Stack %d is Full!\n", Tag);
            break;
        case pop:
            scanf("%d", &Tag);
            X = Pop(S, Tag);
            if (X == ERROR)
                printf("Stack %d is Empty!\n", Tag);
            break;
        case end:
            PrintStack(S, 1);
            PrintStack(S, 2);
            done = 1;
            break;
        }
    }
    return 0;
}

/* 你的代码将被嵌在这里 */

Stack CreateStack(int MaxSize)
{
    Stack s = (Stack)malloc(sizeof(Stack));
    s->Data = (ElementType *)malloc(sizeof(ElementType) * MaxSize);
    s->Top1 = -1;
    s->Top2 = MaxSize;
    s->MaxSize = MaxSize;
    return s;
}

bool Push(Stack S, ElementType X, int Tag)
{
    if (S->Top1 + 1 >= S->Top2)
    {
        printf("Stack Full\n");
        return false;
    }
    switch (Tag)
    {
    case 1:
        S->Data[++S->Top1] = X;
        break;
    case 2:
        S->Data[--S->Top2] = X;
        break;
    }
    return true;
}

ElementType Pop(Stack S, int Tag)
{
    switch (Tag)
    {
    case 1:
        return S->Top1 < 0 ? printf("Stack 1 Empty\n"), ERROR : S->Data[S->Top1--];
    case 2:
        return S->Top2 >= S->MaxSize ? printf("Stack 2 Empty\n"), ERROR : S->Data[S->Top2++];
    }
}
