import os
import poplib
import configparser
import email
import re
from email.parser import Parser
from email.header import decode_header
from openpyxl import Workbook
import time

stu = []


def decode_str(s):  # 字符编码转换
    value, charset = decode_header(s)[0]
    if charset:
        value = value.decode(charset)
    return value


def get_att(msg_, zz):
    attachment_files = []

    for part in msg_.walk():
        file_name = part.get_filename()  # 获取附件名称类型

        # contType = part.get_content_type()
        if file_name:
            h = email.header.Header(file_name)
            dh = email.header.decode_header(h)  # 对附件名称进行解码
            filename = dh[0][0]
            if dh[0][1]:
                filename = decode_str(str(filename, dh[0][1]))  # 将附件名称可读化
                pattern = re.compile(zz)
                match = pattern.match(filename.split('.')[0])
                if match:
                    print(match.groups())
                    stu.append(match.groups())
                    # filename = filename.encode(
utf-8)
                    data = part.get_payload(decode=True)  # 下载附件
                    att_file = open(filename, 'wb')  # 在指定目录下创建文件，注意二进制文件需要用wb模式打开
                    attachment_files.append(filename)
                    att_file.write(data)  # 保存附件
                    att_file.close()
    return attachment_files


# 打开配置文件
print('检查配置文件...')
conf = configparser.ConfigParser()
root_path = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
config_path = root_path + r'\config.ini'

if not os.path.isfile(config_path):
    print('错误:', config_path)
    exit()

conf.read(config_path)  # 文件路径


# 读取配置信息
print('配置用户信息...')
host = conf.get('mail', 'host')
username = conf.get('mail', 'username')
password = conf.get('mail', 'password')
match_str = conf.get('mail', 'filename')

# 连接到POP3服务器
print('连接邮件服务器...')
server = poplib.POP3(host)

# 身份验证
print('验证身份...')
server.user(username)
server.pass_(password)  # 参数是你的邮箱密码，如果出现poplib.error_proto: b'-ERR login fail'，就用开启POP3服务时拿到的授权码

# 获取邮件列表
print('获取邮件列表...')
resp, mails, octets = server.list()

# 遍历邮件
index = len(mails)
print('共获取到', index, '封邮件.')
for i in range(index, 0, -1):
    # lines存储了邮件的原始文本的每一行
    print('处理', index - i + 1, '/', index)
    resp, lines, octets = server.retr(i)
    # 邮件的原始文本:
    msg_content = b'\r\n'.join(lines).decode('utf-8')
    # 解析邮件:
    print('解析...')
    msg = Parser().parsestr(msg_content)
    # 获取附件
    f_list = get_att(msg, match_str)

print('所有邮件处理完毕.')

wb = Workbook()
ws = wb.active
ws.append(('学号', '姓名'))
for item in stu:
    ws.append(item)
wb.save('student.xlsx')
print('已提交的学生信息已导出到student.xlsx')

print('此程序将在10秒钟后退出.')
time.sleep(10)

