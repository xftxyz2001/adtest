a = [1, 5, 8, 14, 28, 39, 60, 89, 134, 324, 612, 900]

b = 555

i = 0
while a[i] < b:
    i += 1

a.insert(i, b)

print(a)
