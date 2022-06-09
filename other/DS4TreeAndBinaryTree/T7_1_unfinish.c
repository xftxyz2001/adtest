#include <stdio.h>
#include <stdlib.h>

typedef struct person
{
    int number;
    struct person *next;
} person;

typedef struct club
{
    person *head;
    person *tail;
    int count;
} club;

int main(int argc, char const *argv[])
{
    int n, m;
    scanf("%d", &n); //人数
    scanf("%d", &m); //俱乐部数
    club *clubs = (club *)malloc(m * sizeof(club));
    for (size_t i = 0; i < m; i++)
    {
        int club_person_amount, person_number;
        scanf("%d", &club_person_amount);
        clubs[i].count = club_person_amount;
        clubs[i].tail = (person *)malloc(sizeof(person));
        clubs[i].tail->next = NULL;
        clubs[i].head = clubs[i].tail;
        for (size_t j = 0; j < club_person_amount; j++)
        {
            scanf("%d", &person_number);
            clubs[i].tail->next = (person *)malloc(sizeof(person));
            clubs[i].tail->next->number = person_number;
            clubs[i].tail->next->next = NULL;
            clubs[i].tail = clubs[i].tail->next;
        }
    }
    
    for (size_t i = 1; i < m; i++)
    {
        
    }
    

    // for (size_t i = 0; i < m; i++)
    // {
    //     person *head = clubs[i].head;
    //     while (head = head->next)
    //     {
    //         printf("%d ", head->number);
    //     }
    //     printf("\n");
    // }

    return 0;
}
