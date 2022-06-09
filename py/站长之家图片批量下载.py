import urllib.request
from lxml import etree
import time


def create_request(img_type, page):
    base_url = 'https://sc.chinaz.com/tupian/'
    dot_html = '.html'

    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.159 Safari/537.36 Edg/92.0.902.84'
    }

    return urllib.request.Request(
        url=base_url+img_type+dot_html if page == 1 else base_url + img_type+str(page)+dot_html, headers=headers)


def get_content(request):
    handler = urllib.request.HTTPHandler()
    opener = urllib.request.build_opener(handler)
    response = opener.open(request)
    return response.read().decode('utf-8')


def get_max_page(content):

    tree = etree.HTML(content)
    a_list = tree.xpath('//div[@class="fenye"]/a/b/text()')
    return a_list[len(a_list)-1]


def save_img(content):
    tree = etree.HTML(content)
    alt_list = tree.xpath('//img/@alt')
    src_list = tree.xpath('//img/@src2')
    for i in range(len(alt_list)):
        try:
            file_name = alt_list[i]+'.jpg'
            download_link = 'http:' + src_list[i]
            print(file_name)
            urllib.request.urlretrieve(download_link, file_name)
        except Exception as e:
            print(e)
            continue


if __name__ == '__main__':
    print('-'*20, 'chinaz-image-downloader', '-'*20)
    img_type = input('\timage-type(or head-url):')
    if 'http' in img_type:
        img_type = img_type.split('/')[4].split('.')[0]
    request = create_request(img_type,1)
    try:
        max_ = get_max_page(get_content(request))
    except Exception as e:
        print('type-error')
        exit(-1)
    print('\t\twith:1 -', max_)
    start_page = int(input('\tstart-with:'))
    end_page = int(input('\tend-with:'))
    delay = float(input('\tdelay(seconds):'))
    for page in range(start_page, end_page+1):
        print('trying:',page)
        try:
            request = create_request(img_type,page)
            content = get_content(request)
            save_img(content)
            time.sleep(delay)
        except Exception as e:
            print(e)
            continue
