import sys
import field_cfg_process as fcp
import search_param_file as spf
import os
import util
from config_proxy import configProxy
def showTips():
    print('''
    help                帮助
    quit                退出
    query               查询
    chpath              修改路径  
    ''')

        

if __name__ == "__main__":  
    config = configProxy()
    path  = config.getConfig('path')
    while 1:            
        #path = r"D:\TFS\UIMRIS\BRANCHES\uMR_MAIN\UIH\appdata\MR\Config"
        print(f"当前路径{path}")        
        cmd = input("请输入命令：")
        if cmd == "help":
            showTips()          
        elif cmd == "chpath":
            util.changePath(config)
            path  = config.getConfig('path')
        elif cmd == "query":
            param = input("请输入参数：")
            doc = fcp.process(path,param)
            while 1:
                ans = input("查询结束，是否保存？(Y/N)：")
                if  ans == 'Y' or ans =='y':
                    util.saveLists(doc,input("请选择保存位置："))
                    break
                elif ans == 'N' or ans =='n':
                    break            
        elif cmd == "quit":
            break


#是相同磁场同名线圈参数相同还是不同磁场？
    #磁场 -> 线圈名 -> 参数 ->element、eleG、common