import datetime
import os


def convert(s):
    dt = datetime.datetime.strptime(s, '%Y年%m月%d日')
    return dt.date().strftime('%Y年%m月%d日')


for dirpath, dirnames, filenames in os.walk('.'):
    for filename in filenames:
        if filename.endswith('.md'):
            fullpath = os.path.join(dirpath, filename)
            f = open(fullpath, 'r', encoding='utf-8')
            lines = f.readlines()
            f.close()
            f = open(fullpath, 'w', encoding='utf-8')
            for line in lines:
                if line.startswith('#'):
                    ls = line.split()
                    ls[1] = convert(ls[1])
                    line = ' '.join(ls)
                f.write(line)
            f.close()
            print(fullpath)
