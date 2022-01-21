#pragma once
#include "mmTcpServer.h"
class MUTILITY_DLLEXPORT mmTcpServerThread
{
public:
    mmTcpServerThread(unsigned short iPort, TCPProxy* proxy);
    ~mmTcpServerThread();

    void write(std::string ip,char* s, unsigned int len);
private:
    void start();
    mmTcpServer server;
};

