#include "callbacks.hpp"
#include "../globals.hpp"

void connect_callback(uint16_t fd)
{
  std::cout << "[test connect callback]" << std::endl;
  Client client;

  clients.add_client(fd);
  if (clients.get_client(fd, &client))
  {
    std::cout << "client found in list " << fd << std::endl;
    client.set_auth(false);

    if (client.get_auth())
    {
      std::cout << "client authorized" << std::endl;
    }
    else
    {
      std::cout << "client not authorized" << std::endl;
      char msg[] = "password";
      server.transmit(fd, msg, 14);
    }
  }
  else
  {
    std::cout << "client not found in list " << std::endl;
  }
}

void receive_callback(uint16_t fd, char *buffer)
{
  std::cout << "[test receive callback] msg received from socket_fd: " << fd << std::endl;

  Client client;
  if (clients.get_client(fd, &client))
  {
    std::cout << "client found in list " << std::endl;

    if (client.get_auth())
    {
      std::cout << "client authorized" << std::endl;
    }
    else
    {
      std::cout << "client not authorized" << std::endl;
      if (strcmp(buffer, "PRODUCT_Nsecret handshake") == 0)
      {
        std::cout << "client autorized!" << fd << std::endl;
        client.set_auth(true);
      }
    }
  }
  else
  {
    std::cout << "client not found in list " << std::endl;
  }

  std::cout << "message: \"" << buffer << "\" from client: " << fd << std::endl;
}

void disconnect_callback(uint16_t fd)
{
  std::cout << "[disconnect callback] client: " << fd << std::endl;
}
