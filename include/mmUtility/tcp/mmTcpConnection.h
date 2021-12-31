#pragma once
#include "boost\asio.hpp"
#include "boost\shared_ptr.hpp"
#include "boost\enable_shared_from_this.hpp"
#include "boost\bind.hpp"
#include "DataBuffer.h"
#include "boost\array.hpp"

class mmTcpClientConnection
{
public:
    mmTcpClientConnection();

    bool connect(boost::asio::ip::tcp::endpoint endp);
    void send(char* s, int len);
    void send(const char* s);
    void receive();
private:
    void send();
    void handle_send(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);
    void handle_receive(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);
private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket_;
    DataBuffer recvBuf;
    DataBuffer sendBuf;
    boost::array<char, 1024> cache;
};

class mmTcpConnection : public boost::enable_shared_from_this<mmTcpConnection>
{
public:
    typedef boost::shared_ptr<mmTcpConnection> pointer;

    static pointer create(boost::asio::io_context& io_context);

    boost::asio::ip::tcp::socket& socket();
    void write(char* s, int len);
    void read();
   
private:
    void write();

    mmTcpConnection(boost::asio::io_context& io_context);
    void handle_write(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);
    void handle_read(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);
private:
    boost::asio::ip::tcp::socket socket_;
    DataBuffer recvBuf;
    DataBuffer sendBuf;
    boost::array<char, 1024> cache;
};