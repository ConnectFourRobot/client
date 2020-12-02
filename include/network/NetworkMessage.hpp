#ifndef NETWORKMESSAGE_H
#define NETWORKMESSAGE_H

#include "NetworkMessageType.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class NetworkMessage
{
protected:
    NetworkMessageType _type;
    uint8_t _size;
    std::string _message;
public:
    const static short typeSize = 1;
    const static short sizeSize = 1;

    /**
     * Get the size of the payload
     *
     * @return size of the payload
    */
    unsigned int getPayloadSize();

    /**
     * Get the whole network message
     * Including the type and the size
     *
     * @return network message
    */
    std::string getNetworkMessage();

    /**
     * Get the payload
     *
     * @return payload
    */
    std::string getMessage();

    /**
     * Get length/size of the whole network message
     *
     * @return length
    */
    unsigned int getLength();

    NetworkMessageType getMessageType();
    ~NetworkMessage();
};

class ClientNetworkMessage : public NetworkMessage
{
public:
    ClientNetworkMessage(int8_t column);
};

class ServerNetworkMessage : public NetworkMessage
{
    // We do not know, which servermessage is coming
    // so this is a temporary solution, but it is not in a good oop way
protected:
    int8_t _playerId, _column;

public:
    ServerNetworkMessage(NetworkMessageType type, unsigned int size, std::string serverMessage);
    inline NetworkMessageType getType() const {return this->_type;}
    inline int8_t getPlayerId() const {return this->_playerId;}
    inline int8_t getColumn() const {return this->_column;}
};

#endif
