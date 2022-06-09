#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct Node
{
    char id[18];
    int length;
    struct Node *next;
} Node;
typedef struct
{
    int size;
    Node *linklist;
} HashList;

int nextprime(int n)
{
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

HashList *minit(int n)
{
    HashList *hash = (HashList *)malloc(sizeof(HashList));
    hash->size = nextprime(n);
    hash->linklist = (Node *)malloc((hash->size) * sizeof(Node));
    for (int i = 0; i < hash->size; i++)
    {
        hash->linklist[i].next = NULL;
        hash->linklist[i].id[0] = '\0';
        hash->linklist[i].length = 0;
    }
    return hash;
}

int mhash(HashList *hash, char id[])
{
    int index = 0;
    for (int i = 13; i <= 17; i++)
    {
        if (id[i] == 'x')
        {
            index = index * 10 + 10;
        }
        else
            index = index * 10 + id[i];
    }
    return index;
}

Node *mget(HashList *hash, char id[])
{
    int index = mhash(hash, id) % (hash->size);
    Node *ptr = hash->linklist[index].next;
    while (ptr && strcmp(ptr->id, id))
        ptr = ptr->next;
    return ptr;
}

void mput(HashList *hash, char id[], int l)
{
    Node *p = mget(hash, id);
    if (!p)
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        int index = mhash(hash, id) % (hash->size);
        newnode->next = hash->linklist[index].next;
        hash->linklist[index].next = newnode;
        strcpy(newnode->id, id);
        newnode->length = l;
    }
    else
    {
        p->length = p->length + l;
    }
}

int main(void)
{
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);
    HashList *hash = minit(n);
    char id[18];
    int l;
    for (int i = 0; i <= n - 1; i++)
    {
        scanf("%s", id);
        scanf("%d", &l);
        if (l < k)
            l = k;
        mput(hash, id, l);
    }
    scanf("%d", &n);
    int print[100000];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", id);
        Node *p = mget(hash, id);
        if (!p)
            print[i] = 0;
        else
            print[i] = p->length;
    }
    for (int i = 0; i < n; i++)
    {
        if (print[i] == 0)
            printf("No Info\n");
        else
            printf("%d\n", print[i]);
    }
}
