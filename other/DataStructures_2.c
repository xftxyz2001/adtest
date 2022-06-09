#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Copyright (c)
 * 数据结构与算法用C语言描述 第三版 第二章实习题(3/4/6/7/8/10)
 */

#define MAX_SEZE 100

// 元素类型
typedef int ElemType;

// 顺序表
typedef struct
{
    ElemType elem[MAX_SEZE];
    int size;
} SeqList;

// 单链表
typedef struct Node
{
    ElemType elem;
    struct Node *next;
} Node, *LinkList;

// 3.有序顺序表插入元素
int insert_seqlist(SeqList *list, ElemType x)
{
    if (list->size >= MAX_SEZE)
        return 0; // 表满
    int i;
    for (i = list->size; i > 0 && list->elem[i - 1] > x; i--)
        list->elem[i] = list->elem[i - 1];
    list->elem[i] = x;
    list->size++;
    return 1;
}

// 4.从顺序表中删除第i个元素开始的k个元素
int delete_seqlist(SeqList *list, int i, int k)
{
    if (i < 0 || i >= list->size)
        return 0;              //删除位置不合法或无意义
    if ((k += i) < list->size) //k的位置是第一个要保留的元素下标
        for (; k < list->size; i++, k++)
            list->elem[i] = list->elem[k];
    list->size = i;
    return 1;
}

// 6.奇数在前偶数在后
void odd_first_even_last_seqlist(SeqList *list)
{
    int f = 0, l = list->size - 1;
    while (f < l)
    {
        while (f < list->size && list->elem[f] % 2 != 0)
            f++;
        while (l >= 0 && list->elem[l] % 2 == 0)
            l--;
        if (f < l)
        {
            list->elem[f] ^= list->elem[l];
            list->elem[l] ^= list->elem[f];
            list->elem[f] ^= list->elem[l];
        }
    }
}

// void show_seqlist(SeqList *list)
// {
//     for (int i = 0; i < list->size; i++)
//         printf("%d,", list->elem[i]);
//     printf("\n");
// }

// 7.单链表(整数)递增有序,删除mink < elem < maxk的元素
void delete_linklist(LinkList list, ElemType mink, ElemType maxk)
{
    while (list->next && list->next->elem <= mink)
        list = list->next;
    LinkList list_end = list;
    while (list_end->next && list_end->next->elem < maxk)
        list_end = list_end->next;
    list->next = list_end->next;
}

// 8.逆序合并
LinkList merge_reverse_linklist(LinkList list1, LinkList list2)
{
    Node *p = list1->next, *q = list2->next;
    list1->next = NULL;
    while (p && q)
    {
        if (p->elem < q->elem)
        {
            Node *temp = p->next;
            p->next = list1->next;
            list1->next = p;
            p = temp;
        }
        else
        {
            Node *temp = q->next;
            q->next = list1->next;
            list1->next = q;
            q = temp;
        }
    }
    while (p)
    {
        Node *temp = p->next;
        p->next = list1->next;
        list1->next = p;
        p = temp;
    }
    while (q)
    {
        Node *temp = q->next;
        q->next = list1->next;
        list1->next = q;
        q = temp;
    }
    free(list2);
    return list1;
}

// 10.合并链表
LinkList merge_linklist(LinkList list1, LinkList list2)
{
    Node *p = list1, *q = list2;
    while (p->next && q->next)
    {
        p = p->next;
        q = q->next;
    }
    if (p->next) //如果list1还有
    {
        q->next = p->next;
        return list2;
    }
    else
    {
        p->next = q->next;
        return list1;
    }
}

LinkList create_linklist()
{
    Node *head = (Node *)malloc(sizeof(Node));
    Node *tail = head;
    ElemType latest_value = 0;
    int lll = rand() % 10 + 5;
    for (size_t i = 0; i < lll; i++)
    {
        Node *q = (Node *)malloc(sizeof(Node));
        q->elem = (latest_value += rand() % 10);
        tail->next = q;
        tail = q;
    }
    tail->next = NULL;
    return head;
}

void show_linklist(LinkList list)
{
    while (list = list->next)
        printf("%d,", list->elem);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    srand((unsigned int)time(NULL));
    LinkList list1 = create_linklist();
    show_linklist(list1);
    LinkList list2 = create_linklist();
    show_linklist(list2);
    LinkList list3 = merge_linklist(list1, list2);
    show_linklist(list3);
    return 0;
}
