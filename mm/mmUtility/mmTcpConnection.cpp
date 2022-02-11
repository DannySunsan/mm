#include "mmUtility\tcp\connectMgn.h"
#define SENDSIZE        1024
#include <iostream>
#include "boost\thread.hpp"
mmConnectionData::mmConnectionData(TCPProxy* proxy):
    m_proxy(proxy)
{
}
mmConnectionData::~mmConnectionData()
{
}
void mmConnectionData::resetData()
{
    ZeroMemory(&_fmt, sizeof(DataFormat));
    recvBuf.clear();
    sendBuf.clear();
}

void mmConnectionData::dataProcess(char* s, unsigned int uLen)
{
    recvBuf.push(s, uLen);
    switch (_fmt.state)
    {
    case eStateReceive::start:
        setDataState();
        break;
    case eStateReceive::receiving:
        dealReveiving();
        break;
    default:
        dealData();
        break;
    }
}

void mmConnectionData::setDataState()
{
    std::cout << "start" << std::endl;
    if (recvBuf.Len() < sizeof(TCPMsgHead))
        return;//error
    //if (recvBuf.Len() > sizeof(TCPMsgHead))
    //{
    //    recvBuf.clear();
    //    return;
    //}
    char* head = recvBuf.head();
    _fmt.head = *(TCPMsgHead*)(head);
    std::cout << "Data Len: " << _fmt.head.len << std::endl;

    if (recvBuf.reserve() == _fmt.head.len)
    {
        dealData();
    }
    else
        _fmt.state = eStateReceive::receiving;

   
}

void mmConnectionData::dealReveiving()
{
    std::cout << "receiving" << std::endl;
    if (recvBuf.Len() < _fmt.head.len)
        return;
    dealData();
    _fmt.state = eStateReceive::end;
    std::cout << "end" << std::endl;
}

void mmConnectionData::dealData()
{
    m_proxy->handleProcess(recvBuf.head(), recvBuf.Len());
    _fmt = DataFormat();
    recvBuf.clear();
}

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
    io_context_.run();
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
    sendBuf.push((char*)&data->head, sizeof(TCPMsgHead));
    sendBuf.push(data->s, len-sizeof(TCPMsgHead));    
    if (data->s)
    {
        delete[] data->s;
        data->s = nullptr;
    }
    send();
}

void mmTcpClientConnection::send()
{
    boost::asio::async_write(socket_,boost::asio::buffer(sendBuf.head(),sendBuf.data(SENDSIZE)),
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
    boost::asio::async_read(socket_,boost::asio::buffer(cache),
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

mmTcpServerConnection::mmTcpServerConnection(boost::asio::ip::tcp::socket& socket, connectMgn& connectMgn, TCPProxy* proxy)
    : mmConnectionData(proxy) ,
    socket_(std::move(socket)),
    m_connectMgn(connectMgn)
{
}
void mmTcpServerConnection::init()
{  
    std::string addr = socket_.remote_endpoint().address().to_string();
    int nPort = socket_.remote_endpoint().port();
    std::cout << addr << ":"<<nPort << " has been connected!" << std::endl;
    m_connectMgn.add(addr, boost::enable_shared_from_this<mmTcpServerConnection>::shared_from_this());
    receive();
}
void mmTcpServerConnection::close()
{
    std::string addr = socket_.remote_endpoint().address().to_string();
    m_connectMgn.remove(addr);
}
mmTcpServerConnection::pointer mmTcpServerConnection::create(boost::asio::ip::tcp::socket socket, connectMgn& connectMgn, TCPProxy* proxy)
{
    return pointer(new mmTcpServerConnection(socket, connectMgn,proxy));
}

boost::asio::ip::tcp::socket& mmTcpServerConnection::socket()
{
    return socket_;
}


void mmTcpServerConnection::write(char* s, unsigned int len)
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
    write();
}

void mmTcpServerConnection::write()
{
    auto self(boost::enable_shared_from_this<mmTcpServerConnection>::shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(sendBuf.head(), sendBuf.data(SENDSIZE)),
        [this, self](const boost::system::error_code& error,
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
                    write();
                }
            }
            else
            {
                sendBuf.clear();
                close();
            }
        });
}


void mmTcpServerConnection::receive()
{   
    /*This is done in order to make sure that connection object outlives the asynchronous operation : 
    as long as the lambda is alive(i.e.the async.operation is in progress), 
        the connection instance is alive as well.*/
    auto self(boost::enable_shared_from_this<mmTcpServerConnection>::shared_from_this());
    boost::asio::async_read(socket_, boost::asio::buffer(cache),[this, self](const boost::system::error_code& error,
            size_t bytes_transferred)
            {
                if (!error)
                {
                    dataProcess(cache.data(), bytes_transferred);
                    receive();
                }
                else
                {
                    close();
                }
            }
    );
}