#pragma once
#include "export.h"
#include "mmUtility\tcp\mmTcpClient.h"
class MUTILITY_DLLEXPORT mmTcpClientThread
{
public:
    mmTcpClientThread();
    ~mmTcpClientThread();
    void Listen(const char* sIp, unsigned short iPort);
    void Send(const char* str,unsigned int uLen);
};

