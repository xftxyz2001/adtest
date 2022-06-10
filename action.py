def action(a):
    a.sort(key=lambda x: x[1])
    res = []
    p = 0
    for b, e in a:
        if b > p:
            res.append((b, e))
            p = e
    return res


if __name__ == '__main__':
    # 开始时间 1 3 0 5 3 5 6 8 8 2 12
    # 结束时间 4 5 6 7 8 9 10 11 12 13 15
    a = [(1, 4), (3, 5), (0, 6), (5, 7),
         (3, 8), (5, 9), (6, 10), (8, 11),
         (8, 12), (2, 13), (12, 15)]
    print(action(a))
