#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int top;
    int capacity;
} stack;

stack *init_stack(int n)
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->data = (int *)malloc(n * sizeof(int));
    s->top = -1;
    s->capacity = n;
    return s;
}

int push_stack(stack *s, int e)
{
    if (s->top >= s->capacity - 1 && e > 0)
        return 0;
    s->data[++s->top] = e;
    return 1;
}

int pop_stack(stack *s)
{
    return s->top < 0 ? 0 : s->data[s->top--];
}

int gettop_stack(stack *s)
{
    return s->top < 0 ? 0 : s->data[s->top];
}

int main(int argc, char const *argv[])
{
    int length, temp, now = 1;
    printf("请输入序列长度（1 2 3 ... n）：");
    scanf("%d", &length);
    stack *s = init_stack(length);
    printf("请输入出栈顺序（数字之间使用空格分隔）：");

    for (size_t i = 0; i < length; i++)
    {
        scanf("%d", &temp);
        //push
        while (gettop_stack(s) < temp)
        {
            printf("%d入栈\n", now);
            push_stack(s, now++);
        }
        //pop
        if (now > length + 1)
        {
            printf("NO");
            break;
        }
        else if (gettop_stack(s) >= temp)
        {
            printf("%d出栈\n", pop_stack(s));
            continue;
        }
    }

    return 0;
}
