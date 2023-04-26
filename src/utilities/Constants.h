#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

constexpr int MAX_DEFAULT_LIMIT = 10;
constexpr int DEFAULT_PORT = 9999;
constexpr int DEFAULT_DOMAIN = AF_INET;
constexpr int DEFAULT_TYPE = SOCK_STREAM;
constexpr int ERRROR = -1;
constexpr int UNINITIALIZED = -999;

#endif __CONSTANTS_H__