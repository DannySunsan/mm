import os
import shutil
import stat
import search_param_file as spf
import progressBar as pb
source_path = "../appdata/MR/Config/"
out_path = "./output/Config/"

field_type = \
{
    "MR_0_75_T" : ["uMR360"],
    "MR_1_5_T" : ["uMR560","uMR570","uMR570i","uMR580","uMR586","uMR555e","uMR588","uMR660"],
    "MR_3_T" : ["uMR770","uMR780","uMR790","uMR870","uMR880","uMR890","uPMR790","uPMR890","uMROmega","uMRAthena","uMRAlpha"],
    "MR_5_T" : ["uMRJupiter"]
}
ignore_file = {"DDPConfigFile"}
def copyFile(src,dst):
    try:
        shutil.copytree(src,dst)
    except Exception as err:
        print(err)

def delFiles(path) -> bool:
    try:
        lstFiles = os.listdir(path)
        for file in lstFiles:
            full_path = os.path.join(path,file)
            if os.path.isdir(full_path):
                delFiles(full_path)
            else:
                os.chmod(full_path,stat.S_IWRITE|stat.S_IWGRP|stat.S_IWOTH)
                os.remove(full_path)
        if os.path.exists(path):
            shutil.rmtree(path)
    except Exception as err:
        print(err)
        return False
    return True

def process(src:str,param:str): 
    progress = pb.progressBar()
    if os.path.exists(out_path): 
        if not delFiles(out_path):
            print("删除文件失败！")
            return
    progress.setProgress(1)
    if src == None :
        src = source_path
    else:
        src = src+"\\"
    if os.path.exists(out_path)==False :
        os.makedirs(out_path)

    i = 1
    lstFields = {}
    for key in field_type.keys():       
        lstCoil = {}         
        progress.setProgress(i+1)               
        step = 25//len(field_type[key])
        if step < 1:
            step = 1   

        for value in field_type[key]: 
            i += step   
            step += step

            _src = src + value + "\\CoilFiles\\"
            _dst = out_path + key + "\\" + value + "\\CoilFiles\\"
            if os.path.exists(_src) == False:
                continue

            lstFiles = os.listdir(_src)
            for file in lstFiles:
                if file in lstCoil:
                    continue

                #读取线圈文件
                if os.path.isdir(_src+file) and file not in ignore_file:
                    #copyFile(_src+file,_dst+file)
                    lstCoil.setdefault(file,searchParamList(_src+file,param))
                    
        lstFields.setdefault(key,lstCoil) 
    progress.setProgress(100)
    return lstFields



def searchParamList(coilFile:str,param):    
    lstFiles = os.listdir(coilFile) 

    dicCoil = {}
    dicCoil.setdefault("ElementGroup")
    dicCoil.setdefault("Element")
    dicCoil.setdefault("Common")
    dicCoil["ElementGroup"] = dict()
    dicCoil["Element"] = dict()
    dicCoil["Common"] = dict()

    for file in lstFiles:
        path = coilFile+"\\"+file
        strFile = str(file)
        
        if os.path.isfile(path): 
            MatchParam = spf.getMatchParam(path,param)
            if MatchParam ==None:
                continue;
            
            dicCoil["ElementGroup"].setdefault(strFile)
            dicCoil["Element"].setdefault(strFile)
            dicCoil["Common"].setdefault(strFile)
            # if listField == None:
            #     listField = dict()
            #     listField.setdefault(file)

            if strFile.find("ElementGroup") != -1:
                dicCoil["ElementGroup"][strFile] = MatchParam
            elif strFile.find("Common") != -1:
                dicCoil["Common"][strFile] = MatchParam
            else:
                dicCoil["Element"][strFile] = MatchParam   
    return dicCoil