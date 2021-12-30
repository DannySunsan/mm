#pragma once
#include<string>
class DataBuffer
{
public:
    DataBuffer();
    ~DataBuffer();
    DataBuffer(const char* s, int nlen);
    DataBuffer(const DataBuffer&);
    int Len() const;
    void clear();
    void push(const char*, int nlen);
    DataBuffer pop(int nlen);
    int reserve() const;

    DataBuffer operator<<(const std::string str);
    DataBuffer operator=(const DataBuffer&);    

    char* begin() const;
    char* last() const;
    char* end() const;
    char* head() const;   
private:
    char* _p;
    int _nlen;
    int _nHead;
};