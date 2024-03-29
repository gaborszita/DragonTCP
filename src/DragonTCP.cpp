/**
 * Copyright (C) 2020-2021 Gabor Szita
 * 
 * This file is part of DragonTCP.
 *
 * DragonTCP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 *
 * DragonTCP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with DragonTCP.  If not, see https://www.gnu.org/licenses/ 
 */ 

#include "DragonTCP.hpp"

namespace asio = boost::asio;
using asio::ip::tcp;

DragonTCP::DragonTCP::DragonTCP() : socket(io_service) { }

void DragonTCP::DragonTCP::getMessage(std::string &id, std::string &message, boost::system::error_code &error)
{
    idSizeType idSize = readToType<idSizeType>(error);
    if (error) { return; }

    messageSizeType msgSize = readToType<messageSizeType>(error);
    if (error) { return; }

    asio::streambuf buf;
    asio::streambuf::mutable_buffers_type bufs = buf.prepare(sizeof(char) * idSize);
    asio::read(socket, bufs, boost::asio::transfer_all(), error);
    if (error) { return; }
    const char* data = boost::asio::buffer_cast<const char *>(buf.data());
    id = std::string(data);

    asio::streambuf buf2;
    bufs = buf2.prepare(sizeof(char) * msgSize); 
    asio::read(socket, bufs, boost::asio::transfer_all(), error);
    if (error) { return; }
    data = asio::buffer_cast<const char *>(buf2.data());
    message = std::string(data);
}

void DragonTCP::DragonTCP::getMessage(std::string &id, std::string &message)
{
    idSizeType idSize = readToType<idSizeType>();

    messageSizeType msgSize = readToType<messageSizeType>();

    asio::streambuf buf;
    asio::streambuf::mutable_buffers_type bufs = buf.prepare(sizeof(char) * idSize);
    asio::read(socket, bufs, boost::asio::transfer_all());
    const char* data = boost::asio::buffer_cast<const char *>(buf.data());
    id = std::string(data);

    asio::streambuf buf2;
    bufs = buf2.prepare(sizeof(char) * msgSize); 
    asio::read(socket, bufs, boost::asio::transfer_all());
    data = asio::buffer_cast<const char *>(buf2.data());
    message = std::string(data);
}

void DragonTCP::DragonTCP::sendMessage(const std::string& id, const std::string& message, boost::system::error_code &error)
{
    std::string sendData;
    std::vector<char> idlen = convertToType<char>((idSizeType)id.length());
    std::vector<char> messagelen = convertToType<char>((messageSizeType)message.length());
    sendData.reserve(idlen.size() + messagelen.size() + id.length() + message.length());
    sendData.append(idlen.begin(), idlen.end());
    sendData.append(messagelen.begin(), messagelen.end());
    sendData.append(id);
    sendData.append(message);
    asio::write(socket, boost::asio::buffer(sendData), error);
}

void DragonTCP::DragonTCP::sendMessage(const std::string& id, const std::string& message)
{
    std::string sendData;
    std::vector<char> idlen = convertToType<char>((idSizeType)id.length());
    std::vector<char> messagelen = convertToType<char>((messageSizeType)message.length());
    sendData.reserve(idlen.size() + messagelen.size() + id.length() + message.length());
    sendData.append(idlen.begin(), idlen.end());
    sendData.append(messagelen.begin(), messagelen.end());
    sendData.append(id);
    sendData.append(message);
    asio::write(socket, boost::asio::buffer(sendData));
}

template <typename fnctype>
fnctype DragonTCP::DragonTCP::readToType(boost::system::error_code &error)
{
    asio::streambuf buf;
    asio::streambuf::mutable_buffers_type bufs = buf.prepare(sizeof(char) * (sizeof(fnctype)/sizeof(char)));
    asio::read(socket, bufs, boost::asio::transfer_all(), error);
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

template <typename fnctype> 
fnctype DragonTCP::DragonTCP::readToType()
{
    asio::streambuf buf;
    asio::streambuf::mutable_buffers_type bufs = buf.prepare(sizeof(char) * (sizeof(fnctype)/sizeof(char)));
    asio::read(socket, bufs, boost::asio::transfer_all());
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

void DragonTCP::Client::connect(const std::string& ip, unsigned short port)
{  
    //connection
    socket.connect( asio::ip::tcp::endpoint( asio::ip::address::from_string(ip), port ));
    return;
}

void DragonTCP::Client::connect(const std::string& ip, unsigned short port, boost::system::error_code &error)
{
    //connection
    socket.connect( asio::ip::tcp::endpoint( asio::ip::address::from_string(ip), port ), error);
    return;
}

void DragonTCP::Server::connect(unsigned short port)
{
    //listen for new connection
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), port ));
    //waiting for connection
    acceptor_.accept(socket);
    return;
}

void DragonTCP::Server::connect(unsigned short port, boost::system::error_code &error)
{
    //listen for new connection
    tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), port ));
    //waiting for connection
    acceptor_.accept(socket, error);
    return;
}

void DragonTCP::DragonTCP::disconnect()
{
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket.close();
}

void DragonTCP::DragonTCP::disconnect(boost::system::error_code &error)
{
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
    if (error) { return; }
    socket.close(error);
}
