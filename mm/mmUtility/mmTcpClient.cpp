#include "mmUtility\tcp\mmTcpClient.h"

mmTcpClient::mmTcpClient(boost::asio::ip::tcp::endpoint ep)
    :m_ep(ep)
{

}
void mmTcpClient::connect()
{

}
void mmTcpClient::send()
{
    mmTcpConnection::pointer new_connection =
        mmTcpConnection::create(m_io_context);

    
}

void mmTcpClient::handle_send(mmTcpConnection::pointer new_connection,
    const boost::system::error_code& error)
{
    if (!error)
    {
        
    }

}