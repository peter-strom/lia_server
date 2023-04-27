#ifndef _CLIENTS_HPP_
#define _CLIENTS_HPP_

#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <map>
#include "../config.hpp"
#include "client.hpp"

typedef std::map<uint16_t, Client> clientList_t;

/**
 * @brief class for clients
 *
 */
class Clients
{
public:
  Clients();
  ~Clients();
  void add_client(uint16_t fd);
  bool get_client(uint16_t fd, Client* client);
  void del_client(uint16_t fd);

private:
  clientList_t clientList;
  
};

#endif /* _CLEINTS_HPP_ */