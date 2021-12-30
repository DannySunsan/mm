#include "mmUtility\tcp\DataBuffer.h"
//#include <malloc.h>

DataBuffer::DataBuffer() :
    _p(nullptr),
    _nlen(0),
    _nHead(0)
{
}
DataBuffer::~DataBuffer()
{
    clear();
}
DataBuffer::DataBuffer(const char* s, int nlen)
{
    push(s, nlen);
}
DataBuffer::DataBuffer(const DataBuffer& buf)
{
    this->push(buf.begin(), buf.Len());
}

int DataBuffer::Len() const
{
    return _nlen;
}
char* DataBuffer::begin() const
{
    return _p;
}
char* DataBuffer::last() const
{
    return _p + _nlen;
}
char* DataBuffer::end() const
{
    return last() + 1;
}
char* DataBuffer::head() const
{
    return begin() + _nHead;
}
int DataBuffer::reserve() const
{
    return -_nHead + _nlen;
}
void DataBuffer::clear()
{
    if (_p)
    {
        free(_p);
        _p = nullptr;
        _nlen = 0;
        _nHead = 0;
    }
}
DataBuffer DataBuffer::operator<<(const std::string str)
{   
    return DataBuffer(str.data(), str.length());
}

DataBuffer DataBuffer::operator=(const DataBuffer& buf)
{

    return DataBuffer(buf.begin(), buf.Len());
}

void DataBuffer::push(const char* s, int nlen)
{
    size_t newSize = nlen + _nlen;
    char* p = (char*)realloc(_p , newSize);
    if (p == nullptr)
        return;
    _p = p;
    memcpy(last(), s, nlen);
}

DataBuffer DataBuffer::pop(int nlen)
{
    int nReserve = reserve();
    if (nlen <= nReserve)
    {
        _nHead += nlen;
        return DataBuffer(head(), nlen);
    }
    else
    {
        _nHead += nReserve;
        return DataBuffer(head(), nReserve);
    }
}