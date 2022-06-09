#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 128
#define SYMBOL_LENGTH 128

// 开头有多余左符号	

typedef enum
{
    empty,
    leftParentheses,
    rightParentheses,
    leftSquare,
    rightSquare,
    leftCurly,
    rightCurly,
    leftAnnotation,
    rightAnnotation
} brackets;

//链栈
typedef struct node
{
    brackets data;
    // char data;
    struct node *next;
} LinkStackNode, *LinkStack;

int pos = -1;

// 链栈初始化
LinkStack linkstack_init()
{
    LinkStack ls = (LinkStack)malloc(sizeof(LinkStackNode));
    ls->next = NULL;
    return ls;
}

int linkstack_push(LinkStack ls, brackets ch)
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

int linkstack_pop(LinkStack ls, brackets *ch)
{
    if (linkstack_isEmpty(ls))
        return 0;
    //bug4: *ch = ls->data;
    *ch = ls->next->data;

    ls->next = ls->next->next;
    return 1;
}

brackets linkstack_getTop(LinkStack ls)
{
    if (linkstack_isEmpty(ls))
        return 0;
    return ls->next->data;
}

int mismatch(brackets b1, brackets b2)
{
    return b1 + 1 != b2;
}

int isEnd(char *p)
{
    return strcmp(p, ".") == 0;
}

char *getCharacter(brackets b)
{
    switch (b)
    {
    case leftParentheses:
        return "(";
    case rightParentheses:
        return ")";
    case leftSquare:
        return "[";
    case rightSquare:
        return "]";
    case leftCurly:
        return "{";
    case rightCurly:
        return "}";
    case leftAnnotation:
        return "/*";
    case rightAnnotation:
        return "*/";
    }
    return "";
}

int main(int argc, char const *argv[])
{
    char src[MAX_LENGTH];
    brackets symbols[SYMBOL_LENGTH];
    while (gets(src))
    {
        if (isEnd(src))
            break;
        for (char *chs = src; *chs; chs++)
        {
            switch (*chs)
            {
            case '(':
                symbols[++pos] = leftParentheses;
                break;
            case '[':
                symbols[++pos] = leftSquare;
                break;
            case '{':
                symbols[++pos] = leftCurly;
                break;
            case ')':
                symbols[++pos] = rightParentheses;
                break;
            case ']':
                symbols[++pos] = rightSquare;
                break;
            case '}':
                symbols[++pos] = rightCurly;
                break;
            case '/':
                chs++;
                if (*chs == '*')
                    symbols[++pos] = leftAnnotation;
                break;
            case '*':
                chs++;
                if (*chs == '/')
                    symbols[++pos] = rightAnnotation;
                break;
            } //end switch
        }
    } //以上是符号化所有数据
    int flag = 0;
    LinkStack ls = linkstack_init();
    brackets temp;
    for (int i = 0; i <= pos; i++)
    {
        switch (symbols[i])
        {
        case leftParentheses:
        case leftSquare:
        case leftCurly:
        case leftAnnotation:
            linkstack_push(ls, symbols[i]);
            break;
        case rightParentheses:
        case rightSquare:
        case rightCurly:
        case rightAnnotation:
            if (!linkstack_isEmpty(ls) && !mismatch(linkstack_getTop(ls), symbols[i]))
            {
                linkstack_pop(ls, &temp);
            }
            else
            {
                temp = symbols[i];
                flag = 1;
            }
            break;
        }
        if (flag == 1)
        {
            break;
        }
    }
    if (!flag && linkstack_isEmpty(ls))
        printf("YES\n");
    else
    {
        printf("NO\n");
        if (linkstack_isEmpty(ls))
        {
            if (temp == rightSquare)
                printf("?-]");
            else if (temp == rightParentheses)
                printf("?-)");
            else if (temp == rightAnnotation)
                printf("?-*/");
            else if (temp == rightCurly)
                printf("?-}");
            putchar('\n');
        }
        else
        {
            if (linkstack_getTop(ls) == leftSquare)
                printf("[-?\n");
            else if (linkstack_getTop(ls) == leftParentheses)
                printf("(-?\n");
            else if (linkstack_getTop(ls) == leftCurly)
                printf("{-?\n");
            else if (linkstack_getTop(ls) == leftAnnotation)
                printf("/*-?\n");
        }
    }
    return 0;
}
