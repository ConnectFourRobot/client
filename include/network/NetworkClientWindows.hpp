#ifndef NETWORKCLIENT_WIN_HPP
#define NETWORKCLIENT_WIN_HPP

#include <string>
#include <iostream>
#include "NetworkMessageType.hpp"

/** The Windows Network Client is a dummy, which does not do anything.
 * It is required to compile the source code in Windows OS. */
class NetworkClient
{
private:
    // Do not implement these copy constructors, because an instance
    // of this class should not be copied
    NetworkClient(NetworkClient const&) = delete;
    void operator=(NetworkClient const&) = delete;
public:
    NetworkClient(std::string host, unsigned short port) {};
    int connect()
    {
        return 0;
    };
    void send(std::string message)
    {
        std::cout << "Network-Send: " << message << std::endl;
    };
    std::string read(int size)
    {
        return "";
    };

    ~NetworkClient() {};
};
#endif //NETWORKCLIENT_WIN_HPP
