/**
 *  \file   Communication.h
 *  \brief  Communication interface
 *  \author Emre.ARTIS
 *  \date   13.12.2018
 * */
#ifndef AUTONOMOUS_VEHICLE_GTU_COMMUNICATION_H
#define AUTONOMOUS_VEHICLE_GTU_COMMUNICATION_H

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <exception>
    #include <string>

    #define BUFFER_LENGTH 1024
    namespace GTU {
        namespace AUTONOMOUS_VEHICLE {

            enum class ErrorStatus {
                Success,
                SocketCreationFailed,
                AddressInUse,
                NotValidSocketDescriptor,
                ConnectionRejected,
                BufferSpaceNotAvailable,
                OperationTimedOut,
                SocketWasClosed,
                WriteError
                //
            };
            
            
            //  Communication Interface
            class	Communication {
                public:
                    //virtual ErrorStatus setup() = 0;
                    //virtual ErrorStatus connect() = 0;
                    virtual ErrorStatus send(const std::string & message, int length) = 0;
                    virtual ErrorStatus receive(std::string & message, int length) = 0;
                    //virtual ErrorStatus process(const std::string & in_message, std::string & out_message) = 0;
                // virtual ErrorStatus close() = 0;
            };
            

            class AbstractCommunication : public Communication
            {
                protected:
                    inline void set_SocketDescriptor(int input) {this->socketDescriptor = input;};
                    inline int get_SocketDescriptor() {return this->socketDescriptor;};
                    inline const struct sockaddr_in * getSocketAddress() {return &(this->serverAddress);};
                    struct sockaddr_in  serverAddress;
                private:
                    int                 socketDescriptor;
            };


            class Server : public AbstractCommunication
            {
                public:
                    /**
                     * Creates a socket and binds it to given port number.
                     * As default, it will be 8080.
                     **/
                    Server(int portNumber = 8080);
                    ~Server();
                    //Server operator =(const Server * const otherServer);
                    ErrorStatus receive(std::string & message, int length);
                    ErrorStatus send(const std::string & message, int length);
                private:
                    int commfd = 0;
            };

            class Client : public AbstractCommunication
            {
                public:
                    Client(const std::string & hostName = "localhost", int portNumber = 8080);
                    ErrorStatus receive(std::string & message, int length);
                    ErrorStatus send(const std::string & message, int length);
                    ~Client();
            };
        }    
    }

    #endif AUTONOMOUS_VEHICLE_GTU_COMMUNICATION_H