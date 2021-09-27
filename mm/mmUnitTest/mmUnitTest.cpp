// mmUnitTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<Windows.h>
#include <iostream>
#include "mmUtility/util.h"
#ifndef MDebug
#define MMUTILITY  L"CmmUtility.dll"
#else
#define MMUTILITY  L"CmmUtilityD.dll"
#endif // !MDebug

int main()
{
    wchar_t path[255];
    wchar_t* filePath = _wgetcwd(path,255);
    filePath = lstrcatW(filePath, L"\\..\\");
    filePath = lstrcatW(filePath, MMUTILITY);

    HMODULE hModule = LoadLibrary(filePath);
   // CmmUtility::test();
    std::cout << "Hello World!\n";
}