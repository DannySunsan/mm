// mmUnitTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//#include<Windows.h>
#include <iostream>
#include "mmUtility/util.h"
#include<vector>
#ifndef MDebug
#define IMPORTDLL  L"import.dll"
#else
#define IMPORTDLL  L"importD.dll"
#endif // !MDebug
#include <algorithm>
#include <future>
#include <functional>
#include <thread>


int main()
{
    mmTcpClient client1;
    client1.connect("10.9.81.246",443);
    std::string sen;
    while (std::cin >> sen)
    {
        client1.send(sen.c_str());
    }
}