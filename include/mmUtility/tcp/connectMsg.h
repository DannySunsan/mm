#pragma once
#include <string>
#include "mmTcpConnection.h"
#include <unordered_map>

class connectMsg
{
public:
    void add(std::string ip, mmTcpServerConnection::pointer p);
    mmTcpServerConnection::pointer operator[](std::string ip);
    connectMsg() = default;
    virtual ~connectMsg() = default;
private:
    std::unordered_map<std::string, mmTcpServerConnection::pointer> mapConnections;  
};