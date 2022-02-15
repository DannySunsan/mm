#include "mmClientTcpProxy.h"
#include "mmUtility\tcp\TCPThreadStruct.h"
#include<fstream>
#include<iostream>
#include "mmUtility/util.h"
BEGIN_NAMESPACE_MM
void mmClientTcpProxy::handleProcess(char* s, unsigned int l)
{
    TCPMsgHead* head = (TCPMsgHead*)s;
    if (head == nullptr)
        return;
    std::cout << CmmUtility::make_daytime_string() << "--reveive from:" << head->s_ip << "port:" << head->i_port << "cmd:" << head->s_cmd << "data len:" << head->len << std::endl;
    const char* path2 = "D:\\syq-repos\\abc.txt";
    std::ofstream of(path2, std::ios::out | std::ios::app);
    char* data = (char*)(head + 1);
    of << data;
    std::cout << data << std::endl;
}
END_NAMESPACE_MM