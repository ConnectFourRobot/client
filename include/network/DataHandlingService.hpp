#ifndef DATAHANDLINGSERVICE_H
#define DATAHANDLINGSERVICE_H

#include <string>
#include "NetworkMessage.hpp"
#include "NetworkClient.hpp"

class DataHandlingService
{
private:
    NetworkClient* _networkClient;

    // Has to be private because of Singleton
    DataHandlingService() {};
    DataHandlingService(DataHandlingService const&); // Do not Implement.
    void operator=(DataHandlingService const&); // Do not implement.
public:
    // Singleton
    static DataHandlingService& getInstance()
    {
        static DataHandlingService instance;
        return instance;
    }

    /**
     * Starts the DataHandlingService
     *
     * @param host IP-Address of the host
     * @param port Port of the host
     * @return success identifiers
    */
    int start(std::string host, unsigned short port);

    /**
     * Sends a message to the host
     *
     * @param message ClientMessage that should be send
    */
    void sendMessage(ClientNetworkMessage message);

    /**
     * Receives a message from the host
     *
     * @return ServerNetworkMessage from the host
    */
    ServerNetworkMessage receiveMessage();
    ~DataHandlingService();
};
#endif
