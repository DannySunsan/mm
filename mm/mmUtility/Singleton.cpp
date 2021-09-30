#include "Singleton.h"
template<typename T>
Singleton<T>* Singleton<T>::GetInstance()
{
    if (s_pSigleton == nullptr)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (s_pSigleton == nullptr)
            s_pSigleton = new Singleton<T>();     
    }
    return s_pSigleton;
}