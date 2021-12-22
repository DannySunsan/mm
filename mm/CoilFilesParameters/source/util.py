import write_to_excel as wte
import os
import time
import regex
from config_proxy import configProxy
listField = ["MR_0_75_T","MR_1_5_T","MR_3_T","MR_5_T"]

def changePath(config:configProxy):
    pathNew = input("请输入修改后的有效路径：")
    if not os.path.exists(pathNew):
        print("路径不存在")
    else:
        config.setConfig('path',pathNew)
        print(f"路径已修改，当前路径{pathNew}")

def fillHead(excel:wte.excelProxy,param:str):
    excel.setValue(1,1,"CoilName")
    excel.setValue(1,2,"Scope")
    excel.setValue(1,3,"Source")
    excel.setValue(1,4,param)
    excel.setColWidth('A',30)
    excel.setColWidth('B',30)
    excel.setColWidth('C',50)
    excel.setColWidth('D',50)
def fillElement(excel:wte.excelProxy,value:dict,scope:str,row:int):
    listValue = {}
    listValue = value.get(scope)
    up = row  
    for _key,_value in listValue.items():
        if _value == None:
            continue
        excel.setValue(row,3,_key)
        excel.setValue(row,4,_value)
        row += 1
    if row > up:
        excel.setValue(up,2,scope)
    if row - up >1:
        excel.merge(up,row-1,2,2)
    return row

def fillCoil(excel:wte.excelProxy,name:str,value:dict,row:int):
    up = row
    excel.setValue(row,1,name)
    row = fillElement(excel,value,"ElementGroup",row)
    row = fillElement(excel,value,"Element",row)
    row = fillElement(excel,value,"Common",row)
    if row - up >1:
        excel.merge(up,row-1,1,1)
    return row
       
def getFileName():
    name = "\\{}{}{}{}{}.xlsx".format(time.gmtime().tm_year,time.gmtime().tm_mon,
        time.gmtime().tm_mday,time.gmtime().tm_hour,time.gmtime().tm_min,time.gmtime().tm_sec)  
    return name

def saveLists(doc:dict,param:str,savePath:str):
    if doc == None:
        print("查询结果为空，不需要保存")
        return 
    if not os.path.exists(savePath):
        savePath = f"./output/"        

    excel = wte.excelProxy()
    for field in listField:
        excel.addSheet(field)
        fillHead(excel,param)
        coilParam = doc.get(field)
        row = 2
        for key,value in coilParam.items():
            row = fillCoil(excel,key,value,row) 
    savePath += "\\"+getFileName()
    excel.save(savePath)         
    print(f"文件已保存在：{savePath}") 
    return savePath      