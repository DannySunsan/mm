#pragma once
#include "mmTcpServer.h"
BEGIN_NAMESPACE_MM
class MUTILITY_DLLEXPORT mmTcpServerMgn
{
public:
    mmTcpServerMgn(unsigned short usPort, TCPProxy* proxy);
    ~mmTcpServerMgn();
    void setProxy(TCPProxy* proxy);
    void send(std::string ip, char* s, unsigned int len);
    void broadcast(char* s, unsigned int len);
private:
    mmTcpServer* m_server;//default server
    boost::asio::io_context m_io;
    std::thread th_;
};
END_NAMESPACE_MM

