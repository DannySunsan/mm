#pragma once
class mmTcpServerThread
{
public:
    mmTcpServerThread(unsigned short iPort);
    ~mmTcpServerThread();
private:
    void accept();
    void handle_accept(const boost::system::error_code& ec);
    void read();
    void write();
private:
    boost::asio::ip::tcp::socket m_tcpSocket;
    boost::asio::io_service m_service;
    boost::asio::ip::tcp::acceptor m_acceptor;
    eTcpStatus m_eStatus;

    unsigned char str[1024];
};

