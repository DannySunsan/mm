import sys
import write_to_excel as wte

def test():
    ex = wte.excelProxy() 
    
    ex.setAlignment('center')
    ex.setFont('黑体',20,True)
    ex.setValue(1,1,'hello world')
    ex.merge(1,2,1,10)
    ex.setAlignment()
    

    for i in range(3,10):
        for j in range(1,10):
            ex.setValue(i,j,f'{i},{j}')
    try:
        ex.save(".\output\ex.xlsx")
    except FileExistsError:
        print('文件被占用')
    
    print('Congratulations!')