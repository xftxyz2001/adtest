#include <stdio.h>
#include <stdlib.h>

typedef struct club
{
    int *person;
    int count;
} club;

int AinB(club *a, club *b)
{
    int i = 0, j = 0;
    while (i < a->count && j < b->count)
    {
        if (a->person[i] < b->person[j])
            i++;
        else if (a->person[i] == b->person[j])
            return 1;
        else
            j++;
    }
    return 0;
}

void AtoB(club *a, club *b)
{
    int *person_temp = (int *)malloc((a->count + b->count) * sizeof(int));
    int i = 0, j = 0, k = 0;
    while (i < a->count && j < b->count)
    {
        if (a->person[i] < b->person[j])
            person_temp[k++] = a->person[i++];
        else if (a->person[i] == b->person[j])
        {
            person_temp[k++] = a->person[i++];
            j++;
        }
        else
            person_temp[k++] = b->person[j++];
    }
    while (i < a->count)
        person_temp[k++] = a->person[i++];
    while (j < b->count)
        person_temp[k++] = b->person[j++];
    free(b->person);
    b->person = person_temp;
    b->count = k;
}

int compare(void const *a, void const *b)
{
    return *(int *)a - *(int *)b;
}

int main(int argc, char const *argv[])
{
    int n = 0, m = 0, max = 0;
    scanf("%d", &n); //人数
    scanf("%d", &m); //俱乐部数
    club *clubs = (club *)malloc(m * sizeof(club));
    for (size_t i = 0; i < m; i++)
    {
        int club_person_amount, person_number;
        scanf("%d", &club_person_amount);
        clubs[i].count = club_person_amount;
        clubs[i].person = (int *)malloc(club_person_amount * sizeof(int));
        for (size_t j = 0; j < club_person_amount; j++)
        {
            scanf("%d", &person_number);
            clubs[i].person[j] = person_number;
        }
        qsort(clubs[i].person, club_person_amount, sizeof(int), compare); //调用qsort排序，防止输入的不是按顺序的
    }

    // for (size_t i = 0; i < m; i++)
    // {
    //     for (size_t j = 0; j < clubs[i].count; j++)
    //     {
    //         printf("%d ", clubs[i].person[j]);
    //     }
    //     printf("\n");
    // }

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = i + 1; j < m; j++)
        {
            if (AinB(clubs + i, clubs + j)) // i in j
            {
                AtoB(clubs + i, clubs + j); // i to j
                break;
            }
        }
    }

    for (size_t i = 0; i < m; i++)
    {
        if (clubs[i].count > max)
            max = clubs[i].count;
    }
    printf("%d\n", max);

    return 0;
}
