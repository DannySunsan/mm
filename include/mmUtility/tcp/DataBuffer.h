#pragma once
#include<string>
#include "common\mm_define.h"
BEGIN_NAMESPACE_MM
class DataBuffer
{
public:
    DataBuffer();
    ~DataBuffer();
    DataBuffer(char* s, unsigned int nlen);
    DataBuffer(const DataBuffer&);
    unsigned int Len() const;
    void clear();
    void push(char*, unsigned int nlen);
    unsigned int pop(unsigned int nlen);
    int reserve() const;
    unsigned int data(unsigned int nlen);

    DataBuffer operator<<(const std::string str);
    DataBuffer operator=(const DataBuffer&);    

    char* begin() const;
    char* last() const;
    char* end() const;
    char* head() const;   
private:
    char* _p;
    unsigned int _nlen;
    unsigned int _nHead;
};
END_NAMESPACE_MM