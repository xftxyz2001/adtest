#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ˳������洢Ԫ����Ŀ
#define MAX_SIZE 100
// ״̬��
#define ERROR -1
#define OK 1

// �洢��Ԫ������
typedef int ElemType;

// ˳�����
typedef struct list
{
    ElemType data[MAX_SIZE]; //������
    size_t size;             //��ǰ˳���ʵ�ʴ洢��Ԫ�ظ���
} List;

// ��ʼ��
void init_list(List *list)
{
    // ��Ϊ�ռ���ǰ������,��������ط�ֻ������size
    list->size = 0;
}

// ����
List *create_list()
{
    // ����˳�������ռ�
    return (List *)malloc(sizeof(List));
}

// ��ȡָ��λ�õ�Ԫ��
ElemType get_list(List *list, size_t index)
{
    // Խ�紦��
    if (index < 0 || index >= list->size)
    {
        return ERROR;
    }
    // ��ȡ���ݲ�����
    return list->data[index];
}

// �޸�ָ��λ�õ�Ԫ��
int set_list(List *list, size_t index, ElemType e)
{
    // Խ�紦��
    if (index < 0 || index >= list->size)
    {
        return ERROR;
    }
    list->data[index] = e;
    return OK;
}

// ��ָ��λ�ò���Ԫ��
int insert_list(List *list, size_t index, ElemType e)
{
    // Խ�紦��
    if (index < 0 || index > list->size || list->size >= MAX_SIZE)
    {
        return ERROR;
    }
    // ��������Ԫ���ڳ�λ��
    for (size_t i = list->size; i > index; i--)
    {
        list->data[i] = list->data[i - 1];
    }
    list->data[index] = e;
    list->size++;
    return OK;
}

// ��ĩβ׷��Ԫ��
int append_list(List *list, ElemType e)
{
    // Խ�紦��
    if (list->size >= MAX_SIZE)
    {
        return ERROR;
    }
    list->data[list->size] = e;
    list->size++;
    return OK;
}

// ����ĿҪ��Ĳ����������ɺ���
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

// ��ʾ
void show_list(List *list)
{
    for (size_t i = 0; i < list->size; i++)
    {
        //%d �������������Ӧ�ð���elemtype��������ͽ���ʵ��
        printf("%d ", list->data[i]);
    }
    printf("\n");
}

// ɾ��ָ��λ��Ԫ�ز�����ɾ����Ԫ��
ElemType remove_list(List *list, size_t index)
{
    // Խ�紦��
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

// ɾ����������,���ͷŴ洢�ռ�
void del_list(List *list)
{
    free(list);
}