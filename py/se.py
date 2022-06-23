# with open('data.txt', 'r', encoding='utf-8') as f1:
#     with open('data2.txt', 'w', encoding='utf-8') as f2:
#         for line in f1:
#             ls = line.split('|')
#             for l in ls:
#                 if l.startswith('/resourcescontroller'):
#                     f2.write(l + '\n')

from selenium import webdriver

d = webdriver.Edge('C:/Drivers/msedgedriver.exe')

with open('data2.txt', 'r', encoding='utf-8') as f:
    for line in f:
        d.get('https://mooc1-2.chaoxing.com/' + line)
        d.implicitly_wait(3)
        ...
