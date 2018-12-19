#include "Communication.h"
#include <unistd.h>
#include <netdb.h>
#include <iostream>
using namespace GTU::AUTONOMOUS_VEHICLE;

Server::Server(int portNumber)
{
    set_SocketDescriptor(socket(AF_INET, SOCK_STREAM, 0));
    serverAddress                   = {0};
    serverAddress.sin_family        = AF_INET;
    serverAddress.sin_addr.s_addr   = htonl(INADDR_ANY);
    serverAddress.sin_port          = htons(portNumber);
    if(bind(get_SocketDescriptor(), (struct sockaddr *) &serverAddress, sizeof(sockaddr_in)))
    {
        throw new std::bad_exception();
    }
    if(listen(get_SocketDescriptor(), 1))
    {
        throw new std::exception();
    }
    socklen_t socketLength = sizeof(*(this->getSocketAddress()));
    if ((commfd = accept(this->get_SocketDescriptor(), (struct sockaddr *) this->getSocketAddress(), &socketLength)) == -1 )
        throw std::bad_exception();
}

ErrorStatus Server::receive(std::string & message, int length)
{
    char buffer[255];
    if(read(commfd, &buffer, length) == 0)
    {
        socklen_t socketLength = sizeof(*(this->getSocketAddress()));
        if ((commfd = accept(this->get_SocketDescriptor(), (struct sockaddr *) this->getSocketAddress(), &socketLength)) == -1 )
            throw std::bad_exception();
    }
    message.assign(buffer, 0, length);
    return ErrorStatus::Success;
}

ErrorStatus Server::send(const std::string & message, int length)
{
    if(write(commfd, message.c_str(), length) < 0)
        return ErrorStatus::WriteError;
    return ErrorStatus::Success;
}



Server::~Server()
{
    while(shutdown(commfd, SHUT_RD) == -1 && errno == EINTR); 
    while(close(commfd) == -1 && errno == EINTR);
    shutdown(this->get_SocketDescriptor(), SHUT_RD);
    close(this->get_SocketDescriptor());
}



Client::Client(const std::string & hostName, int portNumber)
{
    struct addrinfo hints = {0},
                    *result;
    hints.ai_addr       = nullptr;
    hints.ai_next       = nullptr;
    hints.ai_family     = AF_INET;
    hints.ai_socktype   = SOCK_STREAM;
    hints.ai_flags      = AI_NUMERICSERV;

    if(getaddrinfo(hostName.c_str(), (std::to_string(portNumber)).c_str(), &hints, &result) != 0)
        throw std::exception();
    
    auto point = result;

    while(point != nullptr)
    {
        set_SocketDescriptor(socket(point->ai_family, point->ai_socktype, point->ai_protocol));
        if(get_SocketDescriptor() != -1 &&
            connect(get_SocketDescriptor(), point->ai_addr, point->ai_addrlen) != -1)
            break;
        close(get_SocketDescriptor());
        point = point->ai_next;
    }
    if(point == nullptr)
        throw std::exception();
    freeaddrinfo(result);
}

ErrorStatus Client::send(const std::string & message, int length)
{
    if(write(get_SocketDescriptor(), message.c_str(), length) != length)
        throw std::exception();
}


ErrorStatus Client::receive(std::string & message, int length)
{
    char * array = (char *) malloc(length * sizeof(char));
    if(read(get_SocketDescriptor(), array, length) != length)
        throw std::exception();
    message = std::string(array);
    free(array);
    array = nullptr;
}


Client::~Client()
{
    shutdown(this->get_SocketDescriptor(), SHUT_RD);
    close(this->get_SocketDescriptor());
}