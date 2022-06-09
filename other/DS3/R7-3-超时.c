#include <stdio.h>
#include <stdlib.h>

int n, N, K;

typedef struct customer
{
    int t; //到达时间
    int p; //办理用时
    int w; //等待时间
} Customer;

typedef struct window
{
    Customer *c;
    int p; // 办理已用时
    int count;
} Window;

typedef Customer *ElementType;

struct QNode
{
    ElementType *Data; /* 存储元素的数组   */
    int Front, Rear;   /* 队列的头、尾指针 */
    int MaxSize;       /* 队列最大容量     */
};
typedef struct QNode *PtrToQNode;
typedef PtrToQNode Deque;

Deque CreateDeque(int MaxSize)
{ /* 注意：为区分空队列和满队列，需要多开辟一个空间 */
    Deque D = (Deque)malloc(sizeof(struct QNode));
    MaxSize++;
    D->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    D->Front = D->Rear = 0;
    D->MaxSize = MaxSize;
    return D;
}

//将元素X插入到双端队列D的头；
int Push(ElementType X, Deque D)
{
    if ((D->Rear + 1) % D->MaxSize == D->Front)
    {
        return 0;
    }
    D->Front = (D->Front - 1 + D->MaxSize) % D->MaxSize;
    D->Data[D->Front] = X;
    return 1;
}

// 删除双端队列D的头元素，并返回；
ElementType Pop(Deque D)
{
    if (D->Front == D->Rear)
    {
        return NULL;
    }
    ElementType e = D->Data[D->Front];
    D->Front = (D->Front + 1) % D->MaxSize;
    return e;
}

// 将元素X插入到双端队列D的尾部；
int Inject(ElementType X, Deque D)
{
    if ((D->Rear + 1) % D->MaxSize == D->Front)
    {
        return 0;
    }
    D->Data[D->Rear] = X;
    D->Rear = (D->Rear + 1) % D->MaxSize;
    return 1;
}

// 删除双端队列D的尾部元素，并返回。
ElementType Eject(Deque D)
{
    if (D->Front == D->Rear)
    {
        return NULL;
    }
    D->Rear = (D->Rear - 1 + D->MaxSize) % D->MaxSize;
    ElementType e = D->Data[D->Rear];
    return e;
}

void windows_process(Window *ws)
{
    // int isFree = 0;
    for (size_t i = 0; i < K; i++)
    {
        if (ws[i].c != NULL)
        {
            if (ws[i].p >= ws[i].c->p || ws[i].p >= 60)
            {
                ws[i].c = NULL;
                ws[i].count++;
                // isFree = 1;
            }
        }
    }
    // return isFree;
}

void queue_wait(Deque D)
{
    int p = D->Front;
    while (p != D->Rear)
    {
        D->Data[p]->w++;
        p = (p + 1) % D->MaxSize;
    }
}

int has_busy_window(Window *ws)
{
    for (size_t i = 0; i < K; i++)
    {
        if (ws[i].c != NULL)
            return 1;
    }
    return 0;
}

int has_free_window(Window *ws)
{
    for (size_t i = 0; i < K; i++)
    {
        if (ws[i].c == NULL)
            return 1;
    }
    return 0;
}

int has_queue_customer(Deque d)
{
    return d->Front != d->Rear;
}

int has_late_customer()
{
    return n < N;
}

void window_add(Window *ws, Customer *c)
{
    for (size_t i = 0; i < K; i++)
    {
        if (ws[i].c == NULL)
        {
            ws[i].c = c;
        }
    }
}

double finder(Customer *cs, int *maxWaitTime)
{
    int sum = 0;
    for (size_t i = 0; i < N; i++)
    {
        if (cs[i].w > *maxWaitTime)
        {
            *maxWaitTime = cs[i].w;
        }
        sum += cs[i].w;
    }
    return (double)sum / N;
}

void show_window_count(Window *ws)
{
    for (size_t i = 0; i < K; i++)
    {
        printf("%d", ws[i].count);
        if (i != K - 1)
        {
            printf(" ");
        }
    }
}

int main(int argc, char const *argv[])
{
    /*
    N:顾客总人数 <=1000
    每行给出一位顾客的到达时间T和事务处理时间P,已经按到达时间先后排好了顺序
    K：开设的营业窗口数 <=10
    */

    // 初始化参数
    scanf("%d", &N);
    Customer *cs = (Customer *)malloc(N * sizeof(Customer)); //N名客人
    Deque d = CreateDeque(N);

    // 创建客人
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &cs[i].t, &cs[i].p);
    }
    // 创建窗口
    scanf("%d", &K);
    Window *ws = (Window *)malloc(K * sizeof(Window)); // K个窗口
    int time;
    for (time = 0;; time++)
    {
        if (has_busy_window(ws) || has_queue_customer(d) || has_late_customer())
        { // 窗口处理
            windows_process(ws);
            //排队
            queue_wait(d);
            //空闲窗口
            while (has_free_window(ws))
            {
                //出队加入窗口
                window_add(ws, Pop(d));
            }
            //加入排队
            while (has_late_customer(cs))
            {
                Inject(cs, d);
            }
        }
        else
        {
            break;
        }
    }
    int maxWaitTime = 0;
    double average = finder(cs, &maxWaitTime);
    printf("%.1f %d %d\n", average, maxWaitTime, time);
    show_window_count(ws);

    return 0;
}
