def gm(g, m):
    n_cnt = [len(g), 0]
    x = [-1]*n_cnt[0]
    res = []

    def same(i):
        for j in range(len(g)):
            if g[i][j] == 1 and x[i] == x[j]:
                return False
        return True

    def dfs(i):
        if i >= n_cnt[0]:
            n_cnt[1] += 1
            res.append(x[:])
            return
        for j in range(m):
            x[i] = j
            if same(i):
                dfs(i+1)
            x[i] = -1
    dfs(0)
    return n_cnt[1], res


if __name__ == '__main__':
    # 1 2
    # 1 3
    # 1 4
    # 2 3
    # 2 4
    # 2 5
    # 3 4
    # 4 5
    #     1  2  3  4  5
    g = [
        [0, 1, 1, 1],
        [1, 0, 0, 1],
        [1, 0, 0, 0],
        [1, 1, 0, 0]
    ]
    n, r = gm(g, 3)
    print(n)
    for i in r:
        print(i)
