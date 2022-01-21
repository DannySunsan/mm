#include "mmUtility\tcp\mmTcpConnection.h"
#define SENDSIZE        1024
#include <iostream>
#include "boost\thread.hpp"
mmConnectionData::mmConnectionData(TCPProxy* n_proxy)
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
    if (recvBuf.Len() > sizeof(TCPMsgHead))
    {
        recvBuf.clear();
        return;
    }
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
    n_proxy->handleProcess(recvBuf.head(), recvBuf.Len());
    _fmt = DataFormat();
    recvBuf.clear();
}

//void mmConnectionData::handleProcess(char* s, unsigned int nlen)
//{
//    std::cout << "mmConnectionData::handleProcess " << std::endl;
//}

mmTcpClientConnection::mmTcpClientConnection(TCPProxy* proxy)
    : mmConnectionData(n_proxy), 
     socket_(io_context)
{
}


bool mmTcpClientConnection::connect(boost::asio::ip::tcp::endpoint endp)
{
    boost::system::error_code ec;
    if (!socket_.connect(endp, ec))
    {
        boost::thread([&]()
            {
                for (;;)
                {
                    while (!task_.valid());
                    fut_ = task_.get_future().share();
                    while (fut_.get()&& sendBuf.Len()>0)
                    {
                        send();
                    }
                    task_.reset();
                }
              

            });
        
    }

    return !ec.failed();
}

void mmTcpClientConnection::send(char* s, unsigned int len)
{
    setTask(s,len);
}

void mmTcpClientConnection::send()
{
    char* head = sendBuf.head();
    std::unique_lock<std::mutex> lock(m_mutex);
    socket_.async_send(boost::asio::buffer(head, sendBuf.pop(SENDSIZE)),
        boost::bind(&mmTcpClientConnection::handle_send,this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void mmTcpClientConnection::handle_send(const boost::system::error_code& error,
    size_t bytes_transferred)
{
    if (!error)
    {
        if (sendBuf.head() == sendBuf.end())
        {
            sendBuf.clear();
        }
    }
  
}

void mmTcpClientConnection::read()
{
    socket_.wait(socket_.wait_read);
    std::unique_lock<std::mutex> lock(m_mutex);
    socket_.async_read_some(boost::asio::buffer(cache),
        boost::bind(&mmTcpClientConnection::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void mmTcpClientConnection::handle_read(const boost::system::error_code& error,
    size_t bytes_transferred)
{
    if (!error)
    {
        dataProcess(cache.data(), bytes_transferred);
    }
}

void mmTcpClientConnection::sync_send(char* s, unsigned int len)
{

}

void mmTcpClientConnection::sync_send(const char* s)
{

}

void mmTcpClientConnection::sync_read()
{

}

mmTcpServerConnection::mmTcpServerConnection(boost::asio::io_context& io_context, TCPProxy* proxy)
    : mmConnectionData(proxy),
    socket_(io_context)
{
    
}
void mmTcpServerConnection::init()
{
    boost::thread th([&]()
        {
            for (;;)
            {
                receive();
            }
        }
    );
    boost::thread([this] {
        for (;;)
        {
            fut_ = proIn_.get_future().share();
            while (fut_.get() && sendBuf.Len() > 0)
            {
                write();
            }
            std::promise<bool> pro;
            proIn_.swap(pro);

            fut_ = proIn_.get_future().share();
        }
        });
}
mmTcpServerConnection::pointer mmTcpServerConnection::create(boost::asio::io_context& io_context, TCPProxy* proxy)
{
    return pointer(new mmTcpServerConnection(io_context, proxy));
}

boost::asio::ip::tcp::socket& mmTcpServerConnection::socket()
{
    return socket_;
}


void mmTcpServerConnection::write(char* s, unsigned int len)
{
    while (fut_.get());
    char* HeadSize = (char*)& len;
    sendBuf.push(HeadSize, sizeof(unsigned int));

    sendBuf.push(s, len); 
    proIn_.set_value(true);
}

void mmTcpServerConnection::write()
{
    char* head = sendBuf.head();
    std::unique_lock<std::mutex> lock(m_mutex);
    boost::asio::async_write(socket_, boost::asio::buffer(head, sendBuf.pop(SENDSIZE)),
        boost::bind(&mmTcpServerConnection::handle_write, boost::enable_shared_from_this<mmTcpServerConnection>::shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void mmTcpServerConnection::handle_write(const boost::system::error_code& error,
    unsigned int bytes_transferred)
{
    if (!error)
    {
        if (sendBuf.head() == sendBuf.end())
        {
            sendBuf.clear();
        }
    }
}

void mmTcpServerConnection::receive()
{ 
    std::unique_lock<std::mutex> lock(m_mutex);
    socket_.async_receive(boost::asio::buffer(cache),
        boost::bind(&mmTcpServerConnection::handle_receive, boost::enable_shared_from_this<mmTcpServerConnection>::shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void mmTcpServerConnection::handle_receive(const boost::system::error_code& error,
    unsigned int bytes_transferred)
{
    if (!error)
    {
        dataProcess(cache.data(), bytes_transferred);     
    }
}