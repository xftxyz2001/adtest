def active(a):
    n_sum_maxsum_laste = [len(a), 0, 0, 0]
    bestx = [-1]*n_sum_maxsum_laste[0]
    x = [_ for _ in range(n_sum_maxsum_laste[0])]

    def dfs(i):
        if i >= n_sum_maxsum_laste[0]:
            if n_sum_maxsum_laste[1] > n_sum_maxsum_laste[2]:
                n_sum_maxsum_laste[2] = n_sum_maxsum_laste[1]
                bestx[:] = x[:]
            return
        for j in range(i, n_sum_maxsum_laste[0]):
            x[i], x[j] = x[j], x[i]
            sum_tmp, laste_tmp = n_sum_maxsum_laste[1], n_sum_maxsum_laste[3]
            if a[x[j]][0] >= n_sum_maxsum_laste[3]:
                n_sum_maxsum_laste[1] += 1
                n_sum_maxsum_laste[3] = a[x[j]][1]
            dfs(i+1)
            x[i], x[j] = x[j], x[i]
            n_sum_maxsum_laste[1], n_sum_maxsum_laste[3] = sum_tmp, laste_tmp
    dfs(0)
    laste = 0
    res = []
    for j in range(n_sum_maxsum_laste[0]):
        if a[bestx[j]][0] >= laste:
            res.append((bestx[j], a[bestx[j]][0], a[bestx[j]][1]))
            laste = a[bestx[j]][1]
    return res


if __name__ == '__main__':
    a = [[1, 3], [2, 5], [4, 8], [6, 10]]
    print(active(a))
