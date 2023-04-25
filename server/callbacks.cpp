#include "callbacks.hpp"
#include "../globals.hpp"

void connect_callback(uint16_t fd)
{
  std::cout << "[test connect callback]" << std::endl;
}

void receive_callback(uint16_t fd, char *buffer)
{
  std::cout << "[test receive callback] msg received from socket_fd: " << fd << std::endl;
  std::cout << "message: " << buffer << std::endl;
  if (strcmp(buffer, "PRODUCT_N") == 0)
  {
    server.transmit(fd, (char *)"kanon");
  }
}

void disconnect_callback(uint16_t fd)
{
  std::cout << "[test disconnect callback]" << std::endl;
}
