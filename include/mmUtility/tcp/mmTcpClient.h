#pragma once
#include "boost\asio.hpp"
#include "mmTcpConnection.h"
class mmTcpClient
{
public:
    mmTcpClient(boost::asio::ip::tcp::endpoint ep);
    void connect();
    void send();
    void handle_send(mmTcpConnection::pointer new_connection,
        const boost::system::error_code& error);
private:
    boost::asio::ip::tcp::endpoint m_ep;
    boost::asio::io_context m_io_context;
};