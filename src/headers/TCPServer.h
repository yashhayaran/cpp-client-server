/*
TCPServer
@brief: Interface to represent a basic server operations.
*/
#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
#include "BaseServer.h"
#include <unordered_map>
#include <unordered_set>

namespace Server
{
    template<typename T>
    class TCPServer : public BaseServer<T>
    {
    public:
        TCPServer() : _nLatestConnectionID(UNINITIALIZED)= default;
        virtual ~TCPServer()                            = default;

        bool Init(const int& nPortNumber = DEFAULT_PORT);
        bool Start();
        bool Read(T& tData);
        bool Send(const T& tData);
        bool Close();

    protected:
        int _nLatestConnectionID;
        std::unordered_map<int, bool> _mapIncomingConnections;
        constexpr size_t _READ_BUFFER_SIZE = 256;
        char _cReadBuffer[_READ_BUFFER_SIZE];

        virtual bool AccepIncomingConnection();
    };
}


#endif __TCPSERVER_H__