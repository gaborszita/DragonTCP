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
        void getMessage(std::string &id, std::string &message, boost::system::error_code &error);

    private:
        typedef unsigned long messageSizeType;
        typedef unsigned char idSizeType;

        template <typename fnctype>
        fnctype readToType(boost::system::error_code &error);

        template <typename targetType, typename sourceType>
        std::vector<targetType> convertToType(sourceType source);
    };

    class Client : public DragonTCP
    {
    public:
        void Connect(const std::string& ip, unsigned short port);
    };

    class Server : public DragonTCP
    {
    public:
        void Connect(unsigned short port);
    };
}


