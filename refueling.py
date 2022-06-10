def refueling(ss, n):  # ss到下个站的距离集，n为汽油箱的容量（距离计）
    if max(ss) > n:
        return -1
    cs = 0  # 当前行驶距离
    cnt = 0  # 加油次数
    for s in ss:
        cs += s
        if cs > n:
            cs = s
            cnt += 1
    return cnt


if __name__ == '__main__':
    ss = [1, 2, 3, 4, 5, 1, 6, 6]
    n = 7
    print(refueling(ss, n))
