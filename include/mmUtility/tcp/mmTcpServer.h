#pragma once
#include "boost\asio.hpp"
#include "connectMsg.h"

class mmTcpServer
{
public:  
    mmTcpServer(unsigned short usPort, TCPProxy* proxy);
    virtual ~mmTcpServer();
    void start_accept();
    void handle_accept(mmTcpServerConnection::pointer new_connection,
        const boost::system::error_code& error);
    virtual void listen();

    virtual void run();
    virtual void stop();
    virtual void restart();
    virtual mmTcpServerConnection::pointer getConnection(std::string ip);
protected:
    mmTcpServer() = default;
private:
    boost::asio::io_context m_io_context;
    boost::asio::ip::tcp::acceptor acceptor_;  
    connectMsg m_Connections;
    TCPProxy* m_proxy;
};