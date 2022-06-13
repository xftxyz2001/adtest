def queen_b(n):
    x = [-1]*n
    sum_ = [0]

    def backtrack(t):
        if t >= n and n > 0:
            sum_[0] += 1
        else:
            for i in range(n):
                x[t] = i
                flag = True
                for j in range(t):
                    if x[j] == x[t] or abs(x[j] - x[t]) == abs(t - j):
                        flag = False
                        break
                if flag:
                    backtrack(t + 1)
    backtrack(0)
    return sum_[0]


def queen(n):
    x = [-1]*n
    sum_ = 0
    t = 0

    def place(k):
        for j in range(k):
            if x[j] == x[k] or abs(x[j] - x[k]) == abs(k - j):
                return False
        return True
    while t >= 0:
        x[t] += 1
        while x[t] < n and not place(t):
            x[t] += 1
        if x[t] < n:
            if t == n - 1:
                sum_ += 1
            else:
                t += 1
                x[t] = -1
        else:
            t -= 1
    return sum_


for i in range(1, 11):
    print(i, queen_b(i) == queen(i))
