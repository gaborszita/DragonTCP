#include <iostream>
#include "tcp.h"
#include <windows.h>

int main()
{
    DragonTCP::Server server;
    server.Connect();
    while (true) 
    {
        std::string input;
        std::cout << "Enter command: ";
        std::cin >> input;
        if (input=="read") 
        {
            boost::system::error_code error;
            std::string id, message;
            server.getMessage(id, message, error);
            if (error)
            {
                std::cout << "Error!!!" << std::endl;
            }
            std::cout << "id: " << id << " message: " << message << std::endl;
        }
        else if (input=="send") 
        {
            std::string id, message;
            std::cout << "Enter id: ";
            std::cin >> id;
            std::cout << "Enter message: ";
            std::cin >> message;
            boost::system::error_code error;
            server.sendMessage(id, message, error);
            if (error)
            {
                std::cout << "Error!!!" << std::endl;
            }
        }
        else
        {
            std::cout << "Command uknown" << std::endl;
        }
    }
}
