def partition(a, s, t):  # 一次划分算法
    tmp = a[s]  # 用序列的第1个记录作为基准
    while s != t:  # 从序列两端交替向中间扫描，直至s=t为止
        while s < t and tmp <= a[t]:
            t -= 1
        a[s] = a[t]
        while s < t and a[s] <= tmp:
            s += 1
        a[t] = a[s]
    a[s] = tmp
    return s


def quicksort(a, s, t):  # 对a[s..t]元素序列进行递增排序
    if s < t:  # 序列内至少存在2个元素的情况
        p = partition(a, s, t)
        quicksort(a, s, p - 1)  # 对左子序列递归排序
        quicksort(a, p + 1, t)  # 对右子序列递归排序


if __name__ == '__main__':
    a = [1, 3, 5, 7, 9, 2, 4, 6, 8, 0]
    quicksort(a, 0, len(a) - 1)
    print(a)
