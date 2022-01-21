#include "mmUtility\tcp\connectMsg.h"
#include "boost\thread.hpp"
mmTcpServerConnection::pointer connectMsg::operator[](std::string ip)
{
    auto itFind = mapConnections.find(ip);
    if (itFind != mapConnections.end())
    {
        return itFind->second;
    }
    else
    {
        return nullptr;
    }
}

void connectMsg::add(std::string ip, mmTcpServerConnection::pointer p)
{
    mapConnections[ip] = p;  
    p->init();
}