// 7-1 Reversing Linked List (20 分)
// Given a constant K and a singly linked list L,
// you are supposed to reverse the links of every K elements on L.
// For example, given L being 1→2→3→4→5→6, if K=3, then you must output 3→2→1→6→5→4;
// if K=4, you must output 4→3→2→1→5→6.

// Input Specification:
// Each input file contains one test case. For each case,
// the first line contains the address of the first node, a positive N (≤10^5)
// which is the total number of nodes, and a positive K (≤N)
// which is the length of the sublist to be reversed.
// The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

// Then N lines follow, each describes a node in the format:

// Address Data Next
// where Address is the position of the node, Data is an integer,
//  and Next is the position of the next node.

// Output Specification:
// For each case, output the resulting ordered linked list. Each node occupies a line,
//  and is printed in the same format as in the input.

// Sample Input:
// 00100 6 4
// 00000 4 99999
// 00100 1 12309
// 68237 6 -1
// 33218 3 00000
// 99999 5 68237
// 12309 2 33218

// Sample Output:
// 00000 4 33218
// 33218 3 12309
// 12309 2 00100
// 00100 1 99999
// 99999 5 68237
// 68237 6 -1

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100001

struct
{
    int data;
    int next;
} StaticList[MAXSIZE];

void show_list()
{
    for (int i = StaticList[MAXSIZE - 1].next; i != -1; i = StaticList[i].next)
        if (StaticList[i].next == -1)
            printf("%05d %d -1\n", i, StaticList[i]);
        else
            printf("%05d %d %05d\n", i, StaticList[i], StaticList[i].next);
}

int reversingSubLinkedList(int head, int the_length_of_the_sublist)
{
    int new_head = StaticList[head].next, i = StaticList[head].next, t;
    StaticList[head].next = -1;
    while (i != -1 && the_length_of_the_sublist--)
    {
        t = StaticList[i].next;
        StaticList[i].next = StaticList[head].next;
        StaticList[head].next = i;
        i = t;
    }
    StaticList[new_head].next = i;
    return new_head;
}

int enough_length(int head, int the_length_of_the_sublist)
{
    while ((head = StaticList[head].next) != -1 && the_length_of_the_sublist)
        the_length_of_the_sublist--;
    return the_length_of_the_sublist ? 0 : 1;
}

void reversingLinkedList(int the_length_of_the_sublist)
{
    int the_last_head = MAXSIZE - 1;
    while (enough_length(the_last_head, the_length_of_the_sublist))
        the_last_head = reversingSubLinkedList(the_last_head, the_length_of_the_sublist);
}

int main(int argc, char const *argv[])
{
    int the_total_number_of_nodes, the_length_of_the_sublist;
    scanf("%d %d %d", &StaticList[MAXSIZE - 1].next, &the_total_number_of_nodes, &the_length_of_the_sublist);
    for (size_t i = 0; i < the_total_number_of_nodes; i++)
    {
        int postion, data, next;
        scanf("%d %d %d", &postion, &data, &next);
        StaticList[postion].data = data;
        StaticList[postion].next = next;
    }
    reversingLinkedList(the_length_of_the_sublist);
    show_list();
    return 0;
}
