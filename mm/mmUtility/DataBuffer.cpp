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
DataBuffer::DataBuffer(char* s, unsigned int nlen):
    _p(nullptr),
    _nlen(0),
    _nHead(0)
{
    push(s, nlen);
}
DataBuffer::DataBuffer(const DataBuffer& buf):
    _p(nullptr),
    _nlen(0),
    _nHead(0)
{
    push(buf.begin(), buf.Len());
}

unsigned int DataBuffer::Len() const
{
    return _nlen;
}
char* DataBuffer::begin() const
{
    return _p;
}
char* DataBuffer::last() const
{
    return _nlen < 1 ?_p : _p + _nlen - 1;
}
char* DataBuffer::end() const
{
    return _nlen == 0? _p: last() + 1;
}
char* DataBuffer::head() const
{
    return begin() + _nHead;
}
int DataBuffer::reserve() const
{
    return _nlen -_nHead;
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
    return DataBuffer((char*)str.data(), str.length());
}

DataBuffer DataBuffer::operator=(const DataBuffer& buf)
{

    return DataBuffer(buf.begin(), buf.Len());
}

void DataBuffer::push(char* s, unsigned int nlen)
{
    unsigned int newSize = nlen + _nlen;

    if (_p == nullptr)
    {
        _p = (char*)malloc(newSize);
    }
    else
    {
        char* p = (char*)realloc(_p, newSize);
        if (p == nullptr)
            return;
        _p = p;
    }
    if (_p == nullptr)
        return;
   
    memcpy(end(), s, nlen);
    _nlen = newSize;
}

unsigned int DataBuffer::pop(unsigned int nlen)
{
    int nPop = data(nlen);   
    _nHead += nPop;
    return nPop;
}

unsigned int DataBuffer::data(unsigned int nlen)
{
    unsigned int nReserve = reserve();
    int nData = nlen;
    if (nData > nReserve)
    {
        nData = nReserve;
    }
    return nData;
}