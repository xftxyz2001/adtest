def ChorusRank(a):
    f1 = [1 for _ in range(len(a))]
    f2 = [1 for _ in range(len(a))]
    for i in range(len(a)):
        for j in range(i):
            if a[i] > a[j]:
                f1[i] = max(f1[i], f1[j] + 1)
            elif a[i] < a[j]:
                f2[i] = max(f2[i], f2[j] + 1)
    return max([g1+g2-1 for g1, g2 in zip(f1, f2)])


if __name__ == '__main__':
    # 176 163 150 180 170 130 167 160
    a = [176, 163, 150, 180, 170, 130, 167, 160]
    print(ChorusRank(a))