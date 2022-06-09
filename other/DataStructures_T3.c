#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType int
#define MAX_ELEMENT_SIZE 50

// 4
// typedef struct snode
// {
//     char c;
//     struct snode *next;
// } snode;

// typedef struct linkedStack
// {
//     snode *first;
// } linkedStack;

// 5
typedef struct qnode
{
    ElementType e;
    struct qnode *next;
} qnode;

typedef struct linkedQueue
{
    qnode *rear;
} linkedQueue;

// 6
typedef struct queue
{
    ElementType Data[MAX_ELEMENT_SIZE];
    int tag; //0空1满
    int front;
    int rear;
} queue;

// linkedStack *createStack()
// {
//     linkedStack *stack = (linkedStack *)malloc(sizeof(linkedStack));
//     snode *first = (snode *)malloc(sizeof(snode));
//     first->next = NULL;
//     stack->first = first;
//     return stack;
// }

// int pushStack(linkedStack *stack, char c)
// {
//     snode *node = (snode *)malloc(sizeof(snode));
//     if (!node)
//         return 0;
//     node->c = c;
//     node->next = stack->first->next;
//     stack->first->next = node;
//     return 1;
// }

// int isEmptyStack(linkedStack *stack)
// {
//     return stack->first->next == NULL;
// }

// int popStack(linkedStack *stack, char *c)
// {
//     if (isEmptyStack(stack))
//         return 0;
//     snode *temp = stack->first->next;
//     stack->first->next = temp->next;
//     *c = temp->c;
//     free(temp);
//     return 1;
// }

// int getTopStack(linkedStack *stack, char *c)
// {
//     if (isEmptyStack(stack))
//         return 0;
//     *c = stack->first->next->c;
//     return 1;
// }

// int isOperator(char c)
// {
//     switch (c)
//     {
//     case '+':
//     case '-':
//     case '*':
//     case '/':
//     case '(':
//     case ')':
//         return 1;
//     default:
//         return 0;
//     }
// }

// int opcmp(char c1, char c2)
// {
//     int[]
// }

// char *toPostfixExpression(char *exp)
// {
//     int len = strlen(exp);
//     char *result = (char *)malloc((len << 1) * sizeof(char));
//     int index = 0;
//     linkedStack *op = createStack();
//     char opch;
//     while (*exp)
//     {
//         do
//         {
//             result[index++] = *exp++;
//         } while (isOperator(*exp) && *exp);
//         if (*exp == '\0')
//             break;
//         result[index++] = ' ';
//         if (getTopStack(op, &opch) && opcmp(opch, *exp) < 0)
//         {
//             do
//             {
//                 popStack(op, &opch);
//                 result[index++] = opch;
//                 result[index++] = ' ';
//             } while (getTopStack(op, &opch) && opcmp(opch, *exp) < 0);
//         }
//         pushStack(op, *exp++);
//     }
//     while (popStack(op, &opch))
//     {
//         result[index++] = opch;
//         result[index++] = ' ';
//     }
//     result[index] = '\0';
//     return result;
// }

//5
linkedQueue *initLinkedQueue()
{
    linkedQueue *queue = (linkedQueue *)malloc(sizeof(linkedQueue));
    qnode *node = (qnode *)malloc(sizeof(qnode));
    node->next = node;
    queue->rear = node;
    return queue;
}

int enterLinkedQueue(linkedQueue *q, ElementType e)
{

    qnode *newNode = (qnode *)malloc(sizeof(qnode));
    if (!newNode)
    {
        return 0;
    }
    newNode->e = e;
    newNode->next = q->rear->next;
    q->rear->next = newNode;
    return 1;
}

int deleteLinkedQueue(linkedQueue *q, ElementType *e)
{
    if (q->rear == q->rear->next)
    {
        return 0;
    }
    qnode *head = q->rear->next;
    qnode *temp = head->next;
    *e = temp->e;
    head->next = head->next->next;
    free(temp);
    return 1;
}

// 6
int enterQueue(queue *q, ElementType e)
{
    if (q->front == q->rear && q->tag == 1)
    {
        return 0;
    }
    q->Data[q->rear] = e;
    q->rear = (q->rear + 1) % MAX_ELEMENT_SIZE;
    return 1;
}

int deleteQueue(queue *q, ElementType *e)
{
    if (q->front == q->rear && q->tag == 0)
    {
        return 0;
    }
    *e = q->Data[q->front];
    q->front = (q->front + 1) % MAX_ELEMENT_SIZE;
    return 1;
}

