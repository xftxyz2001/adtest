def minimumPath(t):
    dp = [[0]*_ for _ in range(1, len(t)+1)]
    pre = [[0]*_ for _ in range(1, len(t)+1)]
    dp[0][0] = t[0][0]
    for i in range(1, len(t)):  # 第1列的边界
        dp[i][0] = dp[i-1][0] + t[i][0]
    for i in range(1, len(t)):  # 对角线的边界
        dp[i][i] = t[i][i] + dp[i-1][i-1]
    for i in range(2, len(t)):  # 有两条达到路径的结点
        for j in range(1, i):
            if dp[i-1][j-1] < dp[i-1][j]:
                pre[i][j] = j-1
                dp[i][j] = t[i][j] + dp[i-1][j-1]
            else:
                pre[i][j] = j
                dp[i][j] = t[i][j] + dp[i-1][j]
    min_len = min(dp[len(t)-1])
    min_index = dp[len(t)-1].index(min_len)
    path = []
    for row in pre[::-1]:
        path.append(min_index)
        min_index = row[min_index]
    path.reverse()
    return min_len, path


if __name__ == '__main__':
    t = [[1],
        [4, 1],
        [3, 2, 4],
        [6, 10, 8, 7]]
    print(minimumPath(t))
