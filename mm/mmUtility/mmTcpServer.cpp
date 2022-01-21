#include "mmUtility\tcp\mmTcpServer.h"
#include <iostream>
#include "boost\thread.hpp"
#include "boost\function.hpp"
mmTcpServer::mmTcpServer(unsigned short usPort,TCPProxy* proxy)
    :m_proxy(proxy),acceptor_(m_io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), usPort))
{
    listen();
}
mmTcpServer::~mmTcpServer()
{
    stop();
}
void mmTcpServer::listen()
{
    acceptor_.listen();
    start_accept();
}

void mmTcpServer::run()
{
    m_io_context.run();
}
void mmTcpServer::stop()
{
   m_io_context.stop();
}

void mmTcpServer::restart()
{
    m_io_context.restart();
}

void mmTcpServer::start_accept()
{
    mmTcpServerConnection::pointer new_connection =
        mmTcpServerConnection::create(m_io_context, m_proxy);

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&mmTcpServer::handle_accept, this, new_connection,
            boost::asio::placeholders::error));
}

void mmTcpServer::handle_accept(mmTcpServerConnection::pointer new_connection,
    const boost::system::error_code& error)
{
    if (!error)
    {
        m_Connections.add(new_connection->socket().remote_endpoint().address().to_string(), new_connection);
        std::cout << acceptor_.local_endpoint().address().to_string() << ":" << acceptor_.local_endpoint().port() << std::endl;
    }
}

mmTcpServerConnection::pointer mmTcpServer::getConnection(std::string ip)
{
    return m_Connections[ip];
}

