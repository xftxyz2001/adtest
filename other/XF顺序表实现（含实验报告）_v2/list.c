#include "listutil.c"

int main(int argc, char const *argv[])
{
    int del_index = 0;
    //创建
    List *list = create_list();
    // 初始化
    init_list(list);

    /* 这里生成一组随机的数据以供测试 */
    random_test_list(list);
    show_list(list);

    // 从控制台输入待删除元素的位置
    printf("请输入要删除的元素的位置坐标:");
    scanf("%d", &del_index);
    // 调用删除函数
    remove_list(list, del_index);
    //显示删除后的列表
    show_list(list);
    //程序最后释放存储空间
    del_list(list);
    return 0;
}
