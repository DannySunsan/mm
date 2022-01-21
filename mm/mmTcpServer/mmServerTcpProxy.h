#pragma once
#include "mmUtility\tcp\mmTcpProxy.h"
#include "mmUtility/util.h"
class mmServerTcpProxy:public TCPProxy
{
public:
    virtual void handleProcess(char*, unsigned int);
    void initServer(unsigned short iPort);
private:
    mmTcpServerThread* th;
};