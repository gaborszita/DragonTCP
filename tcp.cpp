#include "tcp.h"
#include <cstdio>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp> 

namespace asio = boost::asio;
using asio::ip::tcp;

DragonTCP::DragonTCP::DragonTCP() : socket(io_service) { }

void DragonTCP::DragonTCP::getMessage(std::string &id, std::string &message, boost::system::error_code &error)
{
    idSizeType idSize = readToType<idSizeType>(error);
    if (error) { return; }

    messageSizeType msgSize = readToType<messageSizeType>(error);
    if (error) { return; }
    std::cout << "msgsize: " << msgSize << std::endl;

    boost::asio::streambuf buf;
    boost::asio::streambuf::mutable_buffers_type bufs = buf.prepare(sizeof(char) * idSize);
    boost::asio::read(socket, bufs, boost::asio::transfer_all(), error);
    if (error) { return; }
    const char* data = boost::asio::buffer_cast<const char *>(buf.data());
    id = std::string(data);

    boost::asio::streambuf buf2;
    bufs = buf2.prepare(sizeof(char) * msgSize); 
    boost::asio::read(socket, bufs, boost::asio::transfer_all(), error);
    if (error) { return; }
    data = boost::asio::buffer_cast<const char *>(buf2.data());
    message = std::string(data);
}

void DragonTCP::DragonTCP::sendMessage(const std::string& id, const std::string& message, boost::system::error_code &error)
{
    std::string sendData;
    std::vector<char> idlen = convertToType<char>((idSizeType)id.length());
    std::vector<char> messagelen = convertToType<char>((messageSizeType)message.length());
    std::cout << "message len: " << message.length() << std::endl;
    sendData.reserve(idlen.size() + messagelen.size() + id.length() + message.length());
    sendData.append(idlen.begin(), idlen.end());
    sendData.append(messagelen.begin(), messagelen.end());
    sendData.append(id);
    sendData.append(message);
    boost::asio::write( socket, boost::asio::buffer(sendData), error );
}

template <typename fnctype>
fnctype DragonTCP::DragonTCP::readToType(boost::system::error_code &error)
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
    for (long i=sizeof(fnctype)/sizeof(char)-1; i>=0; i--) 
    {
        output <<= sizeof(char)*8;
        output |= data[i];
    }
    return output;
}

template <typename targetType, typename sourceType>
std::vector<targetType> DragonTCP::DragonTCP::convertToType(sourceType source)
{
    std::vector<targetType> target;
    target.reserve(sizeof(sourceType)/sizeof(targetType));
    for (size_t i = 0; i<sizeof(sourceType)/sizeof(targetType); i++)
    {
        target.push_back(source & ((1<<(sizeof(targetType)*8)) - 1));
        source >>= sizeof(targetType)*8;
    }
    return target;
}

void DragonTCP::Client::Connect(const std::string& ip, unsigned short port)
{
    // error variable
    boost::system::error_code error;  
    //connection
    socket.connect( asio::ip::tcp::endpoint( boost::asio::ip::address::from_string(ip), port ), error);
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

void DragonTCP::Server::Connect(unsigned short port)
{
    //listen for new connection
    tcp::acceptor acceptor_(io_service, asio::ip::tcp::endpoint(tcp::v4(), port ));
    //waiting for connection
    acceptor_.accept(socket);
    return;
}
