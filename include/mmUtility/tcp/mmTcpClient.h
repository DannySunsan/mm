#pragma once
#include "mmTcpClientConnection.h"
BEGIN_NAMESPACE_MM
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
END_NAMESPACE_MM