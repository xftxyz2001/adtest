import random


def shuffle(a):
    for i in range(len(a)):
        j = random.randint(0, len(a) - 1)
        a[i], a[j] = a[j], a[i]
    return a
