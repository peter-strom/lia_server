#include "callbacks.hpp"

void connect_callback(uint16_t fd)
{
    std::cout << "test connect callback" << std::endl;
}

void receive_callback(uint16_t fd, char *buffer)
{
    std::cout << "test receive callback" << std::endl;
}

void disconnect_callback(uint16_t fd)
{
    std::cout << "test disconnect callback" << std::endl;
}
