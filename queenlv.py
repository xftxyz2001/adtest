import random


class queen():
    def __init__(self, n):
        self.n = n
        self.x = [0]*(n+1)

    def place(self, k):
        for j in range(1, k):
            if abs(k-j) == abs(self.x[k]-self.x[j]) or self.x[k] == self.x[j]:
                return False
        return True

    def queenLV(self):
        k = 1
        cnt = 1
        while k <= self.n and cnt > 0:
            cnt = 0
            j = 0
            for i in range(1, self.n+1):
                self.x[k] = i
                if self.place(k):
                    cnt += 1
                    if random.randint(0, cnt) == 0:
                        j = i
            if cnt > 0:
                self.x[k] = j
                k += 1
        return cnt > 0

    def nqueen(self):
        while not self.queenLV():
            print(self.x)
            continue
        return self.x


if __name__ == '__main__':
    x = queen(8)
    print(x.nqueen())
