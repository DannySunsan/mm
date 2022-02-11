#include "mmUtility\tcp\connectMgn.h"
#include "boost\thread.hpp"
#include <memory>
connectMgn::connectMgn()
{

}

mmTcpServerConnection::pointer connectMgn::operator[](std::string ip)
{
    auto itFind = m_mapConnections.find(ip);
    if (itFind != m_mapConnections.end())
    {
        return itFind->second;
    }
    else
    {
        return nullptr;
    }
}

void connectMgn::add(std::string ip, mmTcpServerConnection::pointer p)
{
    m_mapConnections[ip] = p;
}

void connectMgn::remove(std::string ip)
{
    auto itFind = m_mapConnections.find(ip);
    if (itFind != m_mapConnections.end())
    {
        m_mapConnections.erase(itFind);
    }
}