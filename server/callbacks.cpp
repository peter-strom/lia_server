#include "callbacks.hpp"
#include "../globals.hpp"

void connect_callback(uint16_t fd)
{
  std::cout << "[test connect callback]" << std::endl;
  Client client;

  clients.add_client(fd);
  if (clients.get_client(fd, &client))
  {
    std::cout << "client found in list " << std::endl;
    client.set_auth(true);

    if (client.get_auth())
    {
      std::cout << "client authorized" << std::endl;
    }
    else
    {
      std::cout << "client not authorized" << std::endl;
      char msg[]="password";
      server.transmit(fd, msg, 9);
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
    }
  }
  else
  {
    std::cout << "client not found in list " << std::endl;
  }



  std::cout << "message: " << buffer << std::endl;



  if (strcmp(buffer, "hej") == 0)
  {
    std::cout << "woho!" << std::endl;
    //server.transmit(fd, (char *)"kanon");
  }
}

void disconnect_callback(uint16_t fd)
{
  std::cout << "[test disconnect callback]" << std::endl;
}
