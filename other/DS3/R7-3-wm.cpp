#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef struct customer
{
    int come;
    int use;
}customer;

typedef struct window
{
    int time;
    int amount;
    int wait_time;
}window;

int main() 
{
    int people_num;
    int i, flag;
    int windows_num;
    int min_time, num, max_waittime(0), maxtime(0);    //最快可办理窗口时间、最快可办理窗口编号、最大等待时间、最后办理结束时间
    double avg(0);
    window a_window;    //用于制造单个窗口
    customer people;    //存储单个客户信息
    queue<customer> wait;    //客户等待队列
    vector<window> windows;    //模拟 n 个窗口

    cin >> people_num;
    for (i = 0; i < people_num; i++)
    {
        cin >> people.come >> people.use;
        if (people.use > 60)
        {
            people.use = 60;
        }
        wait.push(people);
    }
    cin >> windows_num;
    a_window.amount = 0;
    a_window.time = 0;
    a_window.wait_time = 0;
    for ( i = 0; i < windows_num; i++)    //制造 n 个窗口
    {
        windows.push_back(a_window);
    }

    while (!wait.empty())    //等待队列不为空
    {
        flag = 0;
        min_time = 9999;
        people = wait.front();
        wait.pop();
        for ( i = 0; i < windows_num; i++)
        {
            if (windows[i].time <= people.come)    //有空闲窗口
            {
                windows[i].time = people.come;
                windows[i].time += people.use;
                windows[i].amount++;
                flag++;
                break;
            }
            if (windows[i].time < min_time)    //记录最先可办理窗口
            {
                num = i;
                min_time = windows[i].time;
            }
        }
        if (flag == 1)    //已经在空闲窗口办理
        {
            continue;
        }

        if (people.come > windows[num].time)    //到最先可办理窗口办理
        {
            windows[num].time = people.come;
        }
        else
        {
            windows[num].wait_time += (windows[num].time - people.come);
            if ((windows[num].time - people.come) > max_waittime)   //更新最大等待时间
            {
                max_waittime = windows[num].time - people.come;
            }
        }
        windows[num].time += people.use;
        windows[num].amount++;
    }

    for ( i = 0; i < windows_num; i++)
    {
        avg += windows[i].wait_time;
        if (windows[i].time > maxtime)
        {
            maxtime = windows[i].time;
        }
    }
    avg = 1.0 * avg / people_num;
    printf("%.1f ", avg);
    cout << max_waittime << " " << maxtime << endl;
    cout << windows[0].amount;
    for ( i = 1; i < windows_num; i++)
    {
        cout << " " << windows[i].amount;
    }
    return 0;
}