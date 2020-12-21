#include "tcp.h"
#include <cstdio>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp> 

using namespace boost::asio;
using ip::tcp;
namespace pt = boost::property_tree;

DragonTCP::DragonTCP::DragonTCP() : socket(io_service) { }

void DragonTCP::DragonTCP::getMessage(std::string &id, std::string &message, boost::system::error_code& error)
{
    idSizeType idSize = readToType<idSizeType>(error);
    if (error) { return; }

    messageSizeType msgSize = readToType<messageSizeType>(error);
    if (error) { return; }

    boost::asio::streambuf buf;
    boost::asio::streambuf::mutable_buffers_type bufs = buf.prepare(sizeof(char) * idSize);
    boost::asio::read(socket, bufs, boost::asio::transfer_all(), error);
    if (error) { return; }
    const char* data = boost::asio::buffer_cast<const char *>(buf.data());
    id = std::string(data);

    bufs = buf.prepare(sizeof(char) * messageSize); 
    boost::asio::read(socket, bufs, boost::asio::transfer_all(), error);
    if (error) { return; }
    const char* data = boost::asio::buffer_cast<const char *>(buf.data());
    message = std::string(data);
}

template <typename fnctype>
fnctype DragonTCP::DragonTCP::readToType(boost::system::error_code& error)
{
    boost::asio::streambuf buf;
    boost::asio::streambuf::mutable_buffers_type bufs = buf.prepare(sizeof(char) * (sizeof(fnctype)/sizeof(char)));
    boost::asio::read(socket, bufs, boost::asio::transfer_all(), error);
    if (error) 
    {
        return 1;
    }
    const unsigned char* data = boost::asio::buffer_cast<const unsigned char *>(buf.data());
    fnctype output = 0;
    for (fnctype i=0; i<sizeof(fnctype)/sizeof(char); i++) 
    {
        output |= data[i];
        output <<= sizeof(char)*8;
    }
    return output;
}

void DragonTCP::Client::Connect(const std::string& ip)
{
    // error variable
    boost::system::error_code error;  
    //connection
    socket.connect( tcp::endpoint( boost::asio::ip::address::from_string(ip), 1234 ), error);
    if (!error)
    {
        std::cout << "Connected." << std::endl;
    }
    else
    {
        std::cout << "Connection failed." << std::endl;
        return;
    }
    return;
}

void DragonTCP::Server::Connect()
{
    //listen for new connection
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234 ));
    //waiting for connection
    acceptor_.accept(socket);
    return;
}
