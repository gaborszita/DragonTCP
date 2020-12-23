#include <iostream>
#include "tcp.h"
#include <windows.h>

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
        else
        {
            std::cout << "Command uknown" << std::endl;
        }
    }
}
