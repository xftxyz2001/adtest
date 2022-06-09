#include <stdio.h>

int pos = -1;
int top = -1;

char topp(char *str)
{
    return str[top];
}

void pop()
{
    top--;
}

void push(char *stack, char am)
{
    stack[++top] = am;
}

int main(void)
{
    char str[250];
    char stack[250];
    char save[250];
    while (gets(str))
    {
        if (str[0] == '.' && !str[1])
            break;
        for (int i = 0; str[i]; i++)
        {
            if (str[i] == '(' || str[i] == '[' || str[i] == '{' || str[i] == ')' || str[i] == '}' || str[i] == ']')
                save[++pos] = str[i];
            else if (str[i] == '/' && str[i + 1] == '*')
            {
                save[++pos] = '<'; //  将/*替换为a
                i++;
            }
            else if (str[i] == '*' && str[i + 1] == '/')
            {
                save[++pos] = '>';
                i++;
            }
        }
    } //以上是保存括号
    int flag = 0;
    char tep;
    for (int i = 0; i <= pos; i++)
    {
        if (save[i] == '(' || save[i] == '{' || save[i] == '[')
            push(stack, save[i]);
        else if (save[i] == '<')
            push(stack, save[i]);
        else if (save[i] == ')')
        {
            if (top != -1 && topp(stack) == '(')
                pop(); //top！=-1作用，判断栈是否为空，否则数组越界
            else
            {
                tep = save[i];
                flag = 1;
                break;
            }
        }
        else if (save[i] == '}')
        {
            if (top != -1 && topp(stack) == '{')
                pop();
            else
            {
                tep = save[i];
                flag = 1;
                break;
            }
        }
        else if (save[i] == ']')
        {
            if (top != -1 && topp(stack) == '[')
                pop();
            else
            {
                tep = save[i];
                flag = 1;
                break;
            }
        }
        else if (save[i] == '>')
        {
            if (top != -1 && topp(stack) == '<')
                pop();
            else
            {
                tep = save[i];
                flag = 1;
                break;
            }
        }
    }
    if (!flag && top == -1)
        printf("YES\n");
    else
    {
        printf("NO\n");
        if (top != -1)
        {
            switch (topp(stack))
            {
            case '(':
                printf("(-?\n");
                break;
            case '[':
                printf("[-?\n");
                break;
            case '{':
                printf("{-?\n");
                break;
            case '<':
                printf("/*-?\n");
                break;
            }
        }
        else
        {
            switch (tep)
            {
            case ')':
                printf("?-)\n");
                break;
            case ']':
                printf("?-]\n");
                break;
            case '}':
                printf("?-}\n");
                break;
            case '>':
                printf("?-*/\n");
                break;
            }
        }
    }
    return 0;
}
