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
typedef void(*FUNCRETURN)(char*, unsigned int);


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
    TCPProxy* n_proxy;
};
class mmTcpClientConnection: public mmConnectionData
{
public:
    mmTcpClientConnection(TCPProxy* proxy);

    bool connect(boost::asio::ip::tcp::endpoint endp);
    void send(char* s, unsigned int len);
    void read();

    void sync_send(char* s, unsigned int len);
    void sync_send(const char* s);
    void sync_read();
    boost::asio::ip::tcp::socket& socket() {
        return socket_;
    }
private:
    void send();
    void handle_send(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);
    void handle_read(const boost::system::error_code& /*error*/,
        size_t /*bytes_transferred*/);

private:
    void setTask(char* s, unsigned int len)
    {
        std::packaged_task<bool(char*, unsigned int)> task([&](char* s, unsigned int len) {
            sendBuf.clear();
            char* HeadSize = (char*)& len;
            sendBuf.push(HeadSize, sizeof(unsigned int));

            sendBuf.push(s, len);
            return true;
            });

        task_.swap(task);        
    }
private:
    boost::asio::io_context io_context;
    boost::asio::ip::tcp::socket socket_;
    std::packaged_task<bool(char* s, unsigned int len)> task_;
    std::shared_future<bool> fut_;
    std::mutex m_mutex;
};

class mmTcpServerConnection : public boost::enable_shared_from_this<mmTcpServerConnection>,
    public mmConnectionData
{
public:
    typedef boost::shared_ptr<mmTcpServerConnection> pointer;

    static pointer create(boost::asio::io_context& io_context, TCPProxy* proxy);

    boost::asio::ip::tcp::socket& socket();
    void write(char* s, unsigned int len);
    void receive();
    void init();
protected:
    //virtual void handleProcess(char*, unsigned int);
private:
    void write();

    mmTcpServerConnection(boost::asio::io_context& io_context, TCPProxy* n_proxy);
    void handle_write(const boost::system::error_code& /*error*/,
        unsigned int /*bytes_transferred*/);
    void handle_receive(const boost::system::error_code& /*error*/,
        unsigned int /*bytes_transferred*/);
private:
    boost::asio::ip::tcp::socket socket_;
    std::promise<bool> proIn_;
    std::shared_future<bool> fut_;
    std::mutex m_mutex;
};