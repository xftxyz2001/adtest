def loadway(ws, mw):  # ws：重量集合，mw：最大重量
    ws.sort()
    for i in range(len(ws)):
        if sum(ws[:i+1]) > mw:
            return ws[:i], sum(ws[:i]), mw-sum(ws[:i])


if __name__ == '__main__':
    ws = [5, 2, 6, 4, 3]
    mw = 10
    print(loadway(ws, mw))
