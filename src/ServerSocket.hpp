#pragma once
#include <vector>
#include <functional>
#include <thread>

#include "ISocket.hpp"

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class ServerSocket : public ISocket
{
private:
    sockaddr_in ip_addr;

protected:
    static const std::regex ip_pattern;
    int socket_fd;
    std::vector<int> connct_fds;
    int connct_fd_num;
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
    virtual int Recv(std::function<char*(const char*)>);
};