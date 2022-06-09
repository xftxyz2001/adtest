import os

for dirpath, dirnames, filenames in os.walk('.'):
    for filename in filenames:
        if filename.endswith('.md'):
            fullpath = os.path.join(dirpath, filename)
            f = open(fullpath, 'r', encoding='utf-8')
            lines = f.readlines()
            f.close()
            f = open(fullpath, 'w', encoding='utf-8')
            for line in lines:
                # if line.startswith('#'):
                #     line = line.replace('周', '星期')
                while line.startswith(' '):
                    line = line[1:]
                f.write(line)
            f.close()
            print(fullpath)
