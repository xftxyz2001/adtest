def binsearch(a, l, h, k):
    if l > h:
        return -1
    mid = (l + h) // 2
    if a[mid] == k:
        return mid
    elif a[mid] > k:
        return binsearch(a, l, mid - 1, k)
    else:
        return binsearch(a, mid + 1, h, k)


if __name__ == '__main__':
    a = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    print(binsearch(a, 0, len(a) - 1, 5))