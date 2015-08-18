#coding=utf-8
import xlrd
import xlwt
workbook = xlwt.Workbook(encoding='utf-8')
booksheet = workbook.add_sheet('Sheet 1', cell_overwrite_ok=True)
workbook.add_sheet('Sheet 2')
DATA = (('''学号''', '''姓名''', '''年龄''', '性别', '成绩'),
             (1001, 'AAAA', 23, '男', 98),
             (1002, 'BBBB', 21, '女', 90),
             (1003, 'CCCC', 24, '女', 100),
             (1004, 'DDDD', 22, '女', 86),
             (1005, 'EEEE', 25, '女', 88),)

for i, row in enumerate(DATA):
    for j, col in enumerate(row):
        booksheet.write(i, j, col)
booksheet.col(0).width=10
workbook.save('testOut/成绩单.xls')

