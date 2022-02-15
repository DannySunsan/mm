#include "mmUtility\tcp\mmTcpClientConnection.h"
#include "boost\thread.hpp"
#include <iostream>
BEGIN_NAMESPACE_MM
mmTcpClientConnection::mmTcpClientConnection(TCPProxy* proxy)
    : mmConnectionData(proxy),
    io_context_(),
    socket_(io_context_),
    resolver_(io_context_)

{
}


void mmTcpClientConnection::connect(const char* ip, unsigned short port)
{
    recvBuf.clear();
    sendBuf.clear();
    auto endpoints = resolver_.resolve(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip), port));

    boost::asio::async_connect(socket_, endpoints,
        [this](boost::system::error_code ec, boost::asio::ip::tcp::endpoint ep)
        {
            if (!ec)
            {
                std::cout << "connect to :" << ep.address().to_string() << ",ok\n";
                read();
            }
            else
            {
                std::cout << "connect to :" << ep.address().to_string() << ",false\n";
            }
        });
    th_ = std::thread([this]() { io_context_.run(); });
}

void mmTcpClientConnection::close()
{
    th_.join();
    boost::asio::post(io_context_, [this]() { socket_.close(); });
}

void mmTcpClientConnection::send(char* s, unsigned int len)
{
    sendBuf.clear();
    TCPData* data = (TCPData*)s;
    if (data == nullptr)
        return;
    sendBuf.push((char*)& data->head, sizeof(TCPMsgHead));
    sendBuf.push(data->s, len - sizeof(TCPMsgHead));
    if (data->s)
    {
        delete[] data->s;
        data->s = nullptr;
    }
    send();
}

void mmTcpClientConnection::send()
{
    boost::asio::async_write(socket_, boost::asio::buffer(sendBuf.head(), sendBuf.data(SENDSIZE)),
        [this](const boost::system::error_code& error,
            size_t bytes_transferred)
        {
            if (!error)
            {
                sendBuf.pop(SENDSIZE);
                if (sendBuf.head() == sendBuf.end())
                {
                    sendBuf.clear();
                }
                else
                {
                    send();
                }
            }
            else
            {
                close();

            }
        }
    );
}

void mmTcpClientConnection::read()
{
    socket_.async_read_some(boost::asio::buffer(cache),
        [this](const boost::system::error_code& error,
            size_t bytes_transferred)
        {
            if (!error)
            {
                dataProcess(cache.data(), bytes_transferred);
                read();
            }
            else
            {
                close();
            }
        });
}
END_NAMESPACE_MM