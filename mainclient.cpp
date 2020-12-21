#include <iostream>
#include "tcp.h"
#include <windows.h>

int main()
{
    DragonTCP::Client client;
    client.Connect("127.0.0.1");
    while (true) 
    {
        std::string input;
        std::cout << "Enter message or command: ";
        std::cin >> input;
        if (input=="read") 
        {
            client.read();
            std::cout << "OK, read." << std::endl;
        }
        else if (input=="print") 
        {
            std::string data;
            bool success = client.dataStream.getStringUntilDelimiter('\n', data);
            if (success) 
            {
                std::cout << "Message until \\n: " << data << std::endl;
            }
            else
            {
                std::cout << "No message available for reading!" << std::endl;
            }
        }
        else
        {
            client.send(input);
            std::cout << "OK, message sent." << std::endl;
        }
    }
}
