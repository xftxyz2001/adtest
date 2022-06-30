import random

random.random()

def pi():
    """
    Calculate pi using the Monte Carlo method.
    """
    inside = 0
    for i in range(1000000):
        x = random.random()
        y = random.random()
        if x*x + y*y < 1:
            inside += 1
    return 4 * inside / 1000000


if __name__ == '__main__':
    print(pi())