#include "../header/Client.h"
using namespace GTU::AUTONOMOUS_VEHICLE;
Client::Client(const std::string & hostName, int portNumber)
{
    setup(hostName, portNumber);
}

ErrorStatus Client::setup(const std::string & hostName, int port)
{
    struct addrinfo hints = {0},
                    *result;
    hints.ai_addr       = nullptr;
    hints.ai_next       = nullptr;
    hints.ai_family     = AF_INET;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_flags      = AI_NUMERICSERV;

    if(getaddrinfo(hostName.c_str(), (std::to_string(port)).c_str(), &hints, &result) != 0)
        throw std::exception();
    
    auto point = result;

    while(point != nullptr)
    {
        setConnection(socket(point->ai_family, point->ai_socktype, point->ai_protocol));
        if(getConnection() != -1 &&
            connect(getConnection(), point->ai_addr, point->ai_addrlen) != -1)
            break;
        close(getConnection());
        point = point->ai_next;
    }
    if(point == nullptr)
        throw std::exception();
    freeaddrinfo(result);
}



Client::~Client()
{
    this->stop();
}