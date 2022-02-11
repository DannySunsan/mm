#pragma once
#include "boost\asio.hpp"
#include "connectMgn.h"
#include "mmTcpProxy.h"
class mmTcpServer:public std::unique_ptr<mmTcpServer>
{
public:  
    typedef std::unique_ptr<mmTcpServer> pointer;
    mmTcpServer(boost::asio::io_context& io_context,
        const boost::asio::ip::tcp::endpoint& endpoint,
        TCPProxy* m_proxy);
    virtual ~mmTcpServer();
    void start_accept();
    virtual void stop();
    virtual void send(std::string ip, char* s, unsigned int len);
    void broadcast(char* s, unsigned int len);
    void setProxy(TCPProxy* proxy);
protected:
    mmTcpServer() = default;
private:     
    boost::asio::ip::tcp::acceptor m_acceptor;
    connectMgn m_connectMgn;
    TCPProxy* m_proxy;
    bool m_bStop;
};