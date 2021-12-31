#include "mmUtility\tcp\mmTcpConnection.h"
#define SENDSIZE        1024

mmTcpClientConnection::mmTcpClientConnection()
    : socket_(io_context)
{
}
bool mmTcpClientConnection::connect(boost::asio::ip::tcp::endpoint endp)
{
    boost::system::error_code ec;
    socket_.connect(endp, ec);
    return ec.failed();
}

void mmTcpClientConnection::send(char* s, int len)
{
    sendBuf.clear();
    sendBuf.push(s, len);
    send();
}

void mmTcpClientConnection::send(const char* s)
{
    sendBuf.clear();
    sendBuf.push(s, sizeof(s));
    send();
}

void mmTcpClientConnection::send()
{
    DataBuffer send = sendBuf.pop(SENDSIZE);

    socket_.async_send(boost::asio::buffer(send.begin(), send.Len()), 
        boost::bind(&mmTcpClientConnection::handle_send,this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}


void mmTcpClientConnection::receive()
{
    socket_.async_receive(boost::asio::buffer(cache),
        boost::bind(&mmTcpClientConnection::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void mmTcpClientConnection::handle_receive(const boost::system::error_code& error,
    size_t bytes_transferred)
{
    if (!error)
    {
        recvBuf.push(cache.data(), bytes_transferred);
        receive();
    }
}

mmTcpConnection::mmTcpConnection(boost::asio::io_context& io_context)
    : socket_(io_context)
{

}

mmTcpConnection::pointer mmTcpConnection::create(boost::asio::io_context& io_context)
{
    return pointer(new mmTcpConnection(io_context));
}

boost::asio::ip::tcp::socket& mmTcpConnection::socket()
{
    return socket_;
}


void mmTcpClientConnection::handle_send(const boost::system::error_code& error,
    size_t bytes_transferred)
{
    if (!error)
    {
        send();
    }
}


void mmTcpConnection::write(char* s, int len)
{
    sendBuf.clear();
    sendBuf.push(s, len);
    write();

}

void mmTcpConnection::write()
{
    DataBuffer send = sendBuf.pop(SENDSIZE);
    boost::asio::async_write(socket_, boost::asio::buffer(send.begin(),send.Len()),
        boost::bind(&mmTcpConnection::handle_read, boost::enable_shared_from_this<mmTcpConnection>::shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void mmTcpConnection::handle_write(const boost::system::error_code& error,
    size_t bytes_transferred)
{
    if (!error)
    {
        write();
    }
}

void mmTcpConnection::read()
{
    boost::asio::async_read(socket_, boost::asio::buffer(cache),
        boost::bind(&mmTcpConnection::handle_read, boost::enable_shared_from_this<mmTcpConnection>::shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void mmTcpConnection::handle_read(const boost::system::error_code& error,
    size_t bytes_transferred)
{
    if (!error)
    {
        recvBuf.push(cache.data(), bytes_transferred);
        read();       
    }
}

