# 这个程序还不能模拟pv操作

x = 0
y = 0
z = 0
s1 = 0
s2 = 0
p1run = True
p2run = True

ops_list = []


def P(s):
    s -= 1
    return s >= 0


def V(s):
    s += 1
    return s >= 0


def p1_1():
    global y
    y = 1


def p1_2():
    global y
    y += 3


def p1_3():
    global p1run
    p1run = V(s1)


def p1_4():
    global y
    global z
    z = y+1


def p1_5():
    global p2run
    p2run = P(s2)


def p1_6():
    global y
    global z
    y += z


def p2_1():
    global x
    x = 1


def p2_2():
    global x
    x += 5


def p2_3():
    global p1run
    p1run = P(s1)


def p2_4():
    global x
    global y
    x += y


def p2_5():
    global p2run
    p2run = V(s2)


def p2_6():
    global x
    global z
    z += x


def init():
    global x
    global y
    global z
    global s1
    global s2
    x = 0
    y = 0
    z = 0
    s1 = 0
    s2 = 0


p1 = [p1_1, p1_2, p1_3, p1_4, p1_5, p1_6]
p2 = [p2_1, p2_2, p2_3, p2_4, p2_5, p2_6]


def fun(res, left, right):
    if len(left) == 0 and len(right) == 0:
        ops_list.append(res)
        return
    if len(left) != 0:
        rl = res[::]
        rl.append(left[0])
        fun(rl, left[1:], right)
    if len(right) != 0:
        rr = res[::]
        rr.append(right[0])
        fun(rr, left, right[1:])


if __name__ == '__main__':
    res = set()
    fun([], p1, p2)
    # 去重
    # ops_list = list(set(ops_list))
    # 遍历ops_list
    for ops in ops_list:
        init()
        for op in ops:
            op()
        res.add((x, y, z))
    for r in res:
        print(r)
