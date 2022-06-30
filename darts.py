import random


def darts(f, n):  # 计算f的定积分，投掷n次
    s = 0
    for i in range(n):
        s += 1 if random.random() <= f(random.random()) else 0
    return s/n
