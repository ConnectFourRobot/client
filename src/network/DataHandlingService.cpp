#include "../../include/network/DataHandlingService.hpp"
#include "../../include/logger/Logger.hpp"

int DataHandlingService::start(std::string host, unsigned short port)
{
    this->_networkClient = new NetworkClient(host, port);
    return this->_networkClient->connect();
}

void DataHandlingService::sendMessage(ClientNetworkMessage message)
{
    std::string networkMessage = message.getNetworkMessage();
    this->_networkClient->send(networkMessage);
}

ServerNetworkMessage DataHandlingService::receiveMessage()
{
    //type
    std::string typeString = this->_networkClient->read(ServerNetworkMessage::typeSize);
    LOG << "receiveMessage TypeString = " << static_cast<int>(typeString[0]) << ", ";
    //size
    std::string sizeString = this->_networkClient->read(ServerNetworkMessage::sizeSize);
    LOG << "SizeString = " << static_cast<int>(sizeString[0]) << ", ";
    //TODO: Could be better
    unsigned int size = sizeString.at(0);

    //message
    std::string messageString = this->_networkClient->read(size);
    LOG << "MessageString = " << messageString << std::endl;

    ServerNetworkMessage sm((NetworkMessageType)(uint8_t)typeString.at(0), size, messageString);
    return sm;
}

DataHandlingService::~DataHandlingService()
{
    delete _networkClient;
}
