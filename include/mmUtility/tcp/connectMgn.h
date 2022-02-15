#pragma once
#include <string>
#include <unordered_map>
#include "mmUtility\tcp\mmTcpConnection.h"

BEGIN_NAMESPACE_MM
class connectMgn
{
public:
    connectMgn();
    void add(std::string ip,mmTcpServerConnection::pointer);
    void remove(std::string ip);
    void close();
    mmTcpServerConnection::pointer operator[](std::string ip);
    virtual ~connectMgn() = default;
    std::unordered_map<std::string, mmTcpServerConnection::pointer>& getConnections()
    {
        return m_mapConnections;
    };
private:  
    std::unordered_map<std::string, mmTcpServerConnection::pointer> m_mapConnections;
};
END_NAMESPACE_MM