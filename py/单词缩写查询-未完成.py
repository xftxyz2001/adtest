from selenium import webdriver
from lxml import etree
import time
import re


def read_file(filename):  # read a file
    f = open(filename, 'r', encoding='utf-8')
    text = f.read()
    f.close()
    cutwords = re.split('[\s\n]+', text)  # 英文分词
    # interpunctuations = [',', '.', ':', ';', '?', '(', ')', '[', ']', '&', '!', '*', '@', '#', '$', '%']   #定义标点符号列表
    # cutwords = [word for word in cutwords if word not in interpunctuations]   #去除标点符号
    return cutwords


def query(driver, word):  # query a word
    # driver.get('https://fanyi.youdao.com/')
    # https://fanyi.baidu.com/#en/zh/
    driver.get('https://fanyi.baidu.com/#en/zh/')
    driver.find_element_by_id('baidu_translate_input').send_keys(word)
    driver.find_element_by_id('translate-button').click()
    time.sleep(2)
    ps = d.page_source  # 获取网页源代码
    tree = etree.HTML(ps)  # 将源代码转换为HTML树
    p = tree.xpath('//div[@class="dictionary-comment"]/p')
    return p


if __name__ == '__main__':
    print('正在初始化。。。')
    d = webdriver.Edge('C:/Drivers/msedgedriver.exe')  # 创建浏览器对象
    abbr_dict = {}  # 定义缩写字典
    words = read_file('text.md')
    words = list(set(words))  # 去重
    print('待处理词语：')
    print(words)

    for word in words:
        print('正在处理：' + word)
        fys = query(d, word)
        print(fys)
        for fy in fys:
            if fy.startswith('abbr.'):
                print(word, fy)
                abbr_dict[word] = fy
    print('处理完成，即将写入。。。')
    with open('abbr_dict.md', 'w', encoding='utf-8') as f:
        f.write('key' + '|' + 'value' + '\n')
        f.write('---' + '|' + '---' + '\n')
        for key, value in abbr_dict.items():
            f.write(key + '|' + value + '\n')
    d.quit()
