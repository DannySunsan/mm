#pragma once
template<typename T>
class RefCounterPtr
{
public:
    RefCounterPtr(const T* p=nullptr);
    RefCounterPtr(const RefCounterPtr<T>& p);
    ~RefCounterPtr();
    T* Get();
    RefCounterPtr<T>& operator=(const RefCounterPtr<T>& p);

private:
    T* _p;
    int _count;
};