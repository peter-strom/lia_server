#include "clients.hpp"

Clients::Clients()
{
}

Clients::~Clients()
{
}

void Clients::add_client(uint16_t fd)
{
  Client client(fd);
  clientList[fd] = client;
}

bool Clients::get_client(uint16_t fd, Client* client)
{

  clientList_t::const_iterator pos = clientList.find(fd);
  if (pos == clientList.end())
  {
    return false;
  }
  else
  {

  Client hupp;
  hupp = pos->second;
  client = &hupp;
  //client = &Client(pos->second);
  return true;
  }
}

void Clients::del_client(uint16_t fd)
{
}