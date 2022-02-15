#pragma once
#include "boost\array.hpp"
#include "DataBuffer.h"
#include "TCPConnectStruct.h"
#include "mmTcpProxy.h"

BEGIN_NAMESPACE_MM
class mmConnectionData
{
public:
    mmConnectionData(TCPProxy* proxy);
    virtual ~mmConnectionData();
protected:
    virtual void resetData();
    virtual void dataProcess(char* s, unsigned int uLen);
private:
    void setDataState();
    void dealReveiving();
    void dealData();
protected:
    DataBuffer recvBuf;
    DataBuffer sendBuf;
    boost::array<char, 1024> cache;
    DataFormat _fmt;
    TCPProxy* m_proxy;
};
END_NAMESPACE_MM