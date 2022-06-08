def perm(r):
    if len(r) == 0:
        return []
    if len(r) == 1:
        return [r]
    result = []
    for i, x in enumerate(r):
        rem = r[:i] + r[i+1:]
        for p in perm(rem):
            result.append([x] + p)
    return result
