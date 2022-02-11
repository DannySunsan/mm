#pragma once
#include "boost\asio.hpp"
#include "boost\shared_ptr.hpp"
#include "boost\enable_shared_from_this.hpp"
#include "boost\bind.hpp"
#include "boost\function.hpp"
#include "DataBuffer.h"
#include "boost\array.hpp"
#include <mutex>
#include "TCPThreadStruct.h"
#include "mmTcpProxy.h"

class connectMgn;
class mmTcpServerConnection;

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
class mmTcpClientConnection: public mmConnectionData
{
public:
    mmTcpClientConnection(TCPProxy* proxy);

    void connect(const char* ip, unsigned short port);
    void send(char* s, unsigned int len);
    void read();
    boost::asio::ip::tcp::socket& socket() {
        return socket_;
    }
    void close();
private:
    void send();
private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::resolver resolver_;
    std::thread th_;
};

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
private:
    void write();

    mmTcpServerConnection(boost::asio::ip::tcp::socket& /*socket*/, connectMgn& /*connectMgn*/ , TCPProxy* n_proxy);
private:
    boost::asio::ip::tcp::socket socket_;
    connectMgn& m_connectMgn;
};