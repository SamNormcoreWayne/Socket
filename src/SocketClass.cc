#include "ISocket.hpp"

static const std::regex ip_pattern = std::regex("^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$",
        std::regex_constants::ECMAScript | std::regex_constants::icase);

static const std::regex ip6_patter = std::regex("^([\\da-fA-F]{1,4}:){7}[\\da-fA-F]{1,4}$",
        std::regex_constants::ECMAScript | std::regex_constants::icase);