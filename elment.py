import random

def elment(a, n):
    while True:
        x = random.randint(0, len(a))
        y = random.randint(0, len(a))
        if x != y and a[x] == a[y]:
            return a[x]


if __name__ == '__main__':
    a = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 1, 1, 1, 1, 1, 1]
    print(elment(a, 3))