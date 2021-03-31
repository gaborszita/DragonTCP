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

#include <iostream>
#include <DragonTCP/DragonTCP.hpp>

int main()
{
    DragonTCP::Client client;
    client.Connect("127.0.0.1", 9625);
    while (true) 
    {
        std::string input;
        std::cout << "Enter command: ";
        std::cin >> input;
        if (input=="read") 
        {
            std::string id, message;
            client.getMessage(id, message);
            std::cout << "id: " << id << " message: " << message << std::endl;
        }
        else if (input=="send") 
        {
            std::string id, message;
            std::cout << "Enter id: ";
            std::cin >> id;
            std::cout << "Enter message: ";
            std::cin >> message;
            client.sendMessage(id, message);
        }
        else if (input=="disconnect")
        {
            client.disconnect();
            std::cout << "Disconnect successful!" << std::endl;
            std::exit(0);
        }
        else
        {
            std::cout << "Command uknown" << std::endl;
        }
    }
}
