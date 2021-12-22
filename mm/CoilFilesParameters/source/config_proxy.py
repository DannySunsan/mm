import yaml

class configProxy:
    __path = "./_config.yml"
    __config = {}
    def __init__(self):
        f = open(self.__path, mode='r+',encoding='utf-8')
        input = f.read()        
        f.close()
        self.__config =  yaml.load(input, Loader=yaml.FullLoader)
    def __del__(self):
         if self.__config.get("autosave"):
            self.saveConfig()
    def saveConfig(self):
        fw = open(self.__path,mode='w+',encoding='utf-8')
        yaml.dump(self.__config,fw)
        fw.close()

    def setConfig(self,node,value=None):
        if node not in self.__config:
            return False  
        else:
            self.__config[node] = value       

    def getConfig(self,node):
        return self.__config.get(node)