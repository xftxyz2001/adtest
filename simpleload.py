def simpleload(w, W):
    n_maxw = [len(w), 0]
    x = [-1]*n_maxw[0]

    def dfs(i, tw, op):
        if i >= n_maxw[0]:
            if tw > n_maxw[1]:
                n_maxw[1] = tw
                x[:] = op[:]
            return
        if tw + w[i] <= W:
            op[i] = 1
            dfs(i+1, tw+w[i], op)
        if tw + sum(w[i+1:]) > n_maxw[1]:
            op[i] = 0
            dfs(i+1, tw, op)
    dfs(0, 0, [-1]*n_maxw[0])
    return [v for i, v in enumerate(w) if x[i] == 1]


if __name__ == '__main__':
    w = [5, 2, 6, 4, 3]
    W = 10
    print(simpleload(w, W))
