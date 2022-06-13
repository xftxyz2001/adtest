def match4athlete(P, Q):
    n = min(len(P), len(Q))
    F = [[P[i][j]*Q[j][i] for j in range(n)] for i in range(n)]
    cc_bestc = [0, 0]
    x = [_ for _ in range(n)]
    bestx = [-1] * n

    def slove(i):
        if i >= n:
            if cc_bestc[0] > cc_bestc[1]:
                bestx[:] = x[:]
                cc_bestc[1] = cc_bestc[0]
            return
        for j in range(i, n):
            x[i], x[j] = x[j], x[i]
            cc_bestc[0] += F[i][x[i]]
            slove(i + 1)
            cc_bestc[0] -= F[i][x[i]]
            x[i], x[j] = x[j], x[i]
    slove(0)
    return cc_bestc[1], bestx


P = [[2, 1, 3], [4, 5, 1], [1, 3, 6]]
Q = [[2, 3, 2], [3, 4, 7], [1, 2, 6]]
print(match4athlete(P, Q))
