#ifndef NETWORKMESSAGETYPE_H
#define NETWORKMESSAGETYPE_H
typedef enum NetworkMessageType
{
    Configuration = 1,
    Request = 2,
    Answer = 3,
    Move = 4,
    EndGame = 5
}
NetworkMessageType;
#endif
