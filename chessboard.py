from pprint import pprint

tile = 1


def chessboard(b, t, d, s):  # t棋盘左上角，d特殊方格位置，s棋盘大小
    if s == 1:
        return
    global tile  # 初始为1
    tl = tile  # 取一个L型骨，其牌号为tile
    tile += 1
    s //= 2  # 分割棋盘
    if d[0] < t[0]+s and d[1] < t[1]+s:
        chessboard(b, t, d, s)
    else:
        b[t[0]+s-1][t[1]+s-1] = tl
        chessboard(b, t, (t[0]+s-1, t[1]+s-1), s)
    if d[0] < t[0]+s and d[1] >= t[1]+s:
        chessboard(b, (t[0], t[1]+s), d, s)
    else:
        b[t[0]+s-1][t[1]+s] = tl
        chessboard(b, (t[0], t[1]+s), (t[0]+s-1, t[1]+s), s)
    if d[0] >= t[0]+s and d[1] < t[1]+s:
        chessboard(b, (t[0]+s, t[1]), d, s)
    else:
        b[t[0]+s][t[1]+s-1] = tl
        chessboard(b, (t[0]+s, t[1]), (t[0]+s, t[1]+s-1), s)
    if d[0] >= t[0]+s and d[1] >= t[1]+s:
        chessboard(b, (t[0]+s, t[1]+s), d, s)
    else:
        b[t[0]+s][t[1]+s] = tl
        chessboard(b, (t[0]+s, t[1]+s), (t[0]+s, t[1]+s), s)


if __name__ == '__main__':
    board = [[0 for i in range(8)] for j in range(8)]
    chessboard(board, (0, 0), (5, 1), 8)

    for i in board:
        for j in i:
            print('{:3d}'.format(j), end=' ')
        print()
