# 操作系统的某次思考题目

ops_list = []


class a:
    def __init__(self):
        self.val = 10


class b:
    def __init__(self):
        self.val = 10


def A(a, b):
    print('T1：a = a+1', end='\t')
    a.val = a.val + 1


def B(a, b):
    print('T1：b = b+1', end='\t')
    b.val = b.val + 1


def C(a, b):
    print('T1：输出', a.val, b.val, end='\t')


def D(a, b):
    print('T2：b = b*2', end='\t')
    b.val = b.val * 2


def E(a, b):
    print('T2：a = a*2', end='\t')
    a.val = a.val * 2


def F(a, b):
    print('T2：输出', a.val, b.val, end='\t')


def fun(res, left, right):
    if len(left) == 0 and len(right) == 0:
        ops_list.append(res)
        return
    if len(left) != 0:
        rl = res[::]
        rl.append(left[0])
        fun(rl, left[1:], right)
    if len(right) != 0:
        rr = res[::]
        rr.append(right[0])
        fun(rr, left, right[1:])


if __name__ == '__main__':
    fun([], [A, B, C], [D, E, F])
    print('情况\t第一步\t\t第二步\t\t第三步\t\t第四步\t\t第五步\t\t第六步\t\t最终ab的值')
    for i in range(len(ops_list)):
        print(i + 1, end='\t')
        ai = a()
        bi = b()
        for op in ops_list[i]:
            op(ai, bi)
        print('a = ', ai.val, ',b = ', bi.val, sep='')
