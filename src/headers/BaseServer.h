/*
BaseServer
@brief: Interface to represent a basic server operations.
*/
#ifndef __BASESERVER_H__
#define __BASESERVER_H__
#include "IBaseServer.h"

namespace Server
{
    constexpr socklen_t SOCKET_LEN = sizeof(sockaddr);

    template<typename T>
    class BaseServer : public IBaseServer<T>
    {
    public:
        BaseServer() :  _nPortNumber(UNINITIALIZED),
                        _nSocketFileDescriptor(UNINITIALIZED), 
                        _nMaxConnectionLimit(UNINITIALIZED),
                        _bServerStarted(false)      = default;

        virtual ~BaseServer()                       = default;

        bool Init(constexpr int nPortNumber = DEFAULT_PORT) = 0;
        bool Start()                                        = 0;
        bool Read(T& tData)                                 = 0;
        bool Send(const T& tData)                           = 0 ;
        bool Close()                                        = 0;

    protected:
        int         _nPortNumber;
        int         _nSocketFileDescriptor;  
        size_t      _nMaxConnectionLimit;
        sockaddr_in _ServerAddress;
        bool        _bServerStarted;
        
        inline void SetServerAddress(   const unsigned char& cFamilyCode,
                                        const unsigned int& nAddress,
                                        const int& nPortNumber )
        {
            // ZEROed the data
            bzero((char *) &_SocketAddress, SOCKET_LEN);

            // Set the socket 
            _SocketAddress.sin_family = cFamilyCode;
            _SocketAddress.sin_addr.s_addr = nAddress;
            _SocketAddress.sin_port = htons(nPortNumber);
        }
    };
}
#endif __BASESERVER_H__