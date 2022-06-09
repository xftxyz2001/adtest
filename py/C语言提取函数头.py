# 小工具：C语言函数声明提取头文件
# 使用方法：运行脚本，输入c原文件名即可（c++可能也行）

import re

file_name = input('input filename:')

# 提取函数头的正则表达式
pattern = '''(.* .*\(.*\))\n\{'''

with open(file_name, 'r', encoding='utf-8') as fp:
    file_content = fp.read()
    # 匹配所有函数头
    methods_defined = re.findall(pattern, file_content)

    with open(file_name.split('.')[0]+'.h', 'w', encoding='utf-8') as hfp:
        hfp.write('#ifndef _'+file_name.split('.')[0].upper()+'_H_\n')
        hfp.write('#define _'+file_name.split('.')[0].upper()+'_H_\n')
        for method_defined in methods_defined:
            print(method_defined)
            hfp.write(method_defined+';\n\n')
        hfp.write('#endif')
