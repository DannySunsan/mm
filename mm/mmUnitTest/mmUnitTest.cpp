// mmUnitTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<Windows.h>
#include <iostream>
#include "mmUtility/util.h"
#ifndef MDebug
#define IMPORTDLL  L"import.dll"
#else
#define IMPORTDLL  L"importD.dll"
#endif // !MDebug
typedef int(*func)();
typedef int(*func2)(std::string& strFile);
#define Func(Name,Num) myHashSet.Name(Num)

void testCmmUtility();

void testStringSplit();
void testHashTable();
void testXmlParser();
void testXmlWrite();

int main()
{
   
   system("pause");
}
void testXmlParser()
{
    HMODULE hModule = LoadLibrary(IMPORTDLL);
    if (hModule)
    {
        func f = (func)GetProcAddress(hModule, "loadConfig");

        if (f)
        {
            f();
        }
    }
}
void testXmlWrite()
{
    HMODULE hModule = LoadLibrary(IMPORTDLL);
    if (hModule)
    {
        func f = (func)GetProcAddress(hModule, "writeXml");

        if (f)
        {
            f();
        }
    }
}
void testCmmUtility()
{
    CmmUtility::test();
}

void testStringSplit()
{   
    std::string  strSrc = "Bob Jack c++ SYQ";
    std::vector<std::string> vctDest;
    CmmUtility::splitString(strSrc, vctDest);
}

void testHashTable()
{
    std::string strFile;
    HMODULE hModule = LoadLibrary(IMPORTDLL);
    if (hModule)
    {
        func2 f = (func2)GetProcAddress(hModule, "loadDataFile");

        if (f)
        {
            f(strFile);
        }
    }
    std::vector<std::string> vecStr;
    std::vector<int> vecNum;

    MyHashSet myHashSet;
    CmmUtility::splitFunc(strFile, vecStr, vecNum);
    auto it = vecStr.begin();
    auto itNum = vecNum.begin();
    for (; it != vecStr.end() && itNum != vecNum.end(); it++, itNum++)
    {
        if (*it == "contains")std::cout << Func(contains, *itNum) << std::endl;
        if (*it == "remove")Func(remove, *itNum);
        if (*it == "add")Func(add, *itNum);
    }
}