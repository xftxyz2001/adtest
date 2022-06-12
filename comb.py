def comb(n, m):
    c = [[0 for i in range(m + 1)] for j in range(n + 1)]
    for i in range(n + 1):
        for j in range(min(i + 1, m + 1)):
            if j == 0 or j == i:
                c[i][j] = 1
            else:
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j]
    return c[n][m]


# 递归实现
def comb2(n, m):
    if m == 0 or m == n:
        return 1
    return comb2(n - 1, m - 1) + comb2(n - 1, m)


if __name__ == '__main__':
    n = 25
    m = 10
    print(comb(n, m))
    print(comb2(n, m))
