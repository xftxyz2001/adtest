#include <stdio.h>
#include <stdlib.h>

// 顾客
typedef struct customer
{
    int come; //顾客到来的时间
    int use;  //办理业务需要的时间
} customer;

// 窗口
typedef struct window
{
    int time;      //窗口恢复空闲的时间
    int wait_time; //所有客户在该窗口等待的总时间
    int counter;   //办理的客户数量
} window;

typedef struct cqnode
{
    customer *customer;
    struct cqnode *next;
} cqnode;

typedef struct customerQueue
{
    cqnode *front;
    cqnode *rear;
} * customerQueue;

customerQueue initQueue()
{
    customerQueue queue = (customerQueue)malloc(sizeof(struct customerQueue));
    queue->front = (cqnode *)malloc(sizeof(struct cqnode));
    queue->rear = queue->front;
    queue->front->next = NULL;
    return queue;
}

int enterQueue(customerQueue queue, customer *cstm)
{
    cqnode *newNode = (cqnode *)malloc(sizeof(struct cqnode));
    newNode->customer = cstm;
    newNode->next = NULL;
    queue->rear->next = newNode;
    queue->rear = newNode;
    return 1;
}

int deleteQueue(customerQueue queue, customer **cstm)
{
    if (queue->front == queue->rear)
    {
        return 0;
    }
    cqnode *p = queue->front->next;
    queue->front->next = p->next;
    if (queue->rear == p)
    {
        queue->rear = queue->front;
    }
    *cstm = p->customer;
    free(p);
    return 1;
}

int isEmpty(customerQueue queue)
{
    return queue->front == queue->rear;
}

void show_window_count(window *windows, int windowsNumber)
{
    for (size_t i = 0; i < windowsNumber; i++)
    {
        printf("%d", windows[i].counter);
        if (i != windowsNumber - 1)
        {
            printf(" ");
        }
    }
}

double finder(window *windows, int windowsNumber, int *maxWaitTime)
{
    double avg = 0.0;
    for (int i = 0; i < windowsNumber; i++)
    {
        avg += windows[i].wait_time;
        if (windows[i].time > *maxWaitTime)
        {
            *maxWaitTime = windows[i].time;
        }
    }
    return avg;
}

int main()
{
    /*
    N(customerNumber):顾客总人数 <=1000
    每行给出一位顾客的到达时间T和事务处理时间P,已经按到达时间先后排好了顺序
    K(windowsNumber)：开设的营业窗口数 <=10
    */
    int customerNumber, windowsNumber;

    // 初始化参数
    customer *tempCustomer;                           //存储单个客户信息
    customerQueue wait;                               //客户等待队列
    window *windows;                                  //模拟 k 个窗口
    int i, flag;                                      //循环控制变量,受理标志
    int min_time, num, max_waittime = 0, maxtime = 0; //最快可办理窗口时间、最快可办理窗口编号、最大等待时间、最后办理结束时间
    double avg = 0.0;

    // 初始化客人队列
    scanf("%d", &customerNumber);
    wait = initQueue();
    for (i = 0; i < customerNumber; i++)
    {
        tempCustomer = (customer *)malloc(sizeof(customer));
        scanf("%d %d", &tempCustomer->come, &tempCustomer->use);
        if (tempCustomer->use > 60)
            tempCustomer->use = 60;
        enterQueue(wait, tempCustomer);
    }

    // 初始化窗口
    scanf("%d", &windowsNumber);
    windows = (window *)malloc(windowsNumber * sizeof(window));
    for (i = 0; i < windowsNumber; i++) //制造 k 个窗口
    {
        windows[i].counter = 0;
        windows[i].time = 0;
        windows[i].wait_time = 0;
    }

    // 主控逻辑
    while (!isEmpty(wait)) //等待队列不为空
    {
        flag = 0;
        min_time = 9999; //一个理论极大值
        // 出队一个顾客
        tempCustomer = (customer *)malloc(sizeof(customer));
        deleteQueue(wait, &tempCustomer);

        for (i = 0; i < windowsNumber; i++)
        {
            if (windows[i].time <= tempCustomer->come) //有空闲窗口
            {
                windows[i].time = tempCustomer->come;
                windows[i].time += tempCustomer->use;
                windows[i].counter++;
                flag++;
                break;
            }
            if (windows[i].time < min_time) //记录最先可办理窗口
            {
                num = i;
                min_time = windows[i].time;
            }
        }
        if (flag) //已经在空闲窗口办理
            continue;
        if (tempCustomer->come > windows[num].time) //到最先可办理窗口办理
            windows[num].time = tempCustomer->come;
        else
        {
            windows[num].wait_time += (windows[num].time - tempCustomer->come);
            if ((windows[num].time - tempCustomer->come) > max_waittime) //更新最大等待时间
                max_waittime = windows[num].time - tempCustomer->come;
        }
        windows[num].time += tempCustomer->use;
        windows[num].counter++;
    } // end while

    // 数据输出
    avg = finder(windows, windowsNumber, &maxtime) / customerNumber;
    printf("%.1f %d %d\n", avg, max_waittime, maxtime);
    show_window_count(windows, windowsNumber);
    return 0;
}
