#pragma once
#include<mutex>
template<typename T>
class Singleton
{
public:
    static Singleton<T>* GetInstance();
private:
    std::mutex m_mutex;
    static Singleton<T>* s_pSigleton;
};

