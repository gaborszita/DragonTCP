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

#include <iostream>
#include <DragonTCP.hpp>

int main()
{
    DragonTCP::Server server;
    server.Connect(9625);
    while (true) 
    {
        std::string input;
        std::cout << "Enter command: ";
        std::cin >> input;
        if (input=="read") 
        {
            std::string id, message;
            server.getMessage(id, message);
            std::cout << "id: " << id << " message: " << message << std::endl;
        }
        else if (input=="send") 
        {
            std::string id, message;
            std::cout << "Enter id: ";
            std::cin >> id;
            std::cout << "Enter message: ";
            std::cin >> message;
            server.sendMessage(id, message);
        }
        else if (input=="disconnect")
        {
            server.disconnect();
            std::cout << "Disconnect successful!" << std::endl;
            std::exit(0);
        }
        else
        {
            std::cout << "Command uknown" << std::endl;
        }
    }
}
