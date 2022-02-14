// mmTcpServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "mmUtility/util.h"
#include "mmServerTcpProxy.h"
constexpr int PORT = 443;//receive
void get_input(std::promise<int>& pi)
{
    int x;
    std::cout << "Enter an inter va==\n";
    std::cin.exceptions(std::ios::failbit);

    try
    {
        std::cin >> x;
        pi.set_value(x); //set_value会将共享标志位置为ready
    }
    catch (std::exception&)
    {
        pi.set_exception(std::current_exception());
    }
}

void printSth(std::shared_future<int>& fut)
{
    try
    {
        int x = fut.get();//在共享标志位置为ready之前会被阻塞
        std::cout << x << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "exception" << e.what() << std::endl;
    }
}

void startProcess()
{
    std::promise<int> pi;
    std::shared_future<int> fut;
    bool ret = fut.valid();
    fut = pi.get_future().share();
    std::cout << fut.valid() << std::endl;
    std::thread th1(get_input, std::ref(pi));
    std::thread th2(printSth, std::ref(fut));

    th1.join();
    th2.join();
    std::promise<int> pi2;
    pi.swap(pi2);
    std::cout << fut.get() << std::endl;
}

int main()
{
    try
    {
        mmServerTcpProxy* proxy = new mmServerTcpProxy();
       
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