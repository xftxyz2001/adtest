import requests
import json
import openpyxl
import time
from requests.models import Response


def get_list(page):
    url = 'http://nwu.co.cnki.net/Handler/Project.ashx?action=GetStuChoiceProjectsList'

    headers = {
        # 'Accept': ' application/json, text/javascript, */*; q=0.01',
        # 'Accept-Encoding': ' gzip, deflate',
        # 'Accept-Language': ' zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6',
        # 'Connection': ' keep-alive',
        # 'Content-Length': ' 121',
        # 'Content-Type': ' application/x-www-form-urlencoded; charset=UTF-8',
        'Cookie': 'SID_co=012005; ASP.NET_SessionId=5pbj1y3vrnmwab45mgahy245; CO2017_DomainPrefix=nwu; login_usr_role=3; cur_role_id=2; isEssenceVersion=false; CO2017_AutoLoginId=6hxlgpMrbD9gmX6hJqtVWQjHy79XlvYD5EWa2U9meh0JxfvF0SiV6TT2wg8vAS4a2VhPWksJzlxPYI2jJzVM89MlEPbJmcCTNTdfj9WsQkA%3D',
        'Host': 'nwu.co.cnki.net',
        'Origin': 'http://nwu.co.cnki.net',
        'Referer': 'http://nwu.co.cnki.net/Project/StuChoiceProjectList.html?r=0.8271484324701206',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36 Edg/93.0.961.38',
        # 'X-Requested-With': ' XMLHttpRequest'
    }

    data = {
        'page': page,
        'rows': 20,
        'authToken': 'F3C733F45B2ABB68E8818A94910F16DA',
        'dp': 'nwu'
    }

    response = requests.post(url, data, headers=headers)
    tab_data = json.loads(response.content)
    return tab_data


def get_disc(ketiid):
    url = 'http://nwu.co.cnki.net/Handler/Project.ashx?action=GetProjectDetails'

    headers = {
        # 'Accept': ' application/json, text/javascript, */*; q=0.01',
        # 'Accept-Encoding': ' gzip, deflate',
        # 'Accept-Language': ' zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6',
        # 'Connection': ' keep-alive',
        # 'Content-Length': ' 121',
        # 'Content-Type': ' application/x-www-form-urlencoded; charset=UTF-8',
        'Cookie': 'SID_co=012005; ASP.NET_SessionId=5pbj1y3vrnmwab45mgahy245; CO2017_DomainPrefix=nwu; login_usr_role=3; cur_role_id=2; isEssenceVersion=false; CO2017_AutoLoginId=6hxlgpMrbD9gmX6hJqtVWQjHy79XlvYD5EWa2U9meh0JxfvF0SiV6TT2wg8vAS4a2VhPWksJzlxPYI2jJzVM89MlEPbJmcCTNTdfj9WsQkA%3D',
        'Host': 'nwu.co.cnki.net',
        'Origin': 'http://nwu.co.cnki.net',
        'Referer': 'http://nwu.co.cnki.net/Project/StuChoiceProjectList.html?r=0.8271484324701206',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36 Edg/93.0.961.38',
        # 'X-Requested-With': ' XMLHttpRequest'
    }

    data = {
        'ktbh': ketiid,
        'authToken': 'F3C733F45B2ABB68E8818A94910F16DA',
        'dp': 'nwu'
    }

    response = requests.post(url, data, headers=headers)
    tab_data = json.loads(response.content)
    return tab_data


wb = openpyxl.Workbook()
ws = wb.active
name_list = ['SID', 'TID', 'TotalCount', 'num', '专业编号', '允许修改', '创建时间', '名称', '姓名', '学校编号', '学院名称', '审核', '性质',
             '教师编号', '教研室', '是否选择', '来源', '研究方向', '计划编号', '课题专业编号', '课题学院编号', '课题编号', '选择模式', '题目来源名称', '题目类型名称']
ws.append(name_list)

for i in range(1, 28):
    j = 0
    for item in get_list(i)['rows']:
        j += 1
        item_line = []
        for na in name_list:
            item_line.append(item.get(na, '@@@'))
        time.sleep(0.5)
        disc = get_disc(item.get('课题编号'))
        disc_info = disc['rows'][0]
        item_line.append(disc_info['column056'])
        item_line.append(disc_info['column057'])
        item_line.append(disc_info['column058'])
        print(i, j, item_line)
        ws.append(item_line)
    wb.save('info.xlsx')
