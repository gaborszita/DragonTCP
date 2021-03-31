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

/**
 * \brief DragonTCP namespace
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
 *  
 * DragonTCP currently is NOT thread-safe. The reason for this is because 
 * working with mutexes to ensure thread-safety also requires some time, 
 * thus slowing down the program. By handing over the responsibility of 
 * thread-safety to the programmer, we can speed up the program.
 */
namespace DragonTCP
{
    /**
     * Main class for the library.
     */ 
    class DragonTCP
    {
    protected:
        /// default constructor of DragonTCP class
        DragonTCP(); 
    public:
        /// delete copy constructor
        DragonTCP(const DragonTCP&)= delete;
        /// delete move constructor
        DragonTCP(DragonTCP&&)= delete;

    protected:
        /// The io_service object that will be used for the connection.
        boost::asio::io_service io_service;

        /// The socket object that will be used for the connection.
        boost::asio::ip::tcp::socket socket;

    public:
        /**
         * \brief Send data with an id and a message. In case of an error, the 
         *        error argument will be set.
         * 
         * IMPORTANT: 
         * The id cannot be longer than 256 bytes and the message cannot be 
         * longer than 4,294,967,295 bytes. DragonTCP doesn't check this, 
         * because it is optimized for speed. Therefore, it is the programmer's 
         * responsibility to ensure the arguments don't pass these limits. If 
         * it is not checked, undefined behavior could happen. 
         */
        void sendMessage(const std::string& id, const std::string& message, boost::system::error_code &error);

        /**
         * \brief Send data with an id and a message. In case of an error, an 
         *        exception will be thrown.
         * 
         * IMPORTANT: 
         * The id cannot be longer than 256 bytes and the message cannot be 
         * longer than 4,294,967,295 bytes. DragonTCP doesn't check this, 
         * because it is optimized for speed. Therefore, it is the programmer's 
         * responsibility to ensure the arguments don't pass these limits. If 
         * it is not checked, undefined behavior could happen. 
         */
        void sendMessage(const std::string& id, const std::string& message);

        /*
        * The following two functions can be used to receive data with an id and a message. 
        *  
        * The functions block until: 
        * 1. Data is received fully from the other side. 
        * 2. An error occurs. (E.g., EOF error occurs, because other side disconnects)
        */

        /**
         * \brief Receive data. When the function returns, the variables passed
         *        as the id and message arguments will contain the id and 
         *        message of the data. In case of an error, the error argument
         *        will be set.
         * 
         * The method blocks until: 
         * 1. Data is received fully from the other side. 
         * 2. An error occurs. (E.g., EOF error occurs, because other side disconnects)
         */
        void getMessage(std::string &id, std::string &message, boost::system::error_code &error);

        /**
         * \brief Receive data. When the function returns, the variables passed
         *        as the id and message arguments will contain the id and 
         *        message of the data. In case of an error, an exception will 
         *        be thrown.
         * 
         * The method blocks until: 
         * 1. Data is received fully from the other side. 
         * 2. An error occurs. (E.g., EOF error occurs, because other side disconnects)
         */
        void getMessage(std::string &id, std::string &message);
        
        /**
         * \brief Disconnect from the socket. In case of an error, the error argument 
         *        will be set.
         */
        void disconnect(boost::system::error_code &error);

        /**
         * \brief Disconnect from the socket. In case of an error, an exception will 
         *        be thrown.
         */
        void disconnect();
        

    private:
        // Set how big the message of the data can be.
        typedef unsigned long messageSizeType;

        /// Set how big the id of the data can be.
        typedef unsigned char idSizeType;

        /**
         * Read some chars from the socket to a specified type, passed by the 
         * function template fnctype. In case of an error, the error argument 
         * will be set.
         */
        template <typename fnctype>
        fnctype readToType(boost::system::error_code &error);

        /**
         * Read some chars from the socket to a specified type, passed by the 
         * function template fnctype. In case of an error, an exception will 
         * be thrown
         */
        template <typename fnctype>
        fnctype readToType();

        /**
        * Convert a variable of type targetType to an array of sourceType 
        * variables.
        */
        template <typename targetType, typename sourceType>
        std::vector<targetType> convertToType(sourceType source);
    };

    /*
     * Client class of the DragonTCP library. This class should be used when 
     * using a client.
     */
    class Client : public DragonTCP
    {
    public:
        /**
         * \brief Connect to the server. In case of an error, an exception will be 
         *        thrown.
         */
        void Connect(const std::string& ip, unsigned short port);

        /**
         * \brief Connect to the server. In case of an error, the error argument will 
         *        be set.
         */
        void Connect(const std::string& ip, unsigned short port, boost::system::error_code &error);
    };
    /**
     * \example mainclient.cpp
     * This is an example of how to use the Client class.
     */


    /*
     * Server class of the DragonTCP library. This class should be used when 
     * using a server.
     */
    class Server : public DragonTCP
    {
    public:
        /**
         * \brief Wait for a client to connect. In case of an error, an 
         *        exception will be thrown.
         * 
         * The method blocks until a client connects.
         */
        void Connect(unsigned short port);

        /**
         * \brief Wait for a client to connect. In case of an error, the error 
         *        argument will be set.
         * 
         * The method blocks until a client connects.
         */
        void Connect(unsigned short port, boost::system::error_code &error);
    };
    /**
     * \example mainserver.cpp
     * This is an example of how to use the Server class.
     */
}


#endif
