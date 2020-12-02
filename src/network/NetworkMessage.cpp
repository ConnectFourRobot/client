#include "../../include/network/NetworkMessage.hpp"

unsigned int NetworkMessage::getPayloadSize()
{
    return this->_size;
}

std::string NetworkMessage::getNetworkMessage()
{
    //TODO stringSize is unused, probably missing terminating zero, maybe change to char cp[1000] {0};
    char cp[NetworkMessage::typeSize + NetworkMessage::sizeSize];

    //type
    cp[0] = this->_type;
    //size
    cp[1] = this->_size;

    std::stringstream ss;
    ss << std::string(cp, NetworkMessage::typeSize + NetworkMessage::sizeSize) << this->_message;

    return ss.str();
}

unsigned int NetworkMessage::getLength()
{
    return ServerNetworkMessage::typeSize + ServerNetworkMessage::sizeSize + this->_size;
}

NetworkMessageType NetworkMessage::getMessageType()
{
    return this->_type;
}

std::string NetworkMessage::getMessage()
{
    return this->_message;
}

NetworkMessage::~NetworkMessage()
{

}

ClientNetworkMessage::ClientNetworkMessage(int8_t column)
{
    const int size = 1;
    this->_type = NetworkMessageType::Answer;
    this->_size = size;
    // char pointer for payload
    char cp[size];
    *cp = column;

    this->_message = std::string(cp, this->_size);
}

ServerNetworkMessage::ServerNetworkMessage(NetworkMessageType type, unsigned int size, std::string serverMessage)
{
    this->_type = type;
    this->_size = size;
    this->_message = serverMessage;
    this->_column = 0;
    this->_playerId = 0;

    switch (type)
    {
//    case NetworkMessageType::Configuration:
//        this->gameConfig.playerNumber = serverMessage.at(0);
//        break;
    case NetworkMessageType::Move:
        this->_column = serverMessage.at(0);
        this->_playerId = serverMessage.at(1);
        break;
    case NetworkMessageType::EndGame:
        this->_playerId = serverMessage.at(0);
        break;
    default:
        break;
    }
}
