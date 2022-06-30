from queue import PriorityQueue
import math


def sss(a, v):  # 图的邻接矩阵，起点
    n = len(a)
    dist = [math.inf]*n  # 源点到顶点i的最短路径长度
    prev = [v]*n  # 源点到j的最短路径中顶点j的前驱顶点
    qu = PriorityQueue()
    e = [0, v]
    qu.put(e)
    dist[v] = 0
    while not qu.empty():
        e = qu.get()
        for j in range(n):
            if a[e[1]][j] < math.inf and e[0]+a[e[1]][j] < dist[j]:
                dist[j] = e[0] + a[e[1]][j]
                prev[j] = e[1]
                print(prev)
                print(dist)
                e1 = (dist[j], j)
                qu.put(e1)
    res = {}
    for i, d in enumerate(dist):
        if d == math.inf:
            res[i] = '无法到达'
            continue
        res[i] = [i]
        while res[i][-1] != v:
            res[i].append(prev[res[i][-1]])
        res[i].reverse()
        res[i] = (d, res[i])
    return res


if __name__ == '__main__':
    # 0 ∞ ∞ ∞ ∞ ∞
    # ∞ 0 ∞ ∞ ∞ ∞
    # 10 4 0 ∞ ∞ ∞
    # ∞ ∞ 50 0 20 ∞
    # 30 ∞ ∞ ∞ 0 ∞
    # 100 ∞ ∞ 10 60 0
    a = [[0,        math.inf, 10,       math.inf, 30,       100],
         [math.inf, 0,        4,        math.inf, math.inf, math.inf],
         [math.inf, math.inf, 0,        50,       math.inf, math.inf],
         [math.inf, math.inf, math.inf, 0,        math.inf, 10],
         [math.inf, math.inf, math.inf, 20,       0,        60],
         [math.inf, math.inf, math.inf, math.inf, math.inf, 0]]
    # for b in a:
    #     print(b)
    r = sss(a, 0)
    for k, v in r.items():
        print(k, v)
