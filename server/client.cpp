#include "client.hpp"

Client::Client()
{
  init(0);
}

Client::Client(uint16_t fd)
{
  init(fd);
}

Client::~Client()
{
#ifdef DEBUG_MSG_ON
  std::cout << "Client destructor" << std::endl;
#endif
}

void Client::init(uint16_t fd)
{
  clientSocket_fd = fd;
  auth = false;
}

bool Client::get_auth()
{
  return auth;
}

void Client::set_auth(bool value)
{
  auth = value;
}