#include "ServerSocket.hpp"

const std::regex ServerSocket::ip_pattern = std::regex("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$",
        std::regex_constants::ECMAScript | std::regex_constants::icase);

const int ServerSocket::buffer_size = 128;

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
    return sd_status;
}

RecvData ServerSocket::Recv(int conn_fd)
{
    this->buffer = new char[ServerSocket::buffer_size];
    std::memset(this->buffer, '\0', ServerSocket::buffer_size);
    int size = recv(conn_fd, this->buffer, ServerSocket::buffer_size - 1, 0);
    RecvData rec;
    rec.size = size;
    if (this->buffer)
    rec.data = std::forward<char *>(std::move(buffer));
    this->buffer = nullptr;
    return rec;
}