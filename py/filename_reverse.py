# 获取控制台输入的参数
import sys
import os

# 获取控制台输入的参数
args = sys.argv[1:]
for arg in args:
    # 获取文件名和文件扩展名
    filename = os.path.basename(arg)
    # 修改文件名
    new_filename = filename[::-1]
    # 获取文件路径
    path = os.path.dirname(arg)
    # 拼接新的文件路径
    new_path = os.path.join(path, new_filename)
    # 将文件重命名
    os.rename(arg, new_path)
    print('{} --> {}'.format(arg, new_path))
