#include<string>
#include<boost/asio.hpp>
#include"mmUtility/TCPThreadStruct.h"
#include "mmTcpClientThread.h"
#include<iostream>
mmTcpClientThread::mmTcpClientThread()
{    
    m_eStatus = STATUS_OK;
    m_tcpSocket = new boost::asio::ip::tcp::socket(m_service);
    m_tcpSocket->open(boost::asio::ip::tcp::v4());
}
mmTcpClientThread::~mmTcpClientThread()
{
    delete m_tcpSocket;
    m_tcpSocket = nullptr;
}
int mmTcpClientThread::Connect(const char* sIp, unsigned short iPort)
{
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(sIp), iPort);
    
    m_tcpSocket->async_connect(ep, [](const boost::system::error_code& error){
        if (!error)
        {      
           // boost::asio::write(socket, boost::asio::buffer("hello world!", 1024));
            std::cout << "Connect succeeded.\n";
        }   
        else
        {
            std::cout << "Connect error:"<<error.message()<<std::endl;
        }
        });
}
void mmTcpClientThread::Send(const char* str, unsigned int uLen)
{
    m_tcpSocket->async_send(boost::asio::buffer("hello world!", 1024), [](const boost::system::error_code& error) {
        if (!error)
        {
            std::cout << "Send succeeded.\n";
        }
        else
        {
            std::cout << "Send error:" << error.message() << std::endl;
        }   
        });
}