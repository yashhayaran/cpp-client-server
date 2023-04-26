#include "../headers/TCPServer.h"

#define _SERVER template<typename T> TCPServer<T>

using namespace Server;

template<typename T>
TCPServer<T>::TCPServer()
{ }

template<typename T>
TCPServer<T>::~TCPServer()
{ }

template<typename T>
bool TCPServer<T>::Init(const int& nPortNumber)
{
    // Set the port number
    _nPortNumber = nPortNumber;
    
    // Set the server address
    SetServerAddress(AF_INET, INADDR_ANY, _nPortNumber);

    // @link: https://www.linuxhowtos.org/manpages/2/socket.htm
    _nSocketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (_nSocketFileDescriptor == ERRROR)
    {
        _nSocketFileDescriptor = UNINITIALIZED;
        std::cout << "Failed to create socket, error: " << errno << " Please re-init the server object.";
        return false;
    }

    return true;
}

template<typename T>
bool TCPServer<T>::Start()
{
    if(_nSocketFileDescriptor != UNINITIALIZED)
    {
        // @link: https://www.linuxhowtos.org/manpages/2/bind.htm
        if (bind(   _nSocketFileDescriptor, 
                    (struct sockaddr*)&_SocketAddress, 
                    SOCKET_LEN )      == ERRROR) 
        {
            std::cout << "Failed to bind to port " << _nPortNumber << " error: " << errno << std::endl;
        }
        else
        {
            // @link: https://www.linuxhowtos.org/manpages/2/listen.htm
            if (listen(_nSocketFileDescriptor, MAX_DEFAULT_LIMIT) == ERROR) 
            {
                std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
            }
            else
            {
                _bServerStarted = true;
            }
        }
    }
    
    return _bServerStarted;
}

template <typename T>
bool TCPServer<T>::Close()
{
    for (const auto& [connectionID, isActive] : _IncomingConnections)
    {   
        (isActive) ? close(connectionID) : false;
    }

    close(_nSocketFileDescriptor);

    return true;
}

template <typename T>
bool TCPServer<T>::AccepIncomingConnection()
{
    _nLatestConnectionID = accept(  _nSocketFileDescriptor, 
                                    (struct sockaddr*)&_ServerAddress, 
                                    (socklen_t*)SOCKET_LEN);
    if (_nLatestConnectionID == ERROR) 
    {
        std::cout << "Failed to grab connection. errno: " << errno << std::endl;
        _nLatestConnectionID = UNINITIALIZED;
        return false;
    }

    _mapIncomingConnections.insert_or_assign(_nLatestConnectionID, true);
    return true;
}

template <typename T>
bool TCPServer<T>::Read(T& tData)
{
    if(_nLatestConnectionID != UNINITIALIZED && _nLatestConnectionID > 0)
    {
        bzero(_cReadBuffer, _READ_BUFFER_SIZE);
        size_t nBytesRead = read(_nLatestConnectionID, _cReadBuffer, _READ_BUFFER_SIZE);
        
        strMessage = 
    }
}