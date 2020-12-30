/* 
* Copyright (C) 2020 Gabor Szita
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
* along with lidar project.  If not, see https://www.gnu.org/licenses/ 
*/ 

#pragma once
#ifndef _DRAGONTCP_TCP_H
#define _DRAGONTCP_TCP_H

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace DragonTCP
{
    /* 
    * DragonTCP namespace 
    *  
    * DragonTCP is a TCP network communication library. 
    *  
    * Every function that is prone to errors has at least two overrides: One that 
    * throws and exception and one that has a boost::system::error_code as a 
    * reference argument. If an error occurs in the function, this argument 
    * will be set accordingly. 
    *  
    * DragonTCP files use include guards and #pragma once to ensure no header 
    * file conflicts happen. 
    *  
    * IMPORTANT NOTE: DragonTCP is a speed and not user-friendly or 
    * readability optimized library. Please note this before starting to use 
    * this library. 
    */
    class DragonTCP
    {
    public:
        DragonTCP(); // default constructor of DragonTCP class;
        DragonTCP(const DragonTCP&)= delete; // copy constructor deleted
        DragonTCP(DragonTCP&&)= delete; // move constructor deleted

    protected:
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::socket socket;

    public:
        /*
        * The following two functions can be used to send data with an id and a message.
        *  
        * IMPORTANT: 
        * The id cannot be longer than 256 bytes and the message cannot be 
        * longer than 4,294,967,295 bytes. DragonTCP doesn't check this, 
        * because it is optimized for speed. Therefore, it is the programmer's 
        * responsibility to ensure the arguments don't pass these limits. If 
        * it is not checked, undefined behavior could happen. 
        */
        void sendMessage(const std::string& id, const std::string& message, boost::system::error_code &error);
        void sendMessage(const std::string& id, const std::string& message);
        /*
        * The following two functions can be used to receive data with an id and a message. 
        *  
        * The functions block until: 
        * 1. Data is received fully from the other side. 
        * 2. An error occurs. (E.g., EOF error occurs, because other side disconnects)
        */
        void getMessage(std::string &id, std::string &message, boost::system::error_code &error);
        void getMessage(std::string &id, std::string &message);
        // The following two functions can be used to disconnect the socket.
        void disconnect();
        void disconnect(boost::system::error_code &error);

    private:
        typedef unsigned long messageSizeType;
        typedef unsigned char idSizeType;

        template <typename fnctype>
        fnctype readToType(boost::system::error_code &error);

        template <typename fnctype>
        fnctype readToType();

        template <typename targetType, typename sourceType>
        std::vector<targetType> convertToType(sourceType source);
    };

    class Client : public DragonTCP
    {
    public:
        // The following two functions can be used to connect to the server.
        void Connect(const std::string& ip, unsigned short port);
        void Connect(const std::string& ip, unsigned short port, boost::system::error_code &error);
    };

    class Server : public DragonTCP
    {
    public:
        /*
        * The following two functions can be used to connect. 
        * They block until a client connects to the server.
        */
        void Connect(unsigned short port);
        void Connect(unsigned short port, boost::system::error_code &error);
    };
}

#endif
