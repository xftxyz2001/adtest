// 请编写程序检查C语言源程序中下列符号是否配对：
// /*与*/、(与)、[与]、{与}。

// 输入格式:
// 输入为一个C语言源程序。当读到某一行中只有一个句点.和一个回车的时候，
// 标志着输入结束。程序中需要检查配对的符号不超过100个。

// 输出格式:
// 首先，如果所有符号配对正确，则在第一行中输出YES，否则输出NO。
// 然后在第二行中指出第一个不配对的符号：
// 如果缺少左符号，则输出?-右符号；如果缺少右符号，则输出左符号-?。

// cmd: R7-1.exe < R7-1-1.txt
// 开头有多余左符号

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 128

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

brackets *symbolization(char *srcCharacters)
{
    brackets *symbols = (brackets *)malloc(MAX_LENGTH * sizeof(brackets));
    // 初始化
    size_t i = 0;
    for (; i < MAX_LENGTH; i++)
        symbols[i] = empty;

    // 处理
    for (i = 0; *srcCharacters; srcCharacters++)
    {
        switch (*srcCharacters)
        {
        case '(':
            // bug1:i忘记自增
            // symbols[i] = leftParentheses;
            symbols[i++] = leftParentheses;
            break;
        case '[':
            symbols[i++] = leftSquare;
            break;
        case '{':
            symbols[i++] = leftCurly;
            break;
        case ')':
            symbols[i++] = rightParentheses;
            break;
        case ']':
            symbols[i++] = rightSquare;
            break;
        case '}':
            symbols[i++] = rightCurly;
            break;
        case '/':
            srcCharacters++;
            if (*srcCharacters == '*')
                symbols[i++] = leftAnnotation;
            break;
        case '*':
            srcCharacters++;
            if (*srcCharacters == '/')
                symbols[i++] = rightAnnotation;
            break;
        }
    }
    return symbols;
}

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

int mismatch(brackets b1, brackets b2)
{
    return b1 + 1 != b2;
}

int main(int argc, char const *argv[])
{
    char src[MAX_LENGTH];
    // int isAnnotation = 0;
    LinkStack ls = linkstack_init();
    gets(src);
    while (!isEnd(src)) // 非空
    {
        // 去除不必要的字符
        brackets *symbols = symbolization(src);

        while (*symbols != empty)
        {
            brackets temp;
            switch (*symbols)
            {
            case leftParentheses:
            case leftSquare:
            case leftCurly:
            case leftAnnotation:
                // if (!isAnnotation)
                // {
                linkstack_push(ls, *symbols);
                // }
                // bug2:忘记break;
                break;
                // if (!isAnnotation)
                // {
                // linkstack_push(ls, *symbols);
                // }
                // isAnnotation = 1;
                // bug2:忘记break;
                // break;
            case rightParentheses:
            case rightSquare:
            case rightCurly:
            case rightAnnotation:
                if (!linkstack_pop(ls, &temp))
                {
                    printf("NO\n?-%s", getCharacter(*symbols));
                    return 0;
                }
                else if (mismatch(temp, *symbols))
                {
                    // bug5:printf("NO\n?-%s", getCharacter(temp));
                    printf("NO\n%s-?", getCharacter(temp));
                    // 找到一处问题就退出
                    // return -1;
                    return 0;
                }
                break;

                // bug3:symbols忘记自增
                symbols++;
            } // end while
            // 获取下一行数据
            gets(src);
        } // end while
        if (linkstack_isEmpty(ls))
        {
            printf("YES");
        }
        else
        {
            brackets temp;
            linkstack_pop(ls, &temp);
            printf("NO\n%s-?", getCharacter(temp));
        }

        return 0;
    }
