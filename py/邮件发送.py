import smtplib
from email.mime.text import MIMEText


class XFMail:
    # 初始化：设置服务器所需信息
    def __init__(self):
        # 邮箱服务器地址
        self.mail_host = ...
        # 用户名不包含@...
        self.mail_user = ...
        # 密码(部分邮箱为授权码)
        self.mail_pass = ...
        # 邮件发送方邮箱地址
        self.sender = ...
        # 邮件接受方邮箱地址，注意需要[]包裹，这意味着你可以写多个邮件地址群发
        self.receivers = [...]
        # 实例化SMTP对象
        self.smtpObj = smtplib.SMTP()
        # 连接到服务器
        self.smtpObj.connect(self.mail_host, 25)
        # 登录到服务器
        self.smtpObj.login(self.mail_user, self.mail_pass)

    # 发送邮件
    def sendmail(self, subject, connect):
        # 构建邮件内容
        # 邮件内容设置
        message = MIMEText(connect, 'plain', 'utf-8')
        # message = MIMEText(connect)
        # 邮件主题
        message['Subject'] = subject
        # 发送方信息
        message['From'] = self.sender
        # 接受方信息
        message['To'] = self.receivers[0]

        # 发送邮件
        try:
            self.smtpObj.sendmail(
                self.sender, self.receivers, message.as_string())
            print('邮件发送成功')
        except smtplib.SMTPException as e:
            print('邮件发送失败', e)  # 打印错误

    # 退出
    def quit(self):
        self.smtpObj.quit()
