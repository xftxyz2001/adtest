def Knap(w, a):  # w限重，a待放入的物品(重量, 价值)
    x = []
    a.sort(key=lambda x: x[1]/x[0], reverse=True)
    for ow, ov in a:
        x.append(1 if ow <= w else w/ow)
        w -= x[-1]*ow
        if w <= 0:
            break
    total = sum([i*j*k for i, (j, k) in zip(x, a)])
    return total, w  # 总价值，剩余重量


if __name__ == '__main__':
    t, w = Knap(5, [(1, 2), (2, 3), (3, 4), (4, 5)])
    print(t, w)
