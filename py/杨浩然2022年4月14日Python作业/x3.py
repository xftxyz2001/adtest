def func(n):
    ans = 0
    if n % 2 == 0:
        for i in range(2, n+1, 2):
            ans += 1/i
    else:
        for i in range(1, n+1, 2):
            ans += 1/i
    return ans


print(func(6))
print(func(5))
