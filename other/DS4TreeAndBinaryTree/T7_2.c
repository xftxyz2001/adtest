#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int n, t, i, j;
    scanf("%d", &n);
    int *binaryTree = (int *)malloc((n + 1) * sizeof(int));
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &t);
        binaryTree[i] = t;
    }
    scanf("%d", &i);
    scanf("%d", &j);
    if (binaryTree[i] && binaryTree[j])
    {
        while (i != j)
            i > j ? (i /= 2) : (j /= 2);
        printf("%d %d", i, binaryTree[i]);
    }
    else
    {
        printf("ERROR: T[%d] is NULL", binaryTree[i] ? j : i);
        return 0;
    }
    return 0;
}
