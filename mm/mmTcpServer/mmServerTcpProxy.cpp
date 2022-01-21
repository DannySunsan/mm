#include "mmServerTcpProxy.h"
#include "mmUtility\tcp\TCPThreadStruct.h"
#include<fstream>
void mmServerTcpProxy::handleProcess(char* s, unsigned int l)
{
    if (l < sizeof(TCPMsgHead))
    {
        return;
    }
        
    TCPMsgHead* head = (TCPMsgHead*)s;
    const char* path2 = "D:\\syq-repos\\abcttt.txt";
    std::ofstream of(path2, std::ios::out|std::ios::app);
    char* data = (char*) (head + 1);
    of << data;

    TCPData dataRet;
    dataRet.head = *head;
    std::string msg = "receive ok!";

    dataRet.head.len = sizeof(TCPMsgHead) + msg.length();
    dataRet.s = (char*)&msg;
    th->write(head->s_ip,(char*)&dataRet, dataRet.head.len);
}
void mmServerTcpProxy::initServer(unsigned short iPort)
{
    th = new mmTcpServerThread(iPort,this);
}