#include "listutil.c"

int main(int argc, char const *argv[])
{
    int del_index = 0;
    //����
    List *list = create_list();
    // ��ʼ��
    init_list(list);

    /* ��������һ������������Թ����� */
    random_test_list(list);
    show_list(list);

    // �ӿ���̨�����ɾ��Ԫ�ص�λ��
    printf("������Ҫɾ����Ԫ�ص�λ������:");
    scanf("%d", &del_index);
    // ����ɾ������
    remove_list(list, del_index);
    //��ʾɾ������б�
    show_list(list);
    //��������ͷŴ洢�ռ�
    del_list(list);
    return 0;
}
