from selenium import webdriver
from lxml import etree
import time

url = 'http://www.qindi.net/read/santishijie/420630.html'  # 开始下载的章节地址

d = webdriver.Edge('C:/Drivers/msedgedriver.exe')  # 创建浏览器对象
fp = open('正文.md', 'w', encoding='utf-8')  # 创建文件对象

while True:
    print(url)  # 打印链接
    d.get(url)  # 访问网页
    ps = d.page_source  # 获取网页源代码
    tree = etree.HTML(ps)  # 将源代码转换为HTML树

    t = tree.xpath('//h1/text()')  # 获取章节标题
    print(t)  # 打印章节标题
    p = tree.xpath('//div[@id="content"]/p/text()')  # 获取段落

    fp.write('##' + t[0] + '\n')  # 写入章节标题
    fp.write('\n'.join(p))  # 写入文件
    fp.write('\n\n')  # 换行
    fp.flush()  # 刷新文件

    time.sleep(0.3)  # 等待
    url = tree.xpath('//div[@class="m-page"]/a[3]/@href')[0] # 获取下一页的链接
    if url.endswith('/'):  # 如果是最后一页
        break  # 结束循环
    if url.startswith('http'):
        continue
    url = 'http://www.qindi.net' + url  # 拼接完整的链接

d.quit()
fp.close()
