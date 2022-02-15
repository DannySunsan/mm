#include "mmUtility\tcp\connectMgn.h"
#include <iostream>
BEGIN_NAMESPACE_MM
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

void mmTcpServerConnection::sync_close()
{
    socket_.close();
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
    socket_.async_read_some(boost::asio::buffer(cache),[this, self](const boost::system::error_code& error,
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
END_NAMESPACE_MM