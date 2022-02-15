// mmTcpServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "mmUtility/util.h"
#include "mmServerTcpProxy.h"
constexpr int PORT = 443;//receive
int main()
{
    try
    {
        mm::mmServerTcpProxy* proxy = new mm::mmServerTcpProxy();
       
        proxy->initialize(PORT,proxy);     
            
        std::string sen;
        while (std::cin >> sen)
        {
            proxy->broadcast((char*)sen.data(), sen.length());
        }
           
        if (proxy != nullptr)
        {
            delete proxy;
            proxy = nullptr;
        }
    }
    catch (...)
    {

    }
}