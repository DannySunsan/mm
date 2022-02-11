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
#include <fstream>
#include "mmClientTcpProxy.h"
void client()
{
    mmClientTcpProxy* proxy = new mmClientTcpProxy();
    mmTcpClient client1(proxy);
    std::thread sendth([&client1]()
        {
            std::string sen;
            while (std::cin >> sen)
            {
                client1.send((char*)sen.data(), sen.length());
            }
        });

    client1.connect("10.9.81.246", 443);
    sendth.join();
    if (proxy != nullptr)
    {
        delete proxy;
        proxy = nullptr;
    }
}

class c
{
    union 
    {
        int i;
        double d;
        char s[13];
    } ;
public:
    c() 
    {
        memset(s,0x00000001,13);
    }
};
#include <shellapi.h>
#include <stdio.h>
int main()
{
    client();
}