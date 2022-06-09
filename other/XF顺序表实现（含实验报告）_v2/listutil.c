#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 顺序表最大存储元素数目
#define MAX_SIZE 100
// 状态码
#define ERROR -1
#define OK 1

// 存储的元素类型
typedef int ElemType;

// 顺序表定义
typedef struct list
{
    ElemType data[MAX_SIZE]; //数据域
    size_t size;             //当前顺序表实际存储的元素个数
} List;

// 初始化
void init_list(List *list)
{
    // 因为空间提前申请了,所以这个地方只是设置size
    list->size = 0;
}

// 创建
List *create_list()
{
    // 创建顺序表并分配空间
    return (List *)malloc(sizeof(List));
}

// 获取指定位置的元素
ElemType get_list(List *list, size_t index)
{
    // 越界处理
    if (index < 0 || index >= list->size)
    {
        return ERROR;
    }
    // 获取数据并返回
    return list->data[index];
}

// 修改指定位置的元素
int set_list(List *list, size_t index, ElemType e)
{
    // 越界处理
    if (index < 0 || index >= list->size)
    {
        return ERROR;
    }
    list->data[index] = e;
    return OK;
}

// 在指定位置插入元素
int insert_list(List *list, size_t index, ElemType e)
{
    // 越界处理
    if (index < 0 || index > list->size || list->size >= MAX_SIZE)
    {
        return ERROR;
    }
    // 给待插入元素腾出位置
    for (size_t i = list->size; i > index; i--)
    {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = e;
    list->size++;
    return OK;
}

// 在末尾追加元素
int append_list(List *list, ElemType e)
{
    // 越界处理
    if (list->size >= MAX_SIZE)
    {
        return ERROR;
    }
    list->data[list->size] = e;
    list->size++;
    return OK;
}

// 本题目要求的测试数据生成函数
void random_test_list(List *list)
{
    srand((unsigned int)time(NULL));
    size_t n;
    n = rand() % (MAX_SIZE / 2) + 2;
    for (size_t i = 0; i < n; i++)
    {
        append_list(list, rand() % 1000);
    }
}

// 显示
void show_list(List *list)
{
    for (size_t i = 0; i < list->size; i++)
    {
        //%d 输出的是整数，应该按照elemtype定义的类型进行实现
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

// 删除指定位置元素并返回删除的元素
ElemType remove_list(List *list, size_t index)
{
    // 越界处理
    if (index < 0 || index >= list->size)
    {
        return ERROR;
    }
    ElemType e = list->data[index];
    for (size_t i = index; i < list->size; i++)
    {
        list->data[i] = list->data[i + 1];
    }
    list->size--;
    return e;
}

// 删除整个链表,并释放存储空间
void del_list(List *list)
{
    free(list);
}