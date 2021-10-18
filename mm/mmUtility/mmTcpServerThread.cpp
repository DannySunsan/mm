#include<string>
#include<boost/asio.hpp>
#include"mmUtility/TCPThreadStruct.h"
#include "mmTcpServerThread.h"
#include<iostream>

mmTcpServerThread::mmTcpServerThread(unsigned short iPort):
    m_service(),
    m_tcpSocket(m_service), 
    m_acceptor(m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), iPort))
{
    m_eStatus = STATUS_OK;
    m_service.run();
}
mmTcpServerThread::~mmTcpServerThread()
{
}
void mmTcpServerThread::accept() 
{
    m_acceptor.async_accept(m_tcpSocket, [this](const boost::system::error_code& ec)
        {
        handle_accept(ec);
        });
    std::cout << "accept()" << std::endl;

}

void mmTcpServerThread::handle_accept(const boost::system::error_code& ec) 
{
    if (ec) {
        return;
    }
    read();
    std::cout << "start another accept()" << std::endl;
    accept();
}

void mmTcpServerThread::read() 
{
    boost::asio::async_read(m_tcpSocket, boost::asio::buffer(str, 1024), [this](boost::system::error_code ec, std::size_t) 
        {
        if (!ec) {
            write();
            std::cout << "server received: " << str << std::endl; 
        }
        read();
        });
}

void mmTcpServerThread::write() 
{
    boost::asio::async_write(m_tcpSocket, boost::asio::buffer("ok", 2), [this](boost::system::error_code ec, std::size_t) 
        {
        if (!ec) {
            std::cout << "server recalled: " << str << " ok" << std::endl; 
        }
        });
}
