#pragma once
#include "boost\asio.hpp"
#include "boost\shared_ptr.hpp"
#include "boost\enable_shared_from_this.hpp"
#include "mmConnectionData.h"
BEGIN_NAMESPACE_MM
class connectMgn;
class mmTcpServerConnection;

class mmTcpServerConnection : public boost::enable_shared_from_this<mmTcpServerConnection>,
    public mmConnectionData
{
public:
    typedef boost::shared_ptr<mmTcpServerConnection> pointer;

    static pointer create(boost::asio::ip::tcp::socket /*socket*/, connectMgn& /*connectMgn*/ ,TCPProxy* /*proxy*/);

    boost::asio::ip::tcp::socket& socket();
    void write(char* s, unsigned int len);
    void receive();
    void init();
    void close();
    void sync_close();
private:
    void write();

    mmTcpServerConnection(boost::asio::ip::tcp::socket& /*socket*/, connectMgn& /*connectMgn*/ , TCPProxy* n_proxy);
private:
    boost::asio::ip::tcp::socket socket_;
    connectMgn& m_connectMgn;
};
END_NAMESPACE_MM