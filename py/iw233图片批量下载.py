import requests
import time

# 首页：https://iw233.cn/
# 图库：https://iw233.cn/main.html

# API：
随机壁纸 = ['https://iw233.cn/API/Random.php', 'Random']
精选壁纸 = ['https://iw233.cn/API/MirlKoi.php', 'MirlKoi']
电脑壁纸 = ['https://iw233.cn/API/pc.php', 'pc']
手机壁纸 = ['https://iw233.cn/API/mp.php', 'mp']

type_list = [随机壁纸, 精选壁纸, 电脑壁纸, 手机壁纸]

# 类别选择
type_num = int(input('请选择壁纸类别：\n1.随机壁纸\n2.精选壁纸\n3.电脑壁纸\n4.手机壁纸\n'))

# 延时设置
delay = int(input('请设置延时（秒）：'))

while True:
    res = requests.get(type_list[type_num - 1][0])
    imgfilename = res.url.split('/')[-1]
    print('trying:' + imgfilename)
    with open(type_list[type_num - 1][1] + '/' + imgfilename, "wb") as f:
        f.write(res.content)
    time.sleep(delay)
