#pragma once
#include "boost\asio.hpp"
#include "mmConnectionData.h"
BEGIN_NAMESPACE_MM
class mmTcpClientConnection : public mmConnectionData
{
public:
    mmTcpClientConnection(TCPProxy* proxy);

    void connect(const char* ip, unsigned short port);
    void send(char* s, unsigned int len);
    void read();
    boost::asio::ip::tcp::socket& socket() {
        return socket_;
    }
    void close();
private:
    void send();
private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::resolver resolver_;
    std::thread th_;
};
END_NAMESPACE_MM
