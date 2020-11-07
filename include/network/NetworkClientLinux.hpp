#ifndef NETWORKCLIENT_HPP
#define NETWORKCLIENT_HPP

#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <iostream>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

class NetworkClient {
    private:
        std::string _address;
        unsigned short _port;
        struct sockaddr_in _server;
        int _sock;

        // Do not implement these copy constructors, because an instance
        // of this class should not be copied
        NetworkClient(NetworkClient const&);
        void operator=(NetworkClient const&);
    public:
        NetworkClient(std::string host, unsigned short port): _address(host), _port(port), _sock(-1) {};

        /**
         * Build a connection to the host
         *
         * @return success identifier
        */
        int connect();

        /**
         * Send a message to the host
         *
         * @param message the message that should be send
        */
        void send(std::string message);

        /**
         * Reads an incoming message stream
         *
         * @param size The size to read
         * @return the stream as string
        */
        std::string read(int size);

        ~NetworkClient();
};

#endif //!NETWORKCLIENT_HPP
