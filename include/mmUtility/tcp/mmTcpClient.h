#pragma once
#include "mmTcpConnection.h"
class MUTILITY_DLLEXPORT mmTcpClient
{
public:
    mmTcpClient(TCPProxy* proxy);
    void connect(const char * ip,unsigned short port);
    void send(char* s, unsigned int len);
    void close();
private:
    mmTcpClientConnection* client_;    
};