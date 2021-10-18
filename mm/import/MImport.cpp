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
const string g_Test_FilePath = "/../common_config/test.xml";
const string g_Data_FilePath = "/../common_config/data";

string getLibraryPath()
{
    static std::string strPath;
    if (strPath.length() > 0)
        return strPath;
    char modulefile[255];
    if (GetModuleFileNameA(NULL, modulefile, 255) == 0)
    {
        perror("GetModuleFileNameA error");
        return "";
    }  
    strPath.assign(modulefile);
    int nPos = strPath.find_last_of('\\');
    int nLen = strPath.length();
    strPath = strPath.substr(0, nPos);
    return strPath;
}
extern"C" __declspec(dllexport)
int  loadConfig()
{
    std::cout << "loadConfig!\n";
    list<string> lsModulePath;
         
    try
    {   
       
        string strPath = getLibraryPath()+g_Common_Config_FilePath;

        ptree pt;
        read_xml(strPath, pt);     //读入一个xml文件
        ptree child =  pt.get_child("plug.PlugModule");  
        
        string sProperty = child.get<string>("<xmlattr>.moduleType");
        int iTypeId = child.get<int>("<xmlattr>.typeId");
        for (auto itor = child.begin(); itor != child.end(); itor++)
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

extern"C" __declspec(dllexport)
int writeXml()
{
    std::cout << "writeXml!\n";
    ptree rt,root,child1,child2, num, name;
    
    num.put_value<int>(1);

    name.put_value<string>("child2");

    child1.put<string>("<xmlattr>.name", "child1");
    child1.add_child("num", num);
    child1.add_child("name", name);

    root.add_child("child1", child1);
    rt.add_child("root", root);
    //使用setting参数，保证文件内容样式有缩进有对齐.
    auto setting = boost::property_tree::xml_writer_make_settings<string>('\t', 1);
    //写入文件，把proptrt_tree转换为xml格式
    string strPath = getLibraryPath() + g_Test_FilePath;
    write_xml(strPath, rt, std::locale(), setting);
    return 0;
}

extern"C" __declspec(dllexport)
void loadDataFile(string& strFile)
{   
    string strPath = getLibraryPath() + g_Data_FilePath;
    ifstream is;
    string strFc;
    string strNm;
    is.open(strPath,ios::in);
    is >> strFc;
    is >> strNm;
    strFile = strFc + strNm;
    is.close();
}