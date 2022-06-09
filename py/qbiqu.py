import time

from lxml import etree
from selenium import webdriver

xpath_title = "//h1/text()"
xpath_content = "//div[@id='content']/text()"
xpath_next_url = "//div[@class='bottem1']/a[5]/@href"

start_url = 'https://www.qbiqu.com/26_26380/14878164.html'


d = webdriver.Edge('C:/Drivers/msedgedriver.exe')


def get_tree(url):
    time.sleep(1)
    d.get(url)
    html = d.page_source
    tree = etree.HTML(html)
    return tree


if __name__ == '__main__':
    next_url = start_url
    fp = open('qbiqu.md', 'w', encoding='utf-8')
    while next_url.endswith('html'):
        tree = get_tree(next_url)
        title = tree.xpath(xpath_title)[0]
        content = ''.join(tree.xpath(xpath_content))
        next_url = 'https://www.qbiqu.com' + tree.xpath(xpath_next_url)[0]
        print(title)
        fp.write('#' + title + '\n')
        fp.write(content + '\n')
        fp.flush()
    fp.close()
