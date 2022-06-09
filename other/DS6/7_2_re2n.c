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
    int length;
    Node *linklist;
} HashTab;

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

HashTab *minit(int n)
{
    HashTab *hash = (HashTab *)malloc(sizeof(HashTab));
    hash->length = nextprime(n);
    hash->linklist = (Node *)malloc((hash->length) * sizeof(Node));
    for (int i = 0; i < hash->length; i++)
    {
        hash->linklist[i].next = NULL;
        hash->linklist[i].id[0] = '\0';
        hash->linklist[i].length = 0;
    }
    return hash;
}

int hashhash(HashTab *hash, char id[])
{
    int index = 0;
    for (int i = 13; i <= 17; i++)
        index = id[i] == 'x' ? index * 10 + 10 : index * 10 + id[i];

    return index;
}

Node *mget(HashTab *hash, char id[])
{
    int index = hashhash(hash, id) % (hash->length);
    Node *ptr = hash->linklist[index].next;
    while (ptr && strcmp(ptr->id, id))
        ptr = ptr->next;
    return ptr;
}

void mput(HashTab *hash, char id[], int l)
{
    Node *p = mget(hash, id);
    if (!p)
    {
        Node *newnode = (Node *)malloc(sizeof(Node));
        int index = hashhash(hash, id) % (hash->length);
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
    HashTab *hash = minit(n);
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

        print[i] = p ? p->length : 0;
    }
    for (int i = 0; i < n; i++)
        print[i] ? printf("%d\n", print[i]) : printf("No Info\n");
}
