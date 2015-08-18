import xlrd
import xlwt

wbk = xlwt.Workbook()
sheet = wbk.add_sheet('sheet 1')
#indexing is zero based,row then column
for i in range(1,10):
	for j in range(1,10):
		sheet.write(i-1,j-1,i*j)

#sheet.write(0,1,'test text')
#sheet.write(0,0,'fist place')
wbk.save('testOut/myworkbook.xls')

#wb = xlrd.open_workbook('myworkbook.xls')

