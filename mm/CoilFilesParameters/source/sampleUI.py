import tkinter.messagebox as mgbox
import tkinter.filedialog as fileDialog
from tkinter import *
import field_cfg_process as fcp
import search_param_file as spf
from config_proxy import configProxy
import util
import threading
class MainWin():
    def __init__(self,config:configProxy) -> None:
        self.__Configpath  = config.getConfig('path')
        self.__instance = Tk(className='线圈参数查询')          
        self.__createWindow()    
        self.__instance.mainloop()
        
    def __del__(self):
        pass

    def __createWindow(self):
        self.__instance.geometry('410x160')
        #menu
        self.__menu = Menu(self.__instance)
        #self.__menu.grid(row = 0,column = 5)
        #grid 
        # search              
        self.__labelParam = Label(self.__instance,text="参数名称:")
        self.__labelParam.place(x=20,y=20,height=25,width=60)

        self.__txtParam = Entry(self.__instance)
        self.__txtParam.place(x =85,y =20,height=25,width=250)

        #path
        self.__labelPath = Label(self.__instance,text="搜索路径:")
        self.__labelPath.place(x =20,y =55,height=25,width=60)

        self.__pathVar = StringVar()
        self.__txtPath = Entry(self.__instance,textvariable=self.__pathVar)
        self.__txtPath.place(x =85,y =55,height=25,width=250)
        self.__pathVar.set(self.__Configpath)

        self.__buttonPath = Button(self.__instance,text="选择路径",command=self.clickSelectPath)
        self.__buttonPath.place(x =340,y =85,height=25,width=60)

        #search
        self.__buttonSearch = Button(self.__instance,text="搜索",command=self.clickSearch)
        self.__buttonSearch.place(x =20,y =85,height=25,width=60)
        #save
        self.__buttonSave = Button(self.__instance,text="保存",command=self.clickSave)
        self.__buttonSave.place(x =85,y =85,height=25,width=60)
        
        self.__buttonSave2 = Button(self.__instance,text="另保存",command=self.clickSave2)
        self.__buttonSave2.place(x =150,y =85,height=25,width=60)

        #status
        self.__status = StringVar()
        self.__labelStatus = Label(self.__instance,text="状态:",textvariable=self.__status)
        self.__labelStatus.place(x =10,y =120,height=30,width=400)

    def setPath(self,path):
        self.__labelPath['text'] = path

    def clickSearch(self):
        if self.__txtParam.get() == None:
            mgbox.showinfo('提示','查询参数为空')
            return
        if self.__pathVar.get() == None:
            mgbox.showinfo('提示','查询config路径为空')
            return
        self.__doc = fcp.process(self.__pathVar.get(),self.__txtParam.get())
        self.__status.set("搜索结束")

    def clickSave(self):
        savePath = util.saveLists(self.__doc,self.__txtParam.get())
        self.__status.set(f"文件保存在：{savePath}")

    def clickSave2(self):
        dir =fileDialog.askdirectory()
        if len(dir) > 2:            
            savePath = util.saveLists(self.__doc,self.__txtParam.get(),dir)
            self.__status.set(f"文件保存在：{savePath}")
    def clickSelectPath(self):
        dir =fileDialog.askdirectory()
        if len(dir) > 2:
            self.__pathVar.set(dir)

    def setStatus(self,status:str):
        self.__status = f"状态:{status}"