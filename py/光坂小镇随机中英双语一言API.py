import requests
import time

# 数据来源： https://www.clfans.club/

url = 'https://www.clfans.club/wp-content/themes/zibll/yiyan/qv-yiyan.php'

while True:
    response = requests.get(url)
    text = response.text.replace('/&/', '\n')
    print(text)
    with open('t.txt', 'a', encoding='utf-8') as f:
        f.write(text)
        f.write('\n')
    time.sleep(0.3)
