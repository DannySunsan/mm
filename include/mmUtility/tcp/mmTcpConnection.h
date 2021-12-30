#pragma once
#include "boost\asio.hpp"
#include "boost\shared_ptr.hpp"
#include "boost\enable_shared_from_this.hpp"
#include "boost\bind.hpp"
#include "DataBuffer.h"
#include "boost\array.hpp"
class mmTcpConnection : public boost::enable_shared_from_this<mmTcpConnection>
{
public:
    typedef boost::shared_ptr<mmTcpConnection> pointer;

    static pointer create(boost::asio::io_context& io_context);

    boost::asio::ip::tcp::socket& socket();
    void send(char* s, int len);
    void receive(char* s, int len);
    void write(char* s, int len);
    void read();
    void connect(const char* ip, unsigned short uiport);
protected:
    void send();
    void receive();
    void write();
private:
    mmTcpConnection(boost::asio::io_context& io_context);
    void handle_write(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);
    void handle_read(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);
    void handle_connect(const boost::system::error_code& /*error*/);
    void handle_send(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);
    void handle_receive(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);
private:
    boost::asio::ip::tcp::socket socket_;
    DataBuffer recvBuf;
    DataBuffer sendBuf;
    boost::array<char, 1024> cache;
};