// 9
void bin(int b[], int n)
{
    if (n == 1)
    {
        b[1] = 2;
        b[2] = 2;
    }
    else
    {
        bin(b, n - 1);
        b[n + 1] = 2;
        for (int i = n; i >= 2; i--)
            b[i] += b[i - 1];
    }
}

char *to_Reverse_Polish_notation(char *Expression)
{
    //int debug = 0;
    char *res, *res_p;
    char yunsuanfu;
    StackArrayChar *sc;
    res = (char *)malloc(sizeof(char) * Length_Expression * 2);
    res_p = res;
    sc = (StackArrayChar *)malloc(sizeof(StackArrayChar));
    Init_StackArrayChar(sc);
    while (*Expression)
    {

        //printf("%c", *Expression);
        //先判断是操作数
        while (isDigit(*Expression))
        {
            *res_p++ = *Expression++;
            if (!isDigit(*Expression))
            {
                /*
				if (*Expression == '\0')
				{
					break;
					//return res;
				}
				*/
                *res_p++ = ' ';
                break;
            }
        }
        //操作符
        if (*Expression == '\0')
        {
            break;
        }
        else if (*Expression == '(')
        {
            Push_StackArrayChar(sc, *Expression++);
        }
        else if (*Expression == ')')
        {
            while (Pop_StackArrayChar(sc, &yunsuanfu))
            {
                if (yunsuanfu != '(')
                {
                    //printf(")read\n");
                    *res_p++ = yunsuanfu;
                    *res_p++ = ' ';
                }
                else
                {
                    break;
                }
            }
            Expression++;
        }
        else if (GetTop_StackArrayChar(sc, &yunsuanfu))
        {
            while (GetTop_StackArrayChar(sc, &yunsuanfu))
            {
                //优先级不可比较或表达式的运算符优先级高，压栈
                if (!getPriority(yunsuanfu) || getPriority(*Expression) < getPriority(yunsuanfu))
                {
                    Push_StackArrayChar(sc, *Expression++);
                    break;
                }
                else //表达式的运算符优先级不高于栈中的
                {
                    Pop_StackArrayChar(sc, res_p++);
                    *res_p++ = ' ';
                }
            } //end while
        }
        else
        {
            Push_StackArrayChar(sc, *Expression++);
        }
        //printf("%d:::::%s\n", ++debug, res);
    } //end while
    while (!IsEmpty_StackArrayChar(sc))
    {
        Pop_StackArrayChar(sc, res_p++);
        *res_p++ = ' ';
    }
    *res_p++ = '\0';
    return res;
}

double calculateExpression(char *Expression)
{
    double res, num = 0, a, b;
    int haveDot = 0; //小于0表示在小数点后面了
    char *e_rpn = to_Reverse_Polish_notation(Expression);
    StackArrayDouble *sd = (StackArrayDouble *)malloc(sizeof(StackArrayDouble));
    Init_StackArrayDouble(sd);
    while (*e_rpn != '\0')
    {
        while (isDigit(*e_rpn)) //两种情况，一种是数字，一种是.
        {
            if (*e_rpn == '.') //如果读到小数点，标记小数点
            {
                haveDot--; //标记小数点
                e_rpn++;
                continue;
            }
            if (haveDot < 0)
            {
                num += (*e_rpn - 48) * pow(10, haveDot--);
            }
            else
            {
                num = num * 10 + (*e_rpn - 48);
            }
            e_rpn++;
            if (!isDigit(*e_rpn))
            {
                Push_StackArrayDouble(sd, num);
                //printf("入栈%d\n", num);//
                //printf("%d\n", num);
                num = 0; //入栈操作后将num初始化
                haveDot = 0;
                e_rpn++;
                break;
            }
            //}
        }
        while (getPriority(*e_rpn)) //如果不是个运算符，get的返回值为0
        {
            //printf("%c ", *e_rpn);
            Pop_StackArrayDouble(sd, &a); //右操作数
            Pop_StackArrayDouble(sd, &b); //左操作数
            num = calculate(b, a, *e_rpn);
            //printf("运算%d%c%d=%d\n", b, *e_rpn, a, num);//
            Push_StackArrayDouble(sd, num);
            //printf("入栈%d\n", num);//
            num = 0; //入栈操作后将num初始化
            e_rpn += 2;
        }
    }
    GetTop_StackArrayDouble(sd, &res);
    return res;
}

int main(int argc, char const *argv[])
{
    // int a[10];
    // bin(a, 5);
    // for (size_t i = 0; i < 10; i++)
    // {
    //     printf("%d ", a[i]);//8 2 10 20 20 10 2 0
    // }

    return 0;
}
