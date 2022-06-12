def lcs(x, y):
    m = len(x)
    n = len(y)
    dp = [[0 for i in range(n+1)] for j in range(m+1)]
    for i in range(1, m+1):
        for j in range(1, n+1):
            if x[i-1] == y[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
    k = dp[m][n]
    i = m
    j = n
    res = ''
    while k > 0:
        if dp[i][j] == dp[i-1][j]:
            i -= 1
        elif dp[i][j] == dp[i][j-1]:
            j -= 1
        else:
            res += x[i-1]
            k -= 1
            i -= 1
            j -= 1
    return res[::-1]


if __name__ == '__main__':
    x = 'abcbdb'
    y = 'acbbabdbb'
    print(lcs(x, y))
