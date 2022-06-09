# 1
while True:
    n = int(input("请输入一个大于5的奇数"))
    s = 0
    if n <= 5:
        print("输入的数字小于等于5，请重新输入")
    elif n % 2 == 0:  # 1
        print("输入的数字是偶数，请重新输入")
    else:
        for i in range(1, n + 1, 2):
            k = 1
            for j in range(1, i + 1):  # 2
                k *= j
            s += k  # 3
        print("阶乘之和为：", s)
        break  # 4

# 3
scores = {'语文': 90, '数学': 95, '英语': 88}
total = 0  # 1
for i in scores:
    score = scores[i]  # 2
    total += score  # 3
print('平均成绩为：', total / len(scores))

# 5
n = int(input("请输入整数个数："))
k = []
i = 0
while i != n:
    x = input("请输入第" + str(i + 1) + "个整数：")
    s = 0
    for j in range(len(x)):
        s += int(x[j])
    if s % 2 == 0:  # 1
        k.append(x)
    i += 1  # 2
for y in k:
    print(y)
