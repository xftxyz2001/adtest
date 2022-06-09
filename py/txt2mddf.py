import os

for dirpath, dirnames, filenames in os.walk('.'):
    for filename in filenames:
        if filename.endswith('.txt'):
            date = filename.split('.')[0]
            date_list = date.split('-')
            new_dirpath = os.path.join(dirpath, date_list[0], date_list[1])
            if not os.path.exists(new_dirpath):
                os.makedirs(new_dirpath)
            new_filename = os.path.join(new_dirpath, date + '.md')
            with open(filename, 'r', encoding='utf-16') as fin:
                with open(new_filename, 'w', encoding='utf-8') as fout:
                    fout.write('## ')
                    fout.write(fin.read())
            print(new_filename)
