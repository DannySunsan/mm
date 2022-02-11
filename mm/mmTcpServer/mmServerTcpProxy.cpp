#include "mmServerTcpProxy.h"
#include "mmUtility\tcp\TCPThreadStruct.h"
#include "mmUtility/util.h"
#include<fstream>
#include<iostream>
mmServerTcpProxy::mmServerTcpProxy()
{

}
mmServerTcpProxy::~mmServerTcpProxy()
{
}
void mmServerTcpProxy::initialize(int nPort, mmServerTcpProxy* proxy)
{
    serverMgn_ = new mmTcpServerMgn(nPort, proxy);
}
void mmServerTcpProxy::handleProcess(char* s, unsigned int l)
{
    TCPMsgHead* head = (TCPMsgHead*)s;
    if (head == nullptr)
        return;
    std::cout << CmmUtility::make_daytime_string()<<"--reveive from:" << head->s_ip << "|port:" << head->i_port << "|cmd:" << head->s_cmd<<"|data len:" << head->len <<std::endl;
    const char* path2 = "D:\\syq-repos\\abcttt.txt";
    std::ofstream of(path2, std::ios::out|std::ios::app);
    char* data = (char*) (head + 1);
    of << data;
    std::cout << data << std::endl;

    //Return
    TCPData dataRet;
    dataRet.head = *head;
    std::string msg = "receive ok!";
    dataRet.head.len = sizeof(TCPMsgHead) + msg.length();

    dataRet.s = new char[msg.length()];
    memcpy(dataRet.s, s, msg.length());

    serverMgn_->send(head->s_ip,(char*)&dataRet, dataRet.head.len);
}

void mmServerTcpProxy::broadcast(char* data, unsigned int nlen)
{
    TCPData dataSend;
    dataSend.head.len = sizeof(TCPMsgHead) + nlen;
    dataSend.head.s_cmd[0] = '2';
    dataSend.head.s_cmd[1] = '\0';

    dataSend.s = new char[nlen];
    memcpy(dataSend.s, data, nlen);

    serverMgn_->broadcast((char*)& dataSend, dataSend.head.len);
}