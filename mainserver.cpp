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
        std::cout << "Enter message or command: ";
        std::cin >> input;
        if (input=="read") 
        {
            server.read();
            std::cout << "OK, read." << std::endl;
        }
        else if (input=="print") 
        {
            //std::cout << server.dataStream.spaceUsed << std::endl;
            std::string data;
            //std::cout << server.dataStream.spaceUsed << std::endl;
            bool success = server.dataStream.getStringUntilDelimiter('\n', data);
            //std::cout << server.dataStream.spaceUsed << std::endl;
            if (success) 
            {
                std::cout << "Message until \\n: " << data << std::endl;
            }
            else
            {
                std::cout << "No message available for reading!" << std::endl;
            }
        }
        else if (input=="clean") 
        {
            server.dataStream.cleanup();
            std::cout << "Clean successful!" << std::endl;
        }
        else
        {
            server.send(input);
            std::cout << "OK, message sent." << std::endl;
        }
    }
}
