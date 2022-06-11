import math


def max12(a):
    if len(a) == 0:
        return -math.inf, -math.inf
    if len(a) == 1:
        return a[0], -math.inf
    if len(a) == 2:
        return max(a), min(a)
    lmax1, lmax2 = max12(a[:len(a)//2])
    rmax1, rmax2 = max12(a[len(a)//2:])
    if lmax1 > rmax1:
        max1 = lmax1
        max2 = max(lmax2, rmax1)
    else:
        max1 = rmax1
        max2 = max(rmax2, lmax1)
    return max1, max2


if __name__ == '__main__':
    a = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
    print(max12(a))
