def maxSubSum(a):
    dp = [0 for i in range(len(a)+1)]
    for i, v in enumerate(a):
        dp[i+1] = max(dp[i]+v, v)
    max_i = dp.index(max(dp))
    for k in range(max_i, -1, -1):
        if dp[k] <= 0:
            break
    return a[k:max_i]


if __name__ == '__main__':
    a = [-2, 11, -4, 13, -5, -2]
    print(maxSubSum(a))
