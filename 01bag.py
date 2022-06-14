def bag(wv, W):
    n_maxv = [len(wv), 0]
    x = [-1]*n_maxv[0]

    def dfs(i, tw, tv, op):
        if i >= n_maxv[0]:
            if tw == W and tv > n_maxv[1]:
                n_maxv[1] = tv
                x[:] = op[:]
            return
        op[i] = 1
        dfs(i+1, tw+wv[i][0], tv+wv[i][1], op)
        op[i] = 0
        dfs(i+1, tw, tv, op)
    dfs(0, 0, 0, [-1]*n_maxv[0])
    return n_maxv[1], [_ for _ in range(n_maxv[0]) if x[_] == 1]


if __name__ == '__main__':
    wv = [[5, 4], [3, 4], [2, 3], [1, 1]]
    W = 6
    print(bag(wv, W))
