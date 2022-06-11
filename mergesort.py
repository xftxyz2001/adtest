def merge(a, l, m, h):
    tmp = []
    i = l
    j = m+1
    while i <= m and j <= h:
        if a[i] <= a[j]:
            tmp.append(a[i])
            i += 1
        else:
            tmp.append(a[j])
            j += 1
    tmp.extend(a[i:m+1])
    tmp.extend(a[j:h+1])
    a[l:h+1] = tmp


def mergepass(a, len_, n):
    i = 0
    while i+2*len_ < n+1:
        merge(a, i, i+len_-1, i+2*len_-1)
        i += 2*len_
    if i + len_ < n + 1:
        merge(a, i, i+len_-1, n-1)


def mergesort(a):
    len_ = 1
    while len_ < len(a):
        mergepass(a, len_, len(a))
        len_ *= 2


def mergesort2(a, l, h):
    if l < h:
        m = (l+h)//2
        mergesort2(a, l, m)
        mergesort2(a, m+1, h)
        merge(a, l, m, h)


if __name__ == '__main__':
    a = [1, 3, 5, 7, 9, 2, 4, 6, 8, 0]
    mergesort2(a, 0, len(a)-1)
    print(a)
