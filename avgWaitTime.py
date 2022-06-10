def avgWaitTime(ts):
    ts.sort()
    n = len(ts)
    tp = [(n-i-1)*t for i, t in enumerate(ts)]
    return sum(tp) / n


if __name__ == '__main__':
    ts = [30, 50, 100, 20, 120, 70]
    print(avgWaitTime(ts))
