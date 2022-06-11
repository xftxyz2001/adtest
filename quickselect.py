def quickselect(a, s, t, k):
    if s < t:
        tmp = a[s]
        i = s
        j = t
        while i != j:
            while i < j and a[j] >= tmp:
                j -= 1
            a[i] = a[j]
            while i < j and a[i] <= tmp:
                i += 1
            a[j] = a[i]
        a[i] = tmp
        if k == i - s + 1:
            return a[i]
        elif k < i - s + 1:
            return quickselect(a, s, i - 1, k)
        else:
            return quickselect(a, i + 1, t, k - (i - s + 1))
    elif s == t and s == k - 1:
        return a[k - 1]
