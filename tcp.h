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
        void sendMessage(const std::string& id, const std::string& data);
        void getMessage(std::string &id, std::string &message, boost::system::error_code& error) const noexcept;

    private:
        typedef unsigned long messageSizeType;
        typedef unsigned char idSizeType;

        template <typename fnctype>
        fnctype readToType(boost::system::error_code& error);
    };

    class Client : public DragonTCP
    {
    public:
        void Connect(const std::string& ip);
    };

    class Server : public DragonTCP
    {
    public:
        void Connect();
    };
}


