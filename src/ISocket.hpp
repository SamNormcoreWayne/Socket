#pragma once
#include <iostream>
#include <regex>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class ISocket
{
protected:
    static const std::regex ip_pattern;
    static const std::regex ip6_pattern;
public:
    virtual ~ISocket() = 0;

// Client Socket
    virtual int Send(const char*);

// Server Socket
    virtual int Accept(const char*);

    virtual int Close(int ) = 0;
};