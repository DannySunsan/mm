#pragma once
class mmTcpClientThread
{
public:
    mmTcpClientThread();
    ~mmTcpClientThread();
    int Connect(const char* sIp, unsigned short iPort);
    void Send(const char* str,unsigned int uLen);
private:
    boost::asio::ip::tcp::socket* m_tcpSocket;
    boost::asio::io_service m_service;
    eTcpStatus m_eStatus;
};

