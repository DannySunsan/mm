#include "mmClientTcpProxy.h"
#include "mmUtility\tcp\TCPThreadStruct.h"
#include<fstream>
void mmClientTcpProxy::handleProcess(char* s, unsigned int l)
{
    if (l < sizeof(TCPMsgHead))
    {
        return;
    }

    TCPMsgHead* head = (TCPMsgHead*)s;
    const char* path2 = "D:\\syq-repos\\abc.txt";
    std::ofstream of(path2, std::ios::out | std::ios::app);
    char* data = (char*)(head + 1);
    of << data;
}