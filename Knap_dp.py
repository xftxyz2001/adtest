def Knap(wv, W):
    wv = [[0, 0]] + wv
    dp = [[0 for i in range(W+1)] for j in range(len(wv))]
    for i in range(0, len(wv)):
        for r in range(1, W+1):
            if r < wv[i][0]:
                dp[i][r] = dp[i-1][r]
            else:
                dp[i][r] = max(dp[i-1][r], dp[i-1][r-wv[i][0]] + wv[i][1])
    x = []
    i = len(wv)-1
    while i >= 0:
        if dp[i][W] != dp[i-1][W]:
            x.append(i)
            W -= wv[i][0]
        i -= 1
    return x[::-1], sum(wv[i][1] for i in x)


if __name__ == '__main__':
    wv = [[5, 5], [2, 3], [3, 4]]
    W = 5
    print(Knap(wv, W))
