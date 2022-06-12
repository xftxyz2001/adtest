def maxLongIncreasingSubseq(a):
    dp = [1 for _ in range(len(a))]
    for i in range(len(a)):
        for j in range(i):
            if a[i] > a[j]:
                dp[i] = max(dp[i], dp[j] + 1)
    return max(dp)


# 2，1，5，3，6，4，8，9，7
if __name__ == '__main__':
    a = [2, 1, 5, 3, 6, 4, 8, 9, 7]
    print(maxLongIncreasingSubseq(a))
