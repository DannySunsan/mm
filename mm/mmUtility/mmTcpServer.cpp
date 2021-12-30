#include "mmUtility\tcp\mmTcpServer.h"

mmTcpServer::mmTcpServer(unsigned short usPort)
   // :m_io_context(),
   // acceptor_(m_io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), usPort))
{
    boost::asio::io_context m_io_context;
    boost::asio::ip::tcp::acceptor acceptor_(m_io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), usPort));
    //listen();
}
void mmTcpServer::listen()
{
   // acceptor_.listen();
    start_accept();
}

void mmTcpServer::run()
{
    //m_io_context.run();
}
void mmTcpServer::stop()
{
   // m_io_context.stop();
}

void mmTcpServer::restart()
{
    //m_io_context.restart();
}

void mmTcpServer::start_accept()
{
   /* mmTcpConnection::pointer new_connection =
        mmTcpConnection::create(m_io_context);

    acceptor_.async_accept(new_connection->socket(),
        boost::bind(&mmTcpServer::handle_accept, this, new_connection,
            boost::asio::placeholders::error));*/
}

void mmTcpServer::handle_accept(mmTcpConnection::pointer new_connection,
    const boost::system::error_code& error)
{
    if (!error)
    {
        //new_connection->write();
    }

    start_accept();
}