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
int main()
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

    CmmUtility::test();
   // system("pause");
}