/*
IBaseServer
@brief: Interface to represent a basic server operations.
*/
#ifndef __IBASESERVER_H__
#define __IBASESERVER_H__
#include "../utilities/Constants.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

namespace Server
{
    template <typename T = std::string>
    class IBaseServer
    {
    public:
        IBaseServer()           = delete;
        virtual ~IBaseServer()  = delete;

        virtual bool Init(const int& nPort = DEFAULT_PORT)      = 0;
        virtual bool Start()                                    = 0;
        virtual bool Read(T& tData)                             = 0;
        virtual bool Send(const T& tData)                       = 0;
        virtual bool Close()                                    = 0;
    };
}

#endif __IBASESERVER_H__