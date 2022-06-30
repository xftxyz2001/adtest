# from queue import PriorityQueue
class E():
    def __init__(self, i, w, v, no, x):
        self.i = i
        self.w = w
        self.v = v
        self.no = no
        self.x = x
        self.ub = 0

    def __lt__(self, other):
        return self.ub > other.ub


def bb01bag(w, v, W):
    n = len(w)
    bestx = []
    maxv = [0]

    def bound(e):
        i = e.i+1
        sumw = e.w
        sumv = e.v
        while i < n and sumw+w[i] <= W:
            sumw += w[i]
            sumv += v[i]
            i += 1
        e.ub = sumv + (W-sumw)*v[i-1]/w[i-1] if i < n else sumv

    def enqueue(e, qu):
        if e.i == n:
            if e.v > maxv[0]:
                maxv[0] = e.v
                bestx[:] = e.x[:]
        else:
            qu.append(e)
    qu = []
    total = 1
    e = E(0, 0, 0, total, [])
    total += 1
    bound(e)
    qu.append(e)
    while qu:
        e = qu.pop(0)
        if e.w + w[e.i] <= W:
            e1 = E(e.i+1, e.w+w[e.i], e.v+v[e.i], total, e.x[:]+[1])
            total += 1
            bound(e1)
            enqueue(e1, qu)
        e2 = E(e.i+1, e.w, e.v, total, e.x[:]+[0])
        total += 1
        bound(e2)
        if e2.ub > maxv[0]:
            enqueue(e2, qu)

    return bestx


if __name__ == '__main__':
    w = [16, 15, 15]
    v = [45, 25, 25]
    W = 30
    print(bb01bag(w, v, W))
