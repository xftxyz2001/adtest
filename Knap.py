def Knap(w, a):  # w限重，a待放入的物品(重量, 价值)
    x = []
    a.sort(key=lambda x: x[1]/x[0])
    for ow, ov in a:
        if ow <= w:
            x.append((ow, ov))
            w -= ow
        else:
            x.append((w, w*ov/ow))
            break
    total = sum(i[0]*i[1] for i in x)
    return total, w  # 总价值，剩余重量
