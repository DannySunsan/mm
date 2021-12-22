import os
import re

def getMatchParam(file,param):
    if not os.path.isfile(file):
        return
    f = open(file, mode='r')
    fStrs = str(f.read())
    f.close()  
    pattern = r"(?<=</name>)(\s|\\n)*(?=<value>)"
    fStrs = re.sub(pattern,"",fStrs)
    pattern = "(?<="+re.escape(param) + r"</name><value>).*(?=</value>)"
    property = re.search(pattern,fStrs)
    if property != None:
        return property.group(0)
    return None

