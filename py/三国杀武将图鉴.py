import time
import pymysql
from selenium import webdriver
from lxml import etree

db = pymysql.connect(host='localhost',
                     user='root',
                     password='root',
                     database='sgs',
                     autocommit=True)
cursor = db.cursor()
cursor.execute('DROP TABLE IF EXISTS `character`;')
cursor.execute('CREATE TABLE `character`  ( `cname` varchar(255),  `title` varchar(255),  `gender` varchar(255),  `power` varchar(255),  `famous` varchar(255),  `aname` varchar(255),  `package` varchar(255),  `pubdate` varchar(255),  `exploits` varchar(255),  `position` varchar(255),  `die` varchar(255));')

cursor.execute('DROP TABLE IF EXISTS `skill`;')
cursor.execute(
    'CREATE TABLE `skill`  (  `sname` varchar(255),  `describe` varchar(255),  `line` varchar(255));')

cursor.execute('DROP TABLE IF EXISTS `cs`;')
cursor.execute(
    'CREATE TABLE `cs`  (  `cname` varchar(255),  `sname` varchar(255));')

msedgedriver_path = 'C:/Drivers/msedgedriver.exe'
base_url = 'https://wiki.biligame.com/sgs/'
delay = 1

d = webdriver.Edge(msedgedriver_path)
d.get(base_url + '武将图鉴')
for i in range(10):
    parse_html = etree.HTML(d.page_source)
    name_j = parse_html.xpath(
        '//div[@class="mw-parser-output"]/p/script[1]/text()')
    if len(name_j) > 0:
        break
    time.sleep(delay)


# for names in name_j:
name_list = name_j[0].split('"')[1].split(', ')

for name in name_list:
    url = base_url + name
    print('[[[[[[[[[[trying: ' + url)
    d.get(url)
    time.sleep(delay)
    parse_html = etree.HTML(d.page_source)
    base_xpath = '//div[@id="mw-content-text"]/div[@class="mw-parser-output"]/div[@class="flex-container col-direction"]/'
    # 武将称号
    title_j = parse_html.xpath(base_xpath + 'div[1]/div[1]/div[1]/text()')
    title_ = ''
    for t in title_j:
        if t.startswith('武将称号：'):
            title_ = t.split('：')[1][:-1]
    # 武将简介：性别、势力、名将堂、别称
    intro_j = parse_html.xpath(base_xpath + 'div[1]/div[2]/div/text()')
    gender, power, famous, aname = intro_j
    # 武将包、上线时间、战功、定位、阵亡
    for i in range(2, 4):
        # 武将类型
        type_ = parse_html.xpath(
            base_xpath + 'div['+str(i)+']/div[2]/div[1]/div[2]/div[1]/div/p/text()')
        if len(type_) <= 0 or type_[0] != '经典' and type_[0] != '界限突破':
            break
        type_ = type_[0]
        # 包
        package = parse_html.xpath(
            base_xpath + 'div['+str(i)+']/div[2]/div[1]/div[2]/div[2]/div[1]/div[2]/a/text()')
        if len(package) <= 0:
            package = parse_html.xpath(
                base_xpath + 'div['+str(i)+']/div[2]/div[1]/div[2]/div[2]/div[1]/div[2]/text()')
        package = package[0]
        # 上线时间
        pubdate = parse_html.xpath(
            base_xpath + 'div['+str(i)+']/div[2]/div[1]/div[2]/div[2]/div[2]/div[2]/a/text()')
        if len(pubdate) <= 0:
            pubdate = parse_html.xpath(
                base_xpath + 'div['+str(i)+']/div[2]/div[1]/div[2]/div[2]/div[2]/div[2]/text()')
        pubdate = pubdate[0]
        # 战功
        exploits = parse_html.xpath(
            base_xpath + 'div['+str(i)+']/div[2]/div[1]/div[2]/div[3]/div[1]/div[2]/a/text()')
        if len(exploits) <= 0:
            exploits = parse_html.xpath(
                base_xpath + 'div['+str(i)+']/div[2]/div[1]/div[2]/div[3]/div[1]/div[2]/text()')
        exploits = exploits[0]
        # 定位
        position = parse_html.xpath(
            base_xpath + 'div['+str(i)+']/div[2]/div[1]/div[2]/div[3]/div[2]/div[2]//font/text()')
        if len(position) <= 0:
            position = parse_html.xpath(
                base_xpath + 'div['+str(i)+']/div[2]/div[1]/div[2]/div[3]/div[2]/div[2]/text()')
        position = ' '.join(position)
        # 台词
        skill_line_xpath = base_xpath + \
            'div['+str(i)+']/div[2]/div[2]/div[2]/div[2]/div'
        skill_line_j = parse_html.xpath(skill_line_xpath)
        # 阵亡台词
        die = parse_html.xpath(
            skill_line_xpath+'['+str(len(skill_line_j))+']/div[2]/text()')[0]
        sql = 'INSERT INTO `character` VALUES("%s","%s","%s","%s","%s","%s","%s","%s", "%s", "%s", "%s");' % (
            name, title_, gender, power, famous, aname, package, pubdate, exploits, position, die)
        cursor.execute(sql)
        # 技能
        skill_xpath = base_xpath + \
            'div['+str(i)+']/div[2]/div[2]/div[1]/div[2]/div'
        skill_j = parse_html.xpath(skill_xpath)
        if len(skill_j) <= 0:
            skill_xpath = base_xpath + \
                'div['+str(i)+']/div[2]/div[2]/div[1]/div[3]/div'
            skill_j = parse_html.xpath(skill_xpath)
        for j in range(1, len(skill_j)+1):
            skill_name = parse_html.xpath(
                skill_xpath + '['+str(j)+']/div[1]/a/span/text()')[0]
            skill_desc = parse_html.xpath(
                skill_xpath + '['+str(j)+']/div[2]')[0].xpath('string(.)')
            skill_line = parse_html.xpath(
                skill_line_xpath + '['+str(j)+']/div[2]/text()')[0]
            sql = 'SELECT * FROM `skill` WHERE `sname`="%s";' % skill_name
            cursor.execute(sql)
            if cursor.rowcount > 0 and cursor.fetchone() != (skill_name, skill_desc, skill_line):
                if type_ == '界限突破':
                    skill_name = skill_name + '(界)'
                else:
                    print("====================%s已存在" % skill_name)
            sql = 'INSERT INTO `skill` VALUES("%s","%s","%s");' % (
                skill_name, skill_desc, skill_line)
            cursor.execute(sql)
            sql = 'INSERT INTO `cs` VALUES("%s","%s");' % (
                name, skill_name)
            cursor.execute(sql)

d.quit()
cursor.close()
db.close()
