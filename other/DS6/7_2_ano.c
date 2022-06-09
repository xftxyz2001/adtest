#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct HashList *List;

struct HashList
{
    char num[19];
    int length;
    List next;
};

typedef struct table *Hashtable;

struct table
{
    int size;
    List l;
};

int mhash(char *key, int size)
{
    unsigned int H = 0;
    while (*key != '\0')
        H = (H << 5) + *key++;
    return H % size;
}

int next_prime(int n)
{
    int i;
    if (n % 2 == 0)
        n++;
    while (1)
    {
        int f = 1;
        for (i = 2; i < sqrt(n); i++)
        {
            if (n % i == 0)
            {
                f = 0;
                break;
            }
        }
        if (f)
        {
            return n;
        }
        else
        {
            n += 2;
        }
    }
}
Hashtable minit(int n)
{
    Hashtable p = (Hashtable)malloc(sizeof(struct table));
    p->size = next_prime(n);
    p->l = (List)malloc(sizeof(struct HashList) * (p->size));
    for (int i = 0; i < p->size; i++)
    {
        p->l[i].length = 0;
        p->l[i].next = NULL;
        p->l[i].num[0] = '\0';
    }
    return p;
}
void mput(Hashtable H, char *s, int len, int K)
{

    int place = mhash(s, H->size);
    List L = &(H->l[place]);
    List p = L->next;
    while (p)
    {
        if (!strcmp(p->num, s))
        {
            if (len >= K)
                p->length += len;
            else
                p->length += K;
            return;
        }
        p = p->next;
    }
    List t = (List)malloc(sizeof(struct HashList));
    t->length = len < K ? K : len;
    strcpy(t->num, s);
    t->next = L->next;
    L->next = t;
}
int ask(Hashtable H, char *s)
{
    int place = mhash(s, H->size);
    List L = &(H->l[place]);
    List p = L->next;
    while (p)
    {
        if (!strcmp(p->num, s))
        {
            return p->length;
        }
        p = p->next;
    }
    return -1;
}

int main()
{
    int N, K;
    scanf("%d%d", &N, &K);
    int i, count;
    char num[19];
    Hashtable H = minit(N);

    for (i = 0; i < N; i++)
    {
        getchar();
        scanf("%s%d", num, &count);
        mput(H, num, count, K);
    }

    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        getchar();
        scanf("%s", num);
        int t = ask(H, num);
        if (t == -1)
            printf("No Info\n");
        else
            printf("%d\n", t);
    }
    return 0;
}
