#pragma once
#include "boost\asio.hpp"
#include "mmTcpConnection.h"
class mmTcpServer
{
public:
    mmTcpServer(unsigned short usPort);
    void start_accept();
    void handle_accept(mmTcpConnection::pointer new_connection,
        const boost::system::error_code& error);
    void listen();

    void run();
    void stop();
    void restart();
private:
    //boost::asio::ip::tcp::acceptor acceptor_;
   // boost::asio::io_context m_io_context;
};