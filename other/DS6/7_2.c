#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LEN;

typedef struct node
{
    char id[19];             // 身份标识
    int cumulative_distance; // 累计距离
    struct node *next;
} Node;

typedef struct map
{
    Node **tab;
} Map;

Map *minit(int n)
{
    Map *map = (Map *)malloc(sizeof(Map));
    while (1)
    {
        int flag = 1;
        for (int i = 2; i < n; i++)
        {
            if (n % i == 0)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
            break;
        n++;
    }
    LEN = n;
    map->tab = (Node **)malloc(sizeof(Node) * LEN);
    for (int i = 0; i < LEN; i++)
    {
        map->tab[i] = NULL;
    }
    return map;
}

int mhash(char *id)
{
    int i, sum = 0;
    for (i = 14; id[i] != '\0'; i++)
        sum += id[i];
    return sum % LEN;
}

Node *mget(Map *m, char *id)
{
    int key = mhash(id);
    Node *p = m->tab[key];
    while (p != NULL)
    {
        if (strcmp(p->id, id) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

void mput(Map *m, char *id, int distance)
{
    Node *p = mget(m, id);
    if (p != NULL)
    {
        p->cumulative_distance += distance;
    }
    else
    {
        p = (Node *)malloc(sizeof(Node));
        strcpy(p->id, id);
        p->cumulative_distance = distance;
        int key = mhash(id);
        p->next = m->tab[key];
        m->tab[key] = p;
    }
}

int main(int argc, char const *argv[])
{

    int n; // 记录条数
    scanf("%d", &n);
    Map *map = minit(n);

    int k; //最小里程

    // 初始化，构建哈希表
    scanf("%d", &k);
    for (int i = 0; i < n; i++)
    {
        char id[20];
        int distance;
        scanf("%s %d", id, &distance);
        if (distance < k)
            distance = k;
        // printf("%s %d\n", id, distance);
        mput(map, id, distance);
    }

    // 打印结果
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        char id[20];
        scanf("%s", id);
        Node *p = mget(map, id);
        if (p == NULL)
            printf("No Info\n");
        else
            printf("%d\n", p->cumulative_distance);
    }
    return 0;
}
