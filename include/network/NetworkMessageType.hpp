#ifndef NETWORKMESSAGETYPE_H
#define NETWORKMESSAGETYPE_H

#define NETWORK_REGISTER_CODE 42

typedef enum NetworkMessageType
{
    Register = 0,
    Request = 1,
    Answer = 2,
    Move = 3,
    EndGame = 4,
    Unknown = 255
} NetworkMessageType;
#endif
