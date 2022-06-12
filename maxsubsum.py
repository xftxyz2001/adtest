def maxsubsum(a, l, r):
    if l == r:
        return a[l] if a[l] > 0 else 0
    m = (l + r) // 2
    maxLeftSum = maxsubsum(a, l, m)
    maxRightSum = maxsubsum(a, m + 1, r)
    maxLeftBorderSum = leftBorderSum = 0
    for i in range(m, l - 1, -1):
        leftBorderSum += a[i]
        if leftBorderSum > maxLeftBorderSum:
            maxLeftBorderSum = leftBorderSum
    maxRightBorderSum = rightBorderSum = 0
    for i in range(m + 1, r + 1):
        rightBorderSum += a[i]
        if rightBorderSum > maxRightBorderSum:
            maxRightBorderSum = rightBorderSum
    return max(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum)


# 1 -2 3 5 2 -1 5 -3
print(maxsubsum([1, -2, 3, 5, 2, -1, 5, -3], 0, 7))
