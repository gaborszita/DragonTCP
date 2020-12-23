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
    class DragonTCP
    {
    public:
        DragonTCP();
        DragonTCP(const DragonTCP&)= delete;
        DragonTCP(DragonTCP&&)= delete;

    protected:
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::socket socket;

    public:
        void sendMessage(const std::string& id, const std::string& message, boost::system::error_code &error);
        void sendMessage(const std::string& id, const std::string& message);
        void getMessage(std::string &id, std::string &message, boost::system::error_code &error);
        void getMessage(std::string &id, std::string &message);

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
        void Connect(const std::string& ip, unsigned short port);
        void Connect(const std::string& ip, unsigned short port, boost::system::error_code &error);
    };

    class Server : public DragonTCP
    {
    public:
        void Connect(unsigned short port);
        void Connect(unsigned short port, boost::system::error_code &error);
    };
}

#endif
