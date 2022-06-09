#include <stdio.h>
#include <stdlib.h>

//链栈
typedef struct node
{
    char data;
    struct node *next;
} LinkStackNode, *LinkStack;

// 链栈初始化
LinkStack linkstack_init()
{
    LinkStack ls = (LinkStack)malloc(sizeof(LinkStackNode));
    ls->next = NULL;
    return ls;
}

int linkstack_push(LinkStack ls, char ch)
{
    LinkStackNode *lsn;
    if (!(lsn = (LinkStackNode *)malloc(sizeof(LinkStackNode))))
        return 0;
    lsn->data = ch;
    lsn->next = ls->next;
    ls->next = lsn;
    return 1;
}

int linkstack_isEmpty(LinkStack ls)
{
    return ls->next == NULL;
}

int linkstack_pop(LinkStack ls, char *ch)
{
    if (linkstack_isEmpty(ls))
        return 0;
    *ch = ls->next->data;
    ls->next = ls->next->next;
    return 1;
}

int linkstack_getTop(LinkStack ls, char *ch)
{
    if (linkstack_isEmpty(ls))
        return 0;
    *ch = ls->data;
    return 1;
}

// 1
int isPalindrome(char *s)
{
    LinkStack ls = linkstack_init();
    while (*s != '&')
        linkstack_push(ls, *s++);
    *s++; //移动到&的下一位
    while (*s != '@')
    {
        char temp;
        if (!linkstack_pop(ls, &temp))
            return 0;
        if (temp != *s)
            return 0;
    }
    return linkstack_isEmpty(ls);
}

int main(int argc, char const *argv[])
{

    return 0;
}
