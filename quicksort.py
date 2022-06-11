def partition(a, s, t):
    tmp = a[s]
    while s != t:
        while s < t and tmp <= a[t]:
            t -= 1
        a[s] = a[t]
        while s < t and a[s] <= tmp:
            s += 1
        a[t] = a[s]
    a[s] = tmp
    return s


def quicksort(a, s, t):
    if s < t:
        p = partition(a, s, t)
        quicksort(a, s, p - 1)
        quicksort(a, p + 1, t)


if __name__ == '__main__':
    a = [1, 3, 5, 7, 9, 2, 4, 6, 8, 0]
    quicksort(a, 0, len(a) - 1)
    print(a)
