import functools


def cow(a):
    def cmp(x, y):
        s = x[1] - y[1]
        return s if s != 0 else x[0] - y[0]
    a.sort(key=functools.cmp_to_key(cmp))
    res = []
    for b, e in a:
        for r in res:
            if r[-1][1] < b:
                r.append((b, e))
                break
        else:
            res.append([(b, e)])
    return res


if __name__ == '__main__':
    # {1,1,10},{2,2,4},{3,3,6},{4,5,8},{5,4,7}
    a = [(1, 10), (2, 4), (3, 6), (5, 8), (4, 7)]
    print(cow(a))
