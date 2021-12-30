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

#pragma pack(1)
struct Cell
{
    int i;
    char p;
    double d;
};
#pragma pack()

typedef int(*func)();
typedef int(*func2)(std::string& strFile);
#define Func(Name,Num) myHashSet.Name(Num)
using namespace std;
void testCmmUtility();

void testStringSplit();
void testHashTable();
void testXmlParser();
void testXmlWrite();
void startProcess();
void processWorks();
void shareWorks();
void multiThread();
int main()
{
    Cell c;
    c.i = 4;
    c.p = 1;
    c.d = 8.;
    int nLen = sizeof(Cell);
    BYTE* b = new BYTE[nLen];
    memset(b,0b00000000,nLen);
    *b = 4;
    *(b + 4) = 1;
    *(b + 8) = 8;
   


    Cell n = *(Cell*)(b);
    cout << n.i << n.p << n.d;
    //testCmmUtility();
    //startProcess();
    //processWorks();
    //testCmmUtility();
   // multiThread();
    //shareWorks();
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



    //* . //
    bool isMatch(string s, string p)
    {
        if (p.length() ==0 && s.length() == 0)
            return true;
        if (p.length() == 0 && s.length() > 0)
            return false;
        //处理* p[1] = '*'  特殊情况 '.*'
        if (p.length() > 1&&p[1]=='*')
        {
            char c = p[0];
            p.erase(p.begin(), p.begin() + 1);
            if(s.length() == 0)
                return isMatch(s, p);
            if (c == s[0] || c == '.')
            {
                if (c == s[0])
                {
                   
                }
                else
                {

                }
            }
            else
            {
                s.erase(s.begin());
            }
            
        }
        else
        {
            if (s.length() == 0)
                return false;
            if (p[0] == s[0] || p[0] == '.')
            {
                p.erase(p.begin());
                s.erase(s.begin());
            }        
        }
        return isMatch(s,p);
    }

    void get_input(std::promise<int>& pi)
    {
        
        {
            int x;
            cout << "Enter an inter va==\n";
            std::cin.exceptions(std::ios::failbit);

            try
            {
                std::cin >> x;
                pi.set_value(x);
            }
            catch (std::exception&)
            {
                pi.set_exception(std::current_exception());
            }
        }
        
    }

    void printSth(std::future<int>& fut)
    {
        {
            try
            {
                int x = fut.get();
                cout << x << endl;
            }
            catch (std::exception& e)
            {
                cout << "exception" << e.what() << endl;
            }
        }       
    }
    void fff()
    {
        for (int i = 0; i < 5; ++i)
        {
            cout << this_thread::get_id() << " : " << i << endl;
        }
    }
    void startProcess() 
    {
        /*std::promise<int> pi;
        std::future<int> fut = pi.get_future();

        std::thread th1(get_input, std::ref(pi));
        std::thread th2(printSth, std::ref(fut));

        th1.join();
        th2.join();*/

        /*for (int i = 0; i < 10; ++i)
        {
            Sleep(1000);
            cout << i << endl;
        }*/
        mutex mu;
        condition_variable cdv;
        bool bLock = false;
        xtime t;
        t.sec = 1;
        thread th1([&]
            {
                for (;;)
                {
                    {
                        std::unique_lock<std::mutex> lock(mu);
                        while (cdv.wait_until(lock, &t) == std::cv_status::timeout) {
                            std::cout << this_thread::get_id() << '.' << std::endl;
                        }

                      /*  cdv.wait(lock,
                            [&bLock] { return bLock; });*/

                        bLock = false;
                    }
                    fff();
                }
                
            }
        );

        thread th2([&]
            {
                for (;;)
                {
                    {
                        std::unique_lock<std::mutex> lock(mu);
                        while (bLock&&cdv.wait_for(lock, std::chrono::seconds(1)) == std::cv_status::timeout) {
                            std::cout << this_thread::get_id() <<'.' << std::endl;
                        }
                        
                        /*cdv.wait(lock,
                            [&bLock] { return bLock; });*/

                        bLock = false;
                    }
                    fff();
                }        
            }
        );

        for(;;)
        {
            {
                std::unique_lock<std::mutex> lock(mu);
                bLock = true;              
            } 
            Sleep(5000);
            cdv.notify_one();
        }
    }



    void processWorks()
    {
        std::packaged_task<int(int)> task([](int total) {
            for (int i = 0; i < total; ++i)
            {
                Sleep(1000);
                cout << this_thread::get_id() << " : " << i << endl;
            }
            
            return total;
            });

        std::future<int> fut = task.get_future();       
        
        task(3);
        std::cout << fut.get() << std::endl;//此处会等待task执行完成，并返回结果
        
        task.reset();//重置 packaged_task 的共享状态       
        fut = task.get_future();
        std::thread(std::move(task), 5).detach();
        std::cout << fut.get() << std::endl;//此处会等待task执行完成，并返回结果
    }

    void shareWorks()
    {
        std::future<int> fut = async([] {
            cout << "async\n";
            return 1;
            });
        std::shared_future<int> sFut = fut.share();

        // 共享的 future 对象可以被多次访问.
        std::cout << sFut.get() << std::endl;
        std::cout << sFut.get() << std::endl;
    }

