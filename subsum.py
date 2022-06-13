def subsum(w, C):
    res = []
    x = []

    def backtrack(i):
        if i >= len(w):
            res.append(x[:])
            return
        if sum(x + w[i:i+1]) <= C:
            x.append(w[i])
            backtrack(i + 1)
            x.pop()
        if sum(x + w[i+1:]) >= C:
            backtrack(i + 1)
    backtrack(0)
    return res


if __name__ == '__main__':
    print(subsum([11, 13, 24, 7], 31))
