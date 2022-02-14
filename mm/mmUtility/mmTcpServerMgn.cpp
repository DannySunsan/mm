#include "export.h"
#include "mmUtility\tcp\mmTcpServerMgn.h"
#include "boost\thread.hpp"
#include <iostream>
mmTcpServerMgn::mmTcpServerMgn(unsigned short usPort, TCPProxy* proxy):
    m_io()   
{
    m_server = new mmTcpServer(m_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), usPort), proxy);
    std::cout << "server start success, port: " << usPort << std::endl;
    th_ = std::thread([this]() { m_io.run(); });
}

mmTcpServerMgn::~mmTcpServerMgn()
{
    if (m_server)
    {
        delete m_server;
        m_server = nullptr;
    }
}

void mmTcpServerMgn::send(std::string ip, char* s, unsigned int len)
{
    m_server->send(ip, s, len);           
}

void mmTcpServerMgn::setProxy(TCPProxy* proxy)
{
    m_server->setProxy(proxy);
}

void mmTcpServerMgn::broadcast(char* s, unsigned int len)
{
    m_server->broadcast( s, len);
}