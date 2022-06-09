#include <stdio.h>
#include <stdlib.h>

#define MAX_CUSTOMER_COUNT 512
int N, K;

typedef struct customer
{
    int t; //到达时间
    int p; //办理用时
    int w; //等待时间
} Customer, *CustomerPoint;

typedef struct queue
{
    Customer *Data[MAX_CUSTOMER_COUNT]; /* 存储元素的数组   */
    int Front, Rear;                    /* 队列的头、尾指针 */
} * Queue;

typedef struct window
{
    Queue queue;
    int currentQueueTime; //当前队列耗时
    int count;            //服务人数
} Window;

Queue CreateDeque()
{
    Queue D = (Queue)malloc(sizeof(struct queue));
    D->Front = D->Rear = 0;
    return D;
}

Customer *Pop(Queue D)
{
    if (D->Front == D->Rear)
    {
        return NULL;
    }
    Customer *e = D->Data[D->Front];
    D->Front = (D->Front + 1) % MAX_CUSTOMER_COUNT;
    return e;
}

int Inject(Customer *X, Queue D)
{
    if ((D->Rear + 1) % MAX_CUSTOMER_COUNT == D->Front)
    {
        return 0;
    }
    D->Data[D->Rear] = X;
    D->Rear = (D->Rear + 1) % MAX_CUSTOMER_COUNT;
    return 1;
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

int getMaxCurrentQueueTime(Window *ws)
{
    int maxTime = ws[0].currentQueueTime;
    for (size_t i = 1; i < K; i++)
    {
        if (ws[i].currentQueueTime > maxTime)
        {
            maxTime = ws[i].currentQueueTime;
        }
    }
    return maxTime;
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

    // 创建客人
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &cs[i].t, &cs[i].p);
        if (cs[i].p > 60)
        {
            cs[i].p = 60;
        }
        cs[i].w = 0;
    }

    // 创建窗口
    scanf("%d", &K);
    Window *ws = (Window *)malloc(K * sizeof(Window)); // K个窗口

    // 初始化窗口
    for (size_t i = 0; i < K; i++)
    {
        ws[i].queue = CreateDeque();
        ws[i].currentQueueTime = 0;
        ws[i].count = 0;
    }

    // 遍历所有客人去窗口排队
    for (size_t i = 0; i < N; i++)
    {
        int currentCustomerComeTime = cs[i].t; //下一位顾客到来的时间
        int minWaitWindowIndex = 0;
        for (size_t j = 0; j < K; j++)
        {
            if (ws[j].currentQueueTime - currentCustomerComeTime < 0)
            { //如果时间为负数就去第一个
                minWaitWindowIndex = j;
                break;
            }
            else if (ws[j].currentQueueTime - currentCustomerComeTime < ws[minWaitWindowIndex].currentQueueTime - currentCustomerComeTime)
            {
                minWaitWindowIndex = j;
            }
        }
        Inject(&cs[i], ws[minWaitWindowIndex].queue);
        ws[minWaitWindowIndex].currentQueueTime += cs[i].p;
        ws[minWaitWindowIndex].count++;
    }

    // 各个窗口开始干活
    for (size_t i = 0; i < K; i++)
    {
        Customer *c;
        int currentStopTime = 0;
        // for (int p = ws[i].queue->Front; p != ws[i].queue->Rear; p = (p + 1) % MAX_CUSTOMER_COUNT)
        for (int p = ws[i].queue->Front; p != (ws[i].queue->Rear - 1 + MAX_CUSTOMER_COUNT) % MAX_CUSTOMER_COUNT; p = (p + 1) % MAX_CUSTOMER_COUNT)
        {
            currentStopTime = ws[i].queue->Data[p]->t + ws[i].queue->Data[p]->p;
            for (int q = (p + 1) % MAX_CUSTOMER_COUNT; p != ws[i].queue->Rear; p = (p + 1) % MAX_CUSTOMER_COUNT)
            {
                if (ws[i].queue->Data[q]->t < currentStopTime)
                {
                    ws[i].queue->Data[q]->w = currentStopTime - ws[i].queue->Data[q]->t;
                }
                else
                {
                    break;
                }
            }
        }
    }

    // 数据输出
    int maxWaitTime = 0;
    double average = finder(cs, &maxWaitTime);
    printf("%.1f %d %d\n", average, maxWaitTime, getMaxCurrentQueueTime(ws));
    // 窗口服务的顾客数目
    show_window_count(ws);

    return 0;
}