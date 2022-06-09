#include <stdio.h>
#include <stdlib.h>

int N, M, S_MAX;

// 轨道
typedef struct track
{
    char *obj;
    int pos;
} Track;

// 筐子
typedef struct basket
{
    char *obj;
    int length;
} Basket;

int track_isEmpty(Track *t)
{
    return t->pos >= M;
}

int track_pop(Track *t, char *obj)
{
    if (track_isEmpty(t))
    { //空的
        return 0;
    }
    *obj = t->obj[t->pos++];
    return 1;
}

Basket *basket_init(int S_MAX)
{
    Basket *b = (Basket *)malloc(sizeof(Basket));
    b->obj = (char *)malloc(S_MAX * sizeof(char));
    b->length = 0;
    return b;
}

int basket_isEmpty(Basket *b)
{
    return b->length == 0;
}

int basket_isFull(Basket *b)
{
    return b->length == S_MAX;
}

int basket_pop(Basket *b, char *obj)
{
    if (basket_isEmpty(b))
    { //空的
        return 0;
    }
    *obj = b->obj[--b->length];
    return 1;
}

int basket_push(Basket *b, char obj, char *outObj)
{
    if (basket_isFull(b))
    { //满了拿出来的放到outObj中
        basket_pop(b, outObj);
        b->obj[b->length++] = obj;
        return 0;
    }
    b->obj[b->length++] = obj;
    return 1;
}

int main(int argc, char const *argv[])
{
    /*
    N:轨道的条数（于是轨道从 1 到 N 编号）<=100
    M:每条轨道初始放置的物品数量 <=1000
    S_MAX：筐的最大容量 <=100
    */

    // 初始化参数
    int op = -1;
    scanf("%d %d %d", &N, &M, &S_MAX);
    Track *ts = (Track *)malloc(N * sizeof(Track)); //N条轨道

    // 装配轨道
    for (size_t i = 0; i < N; i++)
    {
        ts[i].obj = (char *)malloc(M * sizeof(char) + 1);
        // gets(ts[i].obj);
        scanf("%s", ts[i].obj);
        ts[i].pos = 0;
    }

    //初始化筐子
    Basket *b = basket_init(S_MAX);

    // 操作
    scanf("%d", &op);
    while (op != -1)
    {
        char obj, outObj;
        if (op) //push
        {
            if (track_pop(&(ts[op - 1]), &obj))
            {
                if (!basket_push(b, obj, &outObj))
                {
                    printf("%c", outObj);
                }
            }
        }
        else //pop
        {
            // bug:if忘记加了
            if (basket_pop(b, &outObj))
            {
                printf("%c", outObj);
            }
        }
        scanf("%d", &op);
    }

    return 0;
}
