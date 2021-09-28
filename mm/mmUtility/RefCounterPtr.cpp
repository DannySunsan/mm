#include <atomic>
#include "RefCounterPtr.h"
template<typename T>
RefCounterPtr<T>::RefCounterPtr(const T* p)
{
    _p = p;
    if (_p == nullptr)
    {
        _p = new T();       
    }
    ++_count;
}

template<typename T>
RefCounterPtr<T>::~RefCounterPtr()
{
    --_count;
    if (_count == 0)
    {
        delete _p;
        _p = nullptr;
    }
}

template<typename T>
RefCounterPtr<T>::RefCounterPtr(const RefCounterPtr<T>& p)
{
    if (this != &p)
    {
        _p = p._p;
        ++_count;
    }
}

template<typename T>
RefCounterPtr<T>& RefCounterPtr<T>::operator=(const RefCounterPtr<T>& p)
{
    if (this == &p)
    {
        return *this;
    }
    ++p._count;
    if (--_count == 0)
    {
        delete _p;        
    }
    _p = p._p;
    ++_count;
    return *this;
}

template<typename T>
T* RefCounterPtr<T>::Get()
{
    return _p;
}