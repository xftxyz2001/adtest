def get_r(s):
    src_r = 10
    dst = int
    if s.startswith('h'):
        src_r = 16
    elif s.startswith('0'):
        src_r = 8
    elif s.startswith('b'):
        src_r = 2

    if s.endswith('h'):
        dst = hex
    elif s.endswith('o'):
        dst = oct
    elif s.endswith('b'):
        dst = bin

    if src_r != 10:
        s = s[1:]
    if dst != int:
        s = s[:-1]
    return s, src_r, dst


if __name__ == '__main__':
    while True:
        str_input = input("请输入数(b二进制、0八进制、h十六进制)【前缀表示输入的形式，后缀表示输出的形式，默认为十进制】：")
        str_input = str_input.lower()
        if str_input == 'q':
            break
        s, src_r, dst = get_r(str_input)

        num = int(s, src_r)
        print(dst(num))
    print('Bye!')