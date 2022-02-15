#include "mmUtility\tcp\mmConnectionData.h"
#include <iostream>
BEGIN_NAMESPACE_MM
mmConnectionData::mmConnectionData(TCPProxy* proxy) :
    m_proxy(proxy)
{
}
mmConnectionData::~mmConnectionData()
{
}
void mmConnectionData::resetData()
{
    memset(&_fmt, 0x00, sizeof(DataFormat));
    recvBuf.clear();
    sendBuf.clear();
}

void mmConnectionData::dataProcess(char* s, unsigned int uLen)
{
    recvBuf.push(s, uLen);
    switch (_fmt.state)
    {
    case eStateReceive::start:
        setDataState();
        break;
    case eStateReceive::receiving:
        dealReveiving();
        break;
    default:
        dealData();
        break;
    }
}

void mmConnectionData::setDataState()
{
    std::cout << "start" << std::endl;
    if (recvBuf.Len() < sizeof(TCPMsgHead))
        return;//error
    char* head = recvBuf.head();
    _fmt.head = *(TCPMsgHead*)(head);
    std::cout << "Data Len: " << _fmt.head.len << std::endl;

    if (recvBuf.reserve() == _fmt.head.len)
    {
        dealData();
    }
    else
        _fmt.state = eStateReceive::receiving;


}

void mmConnectionData::dealReveiving()
{
    std::cout << "receiving" << std::endl;
    if (recvBuf.Len() < _fmt.head.len)
        return;
    dealData();
    _fmt.state = eStateReceive::end;
    std::cout << "end" << std::endl;
}

void mmConnectionData::dealData()
{
    m_proxy->handleProcess(recvBuf.head(), recvBuf.Len());
    _fmt = DataFormat();
    recvBuf.clear();
}
END_NAMESPACE_MM