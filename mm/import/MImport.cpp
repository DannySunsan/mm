#include <windows.h>
#include <iostream>
#include "boost/property_tree/ptree.hpp"
#include <boost/foreach.hpp> 
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp>  
#include <list>
using namespace std;
using namespace boost::property_tree;
const string g_Common_Config_FilePath = "/../common_config/common_plug.xml";

extern"C" __declspec(dllexport)
int  loadConfig()
{
    std::cout << "loadConfig!\n";
    list<string> lsModulePath;
    char modulefile[255];
    if(GetModuleFileNameA(NULL, modulefile, 255)== 0)
    {
        perror("GetModuleFileNameA error");
        return -1;
    }      
    try
    {   
        std::string strPath(modulefile);
        int nPos = strPath.find_last_of('\\');
        int nLen = strPath.length();
        strPath = strPath.substr(0, nPos);
        strPath += g_Common_Config_FilePath;

        ptree pt;
        read_xml(strPath, pt);     //读入一个xml文件
        ptree child =  pt.get_child("PlugModule");
        for (auto itor = child.begin() ; itor!=child.end(); itor++)
        {
            string sModule = itor->second.data();
            lsModulePath.emplace_back(sModule);
        }
    }
    catch (boost::property_tree::file_parser_error& e)
    {
        perror(e.message().c_str());
        return -1;
    }
    for (auto md: lsModulePath)
    {
        HMODULE hand = LoadLibrary(md.c_str());
        if (hand == NULL)
        {
            perror("loadlibrary error");
        }
    }
    return 0;
}

