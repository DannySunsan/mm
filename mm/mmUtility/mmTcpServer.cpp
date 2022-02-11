#include "mmUtility\tcp\mmTcpServer.h"
#include "mmUtility\tcp\mmTcpConnection.h"

#include <iostream>
#include "boost\thread.hpp"
#include "boost\function.hpp"
#include <memory>
mmTcpServer::mmTcpServer(boost::asio::io_context& io_context, 
    const boost::asio::ip::tcp::endpoint& endpoint,
    TCPProxy* proxy):
    m_proxy(proxy),
    m_bStop(false),
    m_acceptor(io_context, endpoint)
{
    
    start_accept();
}
mmTcpServer::~mmTcpServer()
{
    stop();
}

void mmTcpServer::stop()
{
    m_bStop = true;
    //m_Connections.stop();
}

void mmTcpServer::setProxy(TCPProxy* proxy)
{
    m_proxy = proxy;
}

void mmTcpServer::send(std::string ip, char* s, unsigned int len)
{
    mmTcpServerConnection::pointer p = m_connectMgn[ip];
    if (p)
    {
        p->write(s,len);
        std::cout << "send to " << ip << std::endl;
    }
}

void mmTcpServer::broadcast(char* s, unsigned int len)
{
    std::unordered_map<std::string, mmTcpServerConnection::pointer> Connections = m_connectMgn.getConnections();
    for (auto p = Connections.begin(); p != Connections.end(); p++)
    {
        p->second->write(s, len);
        std::cout << "send to " << p->first << std::endl;
    }
}

void mmTcpServer::start_accept()
{    
    m_acceptor.async_accept(
        [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                mmTcpServerConnection::create(std::move(socket), m_connectMgn, m_proxy)->init();
            }

            start_accept();
        });
}
