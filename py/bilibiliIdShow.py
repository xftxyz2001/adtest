from selenium import webdriver
from PIL import Image
import urllib.parse
import json
d_path = 'D:/Drivers/EdgeDriver/phantomjs.exe'
url = 'https://search.bilibili.com/upuser?keyword='

driver = webdriver.PhantomJS(d_path)
count = 0
content = json.load(open('text.json', 'r', encoding='utf-8'))


for nas in content:
    for na in nas:
        img_name = 'img'+str(count)+na+'.png'
        count += 1
        print(img_name)
        driver.get(url+urllib.parse.quote(na))
        driver.save_screenshot(img_name)
        img = Image.open(img_name)
        img.crop((0, 380, 500, 560)).save(img_name)

driver.quit()
