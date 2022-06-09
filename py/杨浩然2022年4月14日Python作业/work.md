## 【第一题】一个整数，它加上100后是一个完全平方数，再加上168又是一个完全平方数，请问该数是多少？
```python
import math

i = 1
while True:
    i100 = i + 100
    i168 = i + 168
    if math.pow(math.floor(math.sqrt(i100)), 2) == i100 and math.pow(math.floor(math.sqrt(i168)), 2) == i168:
        print(i)
        break
    i += 1
```

## 【第二题】有一个已经从小到大排好序的数组a = [1, 5, 8, 14, 28, 39, 60, 89, 134, 324, 612, 900]，现输入一个数b=555，要求按原来的规律将它插入数组中。
```python
a = [1, 5, 8, 14, 28, 39, 60, 89, 134, 324, 612, 900]
b = 555
i = 0
while a[i] < b:
    i += 1

a.insert(i, b)
print(a)
```

## 【第三题】编写一个函数，输入n为偶数时，调用函数求1/2+1/4+...+1/n，当输入n为奇数时，调用函数1+1/3+...+1/n。
```python
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
```
