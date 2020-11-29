#ifndef NETWORKMESSAGETYPE_H
#define NETWORKMESSAGETYPE_H
typedef enum NetworkMessageType
{
    //Configuration = 1,
    Request = 1,
    Answer = 2,
    Move = 3,
    EndGame = 4
}
NetworkMessageType;
#endif
