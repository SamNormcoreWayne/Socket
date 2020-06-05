#pragma once
#include <cstring>
#include <vector>
#include <functional>
#include <thread>

#include "ISocket.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

struct RecvData
{
    int size;
    const char* data;
};

class ServerSocket : public ISocket
{
private:
    sockaddr_in ip_addr;
protected:
    char* buffer;
    static const std::regex ip_pattern;
    static const int buffer_size;

    int socket_fd;
    int connct_fd_num;

    std::vector<int> connct_fds;
public:
    ServerSocket(const char* addr="127.0.0.1", int port = 22)
    {
        if (inet_pton(AF_INET, addr, &this->ip_addr.sin_addr))
        {
            this->ip_addr.sin_family = AF_INET;
            this->ip_addr.sin_port = static_cast<in_port_t>(port);
        }
        this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(
            !bind(this->socket_fd,
                reinterpret_cast<struct sockaddr*>(&this->ip_addr),
                static_cast<socklen_t>(sizeof(this->ip_addr))
            )
        )
        {
            listen(this->socket_fd, 10);
        }
    }

    ServerSocket()
    {
        ServerSocket("127.0.0.1", 22);
    }

    ~ServerSocket()
    {
    }

    virtual int Accept();
    virtual int Close(int );

    /**
     * @param: callback func
     *  Requirements of the callback:
     *  @param: const char*
     *  @return: char *
     * @return: int
     */
    virtual RecvData Recv(int);
};