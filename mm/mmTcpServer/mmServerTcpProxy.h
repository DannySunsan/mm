#pragma once
#include "mmUtility\tcp\mmTcpProxy.h"
#include "mmUtility/util.h"
BEGIN_NAMESPACE_MM
class mmServerTcpProxy:public TCPProxy
{
public:
    mmServerTcpProxy();
    ~mmServerTcpProxy();
    virtual void handleProcess(char*, unsigned int);
    void initialize(int nPort, mmServerTcpProxy* proxy);

    void broadcast(char*, unsigned int);
private:
    mmTcpServerMgn* serverMgn_;
};
END_NAMESPACE_MM