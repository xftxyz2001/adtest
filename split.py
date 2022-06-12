def split(n, k):
    dp = [[0 for i in range(k + 1)] for j in range(n + 1)]
    for i in range(1, n + 1):
        for j in range(1, k + 1):
            if i == 1 or j == 1:
                dp[i][j] = 1
            elif i < j:
                dp[i][j] = dp[i][i]
            elif i == j:
                dp[i][j] = dp[i][j - 1] + 1
            else:
                dp[i][j] = dp[i][j - 1] + dp[i - j][j]
    return dp[n][k]


# 递归
def fun(n, k):
    if n == 1 or k == 1:
        return 1
    elif n < k:
        return fun(n, n)
    elif n == k:
        return fun(n, n - 1) + 1
    else:
        return fun(n - k, k) + fun(n, k - 1)


# 备忘录法
dp = [[0 for i in range(10)] for j in range(10)]


def dpf(n, k):
    if dp[n][k] != 0:
        return dp[n][k]
    if n == 1 or k == 1:
        dp[n][k] = 1
    elif n < k:
        dp[n][k] = dpf(n, n)
    elif n == k:
        dp[n][k] = dpf(n, n - 1) + 1
    else:
        dp[n][k] = dpf(n - k, k) + dpf(n, k - 1)
    return dp[n][k]
