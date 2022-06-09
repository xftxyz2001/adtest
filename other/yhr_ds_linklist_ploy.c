#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Polynode
{
    int coef; // coefficient
    int exp;  // exponent
    struct Polynode *next;
} Polynode, *Polylist;

// Polylist PolyCreate()
// {
//     Polynode *head, *rear, *s;
//     int c, e;
//     head = (Polynode *)malloc(sizeof(Polynode));
//     rear = head;
//     scanf("%d,%d", &c, &e);
//     while (c != 0)
//     {
//         s = (Polynode *)malloc(sizeof(Polynode));
//         s->coef = c;
//         s->exp = c;
//         rear->next = s;
//         rear = s;
//         scanf("%d,%d", &c, &e);
//     }
//     rear->next = NULL;
//     return head;
// }

// === 3 ===
Polylist xf_poly_random_create(int len)
{
    // printf("test");
    Polynode *head, *rear, *s;
    int c, e;
    head = (Polynode *)malloc(sizeof(Polynode));
    rear = head;
    c = rand() % 10 + 1;
    e = rand() % 10 + 1;
    while (len-- > 0)
    {
        s = (Polynode *)malloc(sizeof(Polynode));
        s->coef = c;
        s->exp = e;
        rear->next = s;
        rear = s;
        c = rand() % 10 + 1;
        e += rand() % 10 + 1;
    }
    rear->next = NULL;
    return head;
}

// === 1 ===
// Polylist PolyAdd(Polylist polya, Polylist polyb)
// {
//     Polynode *p, *q, *tail;
//     Polynode *temp;
//     int sum;
//     p = polya->next;
//     q = polyb->next;
//     tail = polya;
//     while (p != NULL && q != NULL)
//     {
//         if (p->exp < q->exp)
//         {
//             tail->next = p;
//             tail = p;
//             p = p->next;
//         }
//         else if (p->exp == q->exp)
//         {
//             sum = p->coef + q->coef;
//             if (sum != 0)
//             {
//                 p->coef = sum;
//                 tail->next = p;
//                 tail = p;
//                 p = p->next;
//                 temp = q;
//                 q = q->next;
//                 free(temp);
//             }
//             else
//             {
//                 temp = p;
//                 p = p->next;
//                 free(temp);
//                 temp = q;
//                 q = q->next;
//                 free(temp);
//             }
//         }
//         else
//         {
//             tail->next = q;
//             tail = q;
//             q = q->next;
//         }
//     }
//     if (p != NULL)
//         tail->next = p;
//     else
//         tail->next = q;
//     return polya;
// }

// === 2 ===
void PolyAdd(Polylist polya, Polylist polyb)
{
    Polynode *p, *q, *tail;
    Polynode *temp;
    int sum;
    p = polya->next;
    q = polyb->next;
    tail = polya;
    while (p != NULL && q != NULL)
    {
        if (p->exp < q->exp)
        {
            tail->next = p;
            tail = p;
            p = p->next;
        }
        else if (p->exp == q->exp)
        {
            sum = p->coef + q->coef;
            if (sum != 0)
            {
                p->coef = sum;
                tail->next = p;
                tail = p;
                p = p->next;
                temp = q;
                q = q->next;
                free(temp);
            }
            else
            {
                temp = p;
                p = p->next;
                free(temp);
                temp = q;
                q = q->next;
                free(temp);
            }
        }
        else
        {
            tail->next = q;
            tail = q;
            q = q->next;
        }
    }
    if (p != NULL)
    {

        tail->next = p;
    }
    else
    {

        tail->next = q;
    }
}

void show_poly(Polylist p)
{
    Polynode *temp;
    temp = p;
    int len = 0;
    while ((temp = temp->next) != NULL)
        len++;
    temp = p->next;
    while (len-- > 1)
    {
        printf("%dx^%d + ", temp->coef, temp->exp);
        temp = temp->next;
    }
    printf("%dx^%d", temp->coef, temp->exp);
    printf("\n");
}

void show_with_label(Polylist p, char *label)
{
    printf("%s: ", label);
    show_poly(p);
}

void exec()
{
    // printf("\n");
    Polylist pa = xf_poly_random_create(rand() % 10 + 3);
    // printf("\n");
    show_with_label(pa, "pa");
    // printf("\n");/
    // printf("\n");
    Polylist pb = xf_poly_random_create(rand() % 10 + 3);
    // printf("\n");
    // show(pb);
    show_with_label(pb, "pb");
    // printf("\n");
    // Polylist pc = PolyAdd(pa, pb);
    PolyAdd(pa, pb);
    // printf("\n");
    // show(pa);
    show_with_label(pa, "ans:");
    printf("\n");
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int n;
    if (argc == 1)
    {
        exec();
    }
    else if (n = atoi(argv[1]))
    {
        while (n-- > 0)
        {
            exec();
        }
    }
    else
    {
        while (1)
        {
            exec();
        }
    }
    return 0;
}
