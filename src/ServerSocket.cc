#include "ServerSocket.hpp"

const std::regex ServerSocket::ip_pattern = std::regex("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$",
        std::regex_constants::ECMAScript | std::regex_constants::icase);

int ServerSocket::Accept()
{
    socklen_t addr_length = sizeof(this->ip_addr);
    int connect_fd = accept(this->socket_fd,
        reinterpret_cast<struct sockaddr*>(&this->ip_addr),
        &addr_length);
    if (!connect_fd)
    {
        this->connct_fds.push_back(connect_fd);
        this->connct_fd_num += 1;
        return connect_fd;
    }
    return -1;
}

int ServerSocket::Close(int connect_fd)
{
    int sd_status = close(connect_fd);

}