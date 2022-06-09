#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node
{                      //构建表的元素结点
    char id[18];       //身份证号数组
    int length;        //里程
    struct Node *next; //下一个结点地址
} Node;

typedef struct
{                   //构造表的结构
    int length;       //表的长度
    Node *linklist; //表的首地址
} HashTab;

int nextprime(int n)
{ //找到大于等于记录条数n的一个素数，用来表示哈希表长度，确保通过哈希计算能得到互不相同的下标
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
    return n;
}

HashTab *minit(int n)
{                                                                 //按照记录条数初始化哈希表
    HashTab *hash = (HashTab *)malloc(sizeof(HashTab));           //分配哈希表空间
    hash->length = nextprime(n);                                    //获取哈希表长度
    hash->linklist = (Node *)malloc((hash->length) * sizeof(Node)); //结点分配空间
    for (int i = 0; i < hash->length; i++)
    { //给初始状态全部赋值为空
        hash->linklist[i].next = NULL;
        hash->linklist[i].id[0] = '\0';
        hash->linklist[i].length = 0;
    }
    return hash; //返回地址
}

int hashhash(HashTab *hash, char id[])
{                  //通过身份证号求哈希值的哈希函数（无x时即最后五位原数）
    int index = 0; //该人所对应在哈希表中的数组下标
    for (int i = 13; i <= 17; i++)
        index = id[i] == 'x' ? index * 10 + 10 : index * 10 + id[i];
    // { //取身份证后五位进行求哈希值
    //     if (id[i] == 'x')
    //     { //x在身份证号中即为10，且必为最后一位
    //         index = index * 10 + 10;
    //     }
    //     else
    //         index = index * 10 + id[i]; //从第十三位，每位乘上10再加上下一位，最终得到又最后五位构成的一个哈希值
    // }
    return index;
}

Node *mget(HashTab *hash, char id[])
{                                                  //基于身份证号求是否已存在该人,若存在，返回其地址
    int index = hashhash(hash, id) % (hash->length); //先通过哈希函数求出哈希值，得到下标
    Node *ptr = hash->linklist[index].next;        //得到该哈希值对应结点的地址的下一个结点
    while (ptr && strcmp(ptr->id, id))             //下一个结点存在且下一个结点存储的id与当前不同（链接分离，解决冲突）
        ptr = ptr->next;
    return ptr; //返回该结点地址（空或地址）
}

//第一个结点不存储信息
void mput(HashTab *hash, char id[], int l)
{                             //若该人不存在，新记录插入到哈希表中，若已存在，更新长度记录
    Node *p = mget(hash, id); //基于身份证号，求出该id所在的地址
    if (!p)
    {                                                  //如果该人是第一次记录（哈希算出的下标的下一个结点的地址为空时）
        Node *newnode = (Node *)malloc(sizeof(Node));  //创造一个新的结点，存储信息
        int index = hashhash(hash, id) % (hash->length); //通过其身份证号求出相应哈希值
        newnode->next = hash->linklist[index].next;    //同步新结点的下一个结点地址与其对应哈希值表示的结点的下一个结点地址
        hash->linklist[index].next = newnode;          //同步结点，即创建新记录，存在下标的下一个结点
        strcpy(newnode->id, id);                       //字符串赋值，对其id进行记录
        newnode->length = l;                           //里程赋值
    }
    else
    {                              //如果已经存在了该人
        p->length = p->length + l; //直接累加里程
    }
}

int main(void)
{
    int n, k; //记录的条数，最少里程
    scanf("%d", &n);
    scanf("%d", &k);          //输入条数，最少里程
    HashTab *hash = minit(n); //构建哈希表
    char id[18];              //记录身份证号码
    int l;                    //记录里程
    for (int i = 0; i <= n - 1; i++)
    {
        scanf("%s", id); //输入身份证
        scanf("%d", &l); //输入里程
        if (l < k)
            l = k;           //如果小于最小里程，要更新为最小里程
        mput(hash, id, l); //该记录插入哈希表
    }

    // 输出查询结果
    scanf("%d", &n);
    int print[100000];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", id);
        Node *p = mget(hash, id);
        // p ? printf("%d\n", p->length) : printf("No Info\n");
        print[i] = p ? p->length : 0;
        // if (!p)
        //     print[i] = 0;
        // else
        //     print[i] = p->length;
    }
    for (int i = 0; i < n; i++)
        print[i] ? printf("%d\n", print[i]) : printf("No Info\n");
    // {
    //     if (print[i] == 0)
    //         printf("No Info\n");
    //     else
    //         printf("%d\n", print[i]);
    // }
}
