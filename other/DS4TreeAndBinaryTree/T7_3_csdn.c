#include <stdio.h>
#include <malloc.h>

int N = 0;
int PreOrder[33] = {'\0'};	//中序
int PostOrder[33] = {'\0'}; //后序
typedef struct node
{ //二叉树结点
	int num;
	struct node *left;
	struct node *right;
} node;
struct node *create(int *pos, int *pre, int n);
void sequence(node *T); //层序排序输出

int main(void)
{
	node *T = NULL; //构建二叉树
	scanf("%d", &N);
	int i = 0;
	for (i = 0; i < N; i++)
		scanf("%d", &PostOrder[i]);
	for (i = 0; i < N; i++)
		scanf("%d", &PreOrder[i]);
	T = create(PostOrder, PreOrder, N);
	sequence(T);

	return 0;
}
void sequence(node *T) //层序遍历二叉树
{
	struct node *p[33], *q;
	int f = 0, r = 0;
	int num = 0;
	if (T)
	{				//树不为空
		p[r++] = T; //根节点入队列
		while (f != r)
		{				//队头不等于队尾时
			q = p[f++]; //出队
			printf("%d", q->num);
			num++; //计数输出空格
			if (num < N)
				printf(" ");
			if (q->left) //左树不为空，入队
				p[r++] = q->left;
			if (q->right) //右树不为空，入队
				p[r++] = q->right;
		}
	}
}
struct node *create(int *pos, int *pre, int n)
{
	int i = 0, k = 0, root = 0;
	if (n == 0) //空树
		return NULL;
	struct node *T;
	T = (struct node *)malloc(sizeof(struct node));
	if (T == NULL) //分配结点内存及判断是否成功
		return -1;
	root = pos[n - 1]; //根节点就是后序遍历的最后一位
	T->num = root;
	for (i = 0; i < n; i++)
	{
		if (pre[i] == root) //通过中序遍历，确定左右子树的长度
		{
			k = i;
			break;
		}
	}
	T->left = create(pos, pre, k); //递归左右子树
	T->right = create(pos + k, pre + k + 1, n - k - 1);

	return T;
}